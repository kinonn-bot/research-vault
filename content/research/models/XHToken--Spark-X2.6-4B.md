---
title: "XHToken Spark-X2.6-4B"
org: XHToken
model_id: XHToken/Spark-X2.6-4B
date: 2026-10-22
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - on-device
  - long-context
  - tool-calling
  - reasoning
  - custom-architecture
downloads: 85
likes: 133
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/XHToken/Spark-X2.6-4B
params: "4B dense (custom model_type spark2_5)"
context: "1,048,576 (1M tokens)"
architecture: "dense — 36 layers (27 sliding-window-512 + 9 full-attention), hidden 2560, head_dim 256, 16 Q / 4 KV heads, tied embeddings, vocab 131k"
---

# XHToken Spark-X2.6-4B

**One-line:** XHToken/SparkLLM's on-device 4B agent model — same architecture as Spark-X2.5-4B, capability gains entirely from improved post-training; lab-reported SWE-bench Verified 62.8 (vs 41.6 for X2.5), BFCL-V4 71.8, τ²-bench 86.9 at ~2.5 GB Q4 on llama.cpp, with selectable thinking levels (none/low/high). Weights 2026-10-19, quant siblings 10-20, card finalised 10-21 — captured late (missed by the 10-20 and 10-21 runs on the download floor).

> ⚠ All numbers below are **lab-reported**, transcribed from the card's benchmark charts (`images/benchmark.svg`, `images/all_benchmark.svg` — no markdown tables on the card). Cells marked `*` on the card are copied from competitors' published model cards; the rest are the Spark team's own runs in thinking mode with `thinking_level=high`. No independent evaluation as of 2026-10-22 (Artificial Analysis / BenchLM have no entry for the X2.6 line yet). The 62.8 SWE-bench Verified figure is unusually high for a 4B dense model and rests on the lab's own harness — treat as unverified.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 62.8 | lab — card chart (X2.5-4B 41.6, Qwen3.5-9B 53.1, Gemma4-12B 44.2) |
| SWE-bench Pro | 54.3 | lab — card chart (X2.5-4B 44.4) |
| SWE-bench Multilingual | 64.7 | lab — card chart (X2.5-4B 53.3) |
| SciCode | 36.8 | lab — card chart |
| SWebBench (in-house web agent bench) | 71.7 | lab — card chart (dataset to be open-sourced) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL-V4 | 71.8 | lab — card chart (X2.5-4B 65.1; Qwen3.5-9B 66.1*) |
| τ²-bench | 86.9 | lab — card chart (X2.5-4B 75.1; Qwen3.5-9B 79.1*) |
| τ³-bench | 34.7 | lab — card chart (X2.5-4B 30.4; Qwen3.5-9B 9.3) |
| MCP-Atlas | 62.4 | lab — card chart (X2.5-4B 54.6) |
| BrowseComp | 53.1 | lab — card chart (X2.5-4B 40.9) |
| PAgentBench (in-house personal-assistant bench) | 74.1 | lab — card chart |
| VitaBench2.0 | 30.8 | lab — card chart |
| EnterpriseOps-Gym | 33.6 | lab — card chart |
| ClawEval-EN | 69.9 | lab — card chart |
| ToolACE | — | not published |
| Tool-use support | SGLang `--tool-call-parser spark25`, Qwen3 reasoning parser, thinking levels none/low/high | card |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA / GPQA Diamond | 69.9 / 77.1 | lab — card chart |
| MATH (Gaokao 2026, 5 papers) | 134.9 | lab — card chart |
| AIME 2026 | 91.2 | lab — card chart |
| HMMT Feb 26 / IMO-AnswerBench | 81.3 / 75.2 | lab — card chart |
| IFEval / IFBench | 93.6 / 75.8 | lab — card chart |
| HLE (no tools / with tools) | 17.9 / 36.9 | lab — card chart |
| AA-LCR v1.1 / LongBench v2 | 67.3 / 53.3 | lab — card chart |
| Card average (30 benchmarks) | 63.3 | lab — card chart (X2.5-4B 52.1, Qwen3.5-9B 49.1) |

## Efficiency

- **Active params:** 4B dense (all params active; no MoE)
- **Context length:** 1,048,576 (1M) — graph-walk and multi-needle retrieval rows published at 256k and 1M; best-in-class long-context retention vs X2.5 (Graphwalks BFS 256k F1 92.2 vs 47.1)
- **VRAM (fp16 rough):** ≈8 GB BF16; ≈2.5–3 GB at Q4_K_M (llama.cpp) — laptop/edge class
- **Runtime:** ⚠ custom architecture (`model_type: spark2_5`, `Spark2_5ForCausalLM` via `auto_map` + `trust_remote_code`); native llama.cpp support needs b10828+, Ollama v0.34.1+, LM Studio 0.4.0+; SGLang/vLLM/MLX recipes on the card. Throughput per card: ~210 tok/s decode and ~18k tok/s prefill at 4K on an RTX 4090 with llama.cpp Q4_K_M
- Sibling family: [Base](https://huggingface.co/XHToken/Spark-X2.6-4B-Base) · [GGUF](https://huggingface.co/XHToken/Spark-X2.6-4B-GGUF) · [FP8](https://huggingface.co/XHToken/Spark-X2.6-4B-FP8) · [INT8](https://huggingface.co/XHToken/Spark-X2.6-4B-INT8) · [INT4](https://huggingface.co/XHToken/Spark-X2.6-4B-INT4)

## What makes it notable

If the numbers hold, this is the best coding/agent-per-byte open model in the sub-5B class: SWE-bench Verified 62.8 and τ²-bench 86.9 out of 4B dense parameters, beating the lab's own 9B-class comparison points (Qwen3.5-9B, Gemma4-12B) on nearly every coding and agent row, with the long-context retention gap (Graphwalks 256k 92.2 vs 47.1 for X2.5) the biggest single jump. For a local agent loop it is the most actionable size in this run: ~3 GB quantised, day-0 llama.cpp/Ollama/LM Studio support, structured tool calls with a `spark25` parser, and a controllable thinking budget for latency/cost trade-offs. Two caveats: all evidence is the lab's own harness (no independent eval yet), and the custom `spark2_5` architecture means runtimes need the repo's remote code or a recent llama.cpp build. Release timing: weights 10-19, quant siblings 10-20, card finalised 10-21 — vaulted as a late capture, below the tracker's launch-day download floor.

## See also

- [[welcome]]
- Source: https://huggingface.co/XHToken/Spark-X2.6-4B
- Predecessor: [XHToken/Spark-X2.5-4B](https://huggingface.co/XHToken/Spark-X2.5-4B) · Ollama: `ollama run SparkLLM/Spark-X2.6-4B`
