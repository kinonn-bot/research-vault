---
title: "IFM/K2-Horizon-32B-Stage1"
org: IFM
model_id: IFM/K2-Horizon-32B
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
downloads: 2168
likes: 30
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/K2-Horizon-32B
params: 32B dense
context: 524288
architecture: dense
---

# IFM/K2-Horizon-32B-Stage1

**One-line:** Large dense member of the K2-Horizon fleet — 32B with 512K context; **stage-1 checkpoint** (final checkpoint to be released), claims GPQA Diamond 82.3 but trails Qwen3.8-27B on agentic coding.

⚠ All scores are **lab-reported** (IFM model card); baseline scores are from Artificial Analysis. The card itself flags this is a stage-1 checkpoint with stage-2 results "out soon" — treat numbers as interim.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| Terminal-Bench 2.1 | 36.6 | *lab-reported* |
| SciCode | 30.2 | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ³-Banking | 22.5 | *lab-reported* |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 82.3 | *lab-reported* |
| HLE (no tools) | 22.8 | *lab-reported* |
| CritPt (frontier physics) | 1.4 | *lab-reported* |
| AA-LCR (long-context) | 65.3 | *lab-reported* |
| AA-Omniscience Accuracy | 16.8 | *lab-reported* |
| AA-Omniscience Non-Hallucination | 58.3 | *lab-reported* |

## Efficiency

- **Active params:** 32B dense
- **Context length:** 524,288 tokens (512K)
- **VRAM (fp16 rough):** ~64 GB (BF16) — 2× H200 per the SGLang recipe; FP8/GGUF builds not yet in repo. Not a consumer-GPU model at full precision.

## What makes it notable

- Positioned as the "local deployment" dense flagship of the fleet, but stage-1 scores trail its own reference table: Terminal-Bench 2.1 36.6 vs Qwen3.8-27B 79.8 and Muse Glimmer-30B 51.7; τ³-Banking 22.5 vs Qwen3.8-27B 48.0.
- Strong reasoning for the size: GPQA Diamond 82.3 (vs Granite 4.2-30B 64.4), HLE 22.8 (vs Muse Glimmer-30B 22.0).
- Wait for the stage-2/final checkpoint before choosing it over Qwen3.8-27B for agent work — the current release is explicitly an intermediate.
- Custom `K2HorizonForCausalLM` architecture; vLLM/SGLang first-party recipes; fully open program (data, W&B, checkpoints).

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/K2-Horizon-32B