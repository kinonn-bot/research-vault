---
title: "XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B"
org: XiaomiMiMo
model_id: XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B
date: 2026-09-23
tags:
  - huggingface
  - image-text-to-text
  - coding
  - agentic
  - dense
  - distill
  - sft
  - vision
downloads: 3253
likes: 397
license: MIT
pipeline: image-text-to-text
source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B
params: 9B (dense)
context: 256K
architecture: dense (Qwen3.5-9B base) + vision encoder
---

# XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B

**One-line:** The locally-runnable member of the MiMo-V2.6 family — 9B agentic SFT of Qwen3.5-9B on MiMo-generated data, SWE-bench Verified 61.1, MIT, vision+text.

⚠ Vision-language model (image-text-to-text) — vision encoder present, but it has real published coding/agentic evals, so it qualifies for the coding/agent tracker.
⚠ Lab-reported numbers (HF card, from the MiMo-V2.6 technical report). Avg@3 for code/cyber/visual, avg@1 for general.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified (avg@3) | 61.1 | lab |
| SWE-bench Multilingual | — | — |
| SWE Pro (avg@3) | 44.6 | lab |
| MiMo Code (mini, avg@3, in-house) | 51.6 | lab |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| Toolathlon-Verified (avg@1) | 35.2 | lab |
| AutomationBench v1.0.6 (avg@1) | 30.3 | lab |
| Terminal Bench 2.1 (avg@1) | 37.1 | lab |
| JobBench (avg@1) | 18.3 | lab |
| MiMo Cyber (mini, in-house) | 31.3 | lab |
| MiMo Visual Coding (mini, in-house) | 64.0 | lab |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2026 | — | — |

## Efficiency

- **Active params:** 9B dense (32 layers, hidden 4096) + 1152-hidden vision encoder; distilled from MiMo-V2.6 onto Qwen3.5-9B
- **Context length:** 256K tokens (max_position_embeddings 262144)
- **VRAM (fp16 rough):** ~18GB fp16 — runs on a 24GB GPU at fp16, ~6GB at Q4; on-disk ~9.4GB. The practical local agent model of the family.
- **Serving:** SGLang with Qwen3.5 support + `--reasoning-parser mimo`; chat template supports `enable_thinking`.

## What makes it notable

SFT checkpoint on MiMo-generated data (77.4B tokens: code 23.2B, cyber 11B, general 22B, visual 21.2B) as the open starting point for agentic-RL research. vs its Qwen3.5-9B base: SWE-bench Verified 60.0→61.1, SWE Pro 32.0→44.6 (+12.6pp), AutomationBench 5.0→30.3, Terminal Bench 2.1 27.0→37.1 — big agentic gains from data alone. Vision + 256K ctx + MIT at 9B makes it the natural local candidate for tool-using agents that also need screenshots/DOM images, if the SGLang/transformers support is stable (custom tokenizer + chat template; verify before betting an agent loop on it).

## See also

- [[welcome]]
- Source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B
- Siblings: [[XiaomiMiMo/MiMo-V2.6-Pro-RL]], [[XiaomiMiMo/MiMo-V2.6-Flash-RL]]