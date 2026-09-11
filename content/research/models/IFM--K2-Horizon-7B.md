---
title: "IFM/K2-Horizon-7B"
org: IFM
model_id: IFM/K2-Horizon-7B
date: 2026-09-12
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - dense
  - open-weights
  - custom-architecture
  - long-context
downloads: 4835
likes: 112
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/K2-Horizon-7B
params: 7B dense
context: 524288
architecture: dense
---

# IFM/K2-Horizon-7B

**One-line:** Medium dense member of the K2 Horizon fleet — 7B with 512K context that claims SWE-bench Verified 70.6 (lab-reported), far above every published 7–12B open-weight competitor.

⚠ All scores are **lab-reported** (IFM model card). The SWE-bench Verified 70.6 claim is striking and unverified by third parties — treat as a claim, not a fact, until an independent run appears.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | 70.6 | *lab-reported* |
| Terminal-Bench 2.1 | 39.1 | *lab-reported* |
| SciCode | 31.6 | *lab-reported* |
| HMMT Feb 2026 | 73.3 | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| τ³-Banking | 25.8 | *lab-reported* |
| BrowseComp | 59.0 | *lab-reported* |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |
| Humanity's Last Exam (no tools) | 18.6 | *lab-reported* |
| AA-LCR (long-context) | 68.0 | *lab-reported* |

## Efficiency

- **Active params:** 7B dense (36 layers, GQA 32→8 KV heads)
- **Context length:** 524,288 tokens (512K)
- **VRAM (fp16 rough):** ~14 GB (BF16); official FP8 + GGUF builds released — runs on a single consumer GPU.

## What makes it notable

- SWE-bench Verified 70.6 at 7B dense would be a step-change if confirmed: comparisons on the same card are Granite 4.2-8B (47.7), Qwen3.5-9B (50.8), Gemma 4-12B (30.6). Terminal-Bench 2.1 39.1 vs Qwen3.5-9B 29.2 too.
- BrowseComp 59.0 reportedly beats GPT-5 (54.9) and DeepSeek V4 Flash (53.5) on the card's reference table — again unverified.
- The diffusion adapters variant (K2-Horizon-7B-Uno, paper 2609.04010) trades a bit of quality for ~2.7× faster generation — adapter repo, not a standalone model.
- Custom `k2_horizon` architecture; vLLM/SGLang first-party recipes. Solid local agent candidate if audited numbers hold.

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/K2-Horizon-7B