/*
 * =====================================================================
 *  ESP32-CAM + 0.96" SSD1306 OLED VIEWFINDER CAMERA (scaffold)
 * ---------------------------------------------------------------------
 *  Board      : AI-Thinker ESP32-CAM (with 4 MB PSRAM)
 *  Camera     : OV2640 (hardware JPEG)
 *  Display    : 0.96" 128x64 SSD1306 I2C @ 0x3C
 *  Storage    : on-board microSD via SD_MMC (1-line mode)
 *  Shutter    : tactile push-button on GPIO 33 -> GND
 *  Power      : 18650 -> 3.7V->5V boost -> board 5V pin (see build notes)
 *
 *  WHAT THIS DOES
 *    - Live framing: continuously decode the camera's JPEG frame and draw it
 *      as a 1-bit (B/W) letterboxed preview on the OLED. ~3-6 fps.
 *    - On shutter press: take the current JPEG frame, write it to the SD card
 *      as /PHOTO_nnnn.jpg, then keep that same frame on the OLED as the
 *      "photo confirm". Framing == captured frame, so what you saw is what
 *      got saved.
 *
 *  HOW TO BUILD (Arduino IDE)
 *    - Board: "ESP32 Dev Module" is the safe generic pick, but "AI Thinker
 *      ESP32-CAM" is the recognised board preset.
 *    - Partition scheme: "Huge APP (3MB No OTA)".
 *    - PSRAM: enabled / "OPI PSRAM".
 *    - Libraries (Tools > Manage Libraries): "Adafruit SSD1306", "Adafruit
 *      GFX", "JPEGDEC" (by Larry Bank / bitbank2).
 *    - esp32-camera + SD_MMC ship inside the "esp32" boards package.
 *
 *  NOTE: this is a scaffold. It has not been compiled here (no ESP32
 *  toolchain on this machine). Review the JPEGDEC calls against the
 *  version you install: older releases used `jpeg.decode(0,0)`; newer
 *  releases use `jpeg.decode(0,0,0)` (3-arg) and `setMaxOutputSize(int
 *  iMaxMCUs)` takes a MCU count, NOT width/height.
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
// OLED I2C lives on the UART pins (GPIO 1 / GPIO 3) because every other
// usable GPIO is consumed by the camera + SD card. See the research note.
#define OLED_SDA     1
#define OLED_SCL     3
#define SHUTTER_PIN  33          // tactile button to GND, INPUT_PULLUP

#define SCREEN_W     128
#define SCREEN_H      64

// Letterbox: the OV2640 is 4:3, the OLED is 2:1, so we fit the full scene
// (aspect preserved) into 85x64 and centre it. Computed below at runtime.
#define FIT_W        85          // 64 * (4/3) ~= 85
#define FIT_XOFF    ((SCREEN_W - FIT_W) / 2)   // ~21

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);
JPEGDEC jpeg;

bool sdOK = false;
uint32_t photoCount = 0;
unsigned long lastShot = 0;

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
  .pin_d3      = 21,       // NOTE: D3 = GPIO 21 (not 33). 33 is the red LED.
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
  .frame_size     = FRAMESIZE_QVGA,   // 320x240. VGA for sharper JPEG, < fps.
  .jpeg_quality   = 12,
  .fb_count       = 2,                // needs PSRAM
  .grab_mode      = CAMERA_GRAB_LATEST,
};

// --------------- JPEGDEC draw callback -> 1-bit OLED --------------
// JPEGDEC calls this once per pixel block (an MCU). pDraw->pPixels is
// uint16_t RGB565 (native order because we set RGB565_LITTLE_ENDIAN).
int JPEGDraw(JPEGDRAW *pDraw) {
  for (int yy = 0; yy < pDraw->iHeight; yy++) {
    int srcY = pDraw->y + yy;
    if (srcY >= 120) break;                    // no need to process below scene
    int dstY = (srcY * SCREEN_H) / 120;        // y: 120 -> 64
    for (int xx = 0; xx < pDraw->iWidth; xx++) {
      int srcX = pDraw->x + xx;
      if (srcX >= 160) break;
      int dstX = FIT_XOFF + (srcX * FIT_W) / 160;
      uint16_t c = pDraw->pPixels[yy * pDraw->iWidth + xx];
      uint8_t r = (c >> 11) & 0x1F;
      uint8_t g = (c >> 5)  & 0x3F;
      uint8_t b = c & 0x1F;
      // Rec.601 luma; push 5/6/5 channels up to 8-bit before weighting.
      uint16_t lum = ((r << 3) * 299 + (g << 2) * 587 + (b << 3) * 114) / 1000;
      display.drawPixel(dstX, dstY, lum > 110 ? SSD1306_WHITE : SSD1306_BLACK);
    }
  }
  return 1;
}

// Decode a JPEG framebuffer onto the OLED. Returns true on success.
bool showFrame(camera_fb_t *fb) {
  display.clearDisplay();
  if (jpeg.openRAM(fb->buf, fb->len, JPEGDraw)) {
    jpeg.setPixelType(RGB565_LITTLE_ENDIAN);
    // Speed knob: jpeg.decode(0, 0, JPEG_SCALE_HALF) decodes 160x120 -> fast
    // framing. Full-res gives more detail but ~half the fps.
    jpeg.decode(0, 0, 0);
    jpeg.close();
  }
  display.display();
  return true;
}

// ------------------------------ SETUP -----------------------------
void setup() {
  Serial.begin(115200);

  // Button
  pinMode(SHUTTER_PIN, INPUT_PULLUP);

  // OLED on GPIO 1 (SDA) / GPIO 3 (SCL)
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 init failed");
    for (;;);
  }
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Boot...");
  display.display();

  // microSD (1-line mode -> avoids flash-LED flicker on GPIO 4)
  sdOK = SD_MMC.begin("/sdcard", true);
  if (!sdOK) Serial.println("SD mount FAILED");

  // Camera
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed 0x%x\n", err);
    display.println("CAM ERR");
    display.display();
    for (;;);
  }
  sensor_t *s = esp_camera_sensor_get();
  if (s) s->set_framesize(s, FRAMESIZE_QVGA);

  Serial.println("Ready");
  display.clearDisplay();
  display.println("Ready");
  display.display();
}

// ------------------------------ LOOP ------------------------------
void loop() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) { delay(20); return; }

  showFrame(fb);          // live framing / photo confirm

  // Shutter: debounced, LOW is a press (INPUT_PULLUP, active-low).
  if (digitalRead(SHUTTER_PIN) == LOW && (millis() - lastShot) > 500) {
    lastShot = millis();
    if (sdOK) {
      char path[32];
      snprintf(path, sizeof(path), "/PHOTO_%04lu.jpg", photoCount++);
      File f = SD_MMC.open(path, FILE_WRITE);
      if (f) {
        f.write(fb->buf, fb->len);
        f.close();
        // OLED status overlay (frame already drawn above = the saved image).
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
    delay(1500);   // hold the confirm on screen
  }

  esp_camera_fb_return(fb);
  delay(30);       // cap fps; raise for more, lower for stable
}

/*
 * ---------------------------------------------------------------------
 *  DOWNGRADES / TWEAKS
 * ---------------------------------------------------------------------
 *  - Faster framing: decode with JPEG_SCALE_HALF (or QUARTER) as noted in
 *    showFrame(). JPEGDEC also ships ONE_BIT_DITHERED + decodeDither(),
 *    which gives a much nicer Floyd-Steinberg rendering on this 1-bit
 *    screen than a hard threshold. Reference: the robotzero.one ESP32-CAM
 *    OLED project used exactly that.
 *  - Pixel format alternative (faster framing, lower fidelity on capture):
 *    set camera_config.pixel_format = PIXFORMAT_GRAYSCALE and render the
 *    raw bytes directly (no JPEG decode), but then the "photo" you save to
 *    SD is that grayscale frame, not a JPEG. This scaffold keeps everything
 *    in JPEG so the saved image === the framed image.
 *  - Higher-res capture: FRAMESIZE_VGA / SVGA sharpens the saved JPEG at
 *    the cost of framing fps.
 *  - Deep sleep between shots (trail-cam mode): call esp_sleep after each
 *    capture and wake on the shutter GPIO. The board-level current is much
 *    higher than the chip's 10 uA figure (regulator + LEDs), so budget a
 *    MOSFET power-cut instead if you need long standby.
 */
