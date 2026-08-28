---
title: "Open-weight LLM Weekly Recap — week of 2026-08-24–2026-08-30"
date: 2026-08-29
week_start: 2026-08-24
week_end: 2026-08-30
release_count: 3
tracker_total: 29
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-08-24–2026-08-30 (3 releases)

### 🏆 Headline

Zhipu (Z.ai) shipped GLM-5.3-Flash under MIT — an independent Artificial Analysis Intelligence Index of 57 that edges out DeepSeek-V4-Pro (53) and sits just behind Kimi K3 (60), while the first native-multimodal GLM-5 costs roughly ~1/10 of GLM-5.2. It's the strongest signal yet that the "Flash" efficiency tier is now genuinely frontier-grade.

### 📊 Releases (ranked by impact)

───────────────

**Zhipu (Z.ai) GLM-5.3-Flash** (320B, 18B active MoE — natively multimodal, 1M ctx, MIT, 2026-08-26)

• Key: AA Intelligence Index 57 (independent) · Terminal-Bench 2.1 84.3 · DeepSWE 63.4 · Toolathlon Verified 78.4 · base MMLU 88.1
• Beats: DeepSeek-V4-Pro on AA Index (57 vs 53); GLM-5.2 on Terminal-Bench 2.1 (84.3 vs 81.0), DeepSWE (63.4 vs 46.2), Toolathlon (78.4 vs 59.9); Claude Opus 4.8 on Toolathlon (78.4 vs 76.2)
• Loses to: Kimi K3 on AA Index (57 vs 60); Opus 4.8 on Terminal-Bench 2.1 (84.3 vs 85.0)
• Why it matters: First native-multimodal GLM-5 with hybrid sparse+linear attention at ~1/10 GLM-5.2 cost — MIT-licensed and independently verified near the top of the open ecosystem.
🔗 https://huggingface.co/zai-org/GLM-5.3-Flash · https://z.ai/blog/glm-5.3-flash

───────────────

**Alibaba Qwen3.8-Flash-Next** (125B, 6B active MoE + 51B n-gram embedding + 4B MTP — multimodal, Qwen Community License 1.0, 2026-08-26)

• Key: GPQA-D 91.7 · LiveCodeBench v6 91.9 · SWE-bench Pro 62.5 · DeepSWE 58.7
• Beats: Qwen3.8-27B on GPQA-D (91.7 vs 89.2), LiveCodeBench v6 (91.9 vs 90.3); DeepSeek-V4-Flash on GPQA-D (91.7 vs 90.8), SWE-bench Pro (62.5 vs 56.0), DeepSWE (58.7 vs 54.4)
• Loses to: DeepSeek-V4-Flash on LiveCodeBench v6 (91.9 vs 90.6 — effectively a tie)
• Why it matters: A Qwen4-architecture preview (GDN+QSA, Gated Residual, n-gram embedding) that delivers near-frontier agentic coding from only 6B active params at ~1/9 the training cost of Qwen3.7-Plus.
🔗 https://huggingface.co/Qwen/Qwen3.8-Flash-Next · https://qwen.ai/blog?id=qwen3.8-flash-next

───────────────

**IBM Granite-4.2 (3B/8B/30B)** (3B / 8B / 30B dense reasoning, Apache 2.0, 2026-08-25)

• Key: GPQA 66.4 (30B) · LiveCodeBench v6 75.8 · AIME25 89.2 · SWE-bench Verified 57.0
• Loses to: Muse Glimmer-30B on GPQA (66.4 vs 83.5), SWE-bench Verified (57.0 vs 76.0), AIME25 (89.2 vs 94.7); Qwen3.8-27B on GPQA (66.4 vs 89.2), LiveCodeBench v6 (75.8 vs 90.3)
• Why it matters: IBM's first Granite with native chain-of-thought reasoning plus thinking/non-thinking/low-effort modes — the enterprise entry point, competitive on math (AIME25 89.2) while trailing small-model leaders on general reasoning.
🔗 https://huggingface.co/collections/ibm-granite/granite-42-language-models · https://huggingface.co/blog/ibm-granite/granite-4-2

### 📈 Trends this week

• The "Flash" efficiency tier is where the action is: 2 of 3 releases are sub-20B-active MoE models (GLM-5.3-Flash 18B, Qwen3.8-Flash-Next 6B) delivering frontier-adjacent scores at a fraction of the cost.
• Agentic coding now dominates the benchmark narrative — SWE-bench Pro, DeepSWE, Terminal-Bench, and Toolathlon are the lead metrics for every release this week, not general knowledge.
• Licenses remain permissive and mixed: MIT (GLM-5.3-Flash), Qwen Community License (Qwen3.8-Flash-Next), and Apache 2.0 (IBM Granite) — no restrictive/non-commercial license appeared.

### 🔭 Looking ahead

The "Flash-Next" and "Flash" naming plus the "Qwen4-arch preview" tag point to bigger siblings in flight — expect a full Qwen4 (non-Flash) and a GLM-5.3-Pro/Ultra tier to land after these efficiency previews. Keep an eye on the tracker for the DeepSeek V4 line, which has been steadily point-releasing.

### Tracker

29 total releases · file at /home/pi/projects/llm-tracker/releases.md

## See also

- [[welcome]]
- /home/pi/projects/llm-tracker/releases.md
