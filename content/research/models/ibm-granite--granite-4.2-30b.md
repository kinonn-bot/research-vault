---
title: "IBM Granite-4.2-30B (Granite 4.2 family)"
org: ibm-granite
model_id: ibm-granite/granite-4.2-30b
date: 2026-08-31
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - reasoning
downloads: 4228
likes: 98
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/ibm-granite/granite-4.2-30b
params: 30B dense (family: 3B, 8B, 30B)
context: 131072 (128K native; 512K via long-context extension)
architecture: dense
---

# IBM Granite-4.2-30B (Granite 4.2 family)

**One-line:** IBM's flagship reasoning/agent model for enterprise agentic workflows — native `<think>` CoT, strong tool-calling (BFCL v4 61.39), solid repo work (SWE-bench Verified 57.0), Apache-2.0, 3B/8B/30B dense family for local deployment.

> ⚠ All benchmark figures below are **lab-reported** (IBM NeMo Evaluator SDK, consistent methodology across the 3B/8B/30B line). Released **2026-08-25** (per IBM Research blog + card); the HF repo `createdAt` (08-07) predates the weight drop — see the "createdAt ≠ release date" pattern. No independent leaderboard (Artificial Analysis / aider.chat) carries Granite-4.2 numbers yet; treat these as lab figures.

**Release event:** Granite 4.2 (3B, 8B, 30B) dropped 2026-08-25 as a new fully-open (Apache-2.0) reasoning generation, positioned specifically for "agentic workflows that today's enterprise use cases require" (IBM Research blog, 6 days before 2026-08-31 run). Post-trained from Granite-4.1-30B-Base via multi-stage SFT + GRPO RL (agentic traces up to 200 tool-calling turns), plus RLHF. Three thinking modes (full / non-thinking / low-effort).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench v6 | 75.77 (30B) | lab (NeMo) |
| Aider polyglot | — | — |
| SWE-bench Verified | 57.0 (30B) | lab (NeMo) |
| SWE-bench Multilingual | 41.89 (30B) | lab (NeMo) |
| SWE-bench Pro | 33.29 (30B) | lab (NeMo) |
| Terminal-Bench 2.1 | 29.24 (30B) | lab (NeMo) |

8B siblings: SWE-bench Verified 47.67, SWE-bench Pro 19.11, Terminal-Bench 2.1 20.56. 3B: not evaluated on SWE/Terminal (NA).

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL (v4) | 61.39 (30B) | lab (NeMo) |
| τ-Bench (τ³-bench AVG) | 62.00 (30B) | lab (NeMo) |
| ToolACE | — | — |
| GAIA | — | — |
| ProfBench | 42.90 (30B) | lab |
| BirdBench | 41.85 (30B) | lab |
| GDPval | 1225 (30B) | lab |

3B/8B BFCL: 52.41 / 52.39.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU-Pro | 77.60 (30B) | lab |
| GPQA | 66.41 (30B) | lab |
| AIME25 | 89.17 (30B) | lab |
| HMMT Feb25 | 89.17 (30B) | lab |

## Efficiency

- **Active params:** 30B dense (25B total is all active; no MoE). Family: 3B / 8B / 30B dense.
- **Context length:** 128K native (131072), 512K with long-context extension.
- **VRAM (fp16 rough):** 30B ≈ 60 GB · 8B ≈ 16 GB · 3B ≈ 6 GB.
- Optimized for vLLM / SGLang (granite_thinking_parser, tool-call parser `qwen3_coder`); 30B needs quantization (or multi-GPU) for a typical local box.

## What makes it notable

Granite-4.2 is the strongest fully-open enterprise model line with a deliberate agentic-reasoning focus: native `<think>` chain-of-thought with switchable effort, reasoning-augmented tool calling (BFCL v4 61.39), and competitive repo work (SWE-bench Verified 57.0, SWE-bench Multilingual 41.89). It sits close to the Qwen3.8 / GLM-5.3 tier for coding/agents at a cheaper dense footprint, and the Apache-2.0 license plus the 3B/8B siblings give a clear local-deployment ladder (3B runs on a modest GPU, 8B on a single 24GB card, 30B needs quant or multi-GPU). For a local runner it's a serious, enterprise-hardened alternative to GLM-5.3 / Qwen3.8 — main caveat is that the numbers are lab-reported and unverified by a third party yet.

## See also

- [[welcome]]
- Source: https://huggingface.co/ibm-granite/granite-4.2-30b
- IBM Research blog: https://research.ibm.com/blog/introducing-granite-4-2
