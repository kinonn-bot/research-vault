---
title: "IFM/K2-Horizon-MoVA-36B-A4B"
org: IFM
model_id: IFM/K2-Horizon-MoVA-36B-A4B
date: 2026-09-12
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - mova
  - open-weights
  - custom-architecture
  - long-context
downloads: 5192
likes: 279
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/K2-Horizon-MoVA-36B-A4B
params: 4B active (36B total)
context: 524288
architecture: moe
---

# IFM/K2-Horizon-MoVA-36B-A4B

**One-line:** Sparse member of the K2 Horizon fleet — 36B MoE with Mixture-of-Values attention running 4B active per token; strongest agentic-terminal score in the sub-10B-active class (Terminal-Bench 2.1 58.6, beats 550B Nemotron 3 Ultra).

⚠ All scores are **lab-reported** (IFM model card). No independent benchmark coverage yet.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| Terminal-Bench 2.1 | 58.6 | *lab-reported* |
| SciCode | 38.9 | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| τ³-Banking | 26.8 | *lab-reported* |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 80.8 | *lab-reported* |
| MATH | — | — |
| AIME 2025 | — | — |
| Humanity's Last Exam (no tools) | 25.2 | *lab-reported* |
| AA-LCR (long-context) | 66.3 | *lab-reported* |

## Efficiency

- **Active params:** 4B (total 36B; 100 MoE experts / 8 per token + 64 MoVA value-experts / 4 per token)
- **Context length:** 524,288 tokens (512K)
- **VRAM (fp16 rough):** ~72 GB total (BF16); FP8 ~36 GB; official GGUF builds released (6.0k downloads). FP8/GGUF makes it feasible on a single 48GB card.

## What makes it notable

- Best Terminal-Bench 2.1 of any ≤12B-active MoE in IFM's comparison: 58.6 vs Nemotron 3 Super (38.6), Qwen3.6-35B-A3B (44.9), ai9stars G9v3-39A5B (32.6) — and it beats Nemotron 3 Ultra (550B/55B act, 53.9).
- Mixture-of-Values (MoVA) attention: value-space experts on top of standard MoE — custom `k2_horizon` architecture, needs repo model code; vLLM/SGLang recipes provided.
- For local agent loops this is the sweet spot of the fleet: 4B active per token at ~36GB quantized with 512K context; τ³-Banking 26.8 clears the 550B Nemotron Ultra (14.2) and Muse Glimmer-30B (23.5).

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/K2-Horizon-MoVA-36B-A4B