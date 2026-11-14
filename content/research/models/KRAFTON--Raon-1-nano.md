---
title: "KRAFTON Raon-1 nano"
org: KRAFTON
model_id: KRAFTON/Raon-1-nano
date: 2026-11-15
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - hybrid-attention
  - tool-calling
  - long-context
  - korean
downloads: 1129
likes: 92
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/KRAFTON/Raon-1-nano
params: "1.5B effective (3.1B total incl per-layer embeddings; 3.2B checkpoint with MTP)"
context: "262144 (256K tokens, NoPE)"
architecture: "dense hybrid (RDA 3 : gated MLA 1, 24 layers, custom raon1_nano, trust_remote_code)"
---

# KRAFTON Raon-1 nano

**One-line:** KRAFTON AI's 1.5B-effective dense distill of Raon-1 mini preview (MoE-to-Dense + 3T continued pretrain + SFT/OPD/RL) — Apache-2.0, 262K ctx, Korean/English tool-calling for office work and mobile control, ships GGUF/MLX/LiteRT for on-device; lab-reported BFCL v4 56.3 trails same-table MiniCPM5-2B (61.0) and LFM3-1.7B (67.2), no SWE-bench or LiveCodeBench published.

> ⚠ All scores below are **lab-reported** from the model card's comparison table (vs Qwen3.5-2B, Gemma 4-E2B, MiniCPM5-2B, LFM3-1.7B on the same harness). "Chatbot Korean" and "Office Work Bench" are internal/unreleased benchmarks. No independent re-run found as of 2026-11-15.

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
| BFCL | 56.3 (v4 General) | lab — vs Qwen3.5-2B 41.2, Gemma 4-E2B 37.9, MiniCPM5-2B 61.0, LFM3-1.7B 67.2 |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Office Work Bench (ko, internal) | 49.2 | lab (internal, unreleased) — vs Qwen3.5-2B 15.7, MiniCPM5-2B 33.9, LFM3-1.7B 39.8 |
| AndroidControl (mobile) | 36.0 | lab — vs Qwen3.5-2B 26.9, MiniCPM5-2B 31.7 |
| NL2SH-ALFA (terminal) | 58.0 | lab — vs MiniCPM5-2B 61.4, Gemma 4-E2B 62.6 |
| BrowseComp Plus (search) | 34.5 | lab — vs MiniCPM5-2B 37.2 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | 81.1 (MMLU-Redux) | lab — vs Qwen3.5-2B 81.5, MiniCPM5-2B 84.0 |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |
| IFBench | 75.9 | lab — vs Qwen3.5-2B 45.7, MiniCPM5-2B 63.8, LFM3-1.7B 73.7 |
| KMMLU-Redux (ko) | 50.9 | lab — leads row (Qwen3.5-2B 46.1) |
| CLIcK (ko) | 65.2 | lab — leads row |

## Efficiency

- **Active params:** 1.5B effective (3.1B total incl 1.5B per-layer embedding table; 3.2B checkpoint with 55M MTP module)
- **Context length:** 262144 tokens (NoPE; only 6 MLA layers keep KV cache, ~7 KiB/token BF16)
- **VRAM (fp16 rough):** ~6.4 GB (BF16 checkpoint; GGUF/MLX/LiteRT builds published for on-device)

## What makes it notable

Derived from Raon-1 mini preview (30B-A4B MoE) via MoE-to-Dense pruning and distillation, then 3T tokens continued pretraining plus SFT/OPD/RL — a small model with a big-model training receipt. Against same-size open models on its own table it leads Korean (KMMLU, CLIcK, Chatbot Korean 91.0), instruction-following (IFBench 75.9) and office/mobile tool tasks, but trails MiniCPM5-2B and LFM3-1.7B on BFCL v4 and publishes no SWE-bench or LiveCodeBench, so repo-level coding ability is unproven. Custom `raon1_nano` arch needs `trust_remote_code`; vLLM/mlx/LiteRT quickstarts are shipped. Position: Korean-first on-device agent model, not a SWE-bench contender on current evidence.

## See also

- [[welcome]]
- Source: https://huggingface.co/KRAFTON/Raon-1-nano
- Sibling preview (MoE teacher): https://huggingface.co/KRAFTON/Raon-1-mini-preview
- Local vault: KRAFTON--Raon-1-mini-preview
