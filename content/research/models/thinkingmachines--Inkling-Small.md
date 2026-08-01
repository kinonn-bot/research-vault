---
title: "Inkling-Small"
org: thinkingmachines
model_id: thinkingmachines/Inkling-Small
date: 2026-07-27
tags:
  - huggingface
  - coding
  - agentic
  - moe
  - multimodal
  - vl
  - instruct
  - million-token-context
downloads: 3998
likes: 209
license: apache-2.0
pipeline: image-text-to-text
source: https://huggingface.co/thinkingmachines/Inkling-Small
params: "12B active / 276B total (MoE, 6/256 routed + 2 shared)"
context: "1M tokens"
architecture: moe (multimodal)
---

# Inkling-Small

**One-line:** Thinking Machines' second open-weight model — a 12B-active MoE that matches or beats its 41B-active sibling Inkling on SWE-bench Verified (80.2 vs 77.6) while being ~1/4 the size; natively multimodal (text/image/audio in), Apache-2.0. ⚠ large (276B total, NVFP4 ~140GB).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 80.2 | lab (bash-only harness) |
| SWE-bench Multilingual | — | not published |
| SWE-bench Pro (public) | 55.9 | lab |
| Terminal Bench 2.1 | 64.7 | lab (internal coding harness; contaminated web-search solutions zeroed) |
| SciCode | 48.7 | lab |

*SWE-bench Verified 80.2 beats Qwen3.5-397B-A17B (76.4), MiniMax M2.7 (79.9), DeepSeek V4 Flash (79.0) and sibling Inkling (77.6) in the card's own comparison table; within ~2 points of DeepSeek-V4-Flash-0731's class. Lab-reported (bash-only harness per card footnote); echoed by benchlm and VentureBeat coverage.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published (Tau 3 Banking: 15.5 lab — weak vs DeepSeek V4 Flash 22.9) |
| ToolACE | — | not published |
| GAIA | — | not published |
| MCP Atlas (public/all) | 79.6 / 79.2 | lab |
| Toolathlon Verified | 54.4 | lab |
| BrowseComp (with context mgmt) | 77.4 | lab |

*MCP Atlas 79.6 is the strongest open-weight number in the card's table (sibling Inkling 78.8, DeepSeek V4 Flash 69.0). Tool-use is a clear strength; multi-turn reliability (τ-Bench banking) is the weak spot.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 89.5 | lab |
| MATH | — | not published |
| AIME 2026 | 95.5 | lab |
| HLE (text / with tools) | 31.6 / 47.8 | lab |
| HMMT Feb 2026 | 90.2 | lab |
| AA Index (v4.1) | 40.0 | lab (Artificial Analysis index in card) |

## Efficiency

- **Active params:** 12B (per token — 6 of 256 routed + 2 shared experts; 42-layer hybrid local/global attention)
- **Total params:** 276B (full disk-resident weight footprint)
- **Context length:** 1,048,576 tokens (1M)
- **VRAM (fp16 rough):** ~552 GB full precision — NOT realistic locally. Official NVFP4 release (thinkingmachines/Inkling-Small-NVFP4) ≈ 140 GB; BF16 variant is for multi-GPU serving (SGLang/vLLM recipes provided). ⚠ large — single-node multi-GPU or heavy quant required.

## What makes it notable

Inkling-Small is the efficiency story of late July 2026: at 12B active it matches or beats its 41B-active sibling Inkling on SWE-bench Verified (80.2 vs 77.6), Terminal-Bench 2.1 (64.7 vs 63.8) and HLE (31.6 vs 29.7), and tops the open-weight field on MCP Atlas (79.6). It's Apache-2.0, natively multimodal, 1M context, with first-class SGLang/vLLM/Unsloth recipes — one of the strongest agent-capable open weights per active-param. Caveats: 276B total means NVFP4 ~140GB to run locally, τ-Bench banking is notably weak (15.5), and all headline numbers are lab-reported from Thinking Machines' own harness.

## See also

- [[welcome]]
- Sibling: Inkling (thinkingmachines/Inkling, 41B active, created 2026-07-14)
- Source: https://huggingface.co/thinkingmachines/Inkling-Small
