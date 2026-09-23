---
title: "XiaomiMiMo/MiMo-V2.6-Pro-RL"
org: XiaomiMiMo
model_id: XiaomiMiMo/MiMo-V2.6-Pro-RL
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
downloads: 4070
likes: 442
license: MIT
pipeline: text-generation
source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Pro-RL
params: 1.02T (42B active)
context: 1M
architecture: moe (hybrid SWA+GA, no shared experts)
---

# XiaomiMiMo/MiMo-V2.6-Pro-RL

**One-line:** First open-weight model to top the Artificial Analysis Intelligence Index (#1/114, score 46) — one mixed RL run across coding, general agents, visual, and cyber ("You Only RL Once").

⚠ **large** — 1.02T total params; not locally runnable (see Efficiency).
⚠ Lab-reported numbers below (Xiaomi HF card + mimo.xiaomi.com blog); AA Intelligence Index is independent. A r/LocalLLaMA thread (2026-09-23) accuses the family of "benchmaxxing"; note AA's 46 is AA's own 10-eval measurement (GDPval-AA, AutomationBench-AA, Terminal-Bench 4.0, SciCode, HLE, …), not a lab-supplied score. Released Sep 21, 2026 (AA-confirmed).

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
| DeepSWE v1.1 (agentic SWE stand-in) | 71.9 | lab |
| ProgramBench | 26.5 | lab |
| MiMo Code Bench (in-house) | 63.2 | lab |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| Toolathlon-Verified | 76.9 | lab |
| AutomationBench v1.0.6 | 53.1 | lab |
| Terminal Bench 2.1 | 89.9 | lab |
| Terminal Bench 4.0 | 34.9 | lab |
| Agents' Last Exam | 31.6 | lab |
| JobBench | 62.0 | lab |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| AA Intelligence Index | 46 (#1/114 open-weight) | Artificial Analysis (independent) |
| GDPval-AA v2.1 | 1673 | AA eval, cited in lab table |
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2026 | — | — |

## Efficiency

- **Active params:** 42B (of 1.02T total; 384 routed experts, 8 active, top-k; ~70 layers, hybrid full+SWA attention, no shared experts)
- **Context length:** 1M tokens
- **VRAM (fp16 rough):** ~2TB fp16 — NOT locally runnable; on-disk weights ~1TB (fp8/bf16 mix per file sizes), needs multi-node expert-parallel or API. AA measured 53.9 tok/s on Xiaomi API.

## What makes it notable

MiMo-V2.6-Pro (MIT, fully open weights + technical report, Sep 21 2026) leads the open-weight pack on AA's Intelligence Index (46 vs GLM-5.3, Kimi K3, Qwen3.8 2.4T, DeepSeek V4.1 Flash, K2 Horizon 375B — all below it at the Sep 2026 snapshot). The "You Only RL Once" recipe runs one mixed GRPO run across coding, general agents, visual and cyber domains, with groupwise agentic grading instead of binary pass/fail. Native omnimodal input (text/image/video/audio) + 1M ctx targets long repo/tool-trace agent sessions. For local deployment this is a datacenter-only heavyweight — the practical local picks from the same family are the Flash-RL (15B active) and the 9B Distill (see siblings).

## See also

- [[welcome]]
- Source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Pro-RL
- Siblings: [[XiaomiMiMo/MiMo-V2.6-Flash-RL]], [[XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B]]