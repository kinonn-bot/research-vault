---
title: "Ricursive / Ripple-65B Preview"
org: ricursiveAI
model_id: ricursiveAI/Ripple-65B-Preview
date: 2026-11-06
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
downloads: 939
likes: 239
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/ricursiveAI/Ripple-65B-Preview
params: 65B dense
context: 1000000
architecture: dense
---

# Ricursive / Ripple-65B Preview

**One-line:** From-scratch US-lab debut — 65B dense, Apache-2.0, 1M context; US open-weight SOTA on Terminal-Bench 2.1 (80.5), beating 500B–975B MoE models.

Public launch 2026-11-05 (repo staged 11-04, weights + launch blog + socials 11-05). First open-weight model from Ricursive Intelligence (chip-design lab); general-purpose variant of the proprietary model behind its AI chip-design platform. Pretrained from scratch on 12T tokens. Ships BF16 + NVFP4 + DFlash2 + pretrain-only base repos.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | *70.9 (base model, internal Olmes fork)* | *lab* |
| HumanEval+ | — | — |
| MBPP Sanitized | *81.5 (base model, internal Olmes fork)* | *lab* |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | *76.5* | *lab* |
| SWE-bench Pro v1.0 | *61.42* | *lab* |
| SWE-bench Pro v2.0 Hard | *79.1 (Terminus 2)* | *lab* |
| DeepSWE 1.1 | *44.3 (Terminus 2)* | *lab* |
| Terminal-Bench 2.1 | *80.5 (self-reported and Terminus-2 rerun agree)* | *lab* |
| SciCode | *39.4* | *lab* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench (τ³ banking) | *31.27* | *lab* |
| ToolACE | — | — |
| GAIA | — | — |
| MCP Atlas | *71.67* | *lab* |
| AutomationBench (public) | *36.4* | *lab* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU | *89.6* | *lab* |
| MMLU-Pro | *84.2* | *lab* |
| GPQA Diamond | *85.2* | *lab* |
| AIME 2024 / 2025 / 2026 | *97.1 / 98.3 / 95.0* | *lab* |

## Efficiency

- **Active params:** 65B (dense, thin-and-deep: d_model 5120, 80 layers)
- **Context length:** 1000000 tokens
- **VRAM (fp16 rough):** ~130 GB (NVFP4 checkpoint + Colab published for local start; lab claims DGX Spark fits)

## What makes it notable

Deliberately anti-MoE bet: dense Transformer with overprovisioned attention heads, SWA + global NoPE mix, trained with plain sharding and 40% MFU by a 1→5-person team — yet it tops Terminal-Bench 2.1 among US open-weight models and matches Reflection Beam 501B on SWE-bench Verified (76.5 vs 81.6) at ~1/8th the total params. The honest-eval posture (own harness reruns of competitors, Terminus-2 cross-checks, "best-effort fair comparison" caveats) reads cleaner than most launch cards. For local agent loops the 65B dense envelope is far friendlier than the 500B+ MoEs it beats — NVFP4 makes single-node serving realistic.

## See also

- [[welcome]]
- Source: https://huggingface.co/ricursiveAI/Ripple-65B-Preview
- Launch blog: https://www.ricursive.com/ripple
