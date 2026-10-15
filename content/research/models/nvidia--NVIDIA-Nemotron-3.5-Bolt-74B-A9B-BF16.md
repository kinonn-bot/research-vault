---
title: "NVIDIA Nemotron 3.5 Bolt 74B-A9B"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-3.5-Bolt-74B-A9B-BF16
date: 2026-10-16
tags:
  - huggingface
  - image-text-to-text
  - multimodal
  - vision-language
  - moe
  - hybrid
  - mamba
  - int4
  - coding
  - agentic
  - tool-calling
  - local
  - nvidia
downloads: 58
likes: 52
license: OpenMDW-1.1
pipeline: "image-text-to-text (VL)"
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-74B-A9B-BF16
params: "74B total / 9B active (MoE, top-9 routed experts)"
context: "262,144 (256K tokens)"
architecture: "hybrid moe (Mamba-2 + LatentMoE, compressed from Super VL 120B-A12B via NVIDIA Star Elastic; C-RADIO v4-H vision encoder; LiLiCorr/DFlash drafter variant; model_type nemotron_h_omni)"
---

# NVIDIA Nemotron 3.5 Bolt 74B-A9B

**One-line:** The first locally-runnable Nemotron 3.5 — a 74B/9B-active vision-language Mamba-2 hybrid MoE compressed from Super VL into a **24 GB memory footprint** (native 2-bit quantization-aware training on routed experts), released 2026-10-15 for "everyday agentic tasks" on RTX Spark / DGX Spark / 24GB-GPU machines; runs day-0 in llama.cpp, vLLM, Ollama, Unsloth and LM Studio. Independent AA Intelligence Index **21.4** — 4th among <100B models, 1st among US models in that class. **This is the local agent model of the release pair** (downloaded variant counts at note time: 24GB 58 / 24GB-GGUF 119 / LiLiCorr 20 / BF16 4; likes shown are for the 24GB variant).

> ⚠ Benchmark table below is **lab-reported** (NVIDIA card; BF16 / 24GB-IQ2 columns), collected by NVIDIA — cross-model gaps are indicative, not audited. Artificial Analysis aggregates (independent) called out separately.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (Terminal-Bench 2.1 / MCP-Atlas used instead) |
| SWE-bench Multilingual | — | not published |
| SciCode | 44.49 (BF16) / 41.02 (24GB) | lab; vs Qwen3.6-35B-A3B 35.33, Gemma4 26B-A4B 40.28, Lightning-30B 31.38 |
| Terminal-Bench 2.1 | 53.93 (BF16) / 50.98 (24GB) | lab; leads Qwen3.6-35B-A3B 44.38, Gemma4 26B-A4B 37.22, Nemotron 3.5 Lightning-30B 23.46 |
| PinchBench (agent tasks) | 90.35 (BF16) / 87.82 (24GB) | lab; vs Qwen3.6-35B-A3B 88.07 |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ³-Bench Banking | 17.01 (BF16) / 17.01 (24GB) | lab; vs Qwen3.6-35B-A3B 10.52, Gemma4 14.02 |
| ToolACE | — | not published |
| MCP-Atlas (500 public tasks) | 55.60 (BF16) / 52.20 (24GB) | lab; vs Qwen3.6-35B-A3B 51.20 (re-measured), Lightning-30B 46.4 |
| GAIA | — | not published |
| BrowseComp | 70.00 (BF16) / 66.75 (24GB) | lab; crushes Qwen3.6-35B-A3B 48.74, Gemma4 26.30 |
| WebArena (vision) | 50.25 (BF16) / 50.86 (24GB) | lab; vs Qwen3.6-35B-A3B 36.60 |
| GDPVal-AA-V2 | 31.13 (BF16) / 28.47 (24GB) | lab; vs Qwen3.6-35B-A3B 25.75, Gemma4 15.33 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 88.83 (BF16) / 86.43 (24GB) | lab; vs Qwen3.6-35B-A3B 83.40, Gemma4 79.61 |
| MATH | — | not published |
| AIME 2025 / 2026 | — | not published |
| HLE (no tools) | 28.73 (BF16) / 25.30 (24GB) | lab; vs Qwen3.6-35B-A3B 19.56, Gemma4 17.42 |
| AA-LCR | 67.38 (BF16) / 64.06 (24GB) | lab; vs Qwen3.6-35B-A3B 61.06 |
| AA-Omniscience (accuracy / non-hallucination) | 21.80 / 56.14 (BF16), 16.90 / 61.27 (24GB) | lab |

