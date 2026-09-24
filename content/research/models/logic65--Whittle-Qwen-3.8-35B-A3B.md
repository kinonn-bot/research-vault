---
title: "logic65/Whittle-Qwen-3.8-35B-A3B"
org: logic65
model_id: logic65/Whittle-Qwen-3.8-35B-A3B
date: 2026-09-24
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - n-gram-memory
  - research-preview
  - llama.cpp
downloads: 1017
likes: 5
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/logic65/Whittle-Qwen-3.8-35B-A3B
params: 3B active (35.1B total: 25.1B body + 10B n-gram memory)
context: 262k (tested to 75k)
architecture: moe (qwen4_exp: hyper-connections, gated DeltaNet + Attention, 10B hashed n-gram memory lookup)
---

# logic65/Whittle-Qwen-3.8-35B-A3B

**One-line:** First Whittle release where the 10B-param n-gram memory is load-bearing (zeroing it measurably hurts the model) — 35.1B total / ~3B active MoE in the Qwen3.8-Flash-Next (`qwen4_exp`) format, runs on stock llama.cpp, distilled from Qwen3.8-27B thinking traces.

⚠ **no published standard benchmarks — agent-loop suitability unknown.** Card ships private probes only (GSM8K subset, a 60-problem MATH-train maths probe, a private long-context PR-diff gate); self-described as "research preview, not a finished distillation". Repo has full weights + eval logs; GGUFs in sibling repo. Released 2026-09-19 (v4.4→tbl1→lw2 lineage; lw2 is root).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| SWE-bench Multilingual | — | — |
| Long-context reading gate (private: 6 levels 4k→75k, real PR diff) | 30/36 | lab (lw2; production Qwen3.6-35B-A3B scores 18/36) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH (private 60-problem probe, levels 2–4) | 44/60 | lab (lw2; tbl1 46/60) |
| GSM8K (private 50-problem subset) | 41/50 | lab (lw2; tbl1 44/50) |

## Efficiency

- **Active params:** ~3B per token (8 of 180 routed experts + shared expert; 10B memory is a lookup, not compute) — total 35.1B = 25.1B body + 10.0B n-gram memory
- **Context length:** 262k positions (as parent Qwen3.8-Flash-Next); tested to 75k (PoSE-trained at offsets up to 131k)
- **VRAM (fp16 rough):** body-only fp16 ≈ 50GB — not single-GPU. The practical path is the Q8_0 GGUF with memory in system RAM: ~25GB GPU footprint (27B-class body), 10.5GB RAM for the memory table, generation speed of a 3B model (author-verified on 3× RTX 3060). Math caveat: `bf16-tbl1/` column scores 2 points higher on maths if that matters more than long-context.

## What makes it notable

Novel post-training recipe (table-first warm-up + dependence loss that punishes the body for being as good *without* the memory; forward-KL distillation on 1,840 complete Qwen3.8-27B thinking traces; PoSE long-context training), and it is the first Whittle where the n-gram memory transfer from Qwen3.8-Flash-Next is actually load-bearing (memory gain +2.84 nats held-out code). Stop/loop battery is clean (24/24, 0 loops, 0 self-turn leaks) under the serving sampler. For an agent-loop buyer this is a watch item, not a drop-in: no SWE-bench/Aider/BFCL numbers, card warns about occasional invalid-JSON for bare structured output (mitigate with JSON-schema grammar at serve time), and thinking length is unbounded by default. Runs on stock llama.cpp with the `qwen4exp` architecture (update llama.cpp if unknown). Apache-2.0, weights + probes public.

## See also

- [[welcome]]
- Source: https://huggingface.co/logic65/Whittle-Qwen-3.8-35B-A3B
- Family: [[logic65/Whittle-Next-27B-A3B]] · GGUFs: logic65/Whittle-Qwen-3.8-35B-A3B-GGUF