---
title: "Nanbeige/Nanbeige4.2-3B"
org: Nanbeige
model_id: Nanbeige/Nanbeige4.2-3B
date: 2026-08-07
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - looped-transformer
  - compact
downloads: 41552
likes: 684
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/Nanbeige/Nanbeige4.2-3B
params: 3B active (4B total)
context: 262144
architecture: dense (Looped Transformer)
---

# Nanbeige/Nanbeige4.2-3B

**One-line:** Smallest model with a 63.6 SWE-bench Verified — a 3B non-embedding Looped-Transformer agentic model that beats Qwen3.5-9B and Gemma4-12B on code-agent and tool-use benchmarks.

> Released 2026-07-21 (technical report arXiv:2607.22083); surfaced in this tracker via the 7-day trending window because its eval-results were published 2026-08-02. ⚠ All scores are **lab-reported** (model card + `.eval_results/` YAML) — no independent verification found yet.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | 72.5 (V6) | lab |
| Aider polyglot | — | — |
| SWE-bench Verified | 63.6 | lab (.eval_results) |
| SWE-bench Multilingual | — | — |
| SWE-bench Pro | 46.9 | lab (.eval_results) |
| Terminal-Bench 2.0 | 44.1 | lab (.eval_results) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| MCP-Atlas | 57.8 | lab |
| GDPval rubrics | 74.3 | lab |
| Claw-Eval (pass³) | 52.2 | lab (.eval_results) |
| Claw-Gym | 65.0 | lab |
| Pinch-Bench-V2 | 74.7 | lab |
| Agent-IF-Oneday | 67.5 | lab |
| Office-QA-Pro | 21.1 | lab |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 87.4 | lab (.eval_results) |
| MATH | — | — |
| AIME 2025 | — | — |
| HLE (w/o search) | 17.8 | lab (.eval_results) |
| HMMT Feb 2026 | 82.1 | lab (.eval_results) |
| SciCode | 35.6 | lab |
| IMO-Answer-Bench | 67.3 | lab |

## Efficiency

- **Active params:** 3B non-embedding (4B total — Looped Transformer reuses the 22 layers for extra capacity without extra parameters)
- **Context length:** 262,144 tokens (256k)
- **VRAM (fp16 rough):** ~8 GB for 4B total (≈6 GB for non-embedding weights + overhead); runs on a single 8-12 GB GPU
- **Deployment note:** custom `nanbeige` architecture (`modeling_nanbeige.py` with LoopSplit, mHC + depth attention, concatenated n-gram embeddings) — needs the repo's custom model code, not a stock transformers class. GGUF builds exist (owao, bartowski).

## What makes it notable

At 3B non-embedding params it posts 63.6 SWE-bench Verified, 46.9 SWE-bench Pro, and 44.1 Terminal-Bench 2.0 — 10+ points clear of Qwen3.5-9B (53.1) and Gemma4-12B (44.2) on the same suite, which makes it one of the strongest open-weight options for local agent loops on modest hardware. The agentic stack (MCP-Atlas 57.8, GDPval 74.3, Claw-Eval 52.2) shows tool-use tuning rather than pure reasoning. Caveats: everything is lab-reported, the custom architecture adds integration friction for llama.cpp-style stacks, and the 3B scale means long-horizon repo work will still trail 30B+ models. If the numbers reproduce, it's the best small-model agent candidate since Inkling-Small.

## See also

- [[welcome]]
- Source: https://huggingface.co/Nanbeige/Nanbeige4.2-3B
- Technical report: https://arxiv.org/abs/2607.22083
