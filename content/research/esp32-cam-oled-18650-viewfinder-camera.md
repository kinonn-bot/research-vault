---
title: ESP32-CAM + 0.96" OLED Portable Still Camera (18650, 3D-printed)
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

# ESP32-CAM + 0.96" OLED Portable Still Camera (18650, 3D-printed)

A **portable still-only camera**: a handheld point-and-shoot built from an **AI-Thinker ESP32-CAM** (OV2640), a **0.96" SSD1306 128×64 I2C OLED** used as a viewfinder + photo-confirm, a **single 18650** for power, and a **3D-printed** body. Captured JPEGs go to the **on-board microSD**.

**Scope: stills only.** No video recording, no streaming, no WiFi. The OLED is only ever for framing a shot and confirming it, and the only output is a JPEG on the SD card. This keeps the firmware small and the power draw much lower.

> The broader landscape is in [[ESP32 + 3D-Printed Camera Projects]]. This note is the *specific* still-camera build with full wiring and a connection diagram.

---

## 0. Reality check — read this before you buy anything

Three things about this exact combo that drive every decision:

1. **The 0.96" SSD1306 is a 1-bit, 128×64, 1024-byte display.** No true grayscale, no smooth video. The viewfinder is a lo-fi **black-and-white preview at ~3–6 FPS** — great for framing a still, not for video. That's fine, because this camera is stills-only anyway.
2. **The ESP32-CAM has almost no spare pins.** The camera eats most GPIOs, the microSD eats the rest. The only clean I2C pair for the OLED is **GPIO 1 + GPIO 3** (the UART pins), and the shutter goes on **GPIO 33** (the onboard red-LED pad).
3. **The 18650 cannot power the board directly.** The cell only delivers ~3.0–4.2 V, and the board's AMS1117 LDO needs **> ~4.4 V in** to hold 3.3 V out. You **must** boost to **5 V** and feed the **5V pin**. This is the #1 cause of "my camera keeps rebooting."

**Buy the PSRAM variant.** Without the 4 MB PSRAM the camera can't hold multiple framebuffers and the whole preview/save pipeline gets much worse.

Because it's stills-only, **WiFi is never initialised** — which removes the ADC2 and microSD conflicts that bit people in the streaming builds, and saves radio current.

---

## 1. Connection diagram

### 1.1 Wiring / schematic (ASCII)

Central board is the ESP32-CAM; everything else hangs off it.

```
                    ================= POWER RAIL =================
  18650 (protected)      TP4056 (w/ protection)        MT3608 boost 3.7V->5.0V
  +  ── BAT+ ──► (charges; Micro-USB in)  OUT+ ──► [SPDT switch] ──► VIN+
  -  ── BAT- ──►                             OUT- ────────────► VIN-         |
                                                                             |
                                        VOUT+ (SET TO EXACTLY 5.0V) ──► 5V pin
                                        VOUT- ──────────────────────► GND

  ======================== ESP32-CAM (AI-Thinker, 4MB PSRAM) ================
   [ 5V ]  <──── from MT3608 VOUT+  (NOT the battery, NOT a 5V USB feed)
   [ GND]  <──── common ground: battery-, TP4056 OUT-, boost VOUT-
   [ 3V3]  ────► OLED VCC           (3.3V output rail — never 5V for the module)
   [ GND]  ────► OLED GND
   [GPIO3/(RX0)] ────► OLED SCL     (I2C clock)
   [GPIO1/(TX0)] ────► OLED SDA     (I2C data)
   [GPIO33] ──< tactile button >── GND    (shutter, INPUT_PULLUP, LOW = press)
   [GPIO4 ] ──── on-board white flash LED (optional; shares SD DATA1 in 4-bit mode)
   [ OV2640 ] ──── on-board flex socket    (do NOT unplug while powered)
   [ microSD ] ──── on-board slot          (1-line mode: SD_MMC.begin("/sdcard",true))

  ===================== programming header (dev only) =======================
   FTDI/CP2102 TX ──► GPIO3 (RX0)      FTDI/CP2102 RX ──► GPIO1 (TX0)
   FTDI 5V ──► board 5V    FTDI GND ──► board GND
   GPIO0 ──► GND  during power-up (boot/flash) then remove
```

