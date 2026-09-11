---
title: "IFM/K2-Horizon-375B-A23B"
org: IFM
model_id: IFM/K2-Horizon-375B-A23B
date: 2026-09-12
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - open-weights
  - custom-architecture
  - long-context
downloads: 3751
likes: 73
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/K2-Horizon-375B-A23B
params: 23B active (375B total)
context: 524288
architecture: moe
---

# IFM/K2-Horizon-375B-A23B

**One-line:** Flagship of IFM's fully-open K2 Horizon fleet (Sept 3, 2026) — frontier-class agentic tool use at 23B active params, with weights, training data, code, and intermediate checkpoints all published; ⚠ large (375B total, ~750GB BF16).

⚠ All scores are **lab-reported** (IFM model card tables). No independent benchmark (Artificial Analysis / LMArena) published yet; The New Stack and independent reviewers note self-reported figures only. IFM's launch blog also carries a self-audit that revised Terminal-Bench 2.1 from 70.2 → 66.9 after a reward-hacking/verification audit.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| SWE Bench Pro (strict) | 42.6 | *lab-reported* |
| SWE-Atlas-QnA (strict) | 48.4 | *lab-reported* |
| Terminal-Bench 2.1 | 70.2 (66.9 audited) | *lab-reported* |
| SciCode | 42.7 | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| τ³-Banking | 34.0 | *lab-reported* |
| Toolathlon Verified | 65.3 | *lab-reported* |
| MCPMark | 67.7 | *lab-reported* |
| Automation Bench Public | 25.3 | *lab-reported* |
| Apex-Agents (pass@1) | 24.8 | *lab-reported* |
| BrowseComp | 72.8 | *lab-reported* |
| WildClawBench | 50.9 | *lab-reported* |
| GDPVal-AA (Elo) | 1,441 | *lab-reported* |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 87.3 | *lab-reported* |
| MATH | — | — |
| AIME 2025 | — | — |
| Humanity's Last Exam (no tools) | 32.0 | *lab-reported* |
| AA-LCR (long-context) | 76.0 | *lab-reported* |

## Efficiency

- **Active params:** 23B (total 375B, 192 experts / 8 per token, 1 shared)
- **Context length:** 524,288 tokens (512K, native from midtraining)
- **VRAM (fp16 rough):** ⚠ large — ~750 GB (BF16); FP8 variant (~375GB) and 8×H200 vLLM/SGLang recipes provided. Not single-GPU; consumer use needs heavy quantization or API.

## What makes it notable

- Largest fully-open launch to date: weights + 15T-token pretraining data + training code + W&B logs + intermediate checkpoints (LLM360 lineage — IFM/Abu Dhabi, ex-MBZUAI).
- Agentic tool use punches above its size: Toolathlon Verified 65.3 beats all listed open references incl. GLM 5.2 max (59.9); τ³-Banking 34.0 ≈ GLM 5.2 max (34.6); Terminal-Bench 2.1 70.2 beats Nemotron 3 Ultra (53.9) and Inkling xhigh (55.1) — audited 66.9 still ahead.
- Trained via 5 expert RL branches (knowledge, IF, search, tool use, reasoning) merged before SFT; reasoning_effort="high" required for stated scores.
- Custom `k2_horizon` architecture (MoE + sigmoid router, `K2HorizonForCausalLM`) — needs repo model code (`trust_remote_code`); first-party vLLM/SGLang recipes exist.

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/K2-Horizon-375B-A23B