---
title: "tau-emotion-bench Tracer-High-8B"
org: tau-emotion-bench
model_id: tau-emotion-bench/Tracer-High-8B
date: 2026-10-20
tags:
  - huggingface
  - text-generation
  - agentic
  - tool-use
  - multi-turn
  - instruct
  - qwen3
  - emotion
downloads: 1047
likes: 0
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/tau-emotion-bench/Tracer-High-8B
params: "8B dense (Qwen3-8B fine-tune)"
context: "32,768 (training max; Qwen3-8B native)"
architecture: "dense decoder-only, Qwen3ForCausalLM (stock qwen3)"
---

# tau-emotion-bench Tracer-High-8B

**One-line:** An 8B multi-turn tool-using agent SFT'd from Qwen3-8B on 32,740 tool-use dialogues with *emotionally expressive* users across ten customer-service domains — the paper's companion artifact for τ-Emotion-Bench. It roughly doubles its base model's pass^k on that benchmark (38.1 vs 24.3 pass@1 under the Qwen3-235B user simulator), but the benchmark is the authors' own, the gains are domain-specific, and nothing has been independently reproduced.

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
| τ-Bench (τ-Emotion-Bench, pass^1 avg) | 38.1 / 54.7 | lab, lab-reported — two user simulators (Qwen3-235B-A22B-Instruct-2507 / GLM-5.2); Qwen3-8B base 24.3 / 37.6 |
| τ-Emotion-Bench (pass^3 avg) | 19.8 / 37.5 | lab — Qwen3-8B base 8.4 / 22.0 |
| τ-Emotion-Bench best domains (pass^1, GLM-5.2 sim) | School 56.0, Retail 56.7, Bank 46.7, Airline 44.8 | lab — vs base 24.7 / 37.1 / 24.7 / 30.5 |
| ToolACE | — | not published |
| GAIA | — | not published |

*τ-Emotion-Bench is the authors' own new benchmark (arXiv 2610.19560) — it is not BFCL-comparable and no third party has run it. Scores are the only agentic evidence available for this model.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** 8B dense (no MoE)
- **Context length:** 32,768 tokens (training max); served at `--max-model-len 32768`
- **VRAM (fp16 rough):** ~16 GB bf16 — single-24 GB-GPU class; Qwen3-8B quants reuse cleanly
- **Serving:** stock architecture (`Qwen3ForCausalLM`), no custom code. vLLM: `--enable-auto-tool-choice --tool-call-parser hermes --reasoning-parser qwen3`; sampling defaults temp 0.6 / top_p 0.95 / top_k 20 / min_p 0 with `enable_thinking: true`. Tool calls follow the **Hermes** convention and every turn carries an inline `<think>` block, so it drops into Hermes-style agent loops without prompt surgery.
- **Training:** SFT only (TRL SFTTrainer) on 2×H100 NVL, FSDP/DDP + FlashAttention-3 + gradient checkpointing; effective batch 32, lr 5e-5 cosine with 3% warmup, paged_adamw_8bit, 3 epochs / 2,007 steps, bf16.

## What makes it notable

Agent reliability research usually measures tool use against cooperative users; this checkpoint is the opposite condition — the same tool-call loop under anxious, angry and distracted users, and it keeps the tools working (Terminal-style pass^k doubles versus base). Practically it is a drop-in Qwen3-8B replacement with Hermes tool-call formatting and a think block, so the cost of trying it in a Hermes agent loop is one vLLM flag set. What it is *not*: a coding model (no HumanEval/SWE-bench/Aider numbers at all), a general-purpose agent (training is customer-service domains — the weakest domains, Movie 6.7 and Travel 14.0, stay weak), or independently validated. Treat the pass^k gains as lab-reported on a new benchmark.

## See also

- [[welcome]]
- Source: https://huggingface.co/tau-emotion-bench/Tracer-High-8B
- Sibling: [[tau-emotion-bench--Tracer-Low-8B]]
- Training data: https://huggingface.co/datasets/tau-emotion-bench/Tracer-High-tau-emotion-data
- Paper: https://arxiv.org/abs/2610.19560 · Benchmark: https://github.com/sahsaeedi/tau-emotion-bench
