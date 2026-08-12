---
title: Mechanical + Microcontroller Project Catalog
tags:
  - research
  - hardware
  - mechanical
  - microcontroller
  - project-ideas
  - 3d-printing
  - laser-cutting
---

# Mechanical + Microcontroller Project Catalog

A deep-research roundup of medium-to-high-complexity projects that combine **mechanical build** (3D printing, laser cutting, gears, linkages, cams) with a **microcontroller** (ESP32, Arduino, RP2040, RPi). Curated for someone who has a split-flap display and a QLOCKTWO-style word clock under their belt, with a Bambu-class FDM printer and a diode-laser cutter on hand.

Every project is tagged with three axes so you can pick by appetite:

| Axis | Low | Med | High |
|---|---|---|---|
| **Build time** | 1 weekend | 1–4 weekends | 1–3 months |
| **Cost (parts only)** | <$50 | $50–$300 | $300+ |
| **Skill ceiling** | soldering + Arduino basics | stepper drivers, I²C, multi-module bring-up | power electronics (HV, drivers), firmware architecture |

> **Start-here rule:** pick a project where your weakest axis (usually power electronics or motion tuning) is exactly what you want to learn. The mechanical/3D side is rarely the blocker — it's the *motor tuning*, *signal integrity*, and *firmware state machine* that separates a finished shelf-queen from a half-built drawer project.

---

## Category Index

