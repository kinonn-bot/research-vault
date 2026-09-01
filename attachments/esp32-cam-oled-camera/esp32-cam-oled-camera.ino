/*
 * =====================================================================
 *  ESP32-CAM + 0.96" SSD1306 OLED — PORTABLE STILL CAMERA (scaffold)
 * ---------------------------------------------------------------------
 *  SCOPE: STILL PHOTOS ONLY. No video, no streaming, no WiFi.
 *  Board      : AI-Thinker ESP32-CAM (with 4 MB PSRAM)
 *  Camera     : OV2640 (hardware JPEG)
 *  Display    : 0.96" 128x64 SSD1306 I2C @ 0x3C (viewfinder + photo confirm)
 *  Storage    : on-board microSD via SD_MMC (1-line mode)
 *  Shutter    : tactile push-button on GPIO 33 -> GND
 *  Power      : 18650 -> TP4056 -> MT3608 boost 5V -> board 5V pin
 *
 *  WHAT THIS DOES
 *    - Viewfinder: continuously decode the camera JPEG frame and draw it as
 *      a 1-bit (B/W) letterboxed preview on the OLED (~3-6 fps) so you can
 *      aim. It decodes a *scaled* copy (JPEG_SCALE_HALF) for speed; the SD
 *      photo is the FULL-resolution JPEG.
 *    - Shutter: write the current full-res JPEG to the SD card as
 *      /PHOTO_nnnn.jpg, then show that same saved frame full-decode on the
 *      OLED as the "photo confirm". What you framed == what you saved.
 *    - WiFi is never initialised: no streaming/network stack, so no ADC2 or
 *      SD conflicts and no radio current.
 *
 *  HOW TO BUILD (Arduino IDE)
 *    - Board: "ESP32 Dev Module" (or "AI Thinker ESP32-CAM").
 *    - Partition scheme: "Huge APP (3MB No OTA)".
 *    - PSRAM: enabled.
 *    - Libraries (Tools > Manage Libraries): "Adafruit SSD1306", "Adafruit
 *      GFX", "JPEGDEC" (by Larry Bank / bitbank2).
 *    - esp32-camera + SD_MMC are in the "esp32" boards core.
 *
 *  JPEGDEC API NOTE (verify against your installed version):
 *    current:  decode(int x, int y, int iOptions);  e.g. decode(0,0,JPEG_SCALE_HALF)
 *    older:    decode(0, 0)
 *    setMaxOutputSize(int) takes an MCU COUNT, NOT width/height — don't use it
 *    for sizing. This scaffold does its own source->display mapping instead.
 *
 *  NOTE: this is a scaffold. It has not been compiled here (no ESP32
 *  toolchain on this machine). It is written to build in Arduino IDE.
 * =====================================================================
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <JPEGDEC.h>
#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"

// ----------------------------- PINS ------------------------------
#define OLED_SDA     1           // GPIO 1 (UART TX0)
#define OLED_SCL     3           // GPIO 3 (UART RX0)
#define SHUTTER_PIN  33          // tactile button to GND, INPUT_PULLUP
#define FLASH_PIN    4           // on-board white LED (optional, see note)

#define SCREEN_W     128
#define SCREEN_H      64
#define FIT_W        85          // 64 * (4/3) ~= 85 (letterbox, aspect kept)
#define FIT_XOFF    ((SCREEN_W - FIT_W) / 2)

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);
JPEGDEC jpeg;

bool sdOK = false;
uint32_t photoCount = 0;
unsigned long lastShot = 0;

// Source dimensions of the streamed JPEG as seen by the draw callback.
// Framing decodes with JPEG_SCALE_HALF, confirm decodes full-res.
static int gSrcW = 0, gSrcH = 0;

// ----------------------- AI-THINKER CAMERA MAP -------------------
static camera_config_t camera_config = {
  .pin_pwdn    = 32,
  .pin_reset   = -1,
  .pin_xclk    = 0,
  .pin_sccb_sda = 26,
  .pin_sccb_scl = 27,
  .pin_d7      = 35,
  .pin_d6      = 34,
  .pin_d5      = 39,
  .pin_d4      = 36,
  .pin_d3      = 21,       // D3 = GPIO 21 (33 is the red LED)
  .pin_d2      = 19,
  .pin_d1      = 18,
  .pin_d0      = 5,
  .pin_vsync   = 25,
  .pin_href    = 23,
  .pin_pclk    = 22,
  .xclk_freq_hz   = 20000000,
  .ledc_timer     = LEDC_TIMER_0,
  .ledc_channel   = LEDC_CHANNEL_0,
  .pixel_format   = PIXFORMAT_JPEG,
  .frame_size     = FRAMESIZE_VGA,   // 640x480 saved photo. SVGA/UXGA for more.
  .jpeg_quality   = 12,
  .fb_count       = 2,               // needs PSRAM
  .grab_mode      = CAMERA_GRAB_LATEST,
};

// --------------- JPEGDEC draw callback -> 1-bit OLED --------------
// JPEGDEC calls this per pixel block (MCU). pDraw->pPixels is uint16_t
// RGB565 (native order; we set RGB565_LITTLE_ENDIAN). We map source (gSrcW
// x gSrcH) -> letterboxed OLED (85x64 centred).
int JPEGDraw(JPEGDRAW *pDraw) {
  if (gSrcW < 1 || gSrcH < 1) return 1;
  for (int yy = 0; yy < pDraw->iHeight; yy++) {
    int srcY = pDraw->y + yy;
    if (srcY >= gSrcH) break;
    int dstY = (srcY * SCREEN_H) / gSrcH;
    for (int xx = 0; xx < pDraw->iWidth; xx++) {
      int srcX = pDraw->x + xx;
      if (srcX >= gSrcW) break;
      int dstX = FIT_XOFF + (srcX * FIT_W) / gSrcW;
      uint16_t c = pDraw->pPixels[yy * pDraw->iWidth + xx];
      uint8_t r = (c >> 11) & 0x1F;
      uint8_t g = (c >> 5)  & 0x3F;
      uint8_t b = c & 0x1F;
      uint16_t lum = ((r << 3) * 299 + (g << 2) * 587 + (b << 3) * 114) / 1000;
      display.drawPixel(dstX, dstY, lum > 110 ? SSD1306_WHITE : SSD1306_BLACK);
    }
  }
  return 1;
}

// Decode a JPEG framebuffer to the OLED. scaleHalf=true speeds framing
// (decodes an intermediate, smaller stream); false = full res (photo confirm).
bool showFrame(camera_fb_t *fb, bool scaleHalf) {
  display.clearDisplay();
  if (jpeg.openRAM(fb->buf, fb->len, JPEGDraw)) {
    jpeg.setPixelType(RGB565_LITTLE_ENDIAN);
    gSrcW = camera_config.frame_size == FRAMESIZE_VGA ? 640 : 800; // VGA or SVGA
    gSrcH = camera_config.frame_size == FRAMESIZE_VGA ? 480 : 600;
    if (scaleHalf) { gSrcW /= 2; gSrcH /= 2; }   // SCALE_HALF halves output
    jpeg.decode(0, 0, scaleHalf ? JPEG_SCALE_HALF : 0);
    jpeg.close();
  }
  display.display();
  return true;
}

// ------------------------------ SETUP -----------------------------
void setup() {
  Serial.begin(115200);

  pinMode(SHUTTER_PIN, INPUT_PULLUP);
  // Optional: flash LED high = off (active-low drives it; GPIO4 also shares
  // SD DATA1 in 4-bit mode, so we're in 1-line SD mode / just leave it).

  // OLED on GPIO 1 (SDA) / GPIO 3 (SCL)
  Wire.begin(OLED_SDA, OLED_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Boot...");
  display.display();

  // microSD (1-line mode -> no flash-LED flicker on GPIO 4)
  sdOK = SD_MMC.begin("/sdcard", true);
  if (!sdOK) Serial.println("SD mount FAILED");

  // Camera — stills only, PSRAM, JPEG
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed 0x%x\n", err);
    display.println("CAM ERR");
    display.display();
    for (;;);
  }
  sensor_t *s = esp_camera_sensor_get();
  if (s) s->set_framesize(s, FRAMESIZE_VGA);

  Serial.println("Ready (still camera, no WiFi)");
  display.clearDisplay();
  display.println("Ready");
  display.display();
}

// ------------------------------ LOOP ------------------------------
void loop() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) { delay(20); return; }

  showFrame(fb, true);        // fast scaled framing view

  // Shutter: debounced (LOW = press, INPUT_PULLUP active-low)
  if (digitalRead(SHUTTER_PIN) == LOW && (millis() - lastShot) > 500) {
    lastShot = millis();
    if (sdOK) {
      char path[32];
      snprintf(path, sizeof(path), "/PHOTO_%04lu.jpg", photoCount++);
      File f = SD_MMC.open(path, FILE_WRITE);
      if (f) {
        f.write(fb->buf, fb->len);   // full-res VGA JPEG
        f.close();
        // Show the SAVED image full-res (photo confirm), matching what's on SD.
        showFrame(fb, false);
        display.fillRect(0, 0, SCREEN_W, 10, SSD1306_BLACK);
        display.setCursor(0, 0);
        display.print("SAVED");
        display.display();
      } else {
        Serial.printf("SD write FAILED %s\n", path);
        display.fillRect(0, 0, SCREEN_W, 10, SSD1306_BLACK);
        display.setCursor(0, 0);
        display.print("SD ERR");
        display.display();
      }
    } else {
      display.fillRect(0, 0, SCREEN_W, 10, SSD1306_BLACK);
      display.setCursor(0, 0);
      display.print("NO SD");
      display.display();
    }
    delay(1500);             // hold the confirm before resuming framing
  }

  esp_camera_fb_return(fb);
  delay(40);                 // throttle framing; lower = smoother, higher = cooler
}

/*
 * ---------------------------------------------------------------------
 *  POWER / IDLE NOTES (still camera, battery)
 * ---------------------------------------------------------------------
 *  - No WiFi = no radio current and no ADC2/SD conflicts. Good for battery.
 *  - Continuous framing draws ~200-300 mA (camera + CPU + OLED), so a
 *    ~2600 mAh 18650 gives roughly 6-8 hours of "camera on, aiming".
 *  - For a longer-between-shots trail-cam style idle, capture one photo then
 *    deep-sleep and wake on the shutter GPIO. NB the AI-Thinker board-level
 *    deep-sleep current is far above the chip's 10 uA (regulator + LEDs); a
 *    MOSFET hard power-cut between shots is the real fix if you need weeks.
 *  - Raise jpeg_quality (lower number = better) for nicer stills; drop the
 *    viewfinder fps if you push toward SVGA/UXGA.
 *  - Nicer 1-bit rendering: JPEGDEC's ONE_BIT_DITHERED + decodeDither() gives
 *    Floyd-Steinberg (the robotzero.one ESP32-CAM-OLED project's approach)
 *    instead of a hard threshold.
 *  - To set framesize higher, change camera_config.frame_size and the VGA/SVGA
 *    constants in showFrame() (they drive the source->display mapping).
 */
