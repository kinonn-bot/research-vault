---
title: "Open-weight LLM Weekly Recap — week of 2026-08-10–2026-08-16"
date: 2026-08-15
week_start: 2026-08-10
week_end: 2026-08-16
release_count: 4
tracker_total: 21
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-08-10–2026-08-16 (4 releases)

### 🏆 Headline

Alibaba open-released Qwen3.8-2.4T-A95B — the first ever Qwen-Max-class open weights (2.4T total / 95B active MoE) — and it immediately takes the open-weight IFBench crown (82.8), beats GPT-5.6 Sol on PaperBench (93.0 vs 90.5), and posts GPQA-D 92.6 within a point of last week's Kimi K3. The biggest open-weight release since Kimi K3's 2.8T debut, and the strongest sign yet that Chinese frontier labs are shipping their flagship-tier weights.

### 📊 Releases (ranked by impact)

───────────────

**Alibaba Qwen3.8-2.4T-A95B** (2.4T, 95B active MoE — 512 experts, Qwen3.8-Max License (MIT-style; commercial OK, brand-display >100M MAU / MaaS >$50M rev clauses), 2026-08-12)

• Key: GPQA-D 92.6 · IFBench 82.8 (best open-weight) · PaperBench 93.0 · Terminal-Bench 2.1 86.6 · HLE w/tools 56.2 · WideSearch 81.9 · LongBench v2 66.3 · MRCR 256K 92.9
• Beats: DeepSeek V4-Flash on GPQA-D (92.6 vs 88.9), IFBench (82.8 vs ~76), Terminal-Bench 2.1 (86.6 vs 82.7); GPT-5.6 Sol on PaperBench (93.0 vs 90.5); Inkling on IFBench (82.8 vs 79.8)
• Loses to: Kimi K3 on GPQA-D (92.6 vs 93.5)
• Why it matters: First open-weights release of a Qwen-Max-class model — hybrid Gated DeltaNet + attention, 262K native ctx extensible to 1M, MTP, reasoning_effort — bringing a 2.4T-class frontier model to the open ecosystem for $1/M-tok-class economics.
🔗 https://huggingface.co/Qwen/Qwen3.8-2.4T-A95B · https://huggingface.co/Qwen/Qwen3.8-2.4T-A95B-FP8 · https://qwen.ai/blog?id=qwen3.8 · https://blog.roboflow.com/qwen3-8-max/ · https://benchlm.ai/models/qwen3-8-max

───────────────

**Meta Muse Glimmer-30B** (29.6B dense incl. 1.8B ViT-G/14 vision encoder, Apache 2.0, 2026-08-10)

• Key: MCP Atlas 75.5 · DeepSearch QA 74.6 · SWE-bench Verified 76.0 · SWE-bench Pro 51.2 · AIME 2026 94.7 · IFBench 77.0 · GPQA-D (AA) 83.5 · Gaia2 43.3
• Beats: Gemma4-31B on MCP Atlas (75.5 vs 54.2), SWE-bench Verified (76.0 vs 66.6), AIME 2026 (94.7 vs 89.2)
• Loses to: Qwen3.6-27B on SWE-bench Verified (76.0 vs 77.2); beats it on DeepSearch QA (74.6 vs 71.1) and MCP Atlas (75.5 vs 62.5)
• Why it matters: Meta's first Apache 2.0 agentic multimodal in the Muse line, distilled from Muse Spark and purpose-built for local agents — DFlash drafter hits 233 tok/s on RTX 5090 (3.1×) and the K-Quant-17GB build fits 24GB VRAM.
🔗 https://huggingface.co/meta-models/Muse-Glimmer-30B · https://developer.meta.com/ai/models/muse-glimmer/ · https://llm-stats.com/models/muse-glimmer-30b

───────────────

**NVIDIA Nemotron 3.5 Lightning** (30B, 3B active MoE, OpenMDW-1.1, 2026-08-11)

• Key: PinchBench 85.4 · SWE-bench Verified 51.6 · MMLU-Pro 81.9 · GPQA-D 75.4 · IFBench 71.9 · BrowseComp 37.0 · τ³-Banking 9.3
• Beats: Gemma4-26B-A4B on PinchBench (85.4 vs 74.7); Nemotron 3 Nano on PinchBench (85.4 vs 66.1)
• Loses to: Qwen3.6-35B-A3B on PinchBench (85.4 vs 88.1), SWE-bench Verified (51.6 vs 70.1), MMLU-Pro (81.9 vs 85.6)
• Why it matters: An execution-layer model for long-running agents (harness-optimized for OpenClaw/Hermes Agent), trading raw benchmark score for ~4× output speed via DFlash/DSpark speculative decoding — NVFP4+BF16 checkpoints at $0.05/$0.20 per M tok, DGX Spark deployable, and OpenMDW-1.1 ships weights + data + recipes.
🔗 https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Lightning-30B-A3B-BF16 · https://developer.nvidia.com/blog/nvidia-nemotron-3-5-lightning-delivers-fast-accurate-specialized-task-execution-for-long-running-agents/ · https://www.lmsys.org/blog/2026-08-11-nemotron-3-5-lightning · https://llm-stats.com/models/nemotron-3.5-lightning-30b-a3b

───────────────

**Ant Group Ling-3.0-tiny** (7.9B, 1.3B active MoE — 128 experts, MIT, 2026-08-10)

• Key: AA Intelligence Index 25 / AA Agentic Index 16 (independent) · Terminal-Bench 2.1 (AA protocol) · 160+ tok/s output, ~18s end-to-end for 500-tok response incl. reasoning
• Beats: nothing in its class tracked yet — it's the smallest Ling sibling (1/16 of Ling-3.0-flash's 124B total params)
• Loses to: Ling-3.0-flash on every absolute metric, by design — this is the edge/tiny tier
• Why it matters: Sub-8B agentic reasoning with native thinking toggle, 3:1 KDA-MLA hybrid-linear attention, 262K ctx, and BF16/FP8/INT4 quants — 86–90 tok/s on an M4 Pro (~8.3GiB peak at 8K ctx) makes it a serious on-device option.
🔗 https://huggingface.co/inclusionAI/Ling-3.0-tiny · https://modelscope.cn/organization/inclusionAI · https://openrouter.ai/inclusionai/ling-3.0-tiny:free

### 📈 Trends this week

• 3 of 4 releases are sub-100B efficiency/edge models (30B, 30B, 7.9B) — the local-agent tier is where the volume is; the one frontier release is Qwen's 2.4T MoE
• Chinese labs keep the open-weights momentum: Alibaba and Ant both shipped this week, and Qwen's Max-class open release directly follows Moonshot's Kimi K3 (2.8T, modified MIT) the week prior
• License variety is widening: Apache 2.0 (Meta), MIT (Ant), OpenMDW-1.1 with weights+data+recipes (NVIDIA), and a MIT-style Qwen3.8-Max license with usage-tier branding clauses — permissive licensing remains the norm

### 🔭 Looking ahead

Qwen's FP8 build of the 2.4T is already on HF, so expect smaller distilled/quantized Qwen3.8 family members (27B-class) to land shortly. DeepSeek's V4 line keeps point-releasing (V4-Flash-0731 last week, V4-Pro-0813 GA this week), so further V4 updates are likely before the next frontier drop.

### Tracker

21 total releases · file at /home/pi/projects/llm-tracker/releases.md

## See also

- [[welcome]]
- /home/pi/projects/llm-tracker/releases.md
