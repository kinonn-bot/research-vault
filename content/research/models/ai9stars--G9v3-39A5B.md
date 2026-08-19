---
title: "AI9Stars G9v3-39A5B"
org: ai9stars
model_id: ai9stars/G9v3-39A5B
date: 2026-08-19
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - instruct
  - long-context
  - tool-calling
  - reasoning
  - custom-architecture
downloads: 2877
likes: 73
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/ai9stars/G9v3-39A5B
params: 39B total / 5B active (MoE)
context: 131072
architecture: moe (G9v3ForCausalLM, 320 routed experts, 32 experts/tok, 38 layers, gated attention)
---

# AI9Stars G9v3-39A5B

**One-line:** 39B-total/5B-active reasoning MoE from AI9Stars with 131K context + native tool calling — AA Intelligence Index 32 (#6 in its size class), but a preview release with custom architecture and no published coding/agent-loop benchmark split yet. ⚠ surfaced via the trending window (repo lastModified 08-19; release ~08-03, no prior vault note) — not a fresh first-drop.

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

*No per-benchmark coding table on the card. Independent Artificial Analysis coverage: SciCode **38.2%**, AA Coding Index **31.7** (disaggregated from the AA composite). No SWE-bench Verified / Aider / LiveCodeBench / BFCL figure published anywhere found — agent-loop repo-resolution suitability unverified.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |

*Card carries `tool-calling` tag and ships supports Think / No Think modes, but publishes no BFCL / τ-Bench / ToolACE / GAIA number. Tool-use capability is claimed, not independently benchmarked.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| AA Intelligence Index | 32 | Artificial Analysis (independent — #6/135 in class) |
| SciCode | 38.2% | Artificial Analysis (independent) |
| GPQA Diamond | ~75.6% (in AA composite) | Artificial Analysis (composite) |
| AA-LCR | 60.3% | Artificial Analysis |
| MMLU / MMLU-Pro | — | not published |
| AIME | — | not published |

## Efficiency

- **Active params:** 5B (MoE, 39B total — sparse design keeps inference cost near a small dense model)
- **Context length:** 131,072 tokens (131K, rope_theta 5e6, no rope_scaling)
- **VRAM (fp16 rough):** ~78 GB for full 39B weights (5B active). Quantization needed for consumer GPUs; no official GGUF published — custom architecture blocks stock llama.cpp loading.
- **Runs on:** vLLM (≥0.21), SGLang (≥0.5.12), Transformers (≥5.6) — **custom model code required** (`G9v3ForCausalLM`, `configuration_g9v3.py` / `modeling_g9v3.py` shipped in-repo). Not loadable by stock transformers 4.x without the custom files, and not llama.cpp-compatible.

## What makes it notable

G9v3-39A5B is a sparse reasoning MoE (5B active of 39B) pairing 131K context with tool-calling and Think/No-Think modes — a strong Intelligence-vs-active-params ratio for self-hosted agent use (AA Intelligence Index 32, well above the class median of 9). Treat it as a promising but preview release: the card publishes zero coding/agent-loop benchmark splits (only the AA composite + SciCode exist independently), it's flagged `preview`, and its **custom architecture** means no llama.cpp/Ollama GGUF path yet — you'd need vLLM/SGLang or the repo's own modeling code. For the local agent-runner it's worth watching for a fuller eval release and community GGUF, but agent-loop repo-resolution suitability is unverified at this point. Released under Apache-2.0, not gated.

## See also

- [[welcome]]
- Source: https://huggingface.co/ai9stars/G9v3-39A5B
- Artificial Analysis: https://artificialanalysis.ai/models/g9v3-39a5b
