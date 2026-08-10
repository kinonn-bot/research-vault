---
title: "Ling-3.0-tiny"
org: inclusionAI
model_id: inclusionAI/Ling-3.0-tiny
date: 2026-08-11
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid
  - instruct
  - long-context
  - local
downloads: 0
likes: 47
license: MIT
pipeline: text-generation
source: https://huggingface.co/inclusionAI/Ling-3.0-tiny
params: "1.3B active / 7.9B total (MoE, 128 experts, 8 routed + 1 shared per token)"
context: "128K native (131072); 256K via YaRN (262144 served)"
architecture: hybrid-linear moe (KDA + MLA, 3:1)
---

# Ling-3.0-tiny

**One-line:** Ant Group's (InclusionAI) small-class hybrid-linear reasoning MoE — 7.9B total / 1.3B active (KDA + MLA, 3:1, 128 experts) — built explicitly for local/edge agent loops; AA Intelligence Index 25 (v4.1.1) / Agentic Index 16, ~168 tok/s, FP8 runs on a single DGX Spark or M4 Pro MacBook.

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
| Terminal-Bench 2.1 | — | evaluated under AA protocol (Terminus 2 harness, 256K ctx) — number only in image-only chart |

*The card's benchmark table is a single image (no `.eval_results/` YAMLs shipped for tiny, unlike flash). Independent AA verification exists only as composite indices (below), not per-benchmark splits in extractable form. No HumanEval/MBPP/LiveCodeBench/Aider/SWE-bench numbers published anywhere — cells left `—` rather than invented.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published (AA Agentic Index includes τ³-Banking component, composite only) |
| ToolACE | — | not published |
| GAIA | — | not published |
| AA Agentic Index | 16 | Artificial Analysis (independent, composite) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| AA Intelligence Index v4.1.1 | 25 | Artificial Analysis (independent; composite of GDPval-AA v2, τ³-Banking, Terminal-Bench 2.1, SciCode, HLE, GPQA Diamond, CritPt, AA-Omniscience, AA-LCR) — #6/56 in class, class median 8 |
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | in image-only chart |
| MATH | — | not published |
| AIME 2025/2026 | — | in image-only chart |
| HLE | — | in image-only chart |

## Efficiency

- **Active params:** 1.3B per token (8 of 128 routed experts + 1 shared expert; 3:1 KDA–MLA hybrid-linear, 24 layers)
- **Total params:** 7.9B (disk-resident footprint)
- **Context length:** 128K native (max_position_embeddings 131072), served at 262,144 via YaRN (rope_theta 6,000,000)
- **VRAM (fp16 rough):** ~16 GB fp16; FP8 ≈ 8 GB; card claims ~8.34 GiB peak memory at 8K ctx. Card-verified deployments: NVIDIA DGX Spark 100–105 tok/s (FP8), Apple Silicon M4 Pro MacBook 86–90 tok/s. BF16/FP8/INT4 weights all provided — genuinely single-box/consumer class.
- ⚠ custom architecture (`BailingMoeV3ForCausalLM`, `trust_remote_code` required — custom model code in repo, not stock transformers). Ollama support in-flight (PR #17643, MLX on Apple Silicon only); SGLang has a dedicated cookbook + pre-built image; vLLM via `vllm-ling-v3` branch.

## What makes it notable

A rare genuinely-small agentic MoE from a major lab: 1.3B active params puts it in the class of models that actually run on a laptop or edge box while scoring AA Intelligence Index 25 — well above its class median (8) and in the same class as much larger reasoning models, per independent AA testing. The hybrid KDA+MLA architecture (borrowed from Kimi Delta Attention + MLA) and 128-expert sparse MoE are the same family as the much larger Ling-3.0-flash (124B), shrunk to consumer hardware — flash's eval files proved the family's reasoning profile (SWE-bench Pro 56.6, AIME 93.2); tiny ships no machine-readable evals, so treat agentic claims as lab-positioned with only AA's composite as independent verification. Positioning vs local leaders: for a 1.3B-active footprint this is one of the strongest agentic-on-paper options (free on OpenRouter until 8/14), but the missing per-benchmark numbers and the custom-code requirement mean verify it yourself before building agent loops on it. Native thinking mode + `ling3` tool-call parser (SGLang/vLLM) make it directly agent-loop deployable.

## See also

- [[welcome]]
- Source: https://huggingface.co/inclusionAI/Ling-3.0-tiny
- Sibling: [[inclusionAI--Ling-3.0-flash]]
