---
title: "CohereLabs North Mini Code 1.0"
org: CohereLabs
model_id: CohereLabs/North-Mini-Code-1.0
date: 2026-11-10
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
downloads: 8301
likes: 588
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/CohereLabs/North-Mini-Code-1.0
params: 3B active (30B total MoE)
context: 262144
architecture: moe
---

# CohereLabs North Mini Code 1.0

**One-line:** Cohere's first open dev model — 30B MoE with only 3B active params posting SWE-bench Verified 67.6, strong for its compute class.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | 67.6 | lab (.eval_results) |
| SWE-bench Multilingual | — | — |
| SWE-bench Pro | 40.2 | lab (.eval_results) |
| Terminal-Bench 2.0 | 36.0 | lab (.eval_results) |
| Terminal-Bench Hard | 31.1 | lab (release table) |

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
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |

## Efficiency

- **Active params:** 3B (30B total MoE)
- **Context length:** 256K tokens (64K max output)
- **VRAM (fp16 rough):** ~60 GB
- **Architecture note:** custom `cohere2_moe` (`Cohere2MoeForCausalLM`) — verify transformers version support before local deploy; FP8 variant (`CohereLabs/North-Mini-Code-1.0-fp8`) also published

## What makes it notable

Cohere's first open-source agentic coding model (June 2026, Apache-2.0), trained with a long-to-longer SFT cascade over 70k+ verifiable tasks across ~5k repos, deduplicated against SWE-bench sources. SWE-V 67.6 at 3B active is an efficiency standout vs larger dense coders. Surfaced in this run via the 2026-11-09 RedHatAI mirror re-upload (`RedHatAI/North-Mini-Code-1.0`, same 49-shard weights) — canonical repo is June, never previously tracked in this vault. Lab numbers corroborated by independent writeup (Raschka); no AA-indexed coding subscore captured at write time.

## See also

- [[welcome]]
- Source: https://huggingface.co/CohereLabs/North-Mini-Code-1.0
- Blog: https://huggingface.co/blog/CohereLabs/introducing-north-mini-code
