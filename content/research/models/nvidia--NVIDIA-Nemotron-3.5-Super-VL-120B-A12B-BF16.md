---
title: "NVIDIA Nemotron 3.5 Super VL 120B-A12B"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-3.5-Super-VL-120B-A12B-BF16
date: 2026-10-16
tags:
  - huggingface
  - image-text-to-text
  - multimodal
  - vision-language
  - moe
  - hybrid
  - mamba
  - coding
  - agentic
  - tool-calling
  - long-context
  - nvidia
downloads: 142
likes: 35
license: OpenMDW-1.1
pipeline: "image-text-to-text (VL)"
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Super-VL-120B-A12B-BF16
params: "120B total / 12B active (MoE, 512 routed experts per MoE layer)"
context: "1,048,576 (1M tokens)"
architecture: "hybrid moe (Mamba-2 + attention, Nemotron Hybrid MoE; C-RADIO v4-H vision encoder; shared MTP head for speculative decoding; model_type nemotron_h_omni)"
---

# NVIDIA Nemotron 3.5 Super VL 120B-A12B

**One-line:** NVIDIA's new flagship open model — a 120B/12B-active Mamba-2 hybrid MoE VLM with 1M context built for always-on agents and document work; released 2026-10-15 with weights + datasets + recipes. Artificial Analysis (independent) scores it the **leading US open-weight model** (Intelligence Index 26.5 vs Inkling-Small 25.7, Nemotron 3 Ultra 23), using ~60% fewer output tokens per task than its predecessor. ⚠ 248.9 GB BF16 (≈60 GB NVFP4) — 4×H100/2×GB200-class serving, not a single-consumer-GPU model.

> ⚠ Coding/agentic numbers below are **lab-reported**, collected via NVIDIA's NeMo Gym harness (recipes published); treat cross-model gaps as indicative. Independent AA aggregates (Intelligence Index 26.5, NVFP4 ≈ lossless, ~630 tok/s @100k prompt on NVFP4) are called out separately.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 88.22 (v6) | lab — NeMo Gym; vs Qwen3.8-Flash-Next 94.1, DeepSeek-V4-Flash-0731 94.6, Inkling-Small 88.3, GLM-5.3-Flash 80.6 |
| Aider polyglot | — | not published |
| SWE-bench Verified | 71.10 | lab — NeMo Gym; vs Qwen3.5-122B-A10B 71.9, DeepSeek-V4-Flash-0731 75.4, Qwen3.8-Flash-Next 78.7, GLM-5.3-Flash 79.10 |
| SWE-bench Multilingual | 67.72 | lab; trails Qwen3.8-Flash-Next 77.10, GLM-5.3-Flash 78.30 |
| SWE-bench Pro | 51.78 | lab; trails Qwen3.8-Flash-Next 60.37, GLM-5.3-Flash 59.70. Harness-level coding-agent results published as an image chart only |
| SciCode (subtask) | 47.13 | lab; vs DeepSeek-V4-Flash 49.3, GLM-5.3-Flash 50.05 |
| DeepSWE [offline] | 24.65 | lab; trails DeepSeek-V4-Flash 42.3, Qwen3.8-Flash-Next 55.57, GLM-5.3-Flash 57.77 |
| Terminal Bench 4 [offline] | 1 | lab; Qwen3.8-Flash-Next 20.71, GLM-5.3-Flash 15.15 |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ²-bench (retail / airline / telecom) | 69.24 / 76.50 / 73.19 | lab; telecom trails badly (Qwen3.8-Flash-Next 90.4, GLM-5.3-Flash 98.5) |
| τ³-Bench Banking | 18.88 | lab; vs Qwen3.8-Flash-Next 44.5, GLM-5.3-Flash 34.8 |
| ToolACE | — | not published |
| Terminal-Bench 2.1 | 66.70 | lab; vs Inkling-Small 53.4, DeepSeek-V4-Flash-0731 76.8, GLM-5.3-Flash 82.7, Qwen3.8-Flash-Next 85.8 |
| GAIA | — | not published |
| BrowseComp | 78.00 | lab (offline 78); vs Qwen3.8-Flash-Next 89.0, GLM-5.3-Flash 86.6 |
| WebVoyager [offline] | 77.72 | lab; vs Qwen3.8-Flash-Next 90.39, GLM-5.3-Flash 72.64 |
| OSWorld-Verified | 51.14 | lab |
| MCP-Atlas | — | not published for Super VL |
| GDPval-AA v2 | 1211 | lab (Elo-style); vs GLM-5.3-Flash 1563, Qwen3.8-Flash-Next 1561 |
| AutomationBench-AA [offline] | 32.44 | lab; vs Qwen3.8-Flash-Next 72.06, GLM-5.3-Flash 70.17 |
| AA-Briefcase-Lite [offline] | 1137 \| 1252 \| 40 | lab (Elo pair + duration) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | 76.91 (MMLU-ProX) | lab; trails Qwen3.5-122B-A10B 83.2, GLM-5.3-Flash 83.0 |
| GPQA Diamond | 89.52 | lab; vs DeepSeek-V4-Flash-0731 89.6, GLM-5.3-Flash 91.2 |
| MATH | — | not published |
| AIME 2025 / 2026 | — | not published |
| HLE | 31.79 (text-only) / 29.20 (full) | lab; vs Qwen3.8-Flash-Next 39.6, GLM-5.3-Flash 36.47 |
| CritPt | 10.86 | lab; vs DeepSeek-V4-Flash 12.6 |
| APEX shortlist | 88.36 | lab |
| AA-LCR v1.1 | 68.62 | lab; trails DeepSeek-V4-Flash 79.7, GLM-5.3-Flash 79.5 |
| IFBench | 70.86 | lab |
| GraphWalks | 89.71 | lab; leads set (GLM-5.3-Flash 88.4, Qwen3.5-122B 86.1) |
| WMT24++ | 84.80 | lab |

