---
title: "pinkelephantlimited/pinkelephant-llm-48b-s"
org: pinkelephantlimited
model_id: pinkelephantlimited/pinkelephant-llm-48b-s
date: 2026-08-15
tags:
  - huggingface
  - text-generation
  - coding
  - moe
  - custom-architecture
  - instruct
downloads: 1415
likes: 0
license: mit
pipeline: text-generation
source: https://huggingface.co/pinkelephantlimited/pinkelephant-llm-48b-s
params: "~14.66B active / 47.7B total (MoE, 8 experts top-2)"
context: "16,384 tokens"
architecture: moe (custom, PinkElephantForCausalLM)
---

# pinkelephantlimited/pinkelephant-llm-48b-s

**One-line:** A 47.7B MoE (8 experts, top-2, ~30% active) upcycled from a dense 14.8B core, refined over two SFT epochs on a 99,661-example code+math curriculum, MIT-licensed. ⚠ weak coding numbers for the size (HumanEval 70.12%, MATH-500 38.4%) and zero agentic/tool-use evals — agent-loop suitability unknown. ⚠ custom architecture (`PinkElephantForCausalLM`, auto_map custom code) — stock llama.cpp/transformers won't load it without the repo's custom model code.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | *70.12* | *lab-reported (115/164 pass@1, greedy; parent 14B was 71.34)* |
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
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | *38.4 (MATH-500)* | *lab-reported (parent 14B was 63.4 — the MoE upcycle actually regressed math)* |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** ~14.66B (30.7%) of 47.7B total — MoE, 8 experts, top-2 routing
- **Context length:** 16,384 tokens
- **VRAM (fp16 rough):** ~95 GB full weights (all experts must be resident); ~29 GB if only active params streamed — practical local use needs quantization + custom loader
- **Architecture note:** custom `PinkElephantForCausalLM` with `auto_map` custom code — will NOT load in stock llama.cpp/transformers; requires the repo's modeling code.

## What makes it notable

A fully-public research lineage (dense 14.8B → upcycled 48B MoE → refined 48B-S) with every artifact MIT-licensed and auditable eval JSONs in-repo. But for the coding/agent use case it's not competitive: HumanEval 70.12% is well below what current 7B-14B models achieve, MATH-500 regressed vs its own dense parent (38.4 vs 63.4), and there are no agentic evals at all. The custom architecture is a deployment blocker for the standard local stack. Tracked because it qualified on structure (MIT, text-gen, lastModified today, 1.4k downloads); treat as a research curiosity, not a coding workhorse.

## See also

- [[welcome]]
- Source: https://huggingface.co/pinkelephantlimited/pinkelephant-llm-48b-s
