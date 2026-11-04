---
title: "sensenova/SenseNova-Loop-9B-Preview"
org: sensenova
model_id: sensenova/SenseNova-Loop-9B-Preview
date: 2026-11-05
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - vl
  - looped
  - thinking
downloads: 2704
likes: 234
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/sensenova/SenseNova-Loop-9B-Preview
params: 9B total (~14.6B inference)
context: 262144
architecture: looped
---

# sensenova/SenseNova-Loop-9B-Preview

**One-line:** SenseTime's looped 9B multimodal (9B stored / ~14.6B inference params, 256K ctx, Apache-2.0) that beats Qwen3.5-27B on office/agent benches but trails it on raw terminal work — lab-reported Terminal-Bench 2.1 40.45, first looped-decoder open release from a major Chinese lab.

> ⚠ All benchmark numbers below are **lab-reported** (image-only chart on the model card, transcribed by third parties — no markdown table, no technical report yet, no independent eval). Treat as claims, not facts, until an independent run appears.

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
| τ-Bench | — (τ³-Banking 18.56, see below) | *lab-reported* |
| ToolACE | — | not published |
| GAIA | — | not published |
| Terminal-Bench 2.1 | 40.45 | *lab-reported* (vs Qwen3.5-27B 47.19, Qwen3.6-35B-A3B 40.45) |
| BIRD-Dev (text-to-SQL) | 71.38 | *lab-reported* (vs Qwen3.5-27B 69.84) |
| WorkBuddy Bench | 66.89 | *lab-reported* (vs Qwen3.6-35B-A3B 61.98) |
| AIDABench | 58.87 | *lab-reported* (vs Qwen3.5-27B 57.19) |
| TeamBench | 48.89 | *lab-reported* (vs Qwen3.6/Qwen3.5-27B 44.44) |
| AutomationBench | 13.72 | *lab-reported* (vs Qwen3.5-27B 10.17) |
| RaccoonPPTBench | 70.70 | *lab-reported* (vs Qwen3.6-35B-A3B 64.30; internal SenseTime bench) |
| TAU-Bench-3 Banking | 18.56 | *lab-reported* (vs Qwen3.5-27B 19.59) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — (mHC ablation +4.42 only, no absolute) | *lab-reported* |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** ~9B stored, ~14.6B inference (24-layer block executed twice)
- **Context length:** 262144 tokens (training recipes up to 256K)
- **VRAM (fp16 rough):** ~18 GB BF16 backbone + FP32 mHC routing params (call it ~20 GB)
- **Custom architecture:** yes — `sensenova_loop`, requires `trust_remote_code=True` (transformers 5.18). SGLang and vLLM support only via unmerged PR branches. 10 community GGUF quants exist but are text-only (no image input, no MTP).

## What makes it notable

First open release of a looped-decoder design from a major lab: 32 distinct decoder layers, middle 24 executed twice with shared weights plus two-stream manifold-constrained hyper-connections (mHC, Sinkhorn-constrained mixing), giving 56 layer executions and deeper reasoning at 9B storage cost. The eval story is office-agent shaped — it leads the comparison set on document/SQL/workflow benches (BIRD-Dev, WorkBuddy, AIDA, TeamBench, AutomationBench, RaccoonPPT) while trailing Qwen3.5-27B on Terminal-Bench 2.1 and banking tasks, so it reads as a long-context workflow agent backbone rather than a raw terminal coder. Caveats: every number is lab-reported with no protocol details and no technical report; the architecture needs custom model code everywhere (no stock vLLM/SGLang/llama.cpp day one); thinking mode exists but is opt-in. For local agent loops the honest fit is document-heavy tool workflows at ~20 GB, not SWE-bench-style repo work where it has no published number at all.

## See also

- [[welcome]]
- Source: https://huggingface.co/sensenova/SenseNova-Loop-9B-Preview
- Code: https://github.com/OpenSenseNova/SenseNova-Loop
