---
title: "Meta Muse Glimmer-30B"
org: meta-models
model_id: meta-models/Muse-Glimmer-30B
date: 2026-08-13
tags:
  - huggingface
  - image-text-to-text
  - coding
  - agentic
  - vision-language
  - dense
  - local
downloads: 0
likes: 1260
license: apache-2.0
pipeline: image-text-to-text
source: https://huggingface.co/meta-models/Muse-Glimmer-30B
params: 30B dense (29.6B incl. 1.8B vision encoder)
context: 131072
architecture: dense
---

# Meta Muse Glimmer-30B

**One-line:** Meta's return to open weights — a 30B dense agentic model (VL input) purpose-built to run on consumer hardware (K-Quant ~17GB fits 24GB VRAM), with published SWE-bench Verified 76.0. 🔬 VL model with real coding/agentic evals → included per tracker rule.

> ℹ️ Released Aug 9-10, 2026 by Meta Superintelligence Lab under org `meta-models` (not `meta-llama`). Confirmed real via research.meta.ai blog "Introducing Muse Glimmer: An Open Agentic Model That Runs on Your…", NVIDIA developer blog, HF blog (Aug 10), marktechpost, r/LocalLLaMA. HF download counter shows 0 (counter lag — 1,260 likes + unsloth/bartowski/RedHatAI quant repos in 24h are inconsistent with 0 downloads); weights verified present (2× safetensors shards, ~60GB fp16).
> ⚠ All benchmark numbers below are **lab-reported** (Meta's card / HF blog, backed by research.meta.ai methodology report). No independent re-run yet.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | *76.0* | *lab-reported* |
| SWE-bench Pro | *51.2* | *lab-reported* |
| TerminalBench 2.1 (with terminus2) | *51.7* | *lab-reported* |
| SciCode | *43.6* | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published (uses τ³-Bench instead) |
| τ³-Banking | *23.5* | *lab-reported* |
| MCP Atlas (Public) | *75.5* | *lab-reported* |
| DeepSearch QA | *74.6* | *lab-reported* |
| GAIA2 | *43.3* | *lab-reported* |
| OSWorld-Verified | *65.9* | *lab-reported* |
| WildClawBench | *47.6* | *lab-reported* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | *83.5* | *lab-reported* |
| AIME 2026 | *94.7* | *lab-reported* |
| HLE Text | *22.0* | *lab-reported* |
| IFBench | *77.0* | *lab-reported* |
| MMMU Pro | *74* | *lab-reported* |

## Efficiency

- **Active params:** 30B dense (29.6B incl. 1.8B ViT-G/14 perception encoder)
- **Context length:** 131,072+ (120K+ per NVIDIA blog; max visual tokens 4,096/image)
- **VRAM (fp16 rough):** ~60 GB. The release is explicitly quantization-first: K-Quant-Dynamic → 32GB VRAM, **K-Quant-17GB → 24GB VRAM** (validated ≤1.0% degradation across 15 benchmarks). DFlash speculative decoder (16-token blocks): RTX 5090 74.9 → **233.4 tok/s** (3.1×); M4 Max 23.7 → 37.8; M5 Max 26.6 → 50.2 (ExecuTorch). `llama serve -hf meta-models/Muse-Glimmer-30B-GGUF` and transformers `AutoModelForMultimodalLM` both supported.

## What makes it notable

This is the first open-weight Meta model explicitly designed for **always-on local agent workflows**: multi-step reasoning with controllable effort (low/med/high/xhigh reasoning strength), reliable tool use, failure recovery after bad tool calls, and interleaved text+image input (screenshots/charts/documents) in one 24GB-VRAM package. On Meta's numbers it beats Gemma4-31B on every agentic row (MCP Atlas 75.5 vs 54.2, DeepSearch QA 74.6 vs 61.7, SWE-bench Verified 76.0 vs 66.6, τ³-Banking 23.5 vs 15.1) and roughly matches Qwen3.6-27B while being natively multimodal. The card explicitly lists **OpenClaw and Hermes Agent** as supported scaffolds — for this user (local runner, pipes models into agents) this is the most directly relevant release of the week. Distribution via GGUF (meta-models + unsloth + bartowski) and ExecuTorch-PTE for Apple Silicon. Apache-2.0 — no use restrictions. First open-weight Meta release since the Llama-4 series.

## See also

- [[welcome]]
- Source: https://huggingface.co/meta-models/Muse-Glimmer-30B
- Meta research blog: https://research.meta.ai/blog/introducing-muse-glimmer-open-agentic-model
- NVIDIA blog: https://developer.nvidia.com/blog/run-local-agentic-ai-workflows-with-metas-muse-glimmer-on-nvidia/
