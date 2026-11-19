---
title: "Microsoft Aion-1.0-Instruct-2.3B"
org: microsoft
model_id: microsoft/Aion-1.0-Instruct-2.3B
date: 2026-11-20
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - slm
  - on-device
downloads: 788
likes: 66
license: mit
pipeline: text-generation
source: https://huggingface.co/microsoft/Aion-1.0-Instruct-2.3B
params: 2.3B dense
context: 32768
architecture: dense
---

# Microsoft Aion-1.0-Instruct-2.3B

**One-line:** Microsoft Windows on-device SLM (Applied Sciences Group, Phi Silica successor, MIT, 32K) — ⚠ no published coding/agentic benchmarks, agent-loop suitability unknown.

> New release 2026-11-18 (created 17:05Z, ~27h before this run) from Microsoft Windows & Devices. MIT license, `pipeline_tag: text-generation`, not gated. Quantized ONNX/WebGPU sibling (`-ONNX-WebGPU`) + community GGUFs appeared same-day, corroborating a real drop. All numbers below are lab-reported (lm-eval-harness; GPT-4o judge where marked †).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
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
| MMLU / MMLU-Pro | 55.15 / 33.35 | lab (lm-eval-harness) |
| MMMLU (multilingual) | 45.51 | lab |
| GPQA Diamond | 28.18 | lab |
| MATH (MATH-500) | 48.00 | lab |
| GSM8K / GSMPlus | 74.91 / 49.56 | lab |
| IFEval / IFBench / Multi-IF | 83.90 / 32.00 / 64.70 | lab |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** 2.3B dense
- **Context length:** 32,768 tokens
- **VRAM (fp16 rough):** ~4.6 GB — fits iGPU / edge / 8GB cards; GGUF + ONNX-WebGPU builds published day one

## What makes it notable

Successor to Phi Silica as the Windows OS SLM (ships in Windows alongside a content-moderation model by end of Jan 2027, per the card). Training data extends Phi Silica's with synthetic math, coding-adjacent, and common-sense reasoning data; 8 languages (multilingual ~6%). Positioned for document comprehension, summarization, rewriting, and chat — NOT for code or tool use: MMLU 55.15 is far below current 2–4B coding peers, and no HumanEval/MBPP/BFCL numbers exist. Usable as a tiny local chat/summarization endpoint inside agent scaffolding, not as the acting model.

## See also

- [[welcome]]
- Source: https://huggingface.co/microsoft/Aion-1.0-Instruct-2.3B
- Sample code: https://github.com/microsoft/Aion-Instruct-Preview-Sample
