---
title: "Mistral Large 4 (Le Chonk)"
org: mistralai
model_id: mistralai/Mistral-Large-4-1T-A52B
date: 2026-11-01
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - multimodal
downloads: 2945
likes: 1396
license: other (Mistral Ecosystem Open-Weight; commercial OK, MaaS needs separate license)
pipeline: image-text-to-text
source: https://huggingface.co/mistralai/Mistral-Large-4-1T-A52B
params: "~1T total / 49B active (52B incl embeddings+output)"
context: 1000000
architecture: moe
---

# Mistral Large 4 (Le Chonk)

**One-line:** Mistral's largest open-weight drop — 1T-param natively multimodal MoE (49B active), 1M context; open weights released 2026-10-29 after the 10-06 API preview, fulfilling the "weights by end of October" promise.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | none published |
| HumanEval+ | — | none published |
| MBPP | — | none published |
| LiveCodeBench | — | none published |
| Aider polyglot | — | none published |
| SWE-bench Verified | — | none published |
| SWE-bench Multilingual | — | none published |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | none published |
| τ-Bench | — | none published |
| ToolACE | — | none published |
| GAIA | — | none published |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | none published |
| GPQA Diamond | — | none published |
| MATH | — | none published |
| AIME 2025 | — | none published |

## Efficiency

- **Active params:** 49B active per token (52B incl embeddings/output layers) of ~1T total; 128 routed experts (4 active/token) + 1 shared expert
- **Context length:** 1,000,000 tokens
- **VRAM (fp16 rough):** ~2 TB full precision — ⚠ large, effectively API/BF16-datacenter or NVFP4 Blackwell only (official NVFP4 sibling: `Mistral-Large-4-1T-A52B-NVFP4`, Blackwell-only, claims same performance)

## What makes it notable

Europe's largest open-weight release to date and the close of a tracked radar item (API preview 10-06, weights promised by end of October, delivered 10-29 — confirmed by the `mistral-large-4-oss` blog, HF blog post, and a 2-day-old r/LocalLLaMA thread). Positions as a coding/agentic generalist: natively multimodal (text+image in, text out), three reasoning efforts (`low`/`medium`/`high`, default high), native function calling with strict JSON-schema enforcement, and an embedded DSpark speculative-decoding draft head. Lab-reported numbers, italicized as unverified: *AA Coding Agent Index 48%, effectively tied with GLM-5.3 at 47% fewer tokens per task* and *AA Intelligence Index v5 26, highest among western open-weight models*. Independently confirmed: Artificial Analysis lists Mistral Large 4 (High) at Intelligence Index 26 (#9/22, "Released October 2026", open-weights model), and BenchLM carries a compiled profile at Capability 51.5/100 (#96/216 public, #48/77 verified) with 1M context. No SWE-bench/Aider/BFCL/LiveCodeBench numbers published anywhere yet, so agent-loop quality rests on the AA/BenchLM aggregates for now. License is the custom Mistral Ecosystem Open-Weight License (MIT derivative, commercial use allowed) with one sharp edge: operating a Model-as-a-Service business requires a separate commercial license — fine for local runs, flagged for anyone planning hosted endpoints.

## See also

- [[welcome]]
- Source: https://huggingface.co/mistralai/Mistral-Large-4-1T-A52B
- Blog: https://mistral.ai/news/mistral-large-4-oss/
- NVFP4 sibling: https://huggingface.co/mistralai/Mistral-Large-4-1T-A52B-NVFP4
