---
title: "NVIDIA NVIDIA-Nemotron-Labs-Teacher-Competition-Coding"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-Labs-Teacher-Competition-Coding
date: 2026-08-16
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid
  - mamba
  - mtp
  - large
downloads: 1231
likes: 4
license: openmdw-1.1
pipeline: text-generation
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Teacher-Competition-Coding
params: 55B active (550B total)
context: 262144
architecture: moe (LatentMoE hybrid: Mamba-2 + MoE + Attention, MTP)
---

# NVIDIA-Nemotron-Labs-Teacher-Competition-Coding

**One-line:** NVIDIA's competition-coding specialist from the Nemotron 3 Ultra family (08/14 drop) — a 550B/55B LatentMoE hybrid tuned for competitive programming, verified solution generation, and MOPD distillation. ⚠ large — datacenter-class (4xGB200/8xH100), not locally runnable. ⚠ no published benchmarks — agent-loop suitability unknown.

> ⚠ **No benchmark numbers published on the card.** The accuracy plot (`accuracy_plot.png`) is a broken link (404 on the repo), there is no `.eval_results/` dir, and the README's only claim is narrative ("achieving leading results on competition coding benchmarks"). The Nemotron 3 Ultra technical report (June 2026) covers the Ultra student, not this teacher checkpoint specifically. All coding/agent cells below are `—`.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published (narrative claim only) |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** 55B active (550B total, 512 experts/layer, top-22)
- **Context length:** 262,144 tokens (config `max_position_embeddings`)
- **VRAM (fp16 rough):** ~1.1 TB full-model (datacenter only; min 4xGB200 / 8xH100 per card) — ⚠ needs quantization (NVFP4 recipe) and multi-GPU even then

## What makes it notable

First standalone release of the **Competition-Coding teacher** from the Nemotron 3 Ultra MOPD (Multi-Teacher On-Policy Distillation) recipe, dropped 2026-08-14 alongside 4 sibling teachers (Chat, STEM, Instruction-Following, General-Reasoning). It's the post-trained Ultra student (550B-A55B, LatentMoE hybrid Mamba-2+MoE+Attention with MTP, 1M ctx capable, OpenMDW-1.1 license) plus an extra coding-focused SFT+RL round over competitive programming data (Codeforces/AtCoder/AIZU/CodeChef-style, strict dedup). NVIDIA explicitly positions it as usable standalone for competitive coding, algorithmic problem solving, verified code-solution/reasoning-trace generation, and as a teacher/grader in distillation pipelines. Custom architecture (`NemotronHForCausalLM`) — stock transformers won't load it without the repo's model code; the family targets vLLM/SGLang/TRT-LLM on GB200-class hardware. No published eval numbers to position vs leaders (DeepSeek-V4-Pro, Kimi-K2.6); treat as unverified until an independent run appears.

## See also

- [[welcome]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Teacher-Competition-Coding
