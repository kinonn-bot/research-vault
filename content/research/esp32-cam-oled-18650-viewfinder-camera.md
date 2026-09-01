---
title: ESP32-CAM + 0.96" OLED Viewfinder Camera (18650, 3D-printed)
date: 2026-09-01
tags:
  - research
  - hardware
  - esp32
  - camera
  - oled
  - 18650
  - build
related: "[[ESP32 + 3D-Printed Camera Projects]]"
---

# ESP32-CAM + 0.96" OLED Viewfinder Camera (18650, 3D-printed)

A handheld point-and-shoot built from an **AI-Thinker ESP32-CAM** (OV2640), a **0.96" SSD1306 128×64 I2C OLED** used as a viewfinder + photo-confirm, a **single 18650** for power, and a **3D-printed** body. Captured JPEGs go to the **on-board microSD**.

This note is the full build design: the parts list (with AliExpress sourcing), the exact wiring, the power architecture, the firmware, and every constraint that actually bites on this board.

> The broad "ESP32 + 3D-printed camera" landscape is in [[ESP32 + 3D-Printed Camera Projects]]. This note is the *specific* build for a 128×64-OLED viewfinder camera.

---

## 0. Reality check — read this before you buy anything

Three things about this exact combo that set the expectations and drive every wiring decision:

1. **The 0.96" SSD1306 is a 1-bit, 128×64, 1024-byte display.** There is **no true grayscale and no smooth video.** Your *live viewfinder* will be a lo-fi **black-and-white preview at ~3–6 FPS** — Game-Boy-camera vibes, not a phone screen. That is fine for *framing* (hold it steady, compose, shoot), but it is not a video viewfinder.

2. **The ESP32-CAM has almost no spare pins.** The camera eats most GPIOs; the microSD eats the rest. The only clean I2C pair for the OLED is **GPIO 1 + GPIO 3** (the UART pins), and the shutter goes on **GPIO 33** (the onboard red-LED pad). This is non-negotiable — see the pin map below.

3. **The 18650 cannot power the board directly.** The cell only ever delivers ~3.0–4.2 V, and the ESP32-CAM's onboard AMS1117 LDO needs **> ~4.4 V in** to hold 3.3 V out. You **must** boost the battery to **5 V** and feed the board's **5V pin**. This is the single most common cause of "my camera keeps rebooting."

**Buy the PSRAM variant of the ESP32-CAM.** Without the 4 MB PSRAM the camera can only hold one small framebuffer and the whole preview/save pipeline gets much worse.

---

## 1. Bill of Materials (AliExpress)

Listings are live as of 2026-09. **Prices vary widely by seller and by bundle** — always verify the PSRAM variant and check the listing photo/diagram before ordering. Don't order a battery that looks too cheap: counterfeit/fake 18650s are common and dangerous.

