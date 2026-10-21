---
title: "Recursive Flint (40B-A2.5B)"
org: RecursiveSI
model_id: RecursiveSI/flint
date: 2026-10-22
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - reasoning
  - tool-calling
  - local-inference
  - custom-architecture
  - us-lab
downloads: 0
likes: 138
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/RecursiveSI/flint
params: "2.5B active (39.8B total; 256 experts, top-6 routed + 1 shared expert; 49 layers = 2 dense + 47 MoE)"
context: "262,144 documented config; blog states support up to 512k, recommends staying within 256k"
architecture: "moe — hybrid attention (35 sliding-window-513 + 14 full-attention, no RoPE on full-attn layers); custom model_type flint / FlintForCausalLM"
---

# Recursive Flint (40B-A2.5B)

**One-line:** Debut model from Recursive Superintelligence (Richard Socher; the $4B "self-improving AI" lab) — a 39.8B-param / ~2.5B-active MoE built from scratch for local agentic coding, Apache-2.0, trained end-to-end by their "Eureka Machine" automated-research loop; lab-reported SWE-bench Verified 74.2 / SWE-bench Pro v2 89.7 / Terminal-Bench 2.1 54.9, with a claim of >125 tok/s on an M4 Pro MacBook Pro and >150 tok/s on a 64GB RTX Spark.

> ⚠ All benchmark numbers below are **lab-reported** (model card + launch blog; agentic evals are average pass@1 over ≥5 attempts, 5-hour agent timeouts). No independent evaluation exists yet as of 2026-10-22 — Artificial Analysis and BenchLM both 404 on `flint`. The SWE-bench Pro v2 figure (89.7) is **above every open-weight model on record** (Kimi K3 88.2, GLM-5.3 84.3, reflection/Beam 76.5) for a 2.5B-active model, which warrants scepticism until reproduced; the card's own caveat is that developer-reported comparison scores may not apply the same strict retrieval adjustment Flint's Terminal-Bench score does.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench v6 | — | listed in the blog's mean-score set, value not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 74.2 | lab — card + blog (mini-swe-agent, no internet) |
| SWE-bench Pro v2 | 89.7 | lab — card + blog (mini-swe-agent, no internet) |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench 2.1 | 54.9 | lab — card + blog (Terminus 2 XML, internet on, retrieved solutions counted as failures) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Tool-use support | OpenAI-compatible tool calls, multi-turn, reasoning_content preserved | card (no BFCL/τ number published) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |
| IFBench / IFEval | — | listed in the blog's mean-score set, values not published |

## Efficiency

- **Active params:** ~2.5B active per token (2.2B body + output head) / 39.8B total; 256 routed experts, 6 selected per token, plus one always-active shared expert
- **Context length:** 262,144 documented (blog: supports up to 512k, recommends ≤256k); prompt and output share the window
- **VRAM (fp16 rough):** ≈80 GB BF16 (15 safetensors shards, ~5.37 GB each) — one B300 or H200 per replica with the shipped SGLang kit. Realistic local path: the first-party `flint-int4` / `flint-int4-gguf` / `flint-nvfp4-gguf` siblings (created the same day) or the Ollama library entry — the blog's 125–150 tok/s local figures are on Apple Silicon / RTX Spark with their optimized engine
- **Runtime:** ⚠ custom architecture (`model_type: flint`, `FlintForCausalLM`) and the card states **Transformers modeling code is not included yet** — day-0 local use means the repo's SGLang serving kit (`github.com/recursive-oss/rec`) or a GGUF/llama.cpp path, not stock `transformers`
- Knowledge cutoff stated as June 2026; vocab 150,144; temp 1.0 / top-p 0.95 / top-k 20

## What makes it notable

First release from Recursive Superintelligence and the strongest "small-active" coding MoE on paper: 2.5B active params is laptop-class decode while the card claims SWE-bench Verified 74.2 and Terminal-Bench 2.1 54.9 — i.e. near reflection/Beam-class agentic coding at ~1/10th the memory of a 501B. The pitch is explicitly local-first ("keep your data on your computer, avoid API fees", 125+ tok/s on an M4 Pro), and the training story is itself the product: the whole stack (architecture search, data, training recipes, inference kernels) was built by their automated "Eureka Machine" research loop in under four months. Caveats: every number is lab-reported and independently unverified; SWE-bench Pro v2 89.7 would be a new open-weight record and should be treated as an unverified claim; and the custom architecture + missing transformers code means it will not load in stock runtimes until community quants/ports land.

## See also

- [[welcome]]
- Source: https://huggingface.co/RecursiveSI/flint
- Launch blog: https://www.recursive.com/updates/introducing-recursive-flint
- Local engine: https://github.com/recursive-oss/rec
- Siblings (created 2026-10-21, same day): [flint-int4](https://huggingface.co/RecursiveSI/flint-int4) · [flint-int4-gguf](https://huggingface.co/RecursiveSI/flint-int4-gguf) · [flint-nvfp4-gguf](https://huggingface.co/RecursiveSI/flint-nvfp4-gguf) · community: [HawkBearPig/flint-FP8-BF16-Layerwise](https://huggingface.co/HawkBearPig/flint-FP8-BF16-Layerwise) · [TechnoBaptist/flint](https://huggingface.co/TechnoBaptist/flint)
