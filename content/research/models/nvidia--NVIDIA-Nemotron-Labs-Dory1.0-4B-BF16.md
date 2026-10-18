---
title: "NVIDIA-Nemotron-Labs-Dory1.0-4B"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-Labs-Dory1.0-4B-BF16
date: 2026-10-19
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - looped
  - latent-recurrent
  - nvidia
  - instruct
  - tool-use
  - edge
downloads: 1247
likes: 115
license: OpenMDW-1.1
pipeline: text-generation
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Dory1.0-4B-BF16
params: "4B total (8 input + 20 shared recurrent looped + 8 output layers)"
context: "262,144 (256K tokens)"
architecture: "looped latent-recurrent normalized-GPT (dory / DoryForCausalLM; interleaved sliding-window + full attention; elastic 1/2/4 inference loops)"
---

# NVIDIA-Nemotron-Labs-Dory1.0-4B

**One-line:** NVIDIA's looped (latent-recurrent) 4B — one checkpoint, three compute budgets: the shared recurrent block runs 1/2/4 times at inference, taking SWE-bench Verified from 50.3 → 59.5 → **61.8** (matching Qwen3.5-9B's 61.0 at 2.3× the parameter count), with last-loop KV caching that keeps cache memory at the one-loop size. Commercially usable OpenMDW-1.1, 256K context, runs from an ~8 GB GGUF.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 50.3 / 59.5 / 61.8 (1 / 2 / 4 loops) | lab (NVIDIA, NeMo Gym / Nemo Evaluator SDK) — vs Qwen3.5-4B 54.7, Qwen3.5-9B 61.0, Gemma 4 26B-A4B 57.40, Qwen3.6-35B-A3B 73.4† |
| SWE-bench Multilingual | — | not published |
| SciCode | 27.3 / 34.94 / 35.11 (1 / 2 / 4 loops) | lab |
| Terminal-Bench 2.1 | 12.5 / 18.1 / 22.2 (1 / 2 / 4 loops) | lab (Terminus-2 harness for all models) — vs Qwen3.5-9B 24, Gemma 4 26B-A4B 35, Qwen3.6-35B-A3B 43 |

*All numbers lab-reported; no independent replication published yet (Artificial Analysis has only NVIDIA's own supplied aa432 estimate chart on the card). NVIDIA recommends 2 loops as the default and 4 for agentic work.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench (τ³-bench, Banking) | 11.6 / 12.89 / 14.69 (1 / 2 / 4 loops) | lab — vs Qwen3.5-9B 7.22, Gemma 4 26B-A4B 13.66, Qwen3.6-35B-A3B 9.54 |
| ToolACE | — | not published |
| GAIA | — | not published |
| GDPval-AA-V2 | 815 / 946 / 967 Elo (1 / 2 / 4 loops) | lab — vs Qwen3.5-9B 546, Gemma 4 26B-A4B 751.6, Qwen3.6-35B-A3B 987 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| GPQA Diamond (no tools) | 69.19 / 72.41 / 72.16 (1 / 2 / 4 loops) | lab — behind Qwen3.5-4B 77.71 |
| HLE (text-only, no tools) | 8.25 / 10.89 / 10.43 | lab — vs Qwen3.5-9B 15.43 |
| IFBench | 74.29 / 77.94 / 79.00 | lab — beats Qwen3.5-9B 59 and Qwen3.6-35B-A3B 57.44 |
| AA-LCR (long context) | 63 / 71 / 73 | lab |

## Efficiency

- **Active params:** 4B total — no MoE; the whole model runs per token, with compute scaled by loop count instead (2 loops recommended, 4 for agentic)
- **Context length:** 262,144 tokens (256K validated; sliding-window 1,024 + full-attention layers)
- **VRAM:** BF16 ≈8 GB; official Q5_K_M GGUF is the local path (llama.cpp). NVFP4 runs ~2.17–2.44× faster than BF16 on DGX Spark. Last-loop KV caching keeps KV-cache memory at the one-loop footprint regardless of loop count.
- **Tooling caveat:** architecture is custom (`model_type: dory`) — at release vLLM support was still in review (PR #60149) and llama.cpp lived in PR #30306, so day-0 use means building those branches. Tool calls work via the `qwen3_coder` parser / `--jinja` chat template.
- **Training:** pretrained on 6T tokens (natively NVFP4, then BF16) plus 300B tokens of context extension; post-trained with multi-environment GRPO. English only.

## What makes it notable

The first mainstream open-weight model where inference-time depth is a *runtime dial* rather than a separate checkpoint — for a local agent loop that means one 8 GB download can be run cheap (1 loop) for bulk edits and deep (4 loops) for hard repo tasks, with no model swap and no KV-cache penalty. At 4 loops it matches Qwen3.5-9B on SWE-bench Verified (61.8 vs 61.0) at 4B parameters, and its instruction-following (IFBench 79) is well above models twice its size. The honest limits: Terminal-Bench 2.1 tops out at 22.2, less than half of Qwen3.6-35B-A3B's 43 — this is a small-model coding assistant, not a long-horizon terminal agent — τ³-banking ramps only to 14.69, and every number is vendor-reported with no third-party re-evaluation yet.

## See also

- [[welcome]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Dory1.0-4B-BF16
- GGUF (Q5_K_M): https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Dory1.0-4B-GGUF
- NVFP4: https://huggingface.co/nvidia/NVIDIA-Nemotron-Labs-Dory1.0-4B-NVFP4
