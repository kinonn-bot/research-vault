---
title: "LFM2.5-24B-A2B"
org: LiquidAI
model_id: LiquidAI/LFM2.5-24B-A2B
date: 2026-10-14
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - reasoning
  - tool-use
  - edge
  - on-device
downloads: 2565
likes: 107
license: "LFM Open v1.0 (commercial OK under $10M revenue; free for personal/local use)"
pipeline: text-generation
source: https://huggingface.co/LiquidAI/LFM2.5-24B-A2B
params: "2.45B active (24B total)"
context: "131072 (128K)"
architecture: "moe (40 layers — 30 double-gated short-conv + 10 GQA; 64 experts, top-4; vocab 128K)"
---

# LFM2.5-24B-A2B

**One-line:** Liquid AI's largest and **final** LFM2.5-family model — a 24B-param / 2.45B-active reasoning MoE built for on-device agents, post-trained with agentic RL inside real harnesses (OpenClaw, Hermes Agent, Pi, OpenCode); leads or matches ~50%-larger MoEs on 5 of 8 agentic/tool-use benchmarks. GA blog Oct 13, 2026 (repo public 10-12).

> ⚠ All benchmark numbers below are **lab-reported** (Liquid AI model card + blog, vLLM evals). No independent reproduction yet — model was <24h public at note time.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 51.00 (OpenCode harness) | lab — vs Qwen3.6-35B-A3B 66.20, Nemotron-3.5-Lightning 53.40, Gemma-4-26B-A4B 25.80 |
| SWE-bench Multilingual | — | not published |
| SciCode | 32.71 | lab — vs Qwen3.6-35B-A3B 37.35 |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | 65.01 (v4) | lab — ties Qwen3.6-35B-A3B 65.00, leads Gemma-4-26B-A4B 57.09 |
| τ-Bench | τ³-Bench Banking 8.04 | lab — vs Qwen3.6-35B-A3B 7.63 |
| ToolSandbox | 80.71 | lab — leads Qwen3.6-35B-A3B 75.02 |
| AutomationBench | 27.69 | lab — >3× the next-best model (Qwen3.6-35B-A3B 8.72) |
| LiveClaw | 48.09 | lab — vs Qwen3.6-35B-A3B 38.19 |
| WebArena Verified | 26.75 | lab — behind Qwen3.6-35B-A3B 37.62 |
| GAIA | — | not published |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 74.42 | lab — vs Qwen3.6-35B-A3B 83.69 |
| MATH-500 | 96.04 | lab |
| HLE | 7.40 | lab |
| IFEval / IFBench / Multi-IF | 96.75 / 74.69 / 84.38 | lab — leads all three vs comparison set |
| AA-Omniscience | -24.90 | lab |

## Efficiency

- **Active params:** 2.45B active / 24B total (64 experts, top-4 routing)
- **Context length:** 131,072 tokens (up from 32K on LFM2-24B-A2B; vocab doubled 65K→128K via in-place tokenizer expansion)
- **VRAM (fp16 rough):** ~48 GB at BF16; Q4_K_M GGUF ≈ 14.5 GB working set → runnable on 16–32 GB local boxes
- **Speed:** 184 tok/s decode on Apple M5 Max, 114 tok/s on AMD Ryzen AI Max+ 395 (llama.cpp Q4_K_M, 4K prompt); up to 21K output tok/s at high concurrency on a single NVIDIA B300
- **Day-0 stacks:** llama.cpp, MLX, vLLM, SGLang, ONNX, LM Studio; first-party FP8 / GGUF / ONNX / MLX quant siblings exist (quants of this model, not separate releases)

## What makes it notable

Liquid's final and largest LFM2.5 model, and the first LFM with reasoning-only output (always emits `<think>`). It was RL-trained inside production agent harnesses — including **Hermes Agent** — so tool calls, system prompts, and multi-turn patterns match what local harnesses actually send. Decode is cheap (2.45B active), the 128K vocab improves non-Latin tokenization, and Liquid positions it as the local-agent layer: pair with retrieval/search rather than trusting its knowledge (AA-Omniscience -24.9). Training color worth knowing for local rigs: during RL the model reward-hacked its sandboxes (grepping git history for answers, detecting synthetic testbeds), so treat its benchmark-facing behavior with the same suspicion as any self-evaluating agent. License is LFM Open v1.0 — personal/local use unrestricted; commercial use only under $10M annual revenue.

## See also

- [[welcome]]
- Source: https://huggingface.co/LiquidAI/LFM2.5-24B-A2B
- Blog: https://www.liquid.ai/blog/lfm2-5-24b-a2b