### 1.2 Pin map

| Function | ESP32-CAM pin | Why this pin |
|---|---|---|
| **OLED VCC** | `3V3` output rail | SSD1306 is 3.3 V. |
| **OLED GND** | `GND` | common ground. |
| **OLED SCL** | **GPIO 3** (UART RX0) | Only clean free I2C pair. |
| **OLED SDA** | **GPIO 1** (UART TX0) | Only clean free I2C pair. |
| **Shutter button** | **GPIO 33** | Not used by camera/SD; the red-LED pad. `INPUT_PULLUP`. |
| **5 V in** | **5V pin** | from MT3608 boost (5.0 V). |
| **microSD** | on-board slot | `SD_MMC.begin("/sdcard", true)` (1-line). |
| **Camera** | on-board flex socket | OV2640 ships attached — be gentle. |
| **Flash LED** | **GPIO 4** (optional) | shared with SD DATA1; skip or use 1-line SD mode. |

**Why GPIO 1/3 and not GPIO 12/13:** pins 12 and 13 look like "spare" I2C pins but **GPIO 12 is a boot strapping pin** (flash-voltage select). If the OLED's pull-ups hold it high, the board won't boot or flash (Arduino forum threads confirm). GPIO 1/3 are **not** strapping pins, so the OLED pull-ups won't break booting and re-flashing still works. You give up the serial monitor — irrelevant here.

---

## 2. Bill of Materials (AliExpress)

Prices vary by seller/bundle; **verify the PSRAM variant** and the listing photo before ordering. Don't buy a suspiciously cheap 18650 — counterfeits are common and dangerous.

