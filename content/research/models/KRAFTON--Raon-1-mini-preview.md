---
title: "KRAFTON Raon-1 mini (preview)"
org: KRAFTON
model_id: KRAFTON/Raon-1-mini-preview
date: 2026-10-24
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - tool-calling
  - hybrid-attention
  - long-context
  - from-scratch
  - korean
  - preview
downloads: 548
likes: 146
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/KRAFTON/Raon-1-mini-preview
params: "4.3B active (28.8B total)"
context: "262,144 (256K tokens)"
architecture: "moe — hybrid Raon Delta Attention 3 : gated MLA 1, 25 layers, 128 experts (6 routed + 1 shared), Raon-mHC 4-stream residuals, NoPE, custom model_type raon1_mini"
---

# KRAFTON Raon-1 mini (preview)

**One-line:** KRAFTON AI's first from-scratch LLM — a 28.8B / 4.3B-active hybrid MoE (Raon Delta Attention + gated MLA, 256K ctx) released under Apache-2.0 with shipped tool-calling configs for **Hermes Agent**, OpenCode and Pi; lab-reported SWE-bench Verified 70.8 at 4.3B active beats Qwen3.6-35B-A3B (63.2) and Gemma-4-26B-A4B (61.6) on the same table, with LiveCodeBench v6 81.6 and IFBench 84.2 (best in row). ⚠ preview, not final — "specs and results may change".

> Repo created 2026-10-21 00:14Z; weights are ~33 GB BF16 (`model.safetensors.index.json` total_size 32,699,649,368). **Late capture:** the 2026-10-22 run rejected it on `gated=auto` + an empty card, and the 2026-10-23 run had it outside the 36h window. This run: the card is fully populated (57.5 KB with benchmark tables, quickstarts, sampling params and speculative-decoding numbers), HF's `gated` flag is now `false`, and unauthenticated `GET /resolve/main/config.json` + `/resolve/main/model.safetensors.index.json` both return **200 with real content** — verified downloadable. The card's Quickstart still carries the sentence "The model repositories are gated. Request access once on this page (approval is automatic…)", so treat that line as stale; the frontmatter still holds inert `extra_gated_*` keys.

> ⚠ All benchmark numbers below are **lab-reported** from the model card; judge and user simulator = gpt-5.6-luna for every row. Footnote caveats from the card: AutomationBench is the **public split, not the official eval set**; GDP.pdf is the Artificial Analysis text-only version (PDFs OCR-ed in advance); "Chatbot Korean" is an **internal, unreleased** benchmark. No independent re-run found as of 2026-10-24.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench v6 | 81.6 | lab — vs Qwen3.6-35B-A3B 81.2, Gemma 4 26B-A4B 83.4, Muse Glimmer 30B 77.4 |
| Aider polyglot | — | not published |
| SWE-bench Verified | 70.8 | lab — mini-SWE-agent harness; vs Qwen3.6-35B-A3B 63.2, Gemma 4 26B-A4B 61.6, Qwen3.8-27B 74.6, Muse Glimmer 30B 72.0 |
| SWE-bench Multilingual | — | not published |
| SciCode | 38.7 | lab — vs Qwen3.6-35B-A3B 35.6, Gemma 4 26B-A4B 39.6 |
| Terminal-Bench Lite | 47.0 | lab — trails Qwen3.6-35B-A3B 63.3, Qwen3.8-27B 67.0 |
| RepoBench / CrossCodeEval | — | not published |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL v4 Overall | 59.8 | lab — vs Qwen3.6-35B-A3B 64.7, Gemma 4 26B-A4B 65.8, Qwen3.8-27B 72.4 |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| AutomationBench | 29.7 | lab — **public split only**, not the official set (vs Gemma 4 26B-A4B 36.2) |
| GDPVal | 66.0 | lab — judge score, not Elo (vs Qwen3.6-35B-A3B 67.4, Muse Glimmer 30B 67.3) |
| BrowseComp Plus | 55.7 | lab — vs Qwen3.6-35B-A3B 34.8, Gemma 4 26B-A4B 32.2 |
| IFBench (instruction following) | 84.2 | lab — **best in row** (vs Qwen3.6-35B-A3B 66.6, Gemma 4 26B-A4B 80.9, Qwen3.8-27B 82.4) |
| MultiChallenge (multi-turn) | 59.0 | lab — vs Qwen3.6-35B-A3B 58.2, Qwen3.8-27B 63.6 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU Pro | 76.5 | lab — trails Qwen3.6-35B-A3B 85.9, Qwen3.8-27B 85.7 |
| GPQA Diamond | 84.3 | lab — vs Qwen3.6-35B-A3B 83.2, Qwen3.8-27B 89.7 |
| MATH | — | not published |
| AIME 2026 | 93.3 | lab — vs Qwen3.6-35B-A3B 92.9, Qwen3.8-27B 98.8 |
| HMMT Feb 2026 | 84.1 | lab — vs Qwen3.6-35B-A3B 84.5, Muse Glimmer 30B 74.6 |
| AA-LCR (long context) | 67.3 | lab — trails Qwen3.8-27B 80.3, Muse Glimmer 30B 81.3 |
| AA-Omniscience (index) | 3.5 | lab — the only comparison row where Raon leads (Qwen3.6-35B-A3B −7.2, Gemma 4 26B-A4B −46.6) |
| Chatbot Korean (internal) | 92.9 | lab — internal benchmark, not publicly released |