## Multimodal (VL specifics — why it exists)

| Benchmark | Score | Source |
|:---|---:|:---|
| CharXiv reasoning | 80.82 (84 w/ Python tool) | lab; vs Qwen3.8-Flash-Next 85.8 |
| OCRBench v2 (EN / ZH) | 68.12 / 59.15 | lab; EN edges GLM-5.3-Flash 61.8 |
| MMLongBench-Doc | 62.82 | lab |
| MathVision | 78.16 | lab |
| V* | 85.60 | lab |
| OCR-Reasoning | 65.08 | lab |
| Video-MME v2 | 32.85 | lab; vs Qwen3.8-Flash-Next 45.1 |
| BabyVision | 29.60 | lab |

*The card markets vision for "OCR, tables, charts, multi-page documents, and videos" — parse a chart, link it to a table elsewhere in the same document, summarize both without a separate image model.*

## Independent verification (Artificial Analysis, 2026-10-15)

- **Intelligence Index 26.5 — leading US open-weight model**; edges Thinking Machines' Inkling Small (25.7), beats Nemotron 3 Ultra (23) and Meta Muse Glimmer (17). Still trails UAE K2 Horizon 375B A23B (31) and China's MiMo-V2.6-Pro (46) on open-weights intelligence.
- **Token efficiency:** ~46k output tokens per Intelligence Index task — ~60% fewer than predecessor Nemotron 3 Super (114k).
- **NVFP4 ≈ lossless:** NVFP4 scores within 0.1 points of BF16 on the Index (no component moves >2.6 pts).
- **Speed:** ~630 tok/s output @100k-token prompts (pre-release DeepInfra NVFP4 endpoint) — fastest AA has measured among models scoring ≥20 on the Index at that prompt length; 1.8s time-to-first-token. EXO Labs (DGX Spark): no other tested model was both more accurate *and* faster.

## Efficiency

- **Active params:** 12B per token of 120B total (512 routed experts/MoE layer; hybrid Mamba-2 + attention)
- **Context length:** 1,048,576 (1M) — prompt + vision + history + tool results share the window
- **VRAM:** BF16 = 248.9 GB across 64 safetensors (verified). Deployment: 4×H100 (TP4) or 2×GB200 (TP2) for 1M ctx, vLLM (`nemotron-3.5-super-vl`; NeMo Gym recipes published) or SGLang (`lmsysorg/sglang:v0.5.20`). NVFP4 sibling (`-NVFP4`, ~60 GB-class) + `-NVFP4-LiLiCorr` drafter for Blackwell; `-Base-BF16` for pretraining. Native MTP speculative head (3-5 draft tokens, no separate drafter). ⚠ Not local-single-GPU; wait for community GGUF/Unsloth quants (already appearing) for anything smaller.
- **Runs on:** DGX Spark / DGX Station / RTX PRO / RTX, Jetson (edge), data centers; NIM microservice w/ biweekly updates. Optimized for NVIDIA hardware throughout.

## What makes it notable

NVIDIA's successor jump: Nemotron 3 Super (a text model) → a 3.5-generation multimodal agent model that AA scores 2× its predecessor's intelligence, #1 among US open weights. It was distilled from Nemotron 3 Ultra and NVIDIA claims agent-harness parity-or-better vs Ultra at ~1/5 the parameters (their own Hermes + LangChain agent tests). The interesting trade-off for this user: it is not a local model (248.9 GB BF16 / ~60 GB NVFP4), but its token efficiency (~60% fewer tokens per task) and throughput (~630 tok/s NVFP4) target exactly the long-running-agent workload. On the card's cross-comparisons it beats Qwen3.5-122B and Gemma-4-26B-A4B on agentic rows, trails Qwen3.8-Flash-Next / DeepSeek-V4-Flash / GLM-5.3-Flash on most coding rows. Released alongside datasets (post-training v3, pre-training, Indic 2.83T tokens) and recipes. Sister model: [[nvidia--NVIDIA-Nemotron-3.5-Bolt-74B-A9B-BF16]] (74B/9B, 24GB-local). Watch for: `.eval_results`-style machine-readable evals, community quants, and whether SWE-bench Pro harness spread matches the lab chart.

## See also

- [[welcome]]
- Sister: [[nvidia--NVIDIA-Nemotron-3.5-Bolt-74B-A9B-BF16]]
- Prior generation (non-VL): [[nvidia--NVIDIA-Nemotron-3-Super-120B-A12B-BF16]]
- Sibling: [[nvidia--NVIDIA-Nemotron-3.5-Lightning-30B-A3B-BF16]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Super-VL-120B-A12B-BF16
