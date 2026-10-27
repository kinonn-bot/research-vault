---
title: "XHToken Spark-X2.6-1.7B (on-device agent)"
org: XHToken
model_id: XHToken/Spark-X2.6-1.7B
date: 2026-10-28
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - tool-use
  - reasoning
  - long-context
  - edge
downloads: 0
likes: 22
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/XHToken/Spark-X2.6-1.7B
params: "1.7B dense"
context: "1048576 (1M)"
architecture: "dense hybrid-attention (3:1 sliding-512 : full, 28 layers; custom spark2_5 arch, trust_remote_code; native llama.cpp b10828+, Ollama, LM Studio, MLX)"
---

# XHToken Spark-X2.6-1.7B (on-device agent)

**One-line:** iFlytek SparkLLM's 1.7B sibling of the tracked Spark-X2.6-4B — same architecture as X2.5-1.7B, gains entirely from improved post-training; lab-reported SWE-bench Verified 59.8 (vs 28.3 for X2.5), BFCL-V4 55.2 and τ²-bench 85.3 with controllable thinking levels, 0 HF downloads (Ollama/LM Studio distribution) but a genuine 10-19 lab release.

> ⚠ All scores below are **lab-reported**, transcribed exactly from the card's `images/all_benchmark.svg` chart (no markdown tables on the card; tag-stripped SVG text is exact, no OCR). Cells marked `*` on the card are copied from competitors' published cards; the rest are Spark-team runs in thinking mode (`thinking_level=high`, temp 1.0 / top_p 0.95). No independent evaluation as of 2026-10-28. SWebBench and PAgentBench are in-house benchmarks (open-sourcing "soon") — indicative, not controlled. Weights 2026-10-19, GGUF/FP8/INT4/INT8 siblings 10-20/26 — first captured this run (missed on the download floor: HF shows 0 downloads, distribution runs through Ollama `SparkLLM/Spark-X2.6-1.7B` and LM Studio).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 59.8 | lab — card SVG (vs X2.5-1.7B 28.3, MiniCPM5-2B 46.4, Qwen3.5-2B 6.8, X2.6-4B 62.8) |
| SWE-bench Multilingual | 57.3 | lab — card SVG (vs X2.5-1.7B 23.3, MiniCPM5-2B 23.7, X2.6-4B 64.7) |
| SWE-Bench Pro | 26.7 | lab — card SVG (vs X2.5-1.7B 10.4, X2.6-4B 54.3) |
| SciCode | 20.1 | lab — card SVG (vs X2.5-1.7B 18.2, X2.6-4B 36.8) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL-V4 | 55.2 | lab — card SVG (vs X2.5-1.7B 46.9, MiniCPM5-2B 66.6, X2.6-4B 71.8) |
| τ-Bench | — | not published (τ²/τ³ below are different suites — do not compare) |
| τ²-bench | 85.3 | lab — card SVG (vs X2.5-1.7B 65.3, MiniCPM5-2B 82.2, X2.6-4B 86.9) |
| τ³-bench Banking | 21.3 | lab — card SVG (vs X2.5-1.7B 20.1, X2.6-4B 34.7) |
| ToolACE | — | not published |
| GAIA | — | not published |
| MCP-Atlas | 41.8 | lab — card SVG (vs X2.5-1.7B 23.4, X2.6-4B 62.4) |
| VitaBench2.0 | 22.6 | lab — card SVG (vs X2.5-1.7B 8.3, X2.6-4B 30.8) |
| EnterpriseOps-Gym | 26.1 | lab — card SVG (vs X2.5-1.7B 10.5, X2.6-4B 33.6) |
| ClawEval-EN | 66.9 | lab — card SVG (vs X2.5-1.7B 57.9, X2.6-4B 69.9) |
| BrowseComp | 41.7 | lab — card SVG (vs X2.5-1.7B 29.7, X2.6-4B 53.1) |
| SWebBench (in-house) | 53.9 | lab — card SVG, web-browse/retrieval harness (vs X2.5-1.7B 31.6, X2.6-4B 71.7) |
| PAgentBench (in-house) | 58.8 | lab — card SVG, personal-assistant tasks (vs X2.5-1.7B 51.1, X2.6-4B 74.1) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA | 51.3 | lab — card SVG (vs X2.5-1.7B 43.8, X2.6-4B 69.9) |
| GPQA Diamond | 56.1 | lab — card SVG (vs X2.5-1.7B 46.8, X2.6-4B 77.1) |
| MATH | — | not published (Gaokao-2026 118.9/150, AIME-2026 70.1, HMMT-Feb-26 48.8 on card) |
| AIME 2025 | — | not published (AIME-2026 70.1 per card SVG) |
| HLE (no tools / with tools) | 8.7 / 19.9 | lab — card SVG |

## Efficiency

- **Active params:** 1.7B dense (28 layers, hidden 2048, 8Q/2KV GQA, vocab 131072)
- **Context length:** 1048576 (1M) tokens (config max_position_embeddings; 3:1 sliding-512 : full attention)
- **VRAM (fp16 rough):** ≈3.4 GB BF16; Q4 ≈1 GB — llama.cpp native (b10828+), Ollama, LM Studio, MLX (`Spark-MLX-LLM`), SGLang/vLLM via Spark plugin; custom arch needs `trust_remote_code` outside llama.cpp/Ollama

## What makes it notable

The second Spark-X2.6 model and the strongest sub-2B coding-agent claim in the window: SWE-V more than doubles its X2.5 predecessor (59.8 vs 28.3) at the same 1.7B/1.7B architecture — pure post-training gains — and lands within 3pp of its 4B sibling (62.8) on SWE-V/Multilingual while trailing it on BFCL (55.2 vs 71.8) and the in-house suites. For on-device agent loops it is the direct alternative to LFM3-1.7B (also 1.7B, also new this week): Spark leads coding (SWE-V 59.8 vs 43.40), Liquid leads tool-calling (BFCL 71.39 vs 55.2). Controllable thinking levels (none/low/high) let harnesses trade reasoning for latency. Caveats: all numbers lab-reported on an undisclosed harness, no LiveCodeBench/Aider to cross-check, and HF download counts are uninformative (0 — the model ships via Ollama/LM Studio).

## See also

- [[welcome]]
- Source: https://huggingface.co/XHToken/Spark-X2.6-1.7B
- Sibling: https://huggingface.co/XHToken/Spark-X2.6-4B
- Base: https://huggingface.co/XHToken/Spark-X2.6-1.7B-Base
