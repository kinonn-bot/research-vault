---
title: "IFM/K2-Horizon-3.7B"
org: IFM
model_id: IFM/K2-Horizon-3.7B
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
downloads: 5316
likes: 41
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/K2-Horizon-3.7B
params: 3.7B dense
context: 524288
architecture: dense
---

# IFM/K2-Horizon-3.7B

**One-line:** Small dense member of the K2-Horizon fleet — 3.7B with 512K context; claims SWE-bench Verified 68.6, far above every dense sub-5B open model on the card's table.

⚠ All scores are **lab-reported** (IFM model card). Fleet-level results have independent Artificial Analysis backing (per Moor Insights), but these specific numbers are the card's own, with baseline protocols that may differ.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | 68.6 | *lab-reported* |
| Terminal-Bench 2.1 | 25.1 | *lab-reported* |
| SciCode | 25.9 | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL v4 | 50.9 | *lab-reported* |
| τ³-Banking | 17.7 | *lab-reported* |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 65.4 | *lab-reported* |
| HLE | 12.9 | *lab-reported* |
| HMMT Feb 2026 | 70.5 | *lab-reported* |

## Efficiency

- **Active params:** 3.7B dense
- **Context length:** 524,288 tokens (512K)
- **VRAM (fp16 rough):** ~7.5 GB — fits a single consumer GPU at fp16; KV cache at 512K will require quant/long-context handling

## What makes it notable

- SWE-bench Verified 68.6 at 3.7B dense is a step-change claim vs the card's reference table: Qwen3.5-4B (41.2), G9v3-3B (16.4), Granite 4.2-3B (32.2), Nemotron 3 Nano-4B (1.8).
- BFCL v4 50.9 is near Qwen3.5-4B (55.7) — genuinely useful tool-calling for a 3.7B, paired with a native `k2_horizon` tool-call parser.
- 512K native context on a 3.7B is unusual; the card's HMMT Feb 2026 70.5 (vs Qwen3.5-4B 61.6) suggests strong math for the size.
- Custom `K2HorizonForCausalLM` architecture; vLLM/SGLang first-party recipes; fully open training data/recipe with intermediate checkpoints. One of the best local-agent value plays in the fleet if verified.

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/K2-Horizon-3.7B