## Efficiency

- **Active params:** 4.3B active / 28.8B total (6 of 128 routed experts + 1 shared per token)
- **Context length:** 262,144 (256K) native; NoPE position encoding; only the 7 gated-MLA layers keep a KV cache (~8 KiB/token BF16) — 18 of 25 layers are fixed-state RDA, so long-context KV cost is unusually low
- **VRAM:** ≈33 GB BF16 (32.7 GB weights). **NVFP4 build runs on a single RTX 5090 (32 GB)**; MXFP8 and GGUF (Q4_K_M etc.) and MLX builds also shipped, incl. a DGX Spark (GB10) recipe. Practical for a single-consumer-GPU local agent loop via llama.cpp/vLLM/Transformers/MLX.
- **Runtime:** custom architecture (`model_type: raon1_mini`, `Raon1MiniForCausalLM`, ships `modeling_raon1_mini.py`) → `trust_remote_code=True`; the card's vLLM recipe points at a KRAFTON vLLM fork (`krafton-ai/vllm@raon-1-mini-preview`) for the DFlash spec-decode path. Ships `--reasoning-parser raon_1` / `--tool-call-parser raon_1`. Designed for thinking mode (disabling not recommended); recommended temp 1.0 / top_p 0.95 / top_k 20 / min_p 0; presence_penalty 0 for coding/math, 1.5 elsewhere. DFlash2 drafter = up to 2.18× output throughput on one B300.

## What makes it notable

KRAFTON AI's first from-scratch pretrain — and, unusually for a Korean-lab drop, it is pitched at agent execution rather than Korean chat alone: the card ships ready-made provider configs for **Hermes Agent**, OpenCode and Pi, with vLLM tool-call/reasoning parsers. The efficiency story is the interesting part: 4.3B active under a hybrid Raon Delta Attention (a decoupled-gate variant of Kimi Delta Attention) + gated MLA layout, so 18 of 25 layers carry no KV cache — 256K context at ≈8 KiB/token. Its lab-reported SWE-bench Verified 70.8 (mini-SWE-agent harness) is strong for 4.3B active — ahead of Qwen3.6-35B-A3B (63.2) and Gemma 4 26B-A4B (61.6) and within 4 pts of Qwen3.8-27B (74.6) — while IFBench 84.2 leads its whole comparison set. It is not a leader on terminal-first work (Terminal-Bench Lite 47.0 vs 63.3/67.0), knowledge (MMLU Pro 76.5) or BFCL (59.8); the honest read is "cheap local agent executor with excellent long-context and instruction-following economics, preview-grade quality". Caveats: preview status with an explicit "specs and results may change" note, all numbers lab-reported with judge-simulated harnesses, an internal-only Korean benchmark, public-split-only AutomationBench, and a custom architecture that needs `trust_remote_code` plus a vendor vLLM fork for the fastest path.

## See also

- [[welcome]]
- Source: https://huggingface.co/KRAFTON/Raon-1-mini-preview
- Homepage: https://krafton.ai/en/ · Playground: https://raon-mini.krafton.ai/en
- Siblings: [NVFP4](https://huggingface.co/KRAFTON/Raon-1-mini-preview-nvfp4) · [MXFP8](https://huggingface.co/KRAFTON/Raon-1-mini-preview-mxfp8) · [GGUF](https://huggingface.co/KRAFTON/Raon-1-mini-preview-gguf) · [MLX](https://huggingface.co/KRAFTON/Raon-1-mini-preview-mlx) · [DFlash2 drafter](https://huggingface.co/KRAFTON/Raon-1-mini-preview-dflash2)
- Related: [[Qwen--Qwen3.8-27B]] · [[meta-models--Muse-Glimmer-30B]] · [[LiquidAI--LFM2.5-24B-A2B]]
