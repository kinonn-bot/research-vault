---
title: "IFM/K2-Horizon-0.9B"
org: IFM
model_id: IFM/K2-Horizon-0.9B
date: 2026-09-14
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - dense
  - custom-architecture
  - open-weights
  - long-context
downloads: 15704
likes: 69
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/K2-Horizon-0.9B
params: 0.9B dense
context: 131072
architecture: dense
---

# IFM/K2-Horizon-0.9B

**One-line:** Compact dense member of the K2-Horizon fleet — 0.9B with 128K context, multi-teacher distilled (math/code/STEM/IF experts merged via MOPD), claims HumanEval+ 79.9.

⚠ All scores are **lab-reported** (IFM model card). IFM's K2-Horizon family results have been backed by independent evaluation from Artificial Analysis for the fleet (per Moor Insights), but these specific 0.9B numbers are the card's own.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | 79.9 | *lab-reported* |
| MBPP | — | — |
| MBPP+ | 68.0 | *lab-reported* |
| LiveCodeBench v6 | 37.4 | *lab-reported* |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL v4 | 28.0 | *lab-reported* |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 27.3 | *lab-reported* |
| AIME 2025 | 41.7 | *lab-reported* |
| AIME 2026 | 48.5 | *lab-reported* |
| HMMT Feb 2026 | 25.8 | *lab-reported* |

## Efficiency

- **Active params:** 0.9B dense
- **Context length:** 131,072 tokens (128K, YaRN extension from 8K)
- **VRAM (fp16 rough):** ~2 GB — runs comfortably on a Raspberry Pi-class / NPU device

## What makes it notable

- SOTA-in-class claims vs its own card's reference table: Qwen3.5-0.8B (HumanEval+ 16.5), OpenBMB-1B (65.2), Qwen3.5-2B (75.6) — 79.9 HumanEval+ / 68.0 MBPP+ would put it above the 2B reference on coding.
- BFCL v4 28.0 with native tool-call parser (`k2_horizon` XML/JSON) — functional but modest tool-use; agent utility likely from the reasoning loop plus 128K context, not raw tool accuracy.
- Fully open program: training data/recipe, W&B logs, intermediate checkpoints, vLLM PR + SGLang cookbook all public.
- Custom `K2HorizonForCausalLM` architecture — needs repo model code (trust_remote_code) or the vLLM/SGLang first-party recipes; not stock transformers.

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/K2-Horizon-0.9B