| # | Part | Spec / why | AliExpress | Typical price (USD) |
|---|---|---|---|---|
| 1 | **ESP32-CAM, 4 MB PSRAM** (AI-Thinker) | The board. Ships with the OV2640 camera. **Get the PSRAM version.** | [wholesale-esp32-cam-thinker](https://www.aliexpress.com/w/wholesale-esp32-cam-thinker.html) · [kit w/ CH340G](https://www.aliexpress.com/item/1005002808966055.html) | $6–16 (kits $18–31) |
| 2 | **0.96" OLED SSD1306 128×64 I2C** | The viewfinder. `0x3C`, onboard pull-ups, 3.3 V. | [32643950109](https://www.aliexpress.com/item/32643950109.html) · [wholesale-oled-ssd1306-128x64](https://www.aliexpress.com/w/wholesale-oled-display-ssd1306-128x64.html) | $1–3 (up to $10) |
| 3 | **18650 Li-ion (protected, ~2600 mAh)** | One cell. **Protected** (on-cell or via the charger module's). | [wholesale-18650-3.7v-2600mah](https://www.aliexpress.com/w/wholesale-18650-battery-3.7v-2600mah.html) | $3–5 cheap, $5–8 quality |
| 4 | **TP4056 module *with protection*** | Charger + over-discharge/over-current protection. The "with protection" version is required for a bare cell. | [32467578996](https://www.aliexpress.com/item/32467578996.html) · [wholesale-tp4056](https://www.aliexpress.com/w/wholesale-tp4056.html) | $1–3 |
| 5 | **MT3608 boost, 3.7 V→5 V** | **Required.** Set output to exactly 5.0 V. | [wholesale-mt3608](https://www.aliexpress.com/w/wholesale-mt3608.html) | $1–3 |
| 6 | **18650 holder / spring bracket** | Mounts the cell in the printed case. | [wholesale-18650-battery-holder](https://www.aliexpress.com/w/wholesale-18650-battery-holder.html) | $1–3 |
| 7 | **SPDT slide switch** | On/off between battery and boost input. | [wholesale-tact-switch-6mm](https://www.aliexpress.com/w/wholesale-tact-switch-6mm.html) | ~$0.40 |
| 8 | **Tactile push-button (6×6 mm)** | Shutter, on GPIO 33. | [wholesale-tact-switch-6mm](https://www.aliexpress.com/w/wholesale-tact-switch-6mm.html) (10 pcs ~$1) | ~$0.10 ea |
| 9 | **USB-UART programmer** (CP2102 / CH340) | Flashing only. The board has no USB. | [wholesale-cp2102-uart-usb](https://www.aliexpress.com/w/wholesale-cp2102-uart-usb.html) | $3–6 |
| 10 | **Wiring**: Dupont jumpers, short wires, small perfboard | Anchor TP4056 + MT3608 + switch. | commodity | $1–3 |
| 11 | (optional) **10 kΩ resistor** | Shutter pull-up (internal usually enough). | commodity | <$0.10 |

**Programmer hookup:** USB-TTL **TX→GPIO3 (RX0)**, **RX→GPIO1 (TX0)**, 5 V and GND, and pull **GPIO 0 to GND** during power-up. After flashing the same GPIO 1/3 wires are reused as the OLED I2C bus.

---

## 3. Power architecture

```
18650 (protected)
  └── TP4056 (with protection)          Micro-USB in → charges cell (B+/B−)
        OUT+/OUT−  →  protected terminals
              │
              ├── [SPDT switch] ──► MT3608 boost VIN+   (OUT− to common GND)
              │                                      │
              └──── same GND rails                    └── VOUT+ set to 5.0 V
                                                          VOUT− → GND
                                                            │
                                        ESP32-CAM "5V" pin ──┘ (never the 3.3V pin)
```

**Rules that keep it from smoking or rebooting:**

- **Feed the 5V pin, never the 3.3V pin, never the battery directly** — the AMS1117 LDO needs > 4.4 V in.
- **Don't use the `VCC`/`3V3` pin** — that's the board's *output* (default 3.3 V via a zero-ohm jumper), not a clean input.
- **Set the boost to exactly 5.0 V** with a multimeter. Over 5.3 V stresses the LDO/camera; under ~4.5 V the LDO drops out → random reboots.
- **Charge, then use.** Don't run the camera while the TP4056 charges the same node — the classic brownout.
- **TP4056 does NOT boost.** Its `OUT+` is battery voltage (~3.0–4.2 V); you still need the MT3608. (One article wrongly claims the TP4056 outputs 5 V.)

---

## 4. Firmware

The full Arduino sketch lives at `attachments/esp32-cam-oled-camera/esp32-cam-oled-camera.ino` (in-repo, not served on the site) and is reproduced in the [Appendix](#appendix-full-firmware) so this page stands alone. Design:

- **No WiFi, no streaming.** The sketch never initialises networking — this is a still-only camera.
- **Camera stays in `PIXFORMAT_JPEG` at 640×480 (VGA)** the whole time. **What you framed == what you saved** — no camera re-init, no format switching.
- **Viewfinder:** `esp_camera_fb_get()` → decode with **JPEGDEC `JPEG_SCALE_HALF`** (fast, ~320×240 stream) → map into an **85×64 centred letterbox** (aspect preserved) → threshold luma to 1-bit → `display()`. ~3–6 FPS.
- **Shutter (GPIO 33, active-low, debounced):** write the **full-resolution** VGA JPEG to `/PHOTO_nnnn.jpg`, then `showFrame(...false)` — a full-res decode — leaving the *saved* image on the OLED as the confirm + a "SAVED" sticker.
- The source→display mapping is driven by `gSrcW`/`gSrcH`; set them to the decoded size (VGA 640×480 full, 320×240 when scaled).

**Libraries:** `Adafruit SSD1306`, `Adafruit GFX`, `JPEGDEC` (bitbank2); `esp_camera`, `SD_MMC` in the ESP32 core. **Board settings:** *ESP32 Dev Module* (or *AI Thinker ESP32-CAM*), **Huge APP (3 MB No OTA)**, **PSRAM enabled**.

**JPEGDEC API note:** current releases use `decode(int x, int y, int iOptions)` (e.g. `decode(0,0,JPEG_SCALE_HALF)`); older use `decode(0,0)`. `setMaxOutputSize(int)` takes a **MCU count**, not width/height — don't use it for sizing.

**This scaffold is not compiled here** (no ESP32 toolchain on this Pi). It's written to build in Arduino IDE; verify the JPEGDEC call signature against the version you install.

---

## 5. 3D-printed casing requirements

- **Front:** lens aperture for the OV2640. Strain-relieve the flex cable / its socket — the #1 physical failure point.
- **Back / side:** OLED viewing window.
- **Battery bay:** spring holder for the 18650; TP4056 + MT3608 + switch on a small perfboard beside it.
- **Access:** microSD slot, a USB passthrough hole to the TP4056 Micro-USB for charging, and the slide switch.
- **Ventilation:** the ESP32-CAM + camera run warm; add vents so the OLED and camera don't overcook.
- **Focus reality:** the OV2640 is **fixed focus** (~0.5–2 m, standard ~66° lens). For close-ups you'd need a different-FOV / focus-adjustable lens module.
- **Materials:** PLA indoors; PETG/ASA for heat or outdoor/UV.

---

## 6. Things that will bite you (failure modes)

1. **Brownouts / reboots** — almost always power. Boost to a *clean* 5.0 V, feed the 5V pin, don't charge-and-run simultaneously.
2. **Flash LED vs SD** — GPIO 4 is both SD DATA1 and the white flash LED. In 4-bit SD mode the flash glitches; use **1-line SD mode** (`SD_MMC.begin("/sdcard", true)`). Don't rely on the flash with the SD active.
3. **Battery % on the OLED is awkward** — the ADC-capable GPIOs (2, 4, 12, 13, 14, 15) are all used by the SD. Skip the on-screen gauge; just charge-between-uses.
4. **JPEGDEC API drift** — see §4.
5. **Camera connector** — the OV2640 flex-cable socket is fragile. Mount the board so the ribbon isn't under tension.

---

## Sources

- Random Nerd Tutorials — [ESP32-CAM AI-Thinker Pinout Guide](https://randomnerdtutorials.com/esp32-cam-ai-thinker-pinout/) (camera + SD pin tables, "power via the 5V pin", flash-LED/GPIO4, 1-line SD mode)
- Last Minute Engineers — [ESP32-CAM Pinout Reference](https://lastminuteengineers.com/esp32-cam-pinout-reference/) (~10 usable GPIOs, "always power via the 5V pin", `VCC`/jumper note, GPIO0 boot, GPIO33 red LED)
- lexus2k/lcdgfx — [Issue #16: live-updating SSD1306 from camera frames](https://github.com/lexus2k/lcdgfx/issues/16) (feasibility, ~5 FPS, grayscale + dithering, the working `robotzero.one` ESP32-CAM-OLED project)
- Arduino Forum — [ESP32-CAM I2C upload error when SDA/SCL connected](https://forum.arduino.cc/t/esp32-cam-i2c-upload-error-when-sda-scl-are-connected/1336480) (GPIO 12 boot-strap trap)
- how2electronics — [Power Supply for ESP32 with Boost Converter & Battery Charger](https://how2electronics.com/power-supply-for-esp32-with-boost-converter-battery-charger/) (18650→TP4056→boost→5V, ESP32 current draw, LDO dropout)
- AliExpress category pages for exact sourcing (§2 links)

---

## Appendix: full firmware

```cpp
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

```
