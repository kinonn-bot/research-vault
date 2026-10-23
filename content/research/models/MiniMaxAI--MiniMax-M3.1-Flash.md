---
title: "MiniMax M3.1-Flash"
org: MiniMaxAI
model_id: MiniMaxAI/MiniMax-M3.1-Flash
date: 2026-10-24
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - multimodal
  - moe
  - instruct
  - tool-use
  - computer-use
  - long-context
  - cybersecurity
  - china-lab
  - qat
downloads: 1096
likes: 242
license: minimax-community
pipeline: "image-text-to-text (VL)"
source: https://huggingface.co/MiniMaxAI/MiniMax-M3.1-Flash
params: "23B active (428B total)"
context: "1,000,000 (1M tokens)"
architecture: "native multimodal moe (MiniMax Sparse Attention throughout; quantization-aware training; DSpark draft head; custom model_type minimax_m3_vl)"
---

# MiniMax M3.1-Flash

**One-line:** MiniMax's open-weight GA of M3.1-Flash — a 428B-param / 23B-active native-multimodal MoE built for coding, agentic workflows, computer use and cybersecurity, 1M context, MXFP8 QAT checkpoint with a DSpark draft head; lab-reported DeepSWE v1.1 73.7, Automation-Bench 62.8, CyberGym 82.2, OSWorld 2.0 61.7. ⚠ large — ≈430 GB at MXFP8 across 48 shards (server-class only). ⚠ no SWE-bench Verified / LiveCodeBench / Aider / BFCL published yet; MiniMax's card uses DeepSWE v1.1 + Terminal-Bench 4.0 as its coding proxies.

> Weights landed 2026-10-23 03:37Z in a single `Init MiniMaxAI/MiniMax-M3.1-Flash` commit (48 safetensors shards + `dspark/` draft head); the repo itself was created 2026-10-17 but was private until the drop (the 2026-10-22 run's `?search=MiniMax-M3.1` returned 0). The API-only M3.1-Flash launched 2026-09-27 as a preview; this is the open-weights release. Verified license: `MINIMAX COMMUNITY LICENSE` (file in repo) — see caveat below.

> ⚠ All benchmark numbers below are **lab-reported** from the model card's comparison table (evaluated with third-party harnesses: mini-SWE-agent 2.4.5, Claude Code 2.1.x, Codex 0.149.1, OpenCode 1.17.18 — stated per row in the card's Evaluation Notes). BenchLM's independent compilation ranks the model Coding #17/152 and Agentic #19/131, but its rows are also flagged "provider exact" — i.e. still provider-sourced. No independent re-run found as of 2026-10-24.

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
| DeepSWE v1.1 | 73.7 | lab — mini-SWE-agent 2.4.5, 512K ctx; vs DeepSeek V4.1 Flash-1017 77.0, V4.1 Flash 74.2, Opus 5 74.0 |
| Terminal-Bench 4.0 | 38.1 | lab — Codex 0.149.1; vs DeepSeek V4.1 Flash-1017 42.3, Opus 5 51.8 |
| NL2Repo-Bench | 61.2 | lab — Claude Code 2.1.233, 512K ctx, reward-hacking 0; vs DeepSeek V4.1 Flash-1017 68.2 |
| SWE Refactor Bench | 23.0 | lab — Claude Code 2.1.220, 200K ctx; best in row (vs Opus 5 31.0 — trailing) |
| PostTrain Bench v1.1 | 39.3 | lab — Claude Code 2.1.251, 512K ctx |
| SciCode | — | not published |
| MLE-bench Lite | — | not published |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Automation-Bench v1.0.6 | 62.8 | lab — 600 public tasks; best in row (vs DeepSeek V4.1 Flash-1017 60.5, Opus 5 50.3) |
| BankerToolBench | 76.2 | lab — OpenCode 1.17.18, MiniMax-M2.7 judge; ties Opus 5 76.2 |
| OSWorld 2.0 | 61.7 | lab — 0808 full release; vs Opus 5 70.6, GPT-5.6 Sol 65.7 |
| CyberGym | 82.2 | lab — Claude Code 2.1.263, 1M ctx; vs GLM-5.3 84.5 |
| Agents' Last Exam | 29.6 | lab — official Overall setting, full-set leaderboard rows only (blanks = no official result, not zero) |
| LOCA-Bench 256K | 60.3 | lab — official implementation; best in row (vs GPT-5.6 Sol 60.0) |
| BabyVision (with tools) | 91.0 | lab — Claude Code 2.1.285; vs DeepSeek V4.1 Flash-1017 92.5 |
| CharXiv RQ | 82.5 | lab — GPT-5.5 judge |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 / 2026 | — | not published |
| HLE (without tools) | 43.4 | lab — text-only subset (2,158 questions) |

