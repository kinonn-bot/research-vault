---
title: "zgcagi/ZGCM-1-7B"
org: zgcagi
model_id: zgcagi/ZGCM-1-7B
date: 2026-09-16
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - dense
  - custom-architecture
  - open-weights
  - long-context
  - math
downloads: 1162
likes: 23
license: mit
pipeline: text-generation
source: https://huggingface.co/zgcagi/ZGCM-1-7B
params: 7.39B dense
context: 262144
architecture: dense (hybrid gated-sliding-window + global attention)
---

# zgcagi/ZGCM-1-7B

**One-line:** From-scratch 7.39B dense math + agentic-search model from Zhongguancun Academy/ZIAI — GAIA text-only 42.52 with up to 64 web search-and-read steps, 256K context, MIT license, fully open training recipe.

⚠ Surfaced via web-search/HF trending-papers (below the API streams' download cutoff at 406 downloads, createdAt 09-07 just outside the 36h window). All numbers are **lab-reported** from the tech report (arXiv 2609.13356) — no independent third-party eval yet; custom `ZgcmForCausalLM` architecture requires `trust_remote_code=True`, so llama.cpp/Ollama support is not a given.

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
| GAIA | 42.52 (text-only) | *lab-reported* (tech report) |
| WebWalkerQA | 63.09 | *lab-reported* (tech report) |
| BrowseComp | 19.43 | *lab-reported* (tech report) |
| Binary Function Search | 62.00 (31/50 Ghidra tool) | *lab-reported* (tech report) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH-500 | 97.13 | *lab-reported* |
| AIME 2024 | 80.62 | *lab-reported* |
| AIME 2025 | 73.33 | *lab-reported* |
| AIME 2026 | 75.00 | *lab-reported* |
| HMMT 2025 | 70.42 | *lab-reported* |

## Efficiency

- **Active params:** 7.39B dense (32 layers, hidden 4096; 27 gated sliding-window GQA layers + 5 global layers)
- **Context length:** 262,144 tokens (256K)
- **VRAM (fp16 rough):** ~15 GB — needs quant (Q4 ≈ 4–5 GB) for consumer GPUs and Pi-class devices; ⚠ custom architecture means GGUF availability unverified

## What makes it notable

- Strongest published agentic-search numbers at 7B scale: GAIA text-only 42.52 and WebWalkerQA 63.09 with up to 64 web-search steps is well above typical 7–8B VL/agent models, and the MATH-500 97.13 / AIME 2026 75.00 pair tops the report's 7–8B comparison table (DeepSeek-R1-0528-Qwen3-8B, MiniCPM4.1-8B, Qwen3-8B, Olmo 3 7B Think).
- Best average rank across 14 reasoning benchmarks among seven 7–8B models — a genuine from-scratch contender, not a Qwen/Llama fine-tune.
- Fully open recipe: MIT weights, dataset, and complete training code (pretrain → 16K/64K/256K mid-training → SFT/RL with MDP-formulated interaction traces).
- For agent loops: tool-use strength is web search/read + Ghidra-style binary function search; no SWE-bench or BFCL numbers published, so repo-coding suitability is unverified — treat as a research/math-agent model until independent evals appear.

## See also

- [[welcome]]
- Source: https://huggingface.co/zgcagi/ZGCM-1-7B