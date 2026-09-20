---
title: "XingChen-AGI Xing4.0-29B-A4B"
org: XingChen-AGI
model_id: XingChen-AGI/Xing4.0-29B-A4B
date: 2026-09-21
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - mla
  - instruct
downloads: 12617
likes: 848
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/XingChen-AGI/Xing4.0-29B-A4B
params: 4B active (29B total)
context: 256K (extendable to 512K)
architecture: moe
---

# XingChen-AGI Xing4.0-29B-A4B

**One-line:** China Telecom's agent-oriented 29B-A4B MoE (TeleChat lineage) with published SWE-bench Verified 75.0 and τ-Bench 64.6 — first model of its scale trained natively on Ascend NPU. Lab-reported numbers; independent verification pending.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | 75.0 | *lab-reported* (SWE-agent harness, 210K ctx) |
| SWE-bench Multilingual | 66.0 | *lab-reported* (SWE-agent harness, 210K ctx) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | 64.6 | *lab-reported* (τ³-Bench, pass^1 @ 4 runs) |
| ToolACE | — | — |
| GAIA | — | — |
| Terminal-Bench 2.1 | 57.5 | *lab-reported* (terminus-2, avg of 3 runs) |
| Claw-Eval | 76.6 | *lab-reported* (official harness, avg of 3 runs) |
| DeepresearchBII | 60.8 | *lab-reported* (OpenCode + Exa MCP) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2026 | 90.0 | *lab-reported* (avg of 5 runs) |
| IFBench | 69.7 | *lab-reported* |

## Efficiency

- **Active params:** 4B (29B total, 64 routed experts / 4 active + 1 shared, MLA attention, mHC + MTP)
- **Context length:** 256K (YARN-extended from 4096 pretrain)
- **VRAM (fp16 rough):** ~58 GB (needs quantization for single consumer GPU)

## What makes it notable

First model of this scale trained end-to-end on Ascend 910C NPUs (MindSpore), from China Telecom's Xing/TeleChat line. Card claims the strongest agentic numbers in its size class — SWE-bench Verified 75.0, Terminal-Bench 2.1 57.5, τ-Bench 64.6 — edging Qwen3.6-35B-A3B on SWE-bench Multilingual and beating Gemma4-26B-A4B across most agentic rows. Positioning is explicitly agent-loop: compatibility targets include OpenCode, Claude Code, OpenClaw and Hermes, with OpenAI-compatible API and vLLM/SGLang/KTransformers support.

**Caveats:** all numbers are lab-reported (no independent Artificial Analysis / leaderboard confirmation found yet); `model_type: xing4_0` is a custom architecture (transformers 5.14.1, auto_map in-repo) — llama.cpp support unconfirmed, so local runs currently need vLLM/SGLang or community GGUF builds. Alibaba and Zhipu comparisons on the card are direct lab-harness runs, not standardized third-party results.

## See also

- [[welcome]]
- Source: https://huggingface.co/XingChen-AGI/Xing4.0-29B-A4B