## Efficiency

- **Active params:** 23B active / 428B total (MoE). Sparse attention replaces the first three full-attention layers; routed experts **and** attention paths are quantized during training (QAT).
- **Context length:** 1,000,000 (1M) — usable length and throughput depend on GPU memory and serving config.
- **VRAM:** ⚠ **≈430 GB at MXFP8** (48 shards; the shipped checkpoint is QAT MXFP8, not BF16 — MiniMaxAI has no BF16 sibling repo, so treat MXFP8 as the canonical checkpoint rather than a quant re-release). Server-class only; no single-80GB path.
- **Runtime:** SGLang (cookbook), vLLM (recipe), TokenSpeed recipes at launch; Transformers / KTransformers / unsloth / ATOM "in progress". Multi-chip via FlagOS. Custom code required (`model_type: minimax_m3_vl`, `MiniMaxM3SparseForConditionalGeneration`, ships `configuration_minimax_m3_vl.py` + `processing_minimax.py`). Chat template controls `reasoning_effort` (low→max); recommended temp 1.0 / top_p 0.95. DSpark draft head included for speculative decoding. Text + image + video in, text out.
- **License caveat:** `minimax-community` — free for non-commercial use; commercial use requires prominently displaying "Built with MiniMax M3.1-Flash" plus a one-time notice to api@minimax.io, and prior written authorization above **US$20M/year revenue**. Prohibited-uses appendix (military, minors, disinformation, discrimination). Not a bare Apache/MIT drop — eyes open for anything shipping to customers.

## What makes it notable

MiniMax's first open-weights release at this scale tier — 428B/23B active, natively multimodal, 1M context — and it lands squarely in the agentic-coding lane rather than chat: the card's headline rows are DeepSWE v1.1 73.7, Automation-Bench 62.8 (best in its comparison row), BankerToolBench 76.2, OSWorld 2.0 61.7 for computer use, and CyberGym 82.2. Against its nearest open peer, DeepSeek-V4.1-Flash-1017 (already tracked), it wins Automation-Bench (62.8 vs 60.5) and LOCA-Bench 256K (60.3 vs —) but trails on DeepSWE v1.1 (73.7 vs 77.0), Terminal-Bench 4.0 (38.1 vs 42.3) and NL2Repo (61.2 vs 68.2) — so it is a strong-but-not-leading coding model whose edge is breadth (vision/video input, 1M ctx, computer-use, cyber). BenchLM (independent compilation, provider-sourced rows) places it Coding #17/152 and Agentic #19/131, capability 67.1 (#27/227). Two real caveats for a local runner: the shipped checkpoint is MXFP8 QAT at ≈430 GB (frontier memory regardless of the 23B active compute), and the community license adds attribution + a revenue threshold where DeepSeek's MIT does not.

## See also

- [[welcome]]
- Source: https://huggingface.co/MiniMaxAI/MiniMax-M3.1-Flash
- License: https://huggingface.co/MiniMaxAI/MiniMax-M3.1-Flash/raw/main/LICENSE (MINIMAX COMMUNITY LICENSE)
- Paper: https://arxiv.org/abs/2606.13392 (MiniMax Sparse Attention)
- Siblings: [FP8/INT4/GGUF community quants](https://huggingface.co/models?search=MiniMax-M3.1-Flash) · Blog: https://www.minimax.io/blog/minimax-m31f
- Related: [[deepseek-ai--DeepSeek-V4.1-Flash-1017]] · [[moonshotai--Kimi-K3]] · [[zai-org--GLM-5.3-BF16]]
- Independent cross-check: https://benchlm.ai/models/minimax-m3-1-flash
