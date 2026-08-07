---
title: "Open-weight LLM Weekly Recap — week of 2026-08-03–2026-08-09"
date: 2026-08-08
week_start: 2026-08-03
week_end: 2026-08-09
release_count: 1
tracker_total: 16
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-08-03–2026-08-09 (1 release)

### 🏆 Headline

Ant Group's Ling-3.0-flash — the smallest active-parameter agentic MoE yet (5.1B active of 124B total) under an MIT license, claiming parity with its own Ring-2.6-1T flagship (1T/63B) at 1/12 the active params, with independent BenchLM FP8 evals confirming the headline scores.

### 📊 Releases (ranked by impact)

───────────────

**Ant Group Ling-3.0-flash** (124B, 5.1B active MoE — 512 routed + 1 shared expert, MIT, 2026-08-04)

• Key: GPQA-D 85.0 (84.0 BenchLM-verified) · AIME 2026 93.2 · SWE-bench Pro 56.6 · IFBench 74.5 (73.4 verified) · SciCode 41.2 (40.4 verified) · Terminal-Bench 2.0 59.3 · ArcPrize 68.8
• Beats: Ring-2.6-1T (Ant's own 1T/63B flagship) on efficiency — vendor-claimed parity at 1/12 active params
• Loses to: DeepSeek V4-Flash on AIME 2026 (93.2 vs 97.0) and GPQA-D (85.0 vs ~88); Solar Open 2 250B on GPQA-D (86.3); Laguna S 2.1 on SWE-bench Pro (59.4)
• Why it matters: Smallest active-param agentic MoE on the market, with native hybrid-linear KDA+MLA attention (5:1), 262K ctx, 10K+ agentic training environments, and SGLang HiCache+Mooncake serving (TTFT −60–80%) — a serious efficiency play for local/edge agent workloads.
🔗 https://huggingface.co/inclusionAI/Ling-3.0-flash · https://x.com/AntLingAGI/status/2080351022028095681 · https://www.businesswire.com/news/home/20260726584441/en/Ant-Group-Unveils-Ling-3.0-Flash-Delivering-Top-Tier-Performance-at-a-Fraction-of-the-Parameter-Scale · https://benchlm.ai/models/ling-3-0-flash

### 📈 Trends this week

• Second single-release week in a row — cadence has cooled after the late-July burst (Kimi K3, DeepSeek V4-Flash, Solar Open 2)
• Efficiency-first small-active MoE keeps winning: 5.1B active is the smallest agentic MoE recorded in the tracker, and hybrid linear attention (KDA+MLA) mirrors Solar Open 2's hybrid-attention play
• License trend holds permissive: MIT continues to dominate recent Chinese-lab releases (Ling-3.0-flash, DeepSeek V4-Flash, LongCat-2.0)

### 🔭 Looking ahead

Ant followed an API-first pattern (API live Jul 23, weights Aug 4), so a larger Ling-3.x non-flash flagship may follow. DeepSeek's V4 line has dropped roughly monthly (0731 release last week), so a V4-Pro/Max update is plausible in the coming weeks.

### Tracker

16 total releases · file at /home/pi/projects/llm-tracker/releases.md

## See also

- [[welcome]]
- /home/pi/projects/llm-tracker/releases.md
