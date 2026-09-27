---
title: "XiaomiMiMo/MiMo-V2.6-Flash-MOPD"
org: XiaomiMiMo
model_id: XiaomiMiMo/MiMo-V2.6-Flash-MOPD
date: 2026-09-27
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - multimodal
  - rl
  - long-context
downloads: 0
likes: 11
license: MIT
pipeline: text-generation
source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Flash-MOPD
params: 309B (15B active)
context: 1M
architecture: moe (hybrid SWA+GA, no shared experts, MTP)
---

# XiaomiMiMo/MiMo-V2.6-Flash-MOPD

**One-line:** MOPD (Multi-teacher On-Policy Distillation) upgrade of MiMo-V2.6-Flash-RL that fixes tool-call repetition in agent harnesses — same 309B/15B-active, 1M-ctx, MIT omnimodal stack.

⚠ **large** — 309B total params; server-class hardware only (see Efficiency).
⚠ Lab-reported benchmarks below are the MiMo-V2.6 technical-report numbers measured on the **RL checkpoint**; the MOPD checkpoint's card publishes no new eval tables, but Xiaomi's blog (2026-09-27) states the broader benchmark suite "held steady" after MOPD. Released Sep 27, 2026 (weights on HF 04:00Z, API since Sep 25).

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
| DeepSWE v1.1 (agentic SWE stand-in) | 67.9 | lab (V2.6 report, RL ckpt — holds steady) |
| ProgramBench | 26.0 | lab (V2.6 report, RL ckpt) |
| MiMo Code Bench (in-house) | 61.2 | lab (V2.6 report, RL ckpt) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| Toolathlon-Verified | 73.6 | lab (V2.6 report, RL ckpt) |
| AutomationBench v1.0.6 | 52.3 | lab (V2.6 report, RL ckpt) |
| Terminal Bench 2.1 | 87.6 | lab (V2.6 report, RL ckpt) |
| Agents' Last Exam | 27.6 | lab (V2.6 report, RL ckpt) |
| JobBench | 61.2 | lab (V2.6 report, RL ckpt) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2026 | — | — |

## Efficiency

- **Active params:** 15B (of 309B total; 256 routed experts, 8 active; 48 layers hybrid full+SWA, MTP speculative decoder)
- **Context length:** 1M tokens
- **VRAM (fp16 rough):** ~618GB fp16 — NOT consumer-runnable; on-disk ~311GB (fp8/bf16 mix), needs multi-GPU + quant.

## What makes it notable

The MOPD checkpoint is the agentic-reliability patch for the MiMo-V2.6-Flash family: RL scaling surfaced a tool-call-repetition failure mode (e.g. 1.02% exact within-turn repetition rate under OpenCode on Flash-RL) that standard correctness optimization missed. Xiaomi's fix fuses mixRL + SFT teachers via on-policy distillation (standard MOPD, teacher-prefix OPD, SFT-prefix OPD) in a lightweight run (~$90k total, ~4% of the MixRL restart cost) that folds a repetition-specialized teacher in without moving the broader benchmark suite. For agent-loop users this targets a real operational failure — repeated identical tool calls burning context and wall time — rather than a headline eval. Same 309B/15B-active cost profile as Flash-RL: server-class only; the 9B Distill sibling remains the local entry point.

## See also

- [[welcome]]
- Source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Flash-MOPD
- Technical blog: https://mimo.xiaomi.com/blog/mimo-v2-6-tool-call-repetition
- Siblings: [[XiaomiMiMo/MiMo-V2.6-Flash-RL]], [[XiaomiMiMo/MiMo-V2.6-Pro-MOPD]], [[XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B]]