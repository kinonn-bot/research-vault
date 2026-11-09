---
title: "Axion 1.0-35B (Reproduction)"
org: Axion1-0
model_id: Axion1-0/Axion-1.0-35B
date: 2026-11-10
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - tool-use
downloads: 1125
likes: 70
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/Axion1-0/Axion-1.0-35B
params: 3B active (35B total MoE)
context: 131072
architecture: moe
---

# Axion 1.0-35B (Reproduction)

**One-line:** ⚠ Open reproduction (recipe + data) of ByteDance's Axion agent foundation model — 35B/3B-active MoE with tool-use RL, but no SWE-bench/BFCL numbers published, so agent-loop suitability is unverified.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| SWE-bench Multilingual | — | — |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| HLE (full) | 52.8 | paper + repro card (lab-reported) |
| BioMysteryBench (hard subset) | 35.3 | paper + repro card (lab-reported) |
| SEAL-0 | 60.4 | paper + repro card (lab-reported) |
| HiPhO | 45.9 | paper + repro card (lab-reported) |
| FrontierScience Olympiad | 85.0 | paper + repro card (lab-reported) |
| FrontierScience Research | 55.0 | paper + repro card (lab-reported) |
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |

## Efficiency

- **Active params:** 3B (35B total MoE, Qwen3.5-MoE arch)
- **Context length:** 128K tokens (per upstream serving guide)
- **VRAM (fp16 rough):** ~70 GB; upstream serving example uses 8 GPUs with vLLM + TP8

## What makes it notable

Reproduction checkpoint of *Axion 1.0: Open Agent Foundation Models, Simplified* (arXiv:2611.03233), with training recipe (18K SFT + 3 stages incl. RL over agent trajectories), training data (`Axion1-0/axion-training-data`), and eval harness published — reproducibility is the point. Repro matches paper within ~2pp on all six reported science/agent-search evals. Gap: the eval set is science/reasoning only — nothing measuring repo editing or function calling — so for coding-agent loops this is currently unranked. Worth re-checking if the upstream adds SWE-bench or BFCL later.

## See also

- [[welcome]]
- Source: https://huggingface.co/Axion1-0/Axion-1.0-35B
- Paper: https://arxiv.org/abs/2611.03233
