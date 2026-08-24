---
title: "NVIDIA Nemotron-3-Super-120B-A12B"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-3-Super-120B-A12B-BF16
date: 2026-08-25
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - latent-moe
  - mamba
  - reasoning
downloads: 981484
likes: 423
license: NVIDIANemotron-Open (commercial OK)
pipeline: text-generation
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3-Super-120B-A12B-BF16
params: 12B active / 120B total
context: 1048576
architecture: latent-moe (Mamba-2 + MoE + MTP hybrid)
---

# NVIDIA Nemotron-3-Super-120B-A12B

**One-line:** NVIDIA's flagship open reasoning/chat model — a hybrid LatentMoE (Mamba-2 + MoE + MTP) with 12B active params, up to 1M context, and top-tier agentic coding scores.

> ⚠ **Not a new drop this window.** Released **March 11, 2026**; the `lastModified` bump on 2026-08-24 is a card/benchmark-table update, not new weights. Surfacing here because it qualifies as "trending" (high downloads + recent activity). ⚠ **Large:** 120B total — needs multi-GPU/workstation; consumer-local requires heavy quantization.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench (v5) | 81.19 | lab |
| Aider polyglot | — | — |
| SWE-bench Verified (OpenHands) | 60.47 | lab |
| SWE-bench Multilingual (OpenHands) | 45.78 | lab |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench (TauBench V2 avg) | 61.15 | lab |
| ToolACE | — | — |
| GAIA | — | — |
| Terminal Bench Core 2.0 | 31.00 | lab |
| BrowseComp with Search | 31.28 | lab |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU-Pro | 83.73 | lab |
| GPQA Diamond (no tools) | 79.23 | lab |
| MATH | — | — |
| AIME 2025 (no tools) | 90.21 | lab |

## Efficiency

- **Active params:** 12B active / 120B total
- **Context length:** 1,048,576 tokens (default 256k in HF config; 1M requires `VLLM_ALLOW_LONG_MAX_MODEL_LEN=1`)
- **VRAM (fp16 rough):** ~240 GB at fp16 (120B × 2 bytes) — ⚠ not consumer-friendly; quantization required to run locally

## What makes it notable

Nemotron-3-Super is a strong general-purpose coding/agentic model: 60.47 SWE-bench Verified (OpenHands harness), 81.19 LiveCodeBench, and a τ-Bench V2 average of 61.15 plus Terminal Bench/BrowseComp — genuine multi-agent credentials, not just an MMLU card. Its LatentMoE (Mamba-2 + MoE + attention hybrid with MTP) routes through a smaller latent space for better accuracy-per-byte, and it supports up to 1M context for long agent trajectories. Crucially it is **fully open** — weights, datasets, and recipes under the NVIDIA Nemotron Open Model License, and the card states it is "ready for commercial use." The catch for the "run it locally" user is the 120B total footprint. Positioned against Qwen3.5-122B-A10B (~66 SWE-bench) and GPT-OSS-120B (~42 SWE-bench): it splits the difference, beating the open-weights baseline substantially.

## See also

- [[welcome]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3-Super-120B-A12B-BF16
