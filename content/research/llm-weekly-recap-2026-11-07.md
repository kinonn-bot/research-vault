---
title: "Open-weight LLM Weekly Recap — week of 2026-11-02–2026-11-08"
date: 2026-11-07
week_start: 2026-11-02
week_end: 2026-11-08
release_count: 1
tracker_total: 78
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

🗓 Open-weight LLM week of 2026-11-02–2026-11-08 (1 release)

## Headline

Moonshot's Kimi K3.1 Pro is the standout — and only — release this week: the first K3.1-series drop posts an Artificial Analysis Intelligence Index of 55, the highest open-weight reading ever recorded, closing to within a point of Claude Opus 5.5 on Terminal-Bench 4.0 (65.7 vs 66.4).

## Releases (ranked by impact)

───────────────
**Moonshot AI Kimi K3.1 Pro** (2.8T total / 104B active MoE, 896 experts; Kimi K3.1-Pro License — MIT-style, MaaS >$20M rev needs separate agreement; 2026-11-04)
• Key: Terminal-Bench 4.0 65.7 · DeepSWE v1.1 75.5 · GDPval-AA v2.1 Elo 1846 · AA Intelligence Index 55
• Beats: GLM-5.3 on TB 4.0 (65.7 vs 41.8) and GDPval Elo (1846 vs 1650); prior Kimi K3 on AA Index (55 vs ~44)
• Loses to: DeepSeek V4.1-Flash-1017 on DeepSWE v1.1 (75.5 vs 77.0); Opus 5.5 narrowly on TB 4.0 (65.7 vs 66.4) and GDPval Elo (1846 vs 1866)
• Why it matters: Post-trained K3 with MXFP4 QAT and 1M context takes the open-weight crown outright — a single-lab step-change rather than an incremental refresh.
🔗 [HF: moonshotai/Kimi-K3.1-Pro](https://huggingface.co/moonshotai/Kimi-K3.1-Pro) · [Kimi blog](https://www.kimi.ai/blog/kimi-k3-1-pro) · [Vals AI](https://www.vals.ai/models/kimi_kimi-k3.1-pro)

## Trends this week

• Quiet week by volume (1 release vs the usual multi-release pace), but the single drop is the highest-scoring open model to date — quality over quantity.
• Frontier open weights are now benchmarked head-to-head against closed flagships (Opus 5.5, GPT-6 Astra) as a matter of course, not exception.
• License trend holds: MIT-style open-weight licenses with MaaS revenue thresholds (K3.1-Pro's $20M clause) remain the Chinese-lab default over pure Apache 2.0.

## Looking ahead

No new rumors surfaced beyond the tracker this week — the K3.1 series suggests further Moonshot iterations are likely; watch for DeepSeek and GLM responses to the new AA Index bar of 55.

**Tracker:** 78 total · file at /home/pi/projects/llm-tracker/releases.md

## See also

- [[welcome]]
- Tracker source: `/home/pi/projects/llm-tracker/releases.md`
