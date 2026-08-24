---
title: "NitrAI Research Polaris-V1"
org: nitrai-research
model_id: nitrai-research/Polaris-V1
date: 2026-08-25
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - reasoning
  - reinforcement-learning
  - instruct
downloads: 1543
likes: 2
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/nitrai-research/Polaris-V1
params: 4B
context: 1592638
architecture: dense (hybrid linear/full-attention)
---

# NitrAI Research Polaris-V1

**One-line:** A 4B open-weights reasoning model RL-aligned on multi-file code synthesis and theorem-verification rewards — 31.4% SWE-bench Verified at a size that fits consumer GPUs (3.2 GB Q4).

> ⚠ **Provenance caveat:** All reported numbers below are **lab-reported** (NitrAI Research's own model card). As of this write-up there is no independent third-party eval (small download count, newly released). No BFCL/τ-Bench/ToolACE/GAIA published.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | 31.4 | *lab* |
| SWE-bench Multilingual | — | — |
| SWE-bench Pro | 28.0 | *lab* |
| DeepSWE | 26.8 | *lab* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| WildClawBench (agentic trajectories) | 38.5 | *lab* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |

## Efficiency

- **Active params:** 4B (dense; no MoE experts)
- **Context length:** 1,592,638 tokens via YaRN RoPE scaling (base 262k, extended)
- **VRAM (fp16 rough):** 8.4 GB FP16 / 4.5 GB Q8 / 3.2 GB Q4_K_M

## What makes it notable

Polaris-V1 is a genuinely-local coding/agent model: 4B dense, Apache-2.0, aligned via multi-turn RL with multi-file code synthesis + theorem-verification rewards. It posts 31.4% SWE-bench Verified and 28.0% SWE-bench Pro at 4B params — stronger than comparable edge models (e.g. Ling-3.0-tiny at 24.2%) and within striking distance of distilled 9B models (Qwen3.8-9B at 37.8%), at a fraction of the footprint. The 1.59M YaRN context is unusual for this size and suits long agent transcripts. Claim-to-fame: highest SWE-bench-per-dollar on consumer hardware, but the numbers are lab-reported and unverified by third parties, so treat the absolute values as provisional.

## See also

- [[welcome]]
- Source: https://huggingface.co/nitrai-research/Polaris-V1
