---
title: "Open-weight LLM Weekly Recap — week of 2026-09-28–2026-10-04"
date: 2026-10-03
week_start: 2026-09-28
week_end: 2026-10-04
release_count: 1
tracker_total: 42
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-09-28–2026-10-04 (1 release)

### Headline

A single-release week, and it is a specialist rather than a frontier generalist: **NaiveAI Naive-N0.5-Flash** — a 309B / 15.5B-active MIT MoE built on Xiaomi's MiMo-V2.5 base with a 3.25T-token CPT — claims best-open SWE-bench Pro (68.8 vs Qwen3.8-Max 67.7, Hy4-preview 65.7, Nex-N2.5-Max 65.7) and best-open-vendor Agents' Last Exam (32.4 vs DeepSeek V4.1-Flash 31.8), at an aggressive $0.10/$0.40 per M tok. It dropped Sunday Sep 27, just inside this week's 7-day window. Caveat: every number is day-1 vendor-reported (Claude Code harness), and no MMLU/GPQA/HumanEval is published at all.

### Releases (ranked by impact)

───────────────

**NaiveAI Naive-N0.5-Flash** (309B / 15.5B active MoE; hybrid SWA 128-tok sliding window + DSA top-2048, zero full-attention layers; MIT; 2026-09-27)

• Key: SWE-bench Pro 68.8 · DeepSWE v1.1 67.8 · Terminal-Bench 2.1 86.7 · Agents' Last Exam 32.4 · MLE-bench-30 73.7% · PaperBench 63.2 · NL2Repo 71.9 · FrontierSWE v1 78.2 (all vendor-reported, Claude Code 2.1.207 harness, 1M ctx)
• Beats: Qwen3.8-Max on SWE-bench Pro (68.8 vs 67.7); Hy4-preview (65.7) and Nex-N2.5-Max (65.7) on the same bench; DeepSeek V4.1-Flash on Agents' Last Exam (32.4 vs 31.8)
• Loses to: DeepSeek V4.1-Flash on DeepSWE v1.1 (67.8 vs 74.2) and Terminal-Bench 2.1 (86.7 vs 90.6); MiMo-V2.6-Flash on Terminal-Bench 2.1 (87.6) and DeepSWE (67.9)
• Why it matters: first open zero-full-attention frontier-class model aimed at coding + AI-R&D agents, at 1.5–4× cheaper API pricing than its closest competitors — but credibility hinges on independent evals that do not exist yet. NaiveRT claims 2,122 tok/s peak single-stream decode (8 GPUs), 72.4% latency cut vs SGLang speculative round; FP8 ≈ 315GB.
🔗 https://huggingface.co/NaiveAI/Naive-N0.5-Flash · https://huggingface.co/NaiveAI/Naive-N0.5-Flash-FP8 · https://naive.ai/en/research/ · https://github.com/NaiveAI-Labs/Naive-N0.5-Flash · https://x.com/naiveailab/status/2104247060186951725

───────────────

### Trends this week

• Second consecutive single-release week — the majors are quiet ahead of an assumed late-Oct cycle (DeepSeek V4.1-Pro still pending); this week's drop was a coding/AI-R&D specialist, not a generalist.
• Derivative-stack playbook spreading: Naive-N0.5-Flash is a CPT of Xiaomi's MiMo-V2.5 base — Chinese labs increasingly ship on top of each other's open weights rather than pretraining from scratch.
• Attention-design churn: zero full-attention layers (SWA+DSA) joins GDN+QSA (Qwen), DSA (GLM/Hy4), CSA2 (DeepSeek), KDA+MLA (Ant) — dense attention is disappearing from new frontier-class MoEs.
• Frontier price competition keeps sharpening: $0.10 input / $0.01 cache-hit undercuts MiMo-V2.6-Flash ($0.14) and DeepSeek V4.1-Flash ($0.15) on input.

### Looking ahead

DeepSeek **V4.1-Pro** remains the clearest pending item — V4-Pro traffic has been rerouted to V4.1-Flash until it ships. The near-term sanity check to watch: independent llm-stats/BenchLM rows for both Naive-N0.5-Flash and MiMo-V2.6, after September's benchmaxxing flare-up.

### See also

- [[welcome]]
- Tracker: `/home/pi/projects/llm-tracker/releases.md` (42 cumulative releases)