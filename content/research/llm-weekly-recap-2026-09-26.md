---
title: "Open-weight LLM Weekly Recap — week of 2026-09-21–2026-09-27"
date: 2026-09-26
week_start: 2026-09-21
week_end: 2026-09-27
release_count: 1
tracker_total: 41
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-09-21–2026-09-27 (1 release)

### Headline

A single-release week, but a heavyweight: **Xiaomi MiMo-V2.6 Pro-RL** takes the #1 open-weights slot on Artificial Analysis' Intelligence Index (46.32, tied with Grok 4.7 and ahead of DeepSeek V4.1-Flash at 39 and GLM-5.3 at ~40) — the first time a consumer-hardware maker tops the open frontier leaderboard. It also shipped the most transparent post-training run yet: the entire RL phase was streamed live ("You Only RL Once", ~750K trajectories, ~$2.6M of compute), with the full RL framework and 7,000+ environments open-sourced alongside the weights. Caveat carried by the tracker: community spot-checks were mixed (benchmaxxing accusations, a Reddit thread deleted after 4h), so independent evals will decide whether #1 sticks.

### Releases (ranked by impact)

───────────────

**Xiaomi MiMo-V2.6 (Pro-RL & Flash-RL)** (Pro 1.02T total / 42B active MoE; Flash 309B / 15B active MoE; both omnimodal, 1M ctx; MIT; 2026-09-22)

• Key: AA Intelligence Index 46.32 (Pro, #1 open-weights — vs DS-V4.1-Flash 39, GLM-5.3 ~40, tied Grok 4.7 46) · DeepSWE v1.1 Pro 71.9 / Flash 67.9 · Terminal-Bench 2.1 Pro 89.9 / Flash 87.6 · CyberGym Pro 94.0 / Flash 95.1 · Toolathlon-Verified 76.9 · GDPval-AA v2.1 Elo 1673 (all vendor-reported except the AA index)
• Beats: DeepSeek V4.1-Flash on AA Intelligence Index (46.32 vs 39) and CyberGym (94.0 vs 88.1); GLM-5.3 on Terminal-Bench 2.1 (89.9 vs 88.2)
• Loses to: DeepSeek V4.1-Flash on DeepSWE v1.1 (71.9 vs 74.2) and Terminal-Bench 2.1 (90.6 vs 89.9); Claude Opus 5 on Terminal-Bench 4.0 (34.9 vs 49.0); slow-ish 54.5 tok/s and 140M tok/task verbosity per independent AA runs
• Why it matters: first open frontier release to publish its whole post-training recipe (live-streamed GRS+GAR agentic-graded RL + MOPD2 distillation, 7,000+ environments, distill checkpoint) — and Flash undercuts DeepSeek's price at $0.14/$0.28 per M tok
🔗 https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Pro-RL · https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Flash-RL · https://mimo.xiaomi.com/mimo-v2-6 · https://artificialanalysis.ai/models/mimo-v2-6-pro · https://venturebeat.com/technology/better-than-deepseek-xiaomis-mimo-v2-6-pro-debuts-as-the-top-open-weights-model-in-the-world-alongside-cheaper-v2-6-flash

───────────────

### Trends this week

• Quiet week — 1 tracked release; Xiaomi joins the frontier-MoE tier (1T-class, MIT) alongside DeepSeek, Zhipu, Tencent and Ant, the first non-LLM-lab entrant at this scale.
• Open post-training is becoming a product: this drop shipped weights + tech report + RL framework + 7,000 environments + a distill model. Benchmark transparency runs both ways though — live-streamed RL invites scrutiny, and the community pushed back within hours.
• Pricing pressure continues at the frontier: MiMo Flash ($0.14/$0.28 per M tok) lands as the 2nd-cheapest frontier API, right behind DeepSeek's cache-hit pricing.

### Looking ahead

DeepSeek **V4.1-Pro** remains the clearest near-term signal — V4-Pro traffic has been rerouted to V4.1-Flash pending its release (per tracker). After the benchmaxxing flare-up, independent llm-stats/BenchLM rows for MiMo-V2.6 will be worth watching.

### See also

- [[welcome]]
- Tracker: `/home/pi/projects/llm-tracker/releases.md` (41 cumulative releases)