- [1. Mechanical alphanumeric / pixel displays](#1-mechanical-alphanumeric--pixel-displays)
- [2. Clocks & time-based art](#2-clocks--time-based-art)
- [3. Kinetic art & automata](#3-kinetic-art--automata)
- [4. Drawing & plotting machines](#4-drawing--plotting-machines)
- [5. Walking machines & linkages](#5-walking-machines--linkages)
- [6. Musical instruments](#6-musical-instruments)
- [7. Ambient / connected displays](#7-ambient--connected-displays)
- [8. How to pick](#8-how-to-pick)
- [9. Cameras & imaging](#9-cameras--imaging)

---

## 1. Mechanical alphanumeric / pixel displays

The natural next step after a split-flap display. Each one solves the "I want a non-flat display" problem differently — what you pick depends on whether you want **electromagnets**, **rotating servos**, or **POV**.

### 1.1 Flip-Dot Display (DIY controller version)

- **What:** Reclaimed/cheap flip-dot panels (Alfa-Zeta 7×7, 14×24, or generic Bulgarian 28×14) driven by your own ESP32 controller instead of the OEM one.
- **Why it's great:** Industrial bistable dots that hold position with **zero power**. Insanely satisfying tactile click.
- **Complexity:** Medium-High. 20V pulse driver, current-limited darlington/SPI shift-register chain, careful in-rush limiting (H-bridge per column, not per dot). One burned chip per amateur on average — current sink/source is the #1 failure.
- **Cost:** $50–$300 for the panels + $30–$60 driver board.
- **Time:** 2–6 weekends for a 7×7 clock; scaling beyond that quickly becomes a multi-month power-distribution exercise.
- **Refs:**
  - scottbez1-style ESP32 controller: [Hackaday.io: Flip-Dot Display & DIY Controller](https://hackaday.io/project/159415-flip-dot-display-diy-controller) — has the "burning chip" lessons learned documented in detail.
  - Pierre Muth, 14×24 stack with stacked SPI: [Flipping Dots Fast](https://pierremuth.wordpress.com/2021/02/17/flipping-dots-fast/)
  - 7×7 Alfa-Zeta + ESP32 NTP/BLE clock: [FLIPDOTS Clock](https://hackaday.io/project/184036-flipdots-clock)
- **Skill ceiling:** Power electronics, level shifting, impedance vs dot count (48 boards in series will not all flip — you must feed both ends).

### 1.2 Moving Pixel LED Clock (Erich Styger)

- **What:** A grid of tiny stepper motors (28BYJ-48 or NEMA8) each push an LED-backed pixel up out of a black panel. LEDs shine through the raised pixel; lowered pixels look like black voids. RGB LED behind each.
- **Why it's great:** Has the same "physical pixel" feeling as split-flap but **scales more easily** (one cheap 28BYJ per pixel vs NEMA per character). 18-month dev project for Styger, but the learning is reusable.
- **Complexity:** High. Lots of small 3D parts, multiplexing challenge (you'll need 4–8 daisy-chained shift registers or an LED driver per row), stepper tuning, mechanical alignment.
- **Cost:** $150–$400 depending on pixel count.
- **Time:** 1–3 months for a meaningful grid (8×16 minimum).
- **Refs:**
  - [Moving Pixel Clock — Raspberry Pi Official Magazine](https://magazine.raspberrypi.com/articles/moving-pixel-clock)
  - [MCU on Eclipse build log](https://mcuoneclipse.com/2023/12/27/moving-pixel-clock-project/)
  - [Hackster coverage](https://www.hackster.io/news/erich-styger-s-moving-pixel-led-clock-pops-its-leds-out-to-really-make-the-display-stand-out-7ae310b57a20)
- **Skill ceiling:** Multi-channel stepper firmware (AccelStepper or custom), PCB design if you want it to scale.

### 1.3 3D-Printed Electromechanical Pixel (Cooley / Coolfactor "Pixel")

- **What:** Each pixel is a tiny servo rotating a propeller-like vane inside a black casing. Rotated one way = blank, the other way = reveals a colored face. **Greyscale via intermediate positions** is the brilliant trick.
- **Why it's great:** Pure 3D-printed mechanism, no coils, no HV. 64 pixels makes a proper matrix display.
- **Complexity:** Medium. *Manufacturing is the long phase* (Cooley: each pixel is 7 printed parts + 1 servo + 2 nails). Servo jitter at intermediate positions is the only real challenge.
- **Cost:** $100–$200 (the servos are the bulk).
- **Time:** 3–6 weekends, mostly print time.
- **Refs:**
  - [Electromechanical display · Coolfactor](https://www.coolfactor.org/project/pixel/)
  - [Pixel Electromechanical Display — Raspberry Pi Official Magazine](https://magazine.raspberrypi.com/articles/pixel-electromechanical-display)

### 1.4 POV (Persistence of Vision) Propeller Display / Clock

- **What:** A single-arm rotor with a column of LEDs (8–32). Spun at 1000+ RPM, the LEDs strobe in sync with the rotation to draw text/clock faces in mid-air.
- **Why it's great:** Single-sided, fast to build, 100% 3D-printable, can be done with just an Arduino Nano and a $5 motor. Sits nicely on a desk as a fan-blade clock.
- **Complexity:** Low-Medium. The hard part is angular indexing (Hall sensor or optical interrupter), and balancing the rotor so it doesn't shake itself apart. Software is straightforward.
- **Cost:** <$30.
- **Time:** 1 weekend (a usable version) up to 1 month (balanced, well-tuned, wall-powered).
- **Refs:**
  - [Bob Blick original propeller clock (still the canonical design)](https://www.electronixandmore.com/projects/propclock/index.html)
  - [CircuitDigest: Arduino Propeller Display](https://circuitdigest.com/microcontroller-projects/arduino-propeller-display)
  - [Catahoula Technologies POV Clock kit](https://catahoulatech.com/index.php?cat=pcb&product=KIT-0020)
- **Skill ceiling:** Just solid-state. Perfect "I haven't done anything in a while" project.

### 1.5 Magnetophoretic / 3D-Printed Passive Magnetic Pixel Displays

- **What:** An FDM printer with a magnetic-PLA filament + a small electromagnet matrix behind the print. Each printed "voxel" becomes a bistable magnetic switch. The matrix paints hidden patterns into a printed surface that only show when you bring a magnetic viewer near.
- **Why it's great:** **Print your display** instead of assembling it. Always-on, no power needed, doesn't look like anything until activated.
- **Complexity:** Medium-High. Magnetizer design is the trick; magnetophoretic patterns require careful FDM pause-and-swap (or multi-material printer).
- **Cost:** $50–$150 + magnetic filament.
- **Time:** 2–4 weekends.
- **Refs:**
  - [3D Printing Magnetophoretic Displays — University of Maryland / ACM](https://dl.acm.org/doi/fullHtml/10.1145/3586183.3606804)
  - [MagPixel toolkit — CHI 2024](https://dl.acm.org/doi/10.1145/3613905.3650901)

### 1.6 PixelWeaver / rotating-cube pixel display

- **What:** Each pixel is a small cube with two black faces and two white faces, rotated 90° by a tiny mechanism to toggle. PixelWeaver by Chris Fenton uses an X/Y string-driven gantry that drags a "turtle" that rotates individual pixels in a 2D grid — clever but complex.
- **Complexity:** High (string-pulled-cartesian stage + per-pixel mechanism). More research project than weekend build.
- **Ref:** [chrisfenton.com/the-pixelweaver](http://www.chrisfenton.com/the-pixelweaver/)

### 1.7 Marble pixel clock (no electro-mechanics, just geometry!)

- **What:** Steel balls held in 3×5 grids with backlit cells. Each "digit" is a 3×5 pixel font; a stepper-driven shuttle lifts/repositions balls in/out of cells on a schedule.
- **Why it's great:** Zero electromagnets — it's all geometry. Quiet. Looks magical.
- **Ref:** [Designboom: mechanical marble clock](https://www.designboom.com/technology/mechanical-marble-clock-moves-steel-balls-pixel-digits-time-strange-inventions/)

---

## 2. Clocks & time-based art

You already have a word clock — here's what's adjacent.

### 2.1 Nixie Tube Clock (IN-14, IN-18, Z568M)

- **What:** Soviet-era neon display tubes. Each digit is a separate wire cathode glowing inside a gas-filled envelope. Driven at **170 V DC** with multiplexed anode control.
- **Why it's great:** Genuinely warm, analog glow. The aesthetic is unmatched. Off-the-shelf kits mean almost zero mechanical work.
- **Complexity:** Medium. **The HV power supply is the only real hazard** — everything else is straightforward 5 V logic + transistor arrays. Pick a kit that has a regulated boost converter + current limiting.
- **Cost:** $80–$250 for a kit (tubes alone are $5–15 each on eBay).
- **Time:** 1–2 weekends.
- **Refs:**
  - [GRA & AFCH NCS314 IN-14 Arduino Shield](https://gra-afch.com/catalog/diy-kit-for-nixie-tubes-clocks/diy-kit-for-shield-nixie-tubes-clocks-in-14-ncs314/)
  - [Instructables: Nixie Clock for Absolute Beginners](https://www.instructables.com/Arduino-Nixie-Clock-for-Absolute-Beginners/)
  - [Arduino Project Hub: simplest design](https://projecthub.arduino.cc/whitebank/nixie-clock-with-arduino-simplest-design-474fc6)
- **Skill ceiling:** Just be careful around 170 V — *this will kill a 9 V battery feeling and hurt you badly.*

### 2.2 QLOCKTWO-style Word Clock (DIY)

- **What:** 11×10 letter grid; an ESP32 lights the relevant words to spell out the time ("IT IS HALF PAST TWELVE"). You already know this one — these are the variations you haven't done.
- **Why it's great:** Laser-cut diffuser + WS2812 strip + ESP32. This is your bread-and-butter toolchain.
- **Variation A: Stainless steel face** — laser-cut brushed stainless, LED matrix bonded behind. Vigue's version uses a custom PCB with ESP32-S3. ([ref](https://vigue.me/posts/stainless-steel-word-clock))
- **Variation B: Round word clock** — concentric rings of letters instead of a square grid. Rare, beautiful.
- **Variation C: Multilanguage** — ESPWortuhr supports German/English/French/Spanish layouts from a single sketch. ([ref](https://github.com/ESPWortuhr/Multilayout-ESP-Wordclock))
- **Variation D: Web-configurable + OTA** — `ednieuw/Arduino-ESP32-Nano-Wordclock` style. Time zone, brightness curve, animation. ([ref](https://github.com/ednieuw/Arduino-ESP32-Nano-Wordclock))
- **Complexity:** Low–Medium (you've done this). Variations are mostly mechanical: diffuser material choice, stenciling method, case design.
- **Refs:**
  - [1JonaB1/Wordclock](https://github.com/1JonaB1/Wordclock)
  - [t0mg/wordclock](https://github.com/t0mg/wordclock)
  - [benedikt-kuenzel QLOCKTWO clone writeup](https://benedikt-kuenzel.com/2019/01/25/building-a-word-clock-qlocktwo-clone/)

### 2.3 Flip-disc clock / split-flap clock

You have these. The **next step** is a **flip-disc clock** (each digit is a 7-segment grid of magnetic dots that click between two colored faces) — combines the dot flipper controller skill above with a 7-segment clock front end.

---

## 3. Kinetic art & automata

The "I want a desk object that doesn't have a screen" category. These lean more on the mechanical/3D side and use microcontrollers mostly for **sensors + drive patterns**.

### 3.1 Sisyphus-style Kinetic Sand Table

- **What:** A steel ball magnetically dragged through a thin layer of fine sand by a gantry hidden under the table, drawing endless geometric patterns.
- **Why it's great:** Endlessly watchable. Strong DIY community. **Pattern generators exist** (sandify.org) so you don't have to design the art yourself.
- **Variation A (Sisbot, polar):** Closest to the original. Two motors driving a single arm with a magnet on the end. Two-axis kinematics. Compact, beautiful, more math.
- **Variation B (XY ZenXY):** Cartesian X/Y, more 3D-printable parts, easier mechanical build, slightly bigger. [V1 Engineering ZenXY](https://www.v1engineering.com/zenxy/) is the canonical kit; their [V2 blog](https://www.v1e.com/blogs/news/zenxy-v2-sand-table) has the closed-frame EMT-conduit rail design that scales to coffee-table size.
- **Variation C (single-Arduino):** Two NEMA17 + CNC shield + GRBL. Hackaday's 2024 build used exactly this. ([ref](https://hackaday.com/2024/01/07/remote-control-kinetic-sand-table-uses-a-single-arduino/))
- **Complexity:** Medium. Stepper tuning + GRBL/Marlin config + leveling the sand bed + finding non-static sand. **Do not skip** leveling.
- **Cost:** $150–$400 (Z-axis ball magnet is a $5 N52 + something to attach it to the carriage).
- **Time:** 2–6 weekends.
- **Refs:**
  - [Mark Roland's Sand Table Build](https://markroland.github.io/sand-table-build/)
  - [Always Tinkering — DIY Kinetic Sand Art Table](http://alwaystinkering.com/2020/01/14/diy-kinetic-sand-art-table/)
  - [V1 Engineering ZenXY](https://www.v1engineering.com/zenxy/)
  - [Sandify pattern generator](https://sandify.org/)

### 3.2 Marble Machines & Chain Lifts

- **What:** 3D-printed marble runs lifted by an Archimedes screw or chain lift, dropping through tracks and ramps. From a desk toy to a wall-sized sculpture.
- **Why it's great:** Pure mechanical fun; micro is optional (a touch sensor + motor speed control is the typical scope). MakerWorld and Printables have hundreds of STLs.
- **Top picks:**
  - [Greg Zumwalt — 3D Printed Kinetic Marble Machine](https://cults3d.com/en/3d-model/gadget/a-3d-printed-kinetic-marble-machine) — print-in-place dual-axis gimbal.
  - [Sisyphus Marble Machine V3 Motorized](https://makerworld.com/en/models/2207077-sisyphus-marble-machine-v3-motorized) — modern Bambu-friendly design.
  - [Marble City by Jacob Surovsky](https://www.myminifactory.com/object/3d-print-marble-city-kinetic-sculpture-95761) — bridge-and-river sculpture, display piece.
- **Complexity:** Low-Medium. Mostly print-and-assemble. Worth doing once just to understand how 3D-printed kinematic chains fail.
- **Cost:** <$30 in filament + a $5 geared motor.
- **Time:** 1 weekend (small toy) to 1 month (large sculpture).

### 3.3 Cam-driven Automata (Mechanical Toys)

- **What:** Hand-cranked or low-RPM motor driven scenes where **cams** (off-center rotating shapes) push followers that animate characters. Classic Cabriole / Theo Jansen lineage.
- **Why it's great:** Once you understand cam math, you can build **anything that cycles**. Add a sensor + an Arduino and the cam-driven scene becomes a teaching tool (count rotations, sync with sound, etc.).
- **Refs:**
  - [Greg Zumwalt's mechanical models catalog](https://3dprintingindustry.com/news/greg-zumwalts-3d-printed-mechanical-models-122328/)
  - [Mechanical Cam Toys Instructable](https://www.instructables.com/Mechanical-Cam-Toys/)
  - [mechanical-toys.com cams primer](https://www.mechanical-toys.com/cams.html)
- **Complexity:** Low (mechanical) to Medium (if you add a micro for synchronization).
- **Cost:** <$20.
- **Time:** 1–2 weekends.

---

## 4. Drawing & plotting machines

Plotter art is a *huge* maker rabbit hole. The aesthetic is in the lines, not the resolution.

### 4.1 Pen plotter (XY, flatbed) — DIY vs AxiDraw

- **What:** Two stepper-driven carriages (X+Y), pen up/down (servo or solenoid), drawing on paper from SVG/HPGL input.
- **DIY routes:**
  - **CoreXY / H-bot** with linear rails — most precise, most expensive.
  - **Belt-and-pulley on MakerBeam/V-slot** — cheapest; tolerates flex, fine for pen art.
  - **MPCNC (Mostly Printed CNC)** — modular, low-cost, scales to A2+. [thingiverse 2994920](https://www.thingiverse.com/thing:2994920) is the classic design.
- **Buy vs build:** The AxiDraw SE/A3 is $595; DIY is $150–$300 if you have a printer to make the parts. Performance difference is small at A4 scale. ([discussion](https://www.reddit.com/r/PlotterArt/comments/ldv58l/thoughts_on_diy_vs_axidraw/))
- **Complexity:** Medium. GRBL + a CAD pipeline (Inkscape + axidraw extension or `vpype` + `axibot`) is the typical software stack.
- **Time:** 2–4 weekends.

### 4.2 Vertical wall plotter (V-plotter / Polargraph)

- **What:** Two steppers mounted at the top corners of a wall (or whiteboard), with string that suspends a pen gondola. The gondola position is computed from string length — a fun inverse-kinematics exercise.
- **Why it's great:** **No Y-axis rigidity problems** because gravity does the work. The pen hangs freely. Draws huge things.
- **DIY:**
  - **Minimal Pico Vertical Plotter** — RP2040-based, ESPHome-friendly. ([Hackaday.io](https://hackaday.io/project/193338-minimal-pico-vertical-plotter))
  - **Stringent, the $15 wall plotter** — minimalist version. ([Hackster](https://www.hackster.io/fredrikstridsman/stringent-the-15-wall-plotter-d965ca))
  - **Polargraph** — the original open-source design (Sandy Noble), still the most documented.
- **Complexity:** Medium. Inverse kinematics + string-length math + the gondola needs to be lightweight.
- **Cost:** $30–$150.
- **Time:** 1–3 weekends.
- **Refs:** [Instructables: Vertical X-Y Plotter](https://www.instructables.com/VERTICAL-X-Y-PLOTTER-DRAWING-ROBOT-ARDUINO-PLOTTER/) · [Liz Melchor's Wall Hanging Drawing Robot](https://lizmelchor.com/wall-robot/)

### 4.3 Sand plotter / 3D pen plotter

If you really like the Sisyphus idea but want a **plotter for actual pictures on flat surfaces**, the same XY gantry with a pen (or extruder) becomes a flatbed plotter / 3D printer / CNC.

---

## 5. Walking machines & linkages

The mechanical engineering rabbit hole. Each project teaches a different kinematic principle.

### 5.1 Strandbeest (Theo Jansen mechanism) walking machine

- **What:** The famous 11-bar Jansen leg mechanism replicated in 3D-printed links. Single motor drives all legs through a cam shaft.
- **Why it's great:** Pure mechanical genius. Once you've built one, you understand 4-bar linkages forever.
- **Refs:**
  - [Hackaday: Building a 3D-Printed Strandbeest](https://hackaday.com/2025/01/16/building-a-3d-printed-strandbeest/)
  - [Strandbeest Inspired Walking Machine — Printables](https://www.printables.com/model/36896-strandbeest-inspired-walking-machine)
  - [Instructables: Strandbeest Walking Robot WIP](https://www.instructables.com/3D-Printed-Strandbeest-Walking-Robot-WIP/)
- **Complexity:** Medium (mechanical tolerance is everything — link length precision to ~0.1 mm).
- **Cost:** <$20 (just plastic + M3 hardware).
- **Time:** 1 weekend (hand-cranked) → 1 month (RC-controlled, multi-segment).

### 5.2 Biped / quadruped walking robots

- **What:** 3D-printed chassis + NEMA17 with cycloidal gearboxes + IMU for balance. **Quadruped is the current frontier** (Stanford Pupper, Open Dynamic Robot Initiative MIT Cheetah clones).
- **Complexity:** **High.** State estimation, gait timing, balance control. A year-long learning project.
- **Skip if:** you don't already know what a Jacobian is.

### 5.3 6-DOF Robot Arm

- **What:** Articulated arm with 6 servos or steppers + gripper. Pick-and-place, drawing, simple assembly tasks.
- **Why it's great:** Robotics staple — teaches kinematics, IK, inverse Jacobian. Lots of working designs to clone.
- **DIY routes:**
  - **SG90 servos (educational):** [OMARM Zero](https://cults3d.com/en/3d-model/gadget/omarm-6-dof-robotic-arm-for-arduino-full-3d-printed-model-stl) — cheap, low payload (~200 g), fine for learning.
  - **NEMA17 + cycloidal gearbox:** Real load capacity (~5 Nm/joint). [Kingroon top picks](https://kingroon.com/blogs/3d-printing-guides/top-3d-printed-robot-arm-projects) has a good list.
  - **Web-controlled:** [Hackaday.io 6-DOF with web interface](https://hackaday.io/project/204984-arduino-6-dof-robotic-arm-with-web-interface).
- **Complexity:** Medium-High.
- **Cost:** $50 (servo version) – $400 (cycloidal).
- **Time:** 2–6 weekends.

---

## 6. Musical instruments

### 6.1 MIDI Laser Harp

- **What:** Vertical array of laser beams (laser diodes + line generators or galvo-scanned single beam). Break a beam → trigger a MIDI note.
- **Why it's great:** Lasers + MIDI = instant showmanship. Jean-Michel Jarre played these live.
- **Complexity:** Medium. Two main paths:
  - **Multiple lasers + photoresistors** — simple, one MIDI note per beam. 9–13 beams typical.
  - **Galvo + single beam** — one beam swept across the play area; position determines note. More dramatic, more involved.
- **Cost:** $50–$200.
- **Time:** 2–4 weekends.
- **Safety:** Class 3R lasers or below. **Never** class 3B or 4 in a home setup without proper engineering controls.
- **Refs:**
  - [Arduino Blog: 13-note MIDI laser harp](https://blog.arduino.cc/2016/05/04/play-some-tunes-on-a-13-note-midi-laser-harp/)
  - [Laser Harp on Arduino Project Hub](https://projecthub.arduino.cc/giovanni_canone/laser-harp-b39507)
  - [Catherine Maglione's build writeup](https://catherinemaglione.com/project/laser)

### 6.2 Stepper-based percussion (auto-drummer, solenoid drum)

- **What:** Electromagnetic solenoids striking physical surfaces (drum heads, metal bars, wine glasses) under MIDI control.
- **Why it's great:** Easy to make weird, organic sounds. Combination of 3D-printed linkage + simple 12V drivers.

### 6.3 Xenakis-style stochastic music box

- **What:** Stepper-driven disc with pins plucking a tuned comb (like a music box, but programmable). Combine with probability logic in firmware to make algorithmic compositions.

---

## 7. Ambient / connected displays

These are the "lives on a shelf, talks to the internet" category — mostly electronics + mechanical case.

### 7.1 E-Ink Weather Display

- **What:** ESP32 pulling weather + calendar + air quality from APIs and rendering on a 4.2" or 7.5" e-ink panel. **Months of battery life**.
- **Why it's great:** Always-on display with zero backlight, looks like paper. The case is the only mechanical part.
- **Complexity:** Low (electronics) + Medium (if you design a beautiful 3D-printed/laser-cut case).
- **Cost:** $40–$100.
- **Time:** 1–3 weekends.
- **Refs:**
  - [lmarzen/esp32-weather-epd](https://github.com/lmarzen/esp32-weather-epd) — the canonical open implementation.
  - [CircuitDigest: Desktop Weather Station with ESP32 + E-Ink](https://circuitdigest.com/microcontroller-projects/desktop-weather-station-using-esp32)

### 7.2 Smart / Magic Mirror

- **What:** Two-way mirror + thin display panel (ideally USB-C powered 15.6" 1080p) + Raspberry Pi running MagicMirror².
- **Why it's great:** Wall-mounted home dashboard. **Mostly a software + frame-building project** — minimal electronics.
- **Complexity:** Low-Medium. Lots of community modules (calendar, transit, weather, news).
- **Cost:** $150–$400 depending on display size.
- **Time:** 1–3 weekends.
- **Refs:** [magicmirror.builders](https://magicmirror.builders/) · [Raspberry Pi slim smart mirror tutorial](https://www.raspberrypi.com/tutorials/how-to-build-a-super-slim-smart-mirror/)

### 7.3 Connected art frame (e-ink or OLED behind a picture frame)

- **What:** Take an existing art print, add a thin e-ink/OLED behind a cutout, fetch art from an API daily. "Today's painting" frame.

### 7.4 Mechanically animated clock displays (servo-arm clock, flip-disc clock)

- Already covered above (sections 1.1, 1.2). Cross-listed here because the "always-on wall display + WiFi time sync + ambient feel" is the common thread.

---

## 8. How to pick

Match the project to **what you want to learn**, not what's most impressive. The biggest project graveyard is people starting a moving-pixel clock because the videos are cool, hitting week 3 of stepper tuning, and abandoning it.

### If you want to learn **power electronics & high-current drivers**
- Flip-dot display (1.1) — you will learn current limiting, bulk caps, flyback, level shifting, by fire.
- Nixie clock (2.1) — 170 V boost converter + HV safety practice.

### If you want to learn **multi-channel stepper / motion control firmware**
- Moving pixel clock (1.2) — AccelStepper at scale; or build your own Bresenham-based step queue.
- Sisyphus / ZenXY sand table (3.1) — GRBL or Marlin kinematics, pattern buffering, leveling.

### If you want to learn **mechanism design / kinematics**
- Strandbeest (5.1) — 4-bar linkage math.
- Cam automata (3.3) — cam profile design, follower geometry.
- 6-DOF arm (5.3) — inverse kinematics, Jacobian.

### If you want a **fast win** (one weekend, finish something)
- POV propeller clock (1.4).
- Strandbeest desk toy (5.1, hand-cranked).
- Marble machine (3.2, print-and-assemble).

### If you want to learn **firmware + WiFi + API integration**
- E-ink weather display (7.1).
- Magic mirror (7.2).
- Any of the clocks with NTP + web UI.

### If you want to learn **art / aesthetic fabrication**
- V-plotter (4.2) — the lines themselves become the art.
- Sand table (3.1) — algorithmic sculpture.
- Word clock variations (2.2) — material science (diffusers, stencils).

---

## 9. Cameras & imaging

The cheapest path to a WiFi-connected camera is an ESP32 camera board + a printed enclosure. See the dedicated deep-research note: [[ESP32 + 3D-Printed Camera Projects]] — board/sensor selection, streaming constraints (MJPEG-only on S3), enclosure designs, and the power-engineering realities of trail cams.

Quick picks from that note:
- **Printer monitoring cam** (fastest win): AI-Thinker ESP32-CAM (~$7) + snap-fit case + ESPHome — the cheapest documented OctoPrint camera.
- **Portable timelapse cam:** XIAO ESP32-S3 Sense + magnetic-base housing, captures to SD, battery-pad powered.
- **Showpiece:** retro point-and-shoot digital camera on XIAO S3 Sense (AVI with sound, on-device playback, wireless file manager).
- **Engineering challenge:** PIR-triggered wildlife/trail cam — board-level deep sleep is the trap; expect to hard-switch power rather than trust ESP32 sleep modes.

---

## Open questions for future notes

- Magnetic pixel display (MagPixel) — practical feasibility with Bambu-class printers and magnetic PLA quality.
- Split-flap → flip-disc transition — is a flip-disc clock worth it after split-flap?
- Real-time GRBL on ESP32 vs Arduino Mega for the sand table.
- Galvanometer-based laser systems vs multiple discrete laser diodes for the harp.
