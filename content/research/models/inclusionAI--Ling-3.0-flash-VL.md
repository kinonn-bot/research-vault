---
title: "Ling-3.0-flash-VL"
org: inclusionAI
model_id: inclusionAI/Ling-3.0-flash-VL
date: 2026-09-10
tags:
  - huggingface
  - image-text-to-text
  - coding
  - agentic
  - moe
  - hybrid
  - mla
  - vl
  - video
  - reasoning
  - instruct
downloads: 1945
likes: 67
license: mit
pipeline: image-text-to-text
source: https://huggingface.co/inclusionAI/Ling-3.0-flash-VL
params: "5.5B active of 124B total (MoE, hybrid KDA + Gated MLA 5:1, 42 layers)"
context: "256K tokens (131K native + YaRN 2x)"
architecture: moe
---

# Ling-3.0-flash-VL

**One-line:** Native image+video extension of Ling-3.0-flash — 124B MoE with only 5.5B active, 256K context, MIT; AA Intelligence Index 25 on v4.3 (#2 in its open-weight class on the AA chart, independent), positioned for multimodal agent loops (WebVoyager 90.8, MMSearch 79.0). ⚠ large for home hardware — server-class, BF16 ~248GB / FP8 ~124GB. Weights open-sourced 2026-09-10 (repo created 09-04; DeepInfra announced BF16+FP8 release). Custom `bailing_moe_v3_vl` architecture — needs repo model code (SGLang cookbook / vLLM fork provided).

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
| Terminal-Bench 2.1 | — | card footnote: "evaluated under the Artificial Analysis (AA) protocol" — score sits in an image-only chart, not transcribed; no numeric value published in text |
| Vision2Web | 57.69 | lab (frontend coding from screenshots) |

*Caveat: the card's benchmark chart is an image (no `.eval_results/` YAMLs ship with the VL repo; the -fp8 sibling card repeats the same image). Vision2Web and all "lab" rows are from that chart, lab-reported. Independent: AA's own runs (see agentic table) plus the AA Intelligence Index.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| AutomationBench-AA | 36 | Artificial Analysis (independent; chart) |
| Terminal-Bench v4.0 | 0 (chart) | Artificial Analysis — treat as unverified; AA chart lists the model at 0%, no run details published |
| WebVoyager | 90.83 | lab (agentic multimodal) |
| MMSearch | 79.0 | lab (agentic multimodal) |
| ClawEval-MM | 59.9 | lab (agentic multimodal) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |
| AA Intelligence Index | 25 (v4.3) | Artificial Analysis (independent; scale differs from lab claim below) |
| AA Intelligence Index (lab-claimed) | 42 (v4.1.1) | lab — different index version, do not compare directly to AA's 25 |
| MMMU-Pro | 79.0 | lab (image-text) |
| MathVision | 84.87 | lab (image-text) |
| Humanity's Last Exam-MM | 19.88 | lab |

## Efficiency

- **Active params:** 5.5B per token (sparse MoE, 124B total; hybrid backbone: 42 layers alternating KDA and Gated MLA at 5:1)
- **Context length:** 256K tokens (131,072 native + YaRN 2x rope scaling for serving)
- **VRAM (fp16 rough):** ~248GB BF16 → 4×80GB (H100/H800) or 2×141GB-class (H200/B300) per the lab's serving recipes; FP8 variant (~124GB) runs on 2×141GB. Server-class; no single-GPU path.

## What makes it notable

Carries the full Ling-3.0-flash text/reasoning stack into vision with a tiny 5.5B active budget — the same efficiency pitch as its sibling, now with native image+video input for agent tasks that need screen/UI/document understanding (WebVoyager 90.8, Vision2Web 57.7, MMSearch 79.0 all lab-reported). AA independently scores it 25 on AA-II v4.3 and ranks it near the top of its open-weight class, though AA's Terminal-Bench v4.0 chart shows 0% — no run details published, so treat agentic-coding capability as unverified. MIT license, thinking-mode default on. Deployment caveat: `bailing_moe_v3_vl` is custom-code; stick to the lab's SGLang cookbook or `inclusionAI/vllm-ling-v3` fork until upstream support lands.

## See also

- [[welcome]]
- Source: https://huggingface.co/inclusionAI/Ling-3.0-flash-VL
- Sibling (text-only): [[inclusionAI--Ling-3.0-flash]]
- Artificial Analysis: https://artificialanalysis.ai/models/ling-3-0-flash-vl