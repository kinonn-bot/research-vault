---
title: "Open-weight LLM Weekly Recap — week of 2026-10-26–2026-11-01"
date: 2026-10-31
week_start: 2026-10-26
week_end: 2026-11-01
release_count: 1
tracker_total: 75
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

🗓 Open-weight LLM week of 2026-10-26–2026-11-01 (1 release)

## Headline

Quiet week at the frontier: the sole new entry is AgentScope's Blink-27B, a niche decision-model (SystemOne/Jev-format) rather than a general chat or coding model — notable for its bidirectional-prompt architecture, but shipping with zero benchmark scores claimed.

## Releases

**AgentScope AI Blink-27B** (28B, Apache 2.0, 2026-10-28)
Key: no benchmark scores claimed in model card (day-0 release) — no Decision Index rows yet.
Beats / loses to: unranked until independent Decision Index evaluation lands; peers to watch are pplx-decider v1.2 (68.09), vLLM-SR d3 (66.3), Turion Jev 31B (66.16).
Why it matters: first decision model to mix bidirectional full-attention layers (whole prompt visible) with causal Gated DeltaNet, plus tool-review and context-compaction roles — an architectural experiment worth tracking once scores arrive.
🔗 [HF: agentscope-ai/Blink-27B](https://huggingface.co/agentscope-ai/Blink-27B) · [GitHub](https://github.com/agentscope-ai/Blink)

## Trends this week

- Decision/Jev-format models now dominate the October intake — 8 of the last ~10 tracker rows are decision models, not general LLMs.
- No large flagship MoE drop this week (last was MiniMax M3.1-Flash, Oct 23); frontier labs appear to be in a post-release eval lull.
- License trend steady: Apache 2.0 remains the default for decision models; MIT for Chinese agentic flagships.

## Looking ahead

No new rumored releases surfaced in the tracker this week. Pending items to watch: independent Decision Index rows for Blink-27B, and the LFM3-family d1-2B board results.

Tracker: 75 total · file at /home/pi/projects/llm-tracker/releases.md

## See also

- [[welcome]]
- Tracker source: `/home/pi/projects/llm-tracker/releases.md`
