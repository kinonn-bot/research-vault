---
title: "BlinkDL/RWKV-7 G1i (GooseOne)"
org: BlinkDL
model_id: BlinkDL/rwkv7-g1
date: 2026-08-08
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - rnn
  - attention-free
  - recurrent
downloads: 8586
likes: 203
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/BlinkDL/rwkv7-g1
params: 7.2B (family 1.5B–13.3B)
context: 16384
architecture: rnn
---

# BlinkDL/RWKV-7 G1i (GooseOne)

**One-line:** ⚠ no published coding/agent benchmarks — agent-loop suitability unknown. New G1i checkpoint family (1.5B/2.9B/7.2B/13.3B, ctx 16384) of the attention-free pure-RNN RWKV-7 "Goose" architecture, dropped 2026-08-05; headline feature is constant VRAM (no KV cache) — potentially the cheapest long-context local runner, unproven for coding agents.

> ⚠ **No coding or agentic benchmarks published** (lab or third-party) as of 2026-08-08. The BlinkDL card and the official safetensor card (`RWKV/RWKV7-*-20260805`) both ship prompt/tool-call templates but no eval tables. Agent-loop suitability is untested. Community (Zhihu) commentary: "code and STEM still behind Qwen3.5, expected to catch up by year-end" — qualitative, not a number.

**Release event:** the `BlinkDL/rwkv7-g1` repo is old (created 2025-03-07) but the **G1i weights were uploaded 2026-08-05** (`rwkv7-g1i-{1.5b,2.9b,7.2b,13.3b}-20260805-ctx16384.pth`); community GGUF quants (`shoumenchougou/RWKV7-G1i-*-GGUF`) and official safetensor releases (`RWKV/RWKV7-*-20260805`, transformers 5.15+ `Rwkv7ForCausalLM`) appeared 08-05/08-06. G1i is the newest data version — the card says "always use latest models, they are better at everything."

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
| GSM8K | 77.3 (older G1a4-2.9B) | RWKV wiki, community-reported |
| AIME 2025 | — | — |

Language-modeling PPL (Uncheatable Eval, community, older G0a3-7.2B): avg 7.222 vs Qwen2.5-7B 7.323 (lower=better) — but this is a different benchmark class (PPL on raw corpora incl. github cpp/python), not a coding task eval.

## Efficiency

- **Active params:** 1.5B / 2.9B / 7.2B / 13.3B (dense — every param active; pure RNN, no MoE)
- **Context length:** 16,384 tokens (G1i; older G1d was 8192)
- **VRAM (fp16 rough):** 1.5B ≈ 3 GB · 2.9B ≈ 5.8 GB · 7.2B ≈ 14.4 GB · 13.3B ≈ 26.6 GB
- **Constant VRAM/speed** — no KV cache, memory does not grow with context length (unlike attention models)
- Measured (RWKV wiki, 2.9B G1): fp16 5.52 GB (rwkv pip) / 89 tok/s llama.cpp CUDA; Q8_0 3.47 GB / 110 tok/s; int8 3.9 GB; nf4 2.4 GB
- Card claim: 145+ tok/s RWKV-7 7.2B fp16 bsz1 on RTX 5090 (Albatross engine), constant VRAM

## What makes it notable

RWKV-7 is the flagship attention-free recurrent architecture (paper arXiv:2503.14456) — linear-time, constant-state, 100% RNN. G1i is a fresh pretrained family with 16k context, and for the first time ships as official Transformers-format safetensors (`Rwkv7ForCausalLM`, transformers 5.15+) with a chat template that supports system/multi-turn/thinking and **strict model-generated tool-call prompts** (function-call docs: temp 0, topp 0, penalty 0, G1f and newer). For a local runner this is the cheapest long-context option: no KV cache means memory stays flat on long agentic sessions, and 13.3B runs in ~27 GB fp16 (or ~7 GB nf4-class quant). The catch: zero published coding/agent benchmarks — the "no KV cache + tool-call template" pitch is unverified for actual agent loops, and community commentary puts its code/STEM below Qwen3.5 for now. GGUF builds exist for llama.cpp; the raw .pth needs the RWKV pip package / RWKV-LM.

## See also

- [[welcome]]
- Source: https://huggingface.co/BlinkDL/rwkv7-g1
- Official safetensor: https://huggingface.co/RWKV/RWKV7-7.2B-20260805
- RWKV wiki evals: https://wiki.rwkv.com/basic/RWKV-Evals.html