| # | Part | Spec / why | AliExpress | Typical price (USD) |
|---|---|---|---|---|
| 1 | **ESP32-CAM, 4 MB PSRAM** (AI-Thinker) | The board. Ships with the OV2640 camera on a flex cable. Get the **PSRAM** version. | [wholesale-esp32-cam-thinker](https://www.aliexpress.com/w/wholesale-esp32-cam-thinker.html) · [kit w/ CH340G](https://www.aliexpress.com/item/1005002808966055.html) | $6–16 (kit bundles $18–31) |
| 2 | **0.96" OLED SSD1306 128×64 I2C** | The viewfinder. Address `0x3C`, onboard pull-ups, 3.3 V. | [32643950109](https://www.aliexpress.com/item/32643950109.html) · [wholesale-oled-ssd1306-128x64](https://www.aliexpress.com/w/wholesale-oled-display-ssd1306-128x64.html) | $1–3 (up to $10) |
| 3 | **18650 Li-ion (protected, ~2600 mAh)** | One cell. Use a **protected** cell (on-cell protection or the charger's). | [wholesale-18650-3.7v-2600mah](https://www.aliexpress.com/w/wholesale-18650-battery-3.7v-2600mah.html) | $3–5 cheap, $5–8 quality |
| 4 | **TP4056 module *with protection*** | Charger + over-discharge / over-current protection. The "with protection" version is required for a bare cell. | [32467578996](https://www.aliexpress.com/item/32467578996.html) · [wholesale-tp4056](https://www.aliexpress.com/w/wholesale-tp4056.html) | $1–3 |
| 5 | **Boost converter, 3.7 V→5 V** (MT3608) | **Required** — see reality check #3. Set output to exactly 5.0 V. | [wholesale-mt3608](https://www.aliexpress.com/w/wholesale-mt3608.html) | $1–3 |
| 6 | **18650 holder / spring bracket** | Mounts the cell in the printed case. | [wholesale-18650-battery-holder](https://www.aliexpress.com/w/wholesale-18650-battery-holder.html) | $1–3 |
| 7 | **SPDT / SPDT slide switch** | On/off between battery and boost input. | [wholesale-tact-switch-6mm](https://www.aliexpress.com/w/wholesale-tact-switch-6mm.html) | ~$0.40 |
| 8 | **Tactile push-button (6×6 mm)** | Shutter, on GPIO 33. | [wholesale-tact-switch-6mm](https://www.aliexpress.com/w/wholesale-tact-switch-6mm.html) (10 pcs ~$1) | ~$0.10 ea |
| 9 | **USB-UART programmer** (CP2102 / CH340) | Flashing only. The ESP32-CAM has no USB; you need this. | [wholesale-cp2102-uart-usb](https://www.aliexpress.com/w/wholesale-cp2102-uart-usb.html) · [wholesale-usb-ttl-converter](https://www.aliexpress.com/w/wholesale-usb-ttl-converter.html) | $3–6 |
| 10 | **Wiring**: Dupont jumpers, short wires, small perfboard | Anchor the TP4056 + MT3608 + switch. | commodity | $1–3 |
| 11 | (optional) **10 kΩ resistor** | Shutter pull-up. ESP32 internal pull-up usually enough. | commodity | <$0.10 |
| 12 | (optional) **100 kΩ / 100 kΩ divider** | Battery ADC gauge — not recommended (pins used), see §6. | commodity | <$0.50 |

**Programmer note:** for flashing you cross-connect **USB-TTL TX→GPIO3 (RX0)**, **USB-TTL RX→GPIO1 (TX0)**, 5 V (or 3.3 V) and GND, and pull **GPIO 0 to GND** during power-up. After flashing, the GPIO 1/3 wires are reused as the OLED I2C bus.

---

## 2. Power architecture

```
18650 (protected)
  └── TP4056 (with protection)          Micro-USB in → charges cell (B+/B−)
        OUT+/OUT−  →  protected terminals
              │
              ├── [SPDT switch] ──► MT3608 boost VIN+   (OUT− to common GND)
              │                                     │
              └──── same GND rails                  └── VOUT+ set to 5.0 V
                                                          VOUT− → GND
                                                            │
                                        ESP32-CAM "5V" pin ──┘ (never the 3.3V pin)
```

**Rules that keep this from smoking or rebooting:**

- **Feed the 5V pin, never the 3.3V pin, never the battery directly.** The AMS1117 LDO needs >4.4 V in; the cell's 3.0–4.2 V can't do it.
- **Do not use the `VCC`/`3V3` pin** — that is the board's *output* (default 3.3 V via a zero-ohm jumper), not a clean input.
- **Set the boost to exactly 5.0 V with a multimeter** (potentiometer trimmer), not 5.5 V. Over 5.3 V stresses the LDO/camera; under ~4.5 V the LDO drops out → random reboots.
- **Charge, then use.** Don't run the camera while the TP4056 is charging on the same node — that's the classic brownout. It's a handheld, so this is natural.
- **TP4056 does NOT boost.** Its `OUT+` is battery voltage (~3.0–4.2 V). You still need the MT3608. (One hobby article wrongly claims the TP4056 outputs 5 V — it does not.)
- Also: **battery gauge on-screen is awkward** (see §6).

---

## 3. Pin map and wiring

This is the crux. The AI-Thinker ESP32-CAM has **~10 usable GPIOs**, and the camera + SD card consume almost all of them:

**Camera (OV2640):** GPIO 0, 5, 18, 19, 21, 22, 23, 25, 26, 27, 32, 34, 35, 36, 39

**microSD (4-bit mode):** GPIO 2, 4, 12, 13, 14, 15

That leaves **GPIO 1, 3, 16 (= PSRAM), 33 (= red LED)** and GPIO 0 (strapping/LED — avoid). Since you want PSRAM enabled for the framebuffers, GPIO 16 is taken.

| Function | ESP32-CAM pin | Why this pin |
|---|---|---|
| **OLED VCC** | `3V3` output rail | SSD1306 is 3.3 V; never 5 V. |
| **OLED GND** | `GND` | common ground. |
| **OLED SCL** | **GPIO 3** (UART RX0) | Only clean free I2C pair. |
| **OLED SDA** | **GPIO 1** (UART TX0) | Only clean free I2C pair. |
| **Shutter button** | **GPIO 33** | Not used by camera/SD; it's the red-LED pad. `INPUT_PULLUP`, LOW = press. |
| **5 V in** | **5V pin** | from boost converter. |
| **microSD** | on-board slot | use `SD_MMC.begin("/sdcard", true)` (1-line mode). |
| **Camera** | on-board flex socket | OV2640 comes attached — be gentle with the connector. |

**Why GPIO 1/3 and not GPIO 12/13:** the tempting "spare" I2C pins are 12 and 13 (freed only if you drop the SD to 1-line mode). But **GPIO 12 is a boot strapping pin** (flash-voltage select) — if the OLED's pull-ups hold it high, **the board won't boot or flash**. Verified in Arduino forum threads. GPIO 1/3 are not strapping pins, so the OLED pull-ups won't break booting, and re-flashing over UART still works even while the OLED is attached. You give up the serial monitor — irrelevant for a standalone camera.

---

## 4. Firmware

The full Arduino sketch lives in the vault at `attachments/esp32-cam-oled-camera/esp32-cam-oled-camera.ino` (in-repo, not served on the site), and is reproduced in full in the [Appendix](#appendix--full-firmware) below so this page stands alone. Design and rationale:

**Camera stays in `PIXFORMAT_JPEG` the whole time** (QVGA, `jpeg_quality` 12, `fb_count` 2 on PSRAM). This matters because the viewfinder and the saved photo are the *same* frame — **what you framed is what gets saved.** No camera re-init, no format switching.

- **Live framing:** `esp_camera_fb_get()` → decode the JPEG with **JPEGDEC** → for each pixel map it into an **85×64 letterboxed region** (aspect-4:3 preserved, centred) → threshold the luma to 1-bit → `display()`. ~3–6 FPS.
- **Shutter (GPIO 33, active-low, debounced):** take the *current* framebuffer, write its raw JPEG bytes to `/PHOTO_nnnn.jpg` on the SD card, and leave that frame on the OLED as the confirm + a "SAVED" sticker. Frame shown == JPEG saved.

**Libraries (Arduino IDE → Manage Libraries):** `Adafruit SSD1306`, `Adafruit GFX`, `JPEGDEC` (bitbank2). `esp_camera` and `SD_MMC` are in the "esp32" boards core.

**Board settings:** *ESP32 Dev Module* (or *AI Thinker ESP32-CAM*), **Huge APP (3 MB No OTA)** partition scheme, **PSRAM enabled**.

**JPEGDEC API note (gotcha):** `decode(int x, int y, int iOptions)` is the 3-arg form in current releases (older code uses `decode(0,0)`). `setMaxOutputSize(int)` takes a **MCU count**, *not* width/height — do not size the output with it. To speed framing up use the `iOptions` scale flags: `decode(0, 0, JPEG_SCALE_HALF)`. For nicer 1-bit rendering swap to `decodeDither()` with the `ONE_BIT_DITHERED` pixel type (Floyd–Steinberg) — that's what the reference `robotzero.one` ESP32-CAM-OLED project uses and it looks far better than a hard threshold.

**This scaffold has not been compiled here** (no ESP32 toolchain on this machine). It is written to be dropped into Arduino IDE and built; verify the JPEGDEC call signature against the version you install.

---

## 5. 3D-printed casing requirements

- **Front:** lens aperture for the OV2640. Keep the flex cable / its tiny socket strain-relieved — it's the #1 physical failure point.
- **Back / side:** OLED viewing window.
- **Battery bay:** spring holder for the 18650, with the TP4056 + MT3608 + switch anchored on a small perfboard beside it.
- **Access:** microSD slot, a USB passthrough hole to reach the TP4056 Micro-USB for charging, and the slide switch.
- **Ventilation:** the ESP32-CAM + camera run warm; add vents so the OLED and camera don't overcook.
- **Focus reality:** the OV2640 is **fixed focus** (~0.5–2 m, standard ~66° lens). For close-up shots you'd need a different-FOV / focus-adjustable lens module.
- **Materials:** PLA is fine indoors; PETG/ASA for heat or outdoor/UV.

---

## 6. Things that will bite you (failure modes)

1. **Brownouts / reboots** — almost always a power issue. Boost to a *clean* 5.0 V, feed the 5V pin, don't charge-and-run simultaneously.
2. **SD + camera + WiFi conflict** — this is a standalone camera; **don't use WiFi.** WiFi also conflicts with the ADC2 pins and the SD card on some builds. Keep WiFi off for both stability and battery life.
3. **Flash LED vs SD** — GPIO 4 is both SD DATA1 and the white flash LED. In 4-bit SD mode the flash LED glitches. Use **1-line SD mode** (`SD_MMC.begin("/sdcard", true)`) to stop the flicker. Don't plan on using the flash while the SD is active.
4. **Battery % on the OLED is awkward** — the ADC-capable GPIOs (2,4,12,13,14,15) are all used by the SD, and ADC2 conflicts with WiFi. If you insist, run SD in 1-line mode (frees 12/13), disable WiFi, and feed a divider into one of those. For a "primarily framing" camera, skip it and just charge-between-uses.
5. **JPEGDEC API drift** — see §4. `decode()` and `setMaxOutputSize()` signatures changed across versions.
6. **Camera connector** — the OV2640 flex-cable socket is fragile. Mount the board so the ribbon isn't under tension.

---

## Sources

- Random Nerd Tutorials — [ESP32-CAM AI-Thinker Pinout Guide](https://randomnerdtutorials.com/esp32-cam-ai-thinker-pinout/) (camera + SD pin tables, microSD shared pins, "power via the 5V pin", flash-LED/GPIO4 note, 1-line SD mode)
- Last Minute Engineers — [ESP32-CAM Pinout Reference](https://lastminuteengineers.com/esp32-cam-pinout-reference/) (only ~10 usable GPIOs, "always power via the 5V pin", `VCC`/jumper note, GPIO0 boot behavior, GPIO33 red LED)
- lexus2k/lcdgfx — [Issue #16: live-updating SSD1306 from camera frames](https://github.com/lexus2k/lcdgfx/issues/16) (feasibility, ~5 FPS target, grayscale + dithering, the working `robotzero.one` ESP32-CAM-OLED project)
- Arduino Forum — [ESP32-CAM I2C upload error when SDA/SCL connected](https://forum.arduino.cc/t/esp32-cam-i2c-upload-error-when-sda-scl-are-connected/1336480) (GPIO 12 boot-strap trap → use a different pin)
- how2electronics — [Power Supply for ESP32 with Boost Converter & Battery Charger](https://how2electronics.com/power-supply-for-esp32-with-boost-converter-battery-charger/) (18650→TP4056→boost→5V, ESP32 current draw, LDO dropout)
- Aliexpress category pages for exact sourcing (links in §1)

---

## Appendix — full firmware

```cpp
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

```
