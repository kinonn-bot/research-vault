---
title: "Danish Foundation Models DFM-Mimir"
org: danish-foundation-models
model_id: danish-foundation-models/DFM-Mimir
date: 2026-08-20
tags:
  - huggingface
  - text-generation
  - coding
  - instruct
  - dense
  - foundation-model
  - danish
downloads: 2617
likes: 24
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/danish-foundation-models/DFM-Mimir
params: "~1B dense"
context: "4096"
architecture: dense (HRM-Text, hidden 1536, 16 layers)
---

# Danish Foundation Models DFM-Mimir

**One-line:** 1B-parameter model trained **from scratch** on permissible data (HRM-Text architecture, 70.5B tokens/epoch over 161 datasets) — SOTA for Danish, competitive English (~1B class). Apache-2.0. ⚠ small 4K context and Danish/English-only scope limit agent-loop utility.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | 56.7 | lab-reported (card) |
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
| MMLU / MMLU-Pro | 57.5 (MMLU) | lab-reported (card) |
| GPQA Diamond | — | not published |
| MATH | 45.8 | lab-reported (card) |
| AIME 2025 | — | not published |
| GSM8K | 89.9 | lab-reported (card) |

## Efficiency

- **Active params:** ~1B dense (no MoE, all active)
- **Context length:** 4,096 tokens
- **VRAM (fp16 rough):** ~2 GB weights
- **Runtime:** standard transformers (model_type `hrm_text`, safetensors, `endpoints_compatible`), no custom kernels needed

## What makes it notable

DFM-Mimir is a rare open 1B model trained entirely from permissible, audit-scrutinized data (Danish project by Univ. Southern Denmark / Aarhus / Copenhagen + Alexandra Institute, Ministry-funded) with a published memorisation/copyright audit and technical report. It beats prior HRM-Text 1B and sits near larger 2-4B peers on its English benchmark average (69.0 vs Qwen3.5-4B 69.3) and is the clear SOTA for Danish. For the coding/agent tracker specifically it's a modest candidate: coding ability is a side effect of general training (HumanEval 56.7, MATH 45.8) rather than a focus, and the 4K context plus Danish/English-only scope make it a poor agent-loop workhorse compared to 1B models like MiniCPM5-1B (128K context, native tool calling). Its real-value case is researchers/users who need an open, ethically-sourced, audit-clean small model for Danish-language or low-risk English tasks.

## See also

- [[welcome]]
- Source: https://huggingface.co/danish-foundation-models/DFM-Mimir
- Paper: https://arxiv.org/abs/2608.13517
