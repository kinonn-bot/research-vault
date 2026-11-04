---
title: "Personal Voice Recorder (Pocket AI-style) — Android App Research"
date: 2026-11-04
tags: [research, android, stt]
---

# Personal Voice Recorder (Pocket AI-style) — Android App Research

Goal: a personal Android voice-recorder app in the style of the Pocket AI product —
record anywhere, get transcript + summary + action items, English-first with Mandarin bonus.
Researched 2026-11-04. Sources inline at the bottom.

## 1. Pocket AI product reference (heypocket.com)

Pocket AI is a recording **card** by Open Vision Engineering (San Francisco), on sale since 2025
(~$11M raised June 2026 per TechCrunch).

- **Hardware:** magnetically snaps onto phone back; 3 microphones (dual studio mics for
  in-person + contact mic for phone calls); ~52 g; 64 GB storage; quoted ~4 days battery;
  one side-button press to record, works offline, app syncs later.
- **Apps:** iPhone + Android, plus web / Mac / Windows.
- **Pipeline:** record → app pulls audio → cloud transcript + summary + action items;
  "Ask Pocket" Q&A over recordings; speaker detection; integrations (Todoist, Google Tasks,
  Notion, Google Drive, Linear, Asana…).
- **Pricing (US store, Oct 2026):** card $129 (list $199). Free plan included: unlimited
  transcription at standard accuracy, summaries kept 30 days, 3 Ask-Pocket chats/day.
  Pocket Pro $239.88/yr ($19.99/mo billed yearly) or $29.99/mo: highest accuracy, speaker
  names, live transcript, email summaries, PDF/DOCX/Markdown export, full integrations.
- **Takeaway for us:** the hardware is a convenience (always-on-phone, one-press, call mic).
  Everything it does in software — record, transcribe, summarize, Q&A, export — is reproducible
  as a pure Android app. No hardware needed for v1. Main gap vs Pocket: vibration/contact call
  capture (Android call-recording restrictions apply — see §4).

## 2. Open-weights STT models (Nov 2026 landscape)

Benchmark figures below are Open ASR Leaderboard / vendor numbers (WER = word error rate,
lower is better; RTFx = audio-seconds per compute-second, higher is faster).

| Model | Params | WER (EN) | Langs | Licence | Note |
|---|---|---|---|---|---|
| NVIDIA Canary-Qwen 2.5B | 2.5B | **5.63%** | English only | CC-BY-4.0 | Best EN accuracy; NeMo; server GPU |
| IBM Granite Speech 3.3 8B | ~9B | 5.85% | EN ASR + multi-lang translation | Apache 2.0 | Enterprise/server only |
| Whisper Large V3 | 1.55B | 7.4% | **99+** | MIT | Best all-rounder, huge ecosystem |
| Whisper Large V3 Turbo | 809M | 7.75% | 99+ | MIT | ~216x RTFx, good server default |
| Distil-Whisper Large V3 | 756M | ≈ V3 | English only | MIT | 5–6× faster than V3 |
| Parakeet TDT 1.1B | 1.1B | ~8.0% | English (v3: 25 EU langs) | CC-BY-4.0 | **RTFx >2,000**, batch king |
| Moonshine | tiny | higher | EN | permissive | Built for edge/mobile latency |
| SenseVoice-Small | **234M** | strong ZH/Cantonese | zh, yue, en, ja, ko | FunASR licence (see ⚠️) | Non-autoregressive, fast; +emotion/events |
| Dolphin / Dolphin-CN-Dialect | base/small | strong ZH + dialects | 40 Eastern langs, 22 CN dialects | **Apache 2.0** | E-Branchformer; streaming variants (May 2026) |
| Paraformer-large (FunASR zh-cn recipe) | large | top-tier ZH | zh (+en punc) | FunASR ecosystem | Classic highest-accuracy Chinese pick, with VAD + punctuation models |

⚠️ **Licence caveat — SenseVoice:** code is MIT, but weights fall under the FunASR Model Open
Source Licence Agreement; maintainers clarify commercial use is permitted with attribution
(model-name requirements, §2.2), but read the licence text before shipping. Dolphin is the
cleaner Apache 2.0 alternative for Mandarin; Whisper/Parakeet/Moonshine are MIT or CC-BY-4.0
(attribution only).

### Recommendation for this project

- **Server/cloud transcription:** Whisper Large V3 Turbo (multilingual incl. Mandarin,
  MIT, big ecosystem) — or Parakeet TDT if batch throughput matters. Both run via
  faster-whisper / NeMo on GPU.
- **On-device (offline) transcription:** non-negotiable for a recorder (planes, basements,
  privacy). Options below; SenseVoice-Small (234M, EN+ZH) or a quantized Whisper
  small/base are the pragmatic bundles. Dolphin-CN-Dialect-small if dialect coverage wins.
