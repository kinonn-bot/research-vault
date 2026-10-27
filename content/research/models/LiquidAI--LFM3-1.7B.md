---
title: "LiquidAI LFM3-1.7B (tri-hybrid edge agent)"
org: LiquidAI
model_id: LiquidAI/LFM3-1.7B
date: 2026-10-28
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - hybrid
  - tool-use
  - edge
  - long-context
downloads: 6311
likes: 110
license: "LFM Open v1.0 (commercial OK under $10M revenue; free for personal/local use)"
pipeline: text-generation
source: https://huggingface.co/LiquidAI/LFM3-1.7B
params: "1.73B dense"
context: "262144 (256K)"
architecture: "tri-hybrid (13 gated short-conv + 5 sliding-window + 6 global attention, 24 layers; custom lfm3 arch, trust_remote_code)"
---

# LiquidAI LFM3-1.7B (tri-hybrid edge agent)

**One-line:** Liquid's new LFM3 family debut — a 1.73B tri-hybrid (conv + sliding + global attention) explicitly post-trained inside agent harnesses (Hermes Agent, Pi, OpenClaw), 256K ctx, ~1 GB at 4-bit; lab-reported SWE-bench Verified 43.40 (OpenCode), BFCL V4 71.39 and WebArena-Verified 38.42, with the card's own caveat that it is *not recommended for agentic coding or complex multi-step reasoning*.

> ⚠ All scores below are **lab-reported** (model card, 2026-10-23; vLLM BF16 at full 256K ctx unless noted; SWE/TB runs under OpenCode agent). No independent evaluation yet as of 2026-10-28. Reddit r/LocalLLaMA + X coverage same-day confirms the launch. License is LFM Open License v1.0 — personal/local use unrestricted, commercial use only under $10M annual revenue (verified in repo LICENSE: "Threshold shall mean annual revenue of $10,000,000 or more").

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench v6 | 73.46 | lab — card (vs Qwen3.5-9B 69.86, MiniCPM5-2B 70.52) |
| LiveCodeBench Pro 25Q2 | 31.74 | lab — card (vs Qwen3.5-9B 34.43) |
| Aider polyglot | — | not published |
| SWE-bench Verified (OpenCode) | 43.40 | lab — OpenCode agent ≤250 turns (vs Qwen3.5-9B 51.20, Qwen3.5-4B 41.20) |
| SWE-bench Multilingual (OpenCode) | 23.00 | lab — OpenCode agent (vs Qwen3.5-9B 35.00) |
| Terminal-Bench 2.1 (OpenCode) | 12.92 | lab — OpenCode agent ≤100 turns (vs Qwen3.5-9B 17.98) |
| SciCode | 28.47 | lab — card (vs Qwen3.5-9B 31.60) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL V4 | 71.39 | lab — greedy decode (vs Qwen3.5-9B 62.83, MiniCPM5-2B 62.65) |
| τ-Bench | — | not published (τ³-bench avg 68.01 below is a different suite — do not compare) |
| τ³-bench (4 domains), average | 68.01 | lab — card (vs MiniCPM5-2B 69.44, Qwen3.5-9B 67.11) |
| ToolACE | — | not published |
| GAIA | — | not published |
| ToolSandbox | 80.36 | lab — card, best in row (vs Qwen3.5-9B 76.41) |
| MCP-Atlas | 32.57 | lab — ≤256 turns (vs Qwen3.5-9B 42.67) |
| WebArena-Verified | 38.42 | lab — ≤40 steps, best in row (vs Qwen3.5-9B 28.94) |
| AutomationBench (public) | 41.29 | lab — ≤50 turns, best in row (vs Qwen3.5-9B 15.10) |
| EnterpriseOps-Gym | 28.20 | lab — ≤50 turns (vs Qwen3.5-9B 28.97) |
| LiveClaw | 45.60 | lab — OpenClaw agent, best in row (vs Qwen3.5-9B 35.77) |
| BrowseComp-Plus (OpenClaw subset) | 37.00 | lab — OpenClaw agent (vs Qwen3.5-9B 38.00) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 63.37 | lab — card (vs Qwen3.5-9B 80.40) |
| MATH | — | not published |
| AIME 2025 | — | not published |
| HLE (no tools / with tools) | 7.17 / 13.90 | lab — card |

## Efficiency

- **Active params:** 1.73B dense (24 layers: 13 conv + 5 sliding + 6 global; hidden 2048, 16Q/4KV, vocab 128K)
- **Context length:** 262144 (256K) tokens in+out
- **VRAM (fp16 rough):** ≈3.5 GB BF16; ≈1 GB at 4-bit (card claim — fits any phone/laptop); custom `lfm3` arch needs `trust_remote_code` (llama.cpp needs an LFM3-compatible build; GGUF/MLX/ONNX/FP8/NVFP4 siblings shipped day-one)

## What makes it notable

The first LFM3 (22T-token pretrain, MOPD specialist-distillation + agentic RL post-training) and the cheapest credible local-agent executor in the window: BFCL 71.39 and WebArena 38.42 beat Qwen3.5-9B at ~1/5 the params, and the card documents tool-calling (incl. deferred tool search), OpenCode/Pi/Hermes-Agent harness tuning, and edge inference (2.5×+ prefill, least memory on AMD/M5/iPhone 17 Pro). The honest limits are stated on the card itself — not for agentic coding or hard multi-step reasoning (SWE-V 43.40 trails Qwen3.5-9B by ~8pp, GPQA-D trails by 17pp) — so position it as the on-device tool-calling layer, not the coder.

## See also

- [[welcome]]
- Source: https://huggingface.co/LiquidAI/LFM3-1.7B
- Blog: https://www.liquid.ai/blog/lfm3
- Base: https://huggingface.co/LiquidAI/LFM3-1.7B-Base