## Independent verification (Artificial Analysis, 2026-10-15)

- **Intelligence Index 21.4** — 4th among models <100B params, 1st among US models in that class; +8.6 points vs Nemotron 3 Super (12.8) with 39% fewer total parameters; 1.5 points behind Nemotron 3 Ultra 550B (23) at ~1/7 the size.
- Vs Nemotron 3 Ultra: **leads** AutomationBench-AA (15.5% vs 3.0%) and AA-Briefcase (912 vs 874 Elo); **trails** AA-LCR (70% vs 79%) and HLE (25% vs 28%).
- Token usage: ~82k output tokens per Intelligence Index task — 1.8× Super VL, but 28% fewer than Nemotron 3 Super.
- Local-deployment coverage: the-decoder and NVIDIA both pitch "delegate to local agent harnesses (research, write, debug code) without sending workloads to the cloud". A later **Bolt E4B (4GB) for voice assistants is announced for later in October** — radar.

## Efficiency

- **Active params:** 9B per token of 74B total (top-9 routed experts; Parent 120B-A12B → Bolt 74B via Star Elastic router-guided compression, 120B recovery tokens)
- **Context length:** 262,144 (256K)
- **Memory footprint:** **24GB variant = 24.1 GB across 90 safetensors (verified)** — native 2-bit routed-expert quantization (QAT), designed to fit alongside other apps on a 24GB machine. BF16 for post-training = 149.8 GB (64 shards). GGUF for llama.cpp; official `-24GB-GGUF` + `-LiLiCorr` (DFlash drafter; 2.3× speed claim on DGX Spark) variants. Serving: vLLM (newer version, `VLLM_USE_V2_MODEL_RUNNER=1`, FlashInfer mamba backend, `qwen3_coder` tool parser) or llama.cpp/Ollama/LM Studio/Unsloth.
- **Recommendation:** for a 24-32GB GPU box or DGX Spark this is currently the strongest local agentic option in its memory class (BF16-quality with 2-bit footprint; TB2.1 50.98 even in IQ2).

## What makes it notable

NVIDIA's answer to "run a real agent model on a desktop": instead of shrinking a small model, they compressed the 120B Super VL down to 74B/9B and trained natively at 2-bit for a 24GB footprint, keeping published agentic capability (MCP-Atlas 52-56, BrowseComp 67-70, TB2.1 51-54) that beats similar-memory MoEs (Qwen3.6-35B-A3B, Gemma4 26B-A4B) and even their own 30B Lightning by >2× on Terminal-Bench. AA's independent Index (21.4) confirms it lands 4th among open <100B models despite the aggressive quantization. For this user: the 24GB variant is directly relevant to local agent use (llama.cpp/Ollama/LM Studio day-0; "usable from agent frameworks such as Hermes and OpenClaw" per launch coverage). Weaknesses: trails Super VL/Ultra on long-context reasoning (AA-LCR 70 vs 79) and uses ~1.8× Super VL's tokens per task; no SWE-bench Verified number yet. Watch for: SWE-bench Verified / BF16-vs-IQ2 independent audits, community GGUF quality, and Bolt E4B.

## See also

- [[welcome]]
- Parent: [[nvidia--NVIDIA-Nemotron-3.5-Super-VL-120B-A12B-BF16]]
- Sibling: [[nvidia--NVIDIA-Nemotron-3.5-Lightning-30B-A3B-BF16]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-74B-A9B-BF16
- Local variant: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-74B-A9B-24GB (GGUF: `...-24GB-GGUF`)
