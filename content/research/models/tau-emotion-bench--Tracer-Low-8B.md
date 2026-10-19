---
title: "tau-emotion-bench Tracer-Low-8B"
org: tau-emotion-bench
model_id: tau-emotion-bench/Tracer-Low-8B
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
downloads: 1052
likes: 0
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/tau-emotion-bench/Tracer-Low-8B
params: "8B dense (Qwen3-8B fine-tune)"
context: "32,768 (training max; Qwen3-8B native)"
architecture: "dense decoder-only, Qwen3ForCausalLM (stock qwen3)"
---

# tau-emotion-bench Tracer-Low-8B

**One-line:** The four-domain sibling of Tracer-High-8B: Qwen3-8B SFT'd on 21,401 tool-use dialogues with emotionally expressive users (Retail, Telehealth, Telecom, Airline) — pass@1 on τ-Emotion-Bench rises 24.3 → 32.3 (Qwen3-235B user simulator) and 37.6 → 46.7 (GLM-5.2 simulator) versus its base model, with the same caveat that the benchmark is the authors' own and unreplicated.

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
| τ-Bench (τ-Emotion-Bench, pass^1 avg) | 32.3 / 46.7 | lab, lab-reported — two user simulators (Qwen3-235B-A22B-Instruct-2507 / GLM-5.2); Qwen3-8B base 24.3 / 37.6 |
| τ-Emotion-Bench (pass^3 avg) | 15.1 / 31.3 | lab — Qwen3-8B base 8.4 / 22.0 |
| τ-Emotion-Bench best domains (pass^1, GLM-5.2 sim) | Retail 82.4, Telehealth 81.0, Airline 65.7, Telecom 75.2 | lab — vs base 64.3 / 63.3 / 30.5 / 72.9 |
| ToolACE | — | not published |
| GAIA | — | not published |

*τ-Emotion-Bench is the authors' own new benchmark (arXiv 2610.19560) — it is not BFCL-comparable and no third party has run it.*

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
- **VRAM (fp16 rough):** ~16 GB bf16 — single-24 GB-GPU class
- **Serving:** stock `Qwen3ForCausalLM`, no custom code. vLLM: `--enable-auto-tool-choice --tool-call-parser hermes --reasoning-parser qwen3`; sampling defaults temp 0.6 / top_p 0.95 / top_k 20 / min_p 0 with `enable_thinking: true`. Tool calls follow the **Hermes** convention; every turn has an inline `<think>` block.
- **Training:** SFT (TRL) on 2×H100 NVL, FSDP/DDP + FlashAttention-3; effective batch 32, lr 5e-5 cosine 3% warmup, paged_adamw_8bit, 3 epochs / 2,007 steps, bf16 — same recipe as Tracer-High, narrower data (4 domains, 21,401 samples vs 32,740).

## What makes it notable

The narrower-data ablation of the Tracer pair: trained on only the four easiest customer-service domains, it still lifts its Qwen3-8B base by ~8-9 pass@1 points and holds the tool loop under emotional distractors, with the largest single lift on Airline (30.5 → 65.7 under the GLM-5.2 simulator). Choose it over Tracer-High only if you want the tighter, better-measured domain set; neither is a coding model, both are lab-reported on an own-built benchmark, and the earlier baseline behaviour (Bank and Movie stay weak) shows these are reliability micro-fine-tunes rather than capability upgrades.

## See also

- [[welcome]]
- Source: https://huggingface.co/tau-emotion-bench/Tracer-Low-8B
- Sibling: [[tau-emotion-bench--Tracer-High-8B]]
- Training data: https://huggingface.co/datasets/tau-emotion-bench/Tracer-Low-tau-emotion-data
- Paper: https://arxiv.org/abs/2610.19560 · Benchmark: https://github.com/sahsaeedi/tau-emotion-bench
