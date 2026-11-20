---
title: "Open-weight LLM Weekly Recap — week of 2026-11-16–2026-11-22"
date: 2026-11-21
week_start: 2026-11-16
week_end: 2026-11-22
release_count: 1
tracker_total: 81
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Headline

Quiet week — a single release: Tencent distilled its Hy4 flagship into **Hy4-flash**, a 220B MoE that keeps most of the agentic capability at roughly 1/13th the task cost and half the output tokens.

## Releases (ranked by impact)

---

**Tencent Hy4-flash** (220B, 12B active MoE + 64B Engram, Tencent Hy License 1.0, 2026-11-16)
- Key: WorkIndex 42.1 (vs Hy4-preview 39.7) · APEX-Agents 63.1 · OSWorld 68.1 · HLE w/tools 55.2 · DeepSWE 64.6 · TB-4.0 19.2 · base MMLU 88.7 (vs Hy4 base 91.6)
- Beats: Hy4-preview on WorkIndex at ~1/13 task cost; self-distillation cuts output tokens ~50%
- Loses to: full Hy4-preview/Hy4 base on raw capability (base MMLU 88.7 vs 91.6); no independent leaderboard runs yet
- Why it matters: LatentMoE + hybrid sparse/SWA attention + DFly2 speculative decoding (>150 tok/s) makes this Tencent's efficiency play — flagship-class agency at flash pricing.
- Sources: [HF: tencent/Hy4-flash](https://huggingface.co/tencent/Hy4-flash) · [Blog](https://hy.tencent.ai/research/hy4-flash) · [BenchLM](https://benchlm.ai/models/hy4-flash)

## Trends this week

- Only one tracked release — the quietest week since the tracker began daily coverage; labs appear to be in a post-flagship digestion phase after Kimi K3.1 Pro (Nov 4) and LongCat-2.5 (Nov 9).
- Efficiency over scale: Hy4-flash continues the distillation trend (cf. DeepSeek V4.1-Flash-1017 snapshot, MiniMax M3.1-Flash) — same-capability-cheaper is the current battleground.
- License watch: Tencent's Hy License 1.0 (separate agreement above $50M MaaS revenue / 100M MAU) joins the growing club of revenue-gated "open" licenses alongside MiniMax Community and Kimi K3.1-Pro terms.

## Looking ahead

Watch for independent Artificial Analysis / BenchLM verification rows on Hy4-flash, LongCat-2.5, and Decider v1.3 — all still vendor-reported — plus any response from DeepSeek or Zhipu to Tencent's efficiency move.

## Tracker

81 total releases tracked · source file at `/home/pi/projects/llm-tracker/releases.md`

## See also

- [[welcome]]
- Tracker source: `/home/pi/projects/llm-tracker/releases.md`
