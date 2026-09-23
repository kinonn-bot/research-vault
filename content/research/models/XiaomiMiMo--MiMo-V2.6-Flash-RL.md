---
title: "XiaomiMiMo/MiMo-V2.6-Flash-RL"
org: XiaomiMiMo
model_id: XiaomiMiMo/MiMo-V2.6-Flash-RL
date: 2026-09-23
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - multimodal
  - rl
  - long-context
downloads: 13243
likes: 423
license: MIT
pipeline: text-generation
source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Flash-RL
params: 309B (15B active)
context: 1M
architecture: moe (hybrid SWA+GA, no shared experts, MTP)
---

# XiaomiMiMo/MiMo-V2.6-Flash-RL

**One-line:** Cost-optimized V2.6 sibling — 309B total / 15B active, ~DeepSeek-V4.1-Flash-class agentic scores, native omnimodal, 1M ctx, MIT.

⚠ **large** — 309B total params; server-class hardware only (see Efficiency).
⚠ Lab-reported numbers (Xiaomi HF card + blog); see Pro-RL note for the benchmaxxing controversy context. Released Sep 21, 2026.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | — |
| DeepSWE v1.1 (agentic SWE stand-in) | 67.9 | lab |
| ProgramBench | 26.0 | lab |
| MiMo Code Bench (in-house) | 61.2 | lab |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| Toolathlon-Verified | 73.6 | lab |
| AutomationBench v1.0.6 | 52.3 | lab |
| Terminal Bench 2.1 | 87.6 | lab |
| Terminal Bench 4.0 | 28.8 | lab |
| Agents' Last Exam | 27.6 | lab |
| JobBench | 61.2 | lab |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2026 | — | — |

## Efficiency

- **Active params:** 15B (of 309B total; 256 routed experts, 8 active, top-k; 48 layers hybrid full+SWA, 3 MTP next-token-prediction layers)
- **Context length:** 1M tokens
- **VRAM (fp16 rough):** ~618GB fp16 — NOT consumer-runnable; on-disk ~311GB (fp8/bf16 mix), needs multi-GPU + quant. The "Flash" name means cheaper/smaller than Pro, not local.

## What makes it notable

Xiaomi's own appendix positions Flash as the value pick: DeepSWE v1.1 67.9 vs DeepSeek V4.1 Flash's 74.2 and TB2.1 87.6 vs 90.6 (lab table — DeepSeek still edges it on those), but MiMo Flash leads on JobBench (61.2 vs 45.8) and MiMo Code Bench (61.2 vs 60.2). Huge improvement over MiMo-V2.5-Pro (DeepSWE 19.0 → 67.9). Same "You Only RL Once" mixed-reward recipe and 1M-ctx omnimodal stack as Pro, at lower active-param cost per token. Not a realistic local/agent-box model at 309B — the 9B Distill sibling is the local entry point.

## See also

- [[welcome]]
- Source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Flash-RL
- Siblings: [[XiaomiMiMo/MiMo-V2.6-Pro-RL]], [[XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B]]