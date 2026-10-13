---
title: "OpenBMB MiniCPM-V-4.7-35B-A3B"
org: openbmb
model_id: openbmb/MiniCPM-V-4.7-35B-A3B
date: 2026-10-14
tags:
  - huggingface
  - image-text-to-text
  - multimodal
  - vision-language
  - moe
  - coding
  - agentic
  - tool-calling
  - on-device
  - ocr
downloads: 630
likes: 448
license: apache-2.0
pipeline: "image-text-to-text (VL)"
source: https://huggingface.co/openbmb/MiniCPM-V-4.7-35B-A3B
params: "3B active (35B total; Qwen3.5-MoE text backbone — 40 layers, 256 experts, top-8)"
context: "262144 (256K)"
architecture: "VL moe (custom minicpmv4_7; Qwen3.5-MoE text + SigLIP2 vision; mixed 4x/16x visual token compression)"
---

# OpenBMB MiniCPM-V-4.7-35B-A3B

**One-line:** OpenBMB's on-device multimodal MoE — first open-source MoE designed to run *smoothly* on phones (Lookahead Expert Scheduling + fine-grained quant + DSpark → 13+ tok/s on an iPhone 17 Pro Max with 3 GB memory); Qwen3.5-35B-A3B language backbone behind a SigLIP2 vision encoder. Released 2026-10-12; it publishes real coding/agentic evals (LiveCodeBench-v6 56.57, BFCL-V4 60.06, τ²-Bench 84.65) — the qualification for a VL entry in this tracker.

> ⚠ All numbers below are **lab-reported** and were published only as image charts on the model card (read via vision extraction); not independently verified. VL-model numbers are not strictly comparable to text-only pipeline results. Launched <36h before this note.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 56.57 (v6) | lab — image-only card chart; vs Qwen3.6-35B-A3B 54.29, Qwen3.8-27B 63.62, Gemma-4-31B 71.24 |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | 60.06 (V4) | lab — image-only card chart; vs Qwen3.6-35B-A3B 60.20, Qwen3.8-27B 63.72 |
| τ-Bench | τ²-Bench 84.65 | lab — image-only card chart; **leads comparison set** (Qwen3.6-35B-A3B 79.65, Gemma-4-31B 67.35) |
| ToolACE | — | not published |
| GAIA | — | not published |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| CMMLU | 90.21 | lab — image-only card chart; leads set (Qwen3.6-35B-A3B 89.34) |
| MMLU-Pro | 83.45 | lab |
| SuperGPQA | 61.23 | lab |
| IFBench | 47.67 | lab |
| AIME26 @avg16 | 76.46 | lab |

## Efficiency

- **Active params:** ~3B active / 35B total (Qwen3.5-MoE text backbone: 40 layers, 256 experts, top-8, hidden 2048); SigLIP2 vision encoder
- **Context length:** 262,144 tokens (256K)
- **VRAM (fp16 rough):** ~70 GB for LLM+vision at BF16 → quantize for local GPU/desktop; on-device via GGUF/int4/AWQ/GPTQ + FP8 siblings (all first-party)
- **On-device:** 13+ tok/s on iPhone 17 Pro Max with ~3 GB memory; supports iOS/Android/HarmonyOS; day-0 chip support (Rockchip, Houmo, Intel, AMD, Arm)
- **Custom architecture:** `minicpmv4_7` / `MiniCPMV4_7ForConditionalGeneration` — needs repo model code + transformers >= 5.18 (stock loaders may fail)

## What makes it notable

MiniCPM-V 4.7 is the first open-source MoE that targets *lossless* on-device inference rather than a capability/efficiency trade: Lookahead Expert Scheduling prefetches experts while preserving the router's free choice, and DSpark speculative sampling is integrated — so a 35B-A3B model serves at 13+ tok/s on a phone. Under the hood it's a Qwen3.5-35B-A3B backbone (acknowledged on the card) plus SigLIP2, with mixed 4x/16x visual token compression for OCR/PDF/video work. For this tracker the point is that a VL model now posts competitive agentic numbers: τ²-Bench 84.65 beats Qwen3.6-35B-A3B, and BFCL 60.06 is in the same band — making it a plausible local multimodal agent companion, not just an OCR tool. Apache-2.0.

## See also

- [[welcome]]
- Source: https://huggingface.co/openbmb/MiniCPM-V-4.7-35B-A3B
- GitHub: https://github.com/openbmb/MiniCPM-V
