---
title: "logic65/Whittle-Qwen-3.8-45B-A3B"
org: logic65
model_id: logic65/Whittle-Qwen-3.8-45B-A3B
date: 2026-10-07
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - n-gram-memory
  - llama.cpp
  - reasoning
  - research-preview
downloads: 270
likes: 1
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/logic65/Whittle-Qwen-3.8-45B-A3B
params: "~3B active (45.1B total: 35.1B body + 10.0B n-gram memory)"
context: "262k (qwen4_exp parent format; long-context tool probe at ~11k tokens)"
architecture: "moe (qwen4_exp_text; 256 routed experts/layer, 8 active + shared; 10B hashed n-gram memory lookup)"
---

# logic65/Whittle-Qwen-3.8-45B-A3B

**One-line:** The Whittle flagship — the 35B's body with the 76 experts/layer that its prune had removed restored from Qwen3.6-35B-A3B (untrained splice): 45.1B total / ~3B active MoE in the Qwen3.8-Flash-Next (`qwen4_exp`) format, runs on stock llama.cpp, Apache-2.0. ⚠ Experimental and lab-reported only: no third-party evals; arithmetic regressed vs the 35B (GSM-50 38 vs 44) and 2 invented tool calls appeared in the web-page replays (neither the 35B nor the base made any). The author's safe pick is still the 35B.

Caught by the per-org author sweep — invisible to all three API streams: Stream A's 36h `createdAt` cut misses it by ~1.3h and its 270 downloads sit below Streams B/C's 1,000 threshold. GGUF sibling (created 2026-10-04): `logic65/Whittle-Qwen-3.8-45B-A3B-GGUF` (Q3_K_M / Q4_K_M / Q5_K_M / Q8_0; every number below was measured on the Q4_K_M). Browser demo: `logic65/whittle-45b-chat` (ZeroGPU).

## Coding benchmarks

*All lab-reported (author's battery, 2–4 Oct 2026, two T4 GPUs, one sample per item, on the Q4_K_M quant; 35B column ran at Q6_K). No independent evaluation.*

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | 75.6 | lab (EvalPlus pass@1; 35B: 73.8) |
| HumanEval+ | 72.6 | lab (35B: 70.7) |
| MBPP | 77.8 | lab (35B: 76.2) |
| MBPP+ | 65.9 | lab (35B: 61.9) |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |

## Agentic / tool-use benchmarks

*No BFCL/τ-Bench/ToolACE/GAIA published. The card's own tool-use harness is the only agentic signal — lab-reported, NOT BFCL-comparable:*

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Tool-use probes (96; includes a ~11k-token context probe) | 96/96 (context probe 24/24) | lab — 35B: 95, Qwen3.6-35B-A3B: 93 |
| llama.cpp web-chat replay (40; a real chat replayed at two points) | 27/40 finished; 2 invented tool calls | lab — 35B: 34/40, none invented |
| Strict JSON (72 items) | 72 valid / 70 exact | lab — 35B: 72/70; base: 72/72 |
| Stop/loop battery (24) | 24/24 clean | lab — 35B: 23/24 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH-60 (private 60-problem probe) | 44/60 (9 hit the 6,144-token cap) | lab — base Qwen3.6-35B-A3B: 38/60 (19 hit the cap) |
| GSM-50 (private 50-problem subset) | 38/50 | lab — 35B: 44/50 (regression; p = 0.031) |
| PopQA long-tail name completion (252) | 111/252 | lab — 35B: 94, base: 132 |
| PopQA exact match (288) | 52/288 | lab — 35B: 71 (measured at Q6_K) |

## Efficiency

- **Active params:** ~3B/token (8 of 256 routed experts + the shared expert); 45.1B total = 35.1B body + 10.0B n-gram memory (a lookup, not compute)
- **Context length:** qwen4_exp parent format (262k); long-context tool probe at ~11k tokens; the GGUF guide serves at `-c 16384`
- **VRAM:** Q4_K_M 27.1 GB (GPU holds the 21.5 GB expert body; ~5.6 GB memory table in system RAM via `-ot per_layer_token_embd=CPU`); Q5_K_M 31.9 GB; Q8_0 48.0 GB (10.5 GB table); Q3_K_M 21.3 GB. fp16: ~70 GB weights on GPU + ~20 GB table in CPU memory. Needs 5.8 GB more memory than the 35B.
- **Runtime:** stock llama.cpp (`qwen4exp` architecture — update if unknown); sampler temp 0.7 / top_p 0.8 / top_k 20 / repeat_penalty 1.05 (do not decode greedily — it loops); thinking via `enable_thinking=true`, give 4k+ tokens for code and 8k+ for maths. For transformers use the repo's `whittle_load.py` (the stock loader would size the n-gram table wrongly) + `flash-linear-attention`. Tool use: keep each turn's `reasoning_content` in the episode history; Claude Code works against llama-server's `/v1/messages`.

## What makes it notable

The flagship of the Whittle family: restoring the 76 experts/layer trades a GSM regression for real long-tail knowledge (PopQA completion 111 vs 94, p < 0.001) at level coding (HumanEval 75.6 vs 73.8, MBPP+ 65.9 vs 61.9) and 96/96 on the author's tool-use probes including the ~11k-token context set — the strongest Whittle to run so far, at +5.8 GB memory and weaker arithmetic word problems (38 vs 44, p = 0.031). For an agent-loop buyer on llama.cpp it is the current Whittle to try, with the author's own caveat that the safe pick is still the 35B. Treat every number as a single-sample lab measurement (one run, one sample per item; two T4s); no independent evaluation yet. The untrained-splice provenance is the risk: restored experts were trained for Qwen3.6's body and have not been healed into this one; a re-heal is the announced next step.

## See also

- [[welcome]]
- Source: https://huggingface.co/logic65/Whittle-Qwen-3.8-45B-A3B
- GGUFs: https://huggingface.co/logic65/Whittle-Qwen-3.8-45B-A3B-GGUF · Demo: https://huggingface.co/spaces/logic65/whittle-45b-chat
- Family: [[logic65/Whittle-Qwen-3.8-35B-A3B]] · [[logic65/Whittle-Next-27B-A3B]]