- **Mandarin strategy:** single multilingual model (Whisper Turbo / SenseVoice / Dolphin)
  beats juggling separate EN + ZH models — important for Singapore code-switching
  (English ↔ Mandarin in one sentence). Test shortlisted models on code-switched audio
  before committing.

## 3. Android on-device STT feasibility

- **sherpa-onnx** (k2-fsa, actively maintained — v2.0.1 Oct 2026): the pragmatic choice.
  ONNX Runtime, fully offline, first-class **Android** (+ iOS/HarmonyOS) support with
  Java/Kotlin APIs; ships Whisper, Paraformer, SenseVoice, Zipformer model builds plus
  VAD, speaker diarization, punctuation, TTS. Precedent apps exist (offline captioning,
  voice-typing apps bundling Whisper-base via sherpa-onnx).
- **whisper.cpp:** C/C++ via JNI, quantized GGUF models run on mid-range phones
  (base/small real-time-ish on CPU; large needs flagship or server). Larger integration
  effort than sherpa-onnx but biggest community.
- **Moonshine:** designed for edge; worth a look if live-caption latency becomes the goal.
- **Plan:** bundle one small model in-APK (e.g. Whisper base/small-int8 or SenseVoice-Small
  ONNX, tens-to-low-hundreds MB — consider Play Asset Delivery / download-on-first-run),
  transcribe on-device by default, offer server-side Turbo re-transcription as a
  "high accuracy" option. Chunked inference (10–30 s windows + VAD) keeps memory flat.

## 4. Android app architecture (v1 outline)

```
UI (Jetpack Compose, MVI/MVVM)
 │  Recordings list · Player · Transcript view · Summary/Actions · Ask (chat) · Settings
 ▼
ForegroundService recorder (AudioRecord/AAudio → WAV/FLAC/Opus, MediaStore + Room index)
 │  + VAD-based segmentation (sherpa-onnx Silero VAD)
 ▼
Transcription worker (WorkManager) — on-device sherpa-onnx first, server fallback queue
 ▼
Post-processing — punctuation restore, diarization (Pro-tier?), language ID (en/zh)
 ▼
LLM layer — summary + action items + Ask Q&A (cloud API with user key in v1;
           on-device small LLM later). Never train on user audio.
 ▼
Export/share — TXT/MD/PDF, integrations (Google Tasks/Drive, Todoist…)
```

- **Key Android specifics:** Foreground Service with microphone foreground-service type
  (+ persistent notification); `RECORD_AUDIO` runtime permission; battery-optimisation
  exemption prompt for long recordings; Scoped Storage via MediaStore; Room for metadata;
  WorkManager for deferred upload/transcription; Hilt + Coroutines/Flow; minSdk 29–31
  (covers sherpa-onnx Android 11+ precedent).
- **Call recording:** Android restricts direct call audio on modern versions (privacy/PDPA);
  Pocket's contact-mic trick is hardware. v1 should target mic/in-person recording +
  speakerphone-with-consent, and document Singapore PDPA consent expectations.
- **Privacy posture (differentiator vs Pocket/PLAUD):** default offline transcription,
  user-held API keys, no training on recordings, export-and-delete. Pocket processes in
  the US cloud; local-first is our edge.
- **Testing priorities:** code-switched EN/ZH accuracy, battery drain on 2-h recordings,
  low-end device (e.g. 4 GB RAM) transcription latency, consent UX for shared recordings.

## 5. Suggested build order

1. Recorder service + playback + local storage (usable voice memo, no AI).
2. On-device transcription via sherpa-onnx (bundled small model, EN+ZH).
3. Cloud LLM summaries/action items + Ask (BYO API key).
4. Server-side high-accuracy re-transcription option.
5. Diarization, live transcript, export formats, integrations.

## Sources

- heypocket.com product pages (features, specs, pricing); Ajora Pocket AI review
  (Oct 2026 price table: $129 card, Pro $239.88/yr or $29.99/mo); TechCrunch (June 2026, $11M raise).
- Northflank "Best open source STT 2026" (benchmark table, Jan 2026); AssemblyAI 2026
  open-source STT guide; Gladia 2026 guide; Spokenly/LoroNote Parakeet-vs-Whisper comparisons.
- HF FunAudioLLM/SenseVoiceSmall model card + QwenAudio/SenseVoice GitHub (licence notes);
  DataoceanAI/Dolphin GitHub (Apache 2.0, 40 langs, 22 dialects); FunASR models page
  (Paraformer zh-cn recipe); k2-fsa/sherpa-onnx GitHub + docs (Android/offline).
