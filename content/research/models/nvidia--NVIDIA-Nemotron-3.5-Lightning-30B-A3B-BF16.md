---
title: "NVIDIA Nemotron 3.5 Lightning 30B-A3B"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-3.5-Lightning-30B-A3B-BF16
date: 2026-08-11
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid
  - mamba
  - instruct
  - long-context
  - local
downloads: 15740
likes: 61
license: OpenMDW-1.1
pipeline: text-generation
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Lightning-30B-A3B-BF16
params: "30B total / 3B active (MoE)"
context: "256K single-GPU (up to 1M)"
architecture: hybrid moe (Mamba-2 + MoE + Attention, NemotronH)
---

# NVIDIA Nemotron 3.5 Lightning 30B-A3B

**One-line:** First Nemotron 3.5 model (GA 2026-08-11) — a 30B/3B-active hybrid Mamba-MoE reasoning model aimed squarely at long-running agent deployments; AA Intelligence Index 24 (+9 over Nemotron 3 Nano), ~670 tok/s on NVFP4, OpenMDW-1.1 commercial-use license.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 51.56 | NVIDIA (NeMo Evaluator, lab-reported) |
| SWE-bench Multilingual | 39.33 | NVIDIA (lab-reported) |
| Terminal-Bench 2.1 | 24.58 | NVIDIA (lab-reported) — AA independently confirms 24% |
| SciCode | 32.60 | NVIDIA (lab-reported) |
| PinchBench | 85.37 | NVIDIA (lab-reported) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| τ³-bench (Banking) | 9.28 | NVIDIA (lab-reported) |
| GDPval-AA v2 (Elo) | 824 | Artificial Analysis (independent) — surpasses Nemotron 3 Super and gpt-oss-120b; NVIDIA card reports 832 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU Pro | 81.94 | NVIDIA (lab-reported) |
| GPQA Diamond (no tools) | 75.44 | NVIDIA (lab-reported) |
| HLE (text-only, no tools) | 11.72 | NVIDIA (lab-reported) |
| AA Intelligence Index | 24 | Artificial Analysis (independent; vs 15 for Nemotron 3 Nano, 26 for Nemotron 3 Super, 24 for gpt-oss-120b) |
| AA-Omniscience | 17.50 | NVIDIA (lab-reported) |
| BrowseComp | 36.97 | NVIDIA (lab-reported) |
| AA-LCR (long context) | 52.00 | NVIDIA (lab-reported) |

## Efficiency

- **Active params:** 3B per token (30B total; AA measures 31.6B total / 3.6B active)
- **Context length:** up to 1M tokens; 256K configured for single-H100 deployment (max_position_embeddings 262144)
- **VRAM (fp16 rough):** ~60 GB BF16 → needs 1× H100/A100 80GB; NVFP4 ≈ 15 GB → runs on DGX Spark / RTX 5090-class hardware
- **Speed:** ~670 tok/s measured by AA on a pre-release DeepInfra NVFP4 endpoint — fastest in its size class by a wide margin (Qwen3.6-35B-A3B ≈ 3.5 min per AA-index task vs ~0.5 min for Lightning)
- ⚠ Custom architecture (`NemotronHForCausalLM`, `model_type: nemotron_h`) — needs recent transformers (4.57.6+) / vLLM nightly / SGLang; Mamba cache uses FlashInfer backend
- Reasoning mode toggleable via chat template (`enable_thinking=True/False`); ships MTP + DSpark/DFlash speculative decoding; tool-call parser `qwen3_coder` + `--enable-auto-tool-choice` for agent loops
- NVFP4 variant is the recommended deployment path; BF16 is the customization/post-training reference

## What makes it notable

The first Nemotron 3.5 release and a step-change for NVIDIA's small-model agentic line: AA puts it at Intelligence Index 24 — in line with gpt-oss-120b (24) at roughly a quarter of the total parameters, and only behind Nemotron 3 Super (26) which is ~4× its size. The agentic gains vs its predecessor are the headline: GDPval-AA v2 Elo 824 (past gpt-oss-120b and Nemotron 3 Super) and Terminal-Bench 2.1 at 24% vs Nemotron 3 Nano's 7%. For local/agent use this is a genuinely efficient workhorse — 3B active params, 1M context, ~670 tok/s on NVFP4, permissive OpenMDW-1.1 (commercial OK, unlike the $10M-threshold LFM-style licenses). SWE-bench Verified 51.56 is below Qwen3.6-35B-A3B's 70.12 in NVIDIA's own table, so it's not the top coding model in its class — but on cost-per-agent-turn and throughput it's the fastest small open model shipping today, with day-0 SGLang and vLLM support. Position: the pick when you need many parallel long-running agent loops on limited VRAM rather than a single strongest coder.

## See also

- [[welcome]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Lightning-30B-A3B-BF16
- Deploy variant: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Lightning-30B-A3B-NVFP4
- Independent: https://artificialanalysis.ai/articles/nemotron-3-5-lightning-launch
