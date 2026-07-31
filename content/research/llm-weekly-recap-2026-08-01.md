---
title: "Open-weight LLM Weekly Recap — week of 2026-07-27–2026-08-02"
date: 2026-08-01
week_start: 2026-07-27
week_end: 2026-08-02
release_count: 1
tracker_total: 14
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-07-27–2026-08-02 (1 release)

### Headline

Moonshot's Kimi K3, the world's first open 3T-class model, arrived with 2.8T total parameters and 104B active MoE under a Modified MIT license — it matches the frontier on GPQA and Terminal-Bench while beating GPT-5.6 Sol on BrowseComp.

### Releases (ranked by impact)

---

**Moonshot Kimi K3** (2.8T total / 104B active MoE, Modified MIT, 2026-07-27)

- Key: GPQA 93.5 · Terminal-Bench 88.3 · BrowseComp 91.2 · AA Intelligence Index 57
- Beats: Fable 5 on GPQA (92.6); GPT-5.6 Sol on BrowseComp (90.4); DeepSeek V4-Pro on Terminal-Bench (82.7)
- Loses to: GPT-5.6 Sol on GPQA (94.1) and Terminal-Bench (88.8); Fable 5 on AA Intelligence Index (60)
- Why it matters: First open-weight model to cross 3T parameters, with native multimodal (text+image+video) and 1M context — a milestone for the open ecosystem.
- 🔗 https://huggingface.co/moonshotai/Kimi-K3

### Trends this week

- Single-release week — the daily scan captured only Kimi K3, suggesting a quieter period between major drops
- Kimi K3's Modified MIT license keeps the permissive trend alive for 3T-class models
- MoE architectures continue to dominate at the frontier (104B active out of 2.8T total)

### Looking ahead

No rumored or paper-stage releases were flagged in the tracker's recent entries. The next anticipated drop worth watching is any follow-up from DeepSeek or Qwen, given their cadence.

### Tracker

14 total releases · file at /home/pi/projects/llm-tracker/releases.md

## See also

- [[welcome]]
- /home/pi/projects/llm-tracker/releases.md