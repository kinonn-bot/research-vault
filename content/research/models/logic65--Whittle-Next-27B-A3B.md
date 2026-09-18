---
title: "logic65/Whittle-Next-27B-A3B"
org: logic65
model_id: logic65/Whittle-Next-27B-A3B
date: 2026-09-19
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid
  - custom-architecture
  - research-preview
  - long-context
  - open-weights
downloads: 3629
likes: 19
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/logic65/Whittle-Next-27B-A3B
params: 27.1B total / ~3B active (MoE)
context: 262144
architecture: "moe / hybrid (qwen4_exp: linear+full attention, hyper-connections, n-gram memory)"
---

# logic65/Whittle-Next-27B-A3B

**One-line:** Post-hoc 27.1B MoE (≈3B active) carved from Qwen3.6-35B-A3B with Qwen3.8-Flash-Next's 2B-row n-gram memory grafted in — a `qwen4_exp` (Qwen4-Next) research-preview hybrid that runs on stock llama.cpp, but is explicitly **not a finished general-purpose model**.

⚠ Research preview, shipped with caveats by the author: "not a finished, general-purpose model… a working starting point". All numbers are **lab-reported** (self-run, `verified: false`, on Q8_0 GGUF via stock llama.cpp; every reply log in `eval/`). **Zero coding/agentic benchmark suite published** (no HumanEval/MBPP/LiveCodeBench/Aider/SWE-bench/BFCL/τ-Bench) — HumanEval/MBPP were used only as distillation prompts. No independent third-party eval yet.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published (used only as distill prompts) |
| HumanEval+ | — | not published |
| MBPP | — | not published (used only as distill prompts) |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |
| Code probes (fib / bash / LRU) | 3/3 correct | *lab-reported* (v3, eval logs in repo) |

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
| GSM8K (200-Q subset, cap 512, thinking off) | 86.5% (173/200) | *lab-reported* (v3, full logs in repo) |
| GSM8K (200-Q subset, cap 1024, thinking off) | 86.0% (172/200) | *lab-reported* (v3) |
| GSM8K (200-Q subset, cap 2048, thinking on) | 86.5% (173/200) | *lab-reported* (v3) |
| MATH probe (60 train-split L2–4, thinking on) | 48/60 | *lab-reported* (v4.4, vs reader7 43/60) |
| Long-context reading (6 factual Q on real PR + repo files) | 6/6 @4k · 5/6 @8k · 4/6 @26k–75k | *lab-reported* (v4.3; parent Qwen3.6-35B-A3B: 6/6 everywhere) |

## Efficiency

- **Active params:** ~3B of 27.1B total (25.1B body + 2.0B n-gram memory; 180 experts, 8 per token, 40 layers)
- **Context length:** 262,144 max (config); card-tested to 75k; llama-server recommended `-c 16384`
- **VRAM (fp16 rough):** ~54 GB → quant required for real use. Q8_0 ≈ 27 GB; Q5_K_M fits a 16 GB card with `-ot "per_layer_token_embd=CPU"` (memory ~2.1 GB at Q8 moves to system RAM); routed experts can also go to RAM (4–8 tok/s CPU-expert speed). GGUF ladder Q8_0→Q3_K_M on logic65/Whittle-Next-27B-A3B-GGUF.

## What makes it notable

The cheapest local way to run a Qwen4-Next-style (`qwen4_exp`) hybrid architecture: full attention every 4th layer with linear attention elsewhere, 4 hyper-connection streams, per-layer embeddings, and a 2B-row hashed n-gram memory whose contents were **exactly transferred** from Qwen3.8-Flash-Next (not re-fit). Unlike most custom-arch models, it serves on **stock llama.cpp** with no patches (Q8_0→Q3_K_M GGUFs). Reasoning quality tracks its Qwen3.6-35B-A3B parent at a fraction of the active params, and it reproduces Qwen3.8 thinking format (`--reasoning-format deepseek` compatible). Caveats: maths is at 26B level (GSM8K 86.5% on a 200-question subset), long-context exact-identifier recall degrades past 26k vs the parent, greedy decoding loops (sampling required, thinking budgets ≥4k), and the single-author distillation was "hours, not weeks" — the full distillation from Qwen3.8-27B is unfunded. Nice card hygiene: full training logs, checkpoints, and eval replies published in-repo.

## See also

- [[welcome]]
- Parent body: https://huggingface.co/Qwen/Qwen3.6-35B-A3B
- Teacher: https://huggingface.co/Qwen/Qwen3.8-27B
- Memory source: https://huggingface.co/Qwen/Qwen3.8-Flash-Next
- Source: https://huggingface.co/logic65/Whittle-Next-27B-A3B