---
title: "NVIDIA NVIDIA-Nemotron-Labs-Teacher-STEM"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-Labs-Teacher-STEM
date: 2026-08-16
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - reasoning
  - moe
  - hybrid
  - mamba
  - mtp
  - large
downloads: 1021
likes: 6
license: openmdw-1.1
pipeline: text-generation
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Teacher-STEM
params: 55B active (550B total)
context: 262144
architecture: moe (LatentMoE hybrid: Mamba-2 + MoE + Attention, MTP)
---

# NVIDIA-Nemotron-Labs-Teacher-STEM

**One-line:** NVIDIA's STEM/general-reasoning teacher from the Nemotron 3 Ultra family (08/14 drop) — 550B/55B LatentMoE hybrid covering math, code, natural sciences, and tool use (code execution + search), positioned vs DeepSeek V4 Pro (High). ⚠ large — datacenter-class (4xGB200/8xH100), not locally runnable. ⚠ no published benchmarks — agent-loop suitability unknown.

> ⚠ **No benchmark numbers published on the card.** The accuracy plot (`accuracy_plot.png`) is a broken link (404 on the repo), there is no `.eval_results/` dir. The only quantitative claim is narrative: "matching or outperforming DeepSeek V4 Pro (High) on benchmarks such as GPQA, MMLU-Pro, LiveCodeBench v6, IMOAnswerBench, and Apex Shortlist" — lab-reported, no table, no numbers. Coding/agent cells below are `—`.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published (narrative: "vs DeepSeek V4 Pro (High)" only) |
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
| MMLU / MMLU-Pro | — | not published (narrative claim) |
| GPQA Diamond | — | not published (narrative claim) |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** 55B active (550B total, 512 experts/layer, top-22)
- **Context length:** 262,144 tokens (config `max_position_embeddings`)
- **VRAM (fp16 rough):** ~1.1 TB full-model (datacenter only; min 4xGB200 / 8xH100 per card) — ⚠ needs quantization (NVFP4 recipe) and multi-GPU even then

## What makes it notable

Second of five **Nemotron 3 Ultra Teacher** checkpoints released 08/14/2026 (siblings: Competition-Coding, Chat, Instruction-Following, General-Reasoning). Produced from the post-trained Ultra student (550B-A55B, LatentMoE hybrid Mamba-2+MoE+Attention, MTP, OpenMDW-1.1) plus reasoning-focused SFT+RL. Unlike the Competition-Coding teacher it's a general reasoning model — but the training data explicitly covers code and tool use (code execution + search), which is why it's relevant to coding/agent pipelines. NVIDIA's headline positioning: matches or beats DeepSeek V4 Pro (High) on GPQA, MMLU-Pro, LiveCodeBench v6, IMOAnswerBench, Apex Shortlist — unverifiable from the card itself. Custom architecture (`NemotronHForCausalLM`) — needs the repo's model code; no llama.cpp/Ollama path. No independent evals exist yet; treat all claims as lab-reported until verified.

## See also

- [[welcome]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Teacher-STEM
