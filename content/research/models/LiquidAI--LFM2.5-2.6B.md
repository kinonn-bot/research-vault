---
title: "LFM2.5-2.6B"
org: LiquidAI
model_id: LiquidAI/LFM2.5-2.6B
date: 2026-08-04
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - hybrid
  - on-device
  - edge
  - function-calling
downloads: 47393
likes: 111
license: LFM Open License v1.0 (commercial OK under $10M revenue)
pipeline: text-generation
source: https://huggingface.co/LiquidAI/LFM2.5-2.6B
params: "2.69B total (hybrid: 22 conv + 8 GQA attention layers)"
context: "131072 tokens (128K)"
architecture: hybrid
---

# LFM2.5-2.6B

**One-line:** Liquid AI's on-device agent model — 2.6B hybrid (conv + GQA), 128K context, agentic RL-trained inside real agent harnesses, runs in <2.5GB at 113–220 tok/s on CPU/M-series. GA blog Aug 4, 2026. ⚠ Card explicitly says NOT recommended for agentic coding — it's a tool-use/agent model, not a coder.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 59.41 (v6) | lab (card table) |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |

*LiveCodeBench v6 59.41 sits between Qwen3.5-4B (60.85) and gemma-4-E2B-it (54.92) — mid-pack for its class; the card itself steers users away from agentic coding.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | 56.88 (v4) | lab (card table) |
| τ-Bench | — | not published (τ³-Bench Banking: 5.67 lab) |
| ToolACE | — | not published |
| GAIA | — | not published |
| ToolSandbox | 77.83 | lab (card table) |
| Multi-IF | 80.07 | lab (card table) |
| IFStruct | 85.49 | lab (card table) |

*Tool use is the story: BFCLv4 56.88 beats gemma-4-E4B-it (46.39) and Qwen3.5-4B (50.56), trails only Qwen3.5-9B (60.13) in the card's sub-10B comparison; ToolSandbox 77.83 tops all four comparators. IFStruct 85.49 is the best instruction-following number in the table (vs gemma-4-E4B-it 76.65). τ³-Bench Banking 5.67 is a modest multi-turn result (Qwen3.5-9B 5.15, gemma-4-E4B-it 4.12).*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | 51.87 | lab (card table) |
| AA Omniscience | -29.50 | lab (card table; beats gemma-4-E2B-it -74.47, Qwen3.5-9B -50.43) |
| Claw-Eval avg (EN) | 62.85 | lab (card table) |

*AIME25 51.87 beats both Gemma 4 E-class models (26–34) and nearly matches Qwen3.5-9B (56.07) at 1/3 the size — a "pure reasoning model" that always thinks before answering (chat template injects `<think>`).*

## Efficiency

- **Active params:** 2.69B total (hybrid linear-attention — 22 double-gated short-conv blocks + 8 GQA layers; no MoE)
- **Context length:** 131,072 tokens (128K, extended in mid-training)
- **VRAM (fp16 rough):** ~5.4 GB (2.69B × 2 bytes); card claims <2.5 GB memory in quantized form — 220 tok/s on Apple M5 Max, 113 tok/s on AMD Ryzen CPU. GGUF / ONNX / MLX variants officially published.

## What makes it notable

LFM2.5-2.6B is the strongest small-model argument for fully local agent loops in the sub-3B class: agentic RL trained *inside* popular agent harnesses (tools, system prompts, interaction patterns), best-in-class BFCLv4/ToolSandbox/Multi-IF vs Gemma 4 E-class and Qwen3.5-4B/9B at a fraction of the footprint, and official GGUF/ONNX/MLX builds for CPU/edge. Two hard caveats: the card explicitly says it's **not recommended for agentic coding or knowledge-heavy tasks** (position it for tool calling, data extraction, RAG, long-context — not as a SWE agent), and the LFM Open License v1.0 only permits commercial use under $10M annual revenue (fine for personal/local use; larger entities need a commercial agreement). All headline numbers are lab-reported from Liquid's own card table — no independent leaderboard verification yet.

## See also

- [[welcome]]
- Sibling: LFM2.5-8B-A1B (LiquidAI, 8B total / 1B active MoE, released 2026-05-28)
- Source: https://huggingface.co/LiquidAI/LFM2.5-2.6B
