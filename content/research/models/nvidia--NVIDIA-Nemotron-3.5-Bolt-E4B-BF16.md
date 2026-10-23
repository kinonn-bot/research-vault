---
title: "NVIDIA Nemotron 3.5 Bolt E4B (BF16)"
org: nvidia
model_id: nvidia/NVIDIA-Nemotron-3.5-Bolt-E4B-BF16
date: 2026-10-24
tags:
  - huggingface
  - text-generation
  - agentic
  - instruct
  - tool-calling
  - edge
  - slm
  - dense
  - gemma4-base
  - openmdw
downloads: 249
likes: 11
license: openmdw-1.1
pipeline: text-generation
source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-E4B-BF16
params: "8B total (4B effective)"
context: "65,536 (64K in / 64K out)"
architecture: "dense — Gemma-4-E4B post-train (model_type gemma4, Gemma4ForConditionalGeneration)"
---

# NVIDIA Nemotron 3.5 Bolt E4B (BF16)

**One-line:** NVIDIA's Oct-23 edge SLM — an 8B/4B-effective post-train of Gemma-4-E4B-it under OpenMDW-1.1, built for local voice/device assistants and game-NPC agents; the card publishes a full **agentic tool-use table measured under NVIDIA's own NeMo Gym harness** — BFCL-v3 68.51, τ²-Bench 55.10, ToolSandbox 68.77, When2Call Multi-Turn 63.36, IHEval 84.79. ⚠ **no coding benchmarks published at all** (no HumanEval/SWE-bench/LiveCodeBench/Aider) — evaluate it as a small tool-calling/instruction-following model, not a coding agent.

> Release date: NVIDIA's blog (Oct 15) announced Super VL + Bolt 74B-A9B as "available now, with Bolt E4B coming Oct. 23", and the Oct-23 RTX Spark post repeats "Bolt E4B 4GB … releases Friday, Oct. 23". The repo's `createdAt` is 2026-10-05 (staged empty/private), while the commits API pins the actual content drop: `initial commit` **2026-10-23T15:12Z**, then README updates 15:59Z and 17:12Z — i.e. 4.8h before this run. Per the "createdAt ≠ weight release date" rule, 2026-10-23 is the release date.

> ⚠ All numbers below are **NVIDIA-reported**, measured under their NeMo Gym harness ("they may differ from vendors' self-reported numbers" — i.e. NVIDIA re-ran the competitors too, which is a stronger provenance than a pure vendor card, but it is not a third party). No independent (Artificial Analysis / BenchLM / LMArena) evaluation found. **Ratings start at the `.eval_results`-style table on the card, not a third party.**

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

*No coding evaluation of any kind is published for this model — its benchmark slate is tool use, instruction following, persona/RP and RAG-groundedness.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL-v3 | 68.51 | NVIDIA — NeMo Gym; vs Gemma 4 E4B-it 66.39, Qwen3.5 4B 70.95, Nemotron-3 Nano-4B 61.10 |
| τ²-Bench (Tau2-Bench) | 55.10 | NVIDIA — NeMo Gym; **best in the BF16 row** (Gemma base 38.50, Qwen3.5 4B 75.06, Nano-4B 29.20) |
| ToolACE | — | not published (card uses ToolSandbox instead) |
| GAIA | — | not published |
| ToolSandbox | 68.77 | NVIDIA — NeMo Gym (Qwen3.5 4B 69.54) |
| When2Call (multi-turn) | 63.36 | NVIDIA — NeMo Gym; best in row (Gemma base 62.90, Nano-4B 27.70) |
| AgentIF | 25.81 | NVIDIA — NeMo Gym; best in row |
| MultiChallenge | 53.10 | NVIDIA — vs Gemma base 42.08, Qwen3.5 4B 51.76 |
| RelyToolBench (tool hallucination) | 63.16 | NVIDIA — vs Gemma base 61.60 |
| IHEval (instruction hierarchy) | 84.79 | NVIDIA — best in row (Gemma base 67.04) |
| StructEval-T | 80.40 | NVIDIA — vs Qwen3.5 4B 76.01 |
| LongMemEval | 72.10 | NVIDIA — vs Gemma base 70.95 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 / 2026 | — | not published |
| IFBench | 63.79 | NVIDIA — vs Gemma base 42.84, Qwen3.5 4B 58.91 |
| InverseIFEval | 46.84 | NVIDIA — best in row |
| RoleBench / RoleMRC | 67.05 / 80.63 | NVIDIA — persona/RP rows, best in row |
| EQ-Bench v3 | 39.40 | NVIDIA — vs Gemma base 41.17 |
| SysBench | 67.88 | NVIDIA — best in row |
| RULER (64K) | 86.99 | NVIDIA — vs Qwen3.5 4B 95.15 |
| LongBench v2 (48K) | 50.50 | NVIDIA — vs Qwen3.5 4B 59.93 |
| GaRAGe / RAGTruth | 42.61 / 77.59 | NVIDIA — groundedness rows, best in row |
| Brevity Benchmark | 82.52 | NVIDIA — best in row |

## Efficiency

- **Active params:** 4B effective / 8B total (dense Gemma-4-E4B backbone)
- **Context length:** 64K input / 64K output
- **VRAM:** BF16 ≈16 GB — the card's quickstart is a **single H100** (`vllm serve … --tensor-parallel-size 1`). The first-party **Q4_K_M sibling `nvidia/NVIDIA-Nemotron-3.5-Bolt-E4B-4GB`** is the ~4 GB llama.cpp path; a **DFlash NVFP4 drafter** (`…-BF16-DFlash-NVFP4`) ships for speculative decoding (7 draft tokens in the example config).
- **Runtime:** stock `transformers` (`model_type: gemma4`); vLLM v0.31.0+ with `--tool-call-parser gemma4 --reasoning-parser gemma4 --enable-auto-tool-choice`; llama.cpp recipe linked as "pending" on the 4GB card. Chat-template controls `enable_thinking` plus a runtime thinking budget, and a separate `conversational_mode`. Recommended temp 1.0 / top_p 0.95. Card has a technical report + NVIDIA blog; post-training data cutoff May 2026. Text in / text out (the underlying Gemma 4 E4B is multimodal but this post-train is text-only).
- **License:** OpenMDW-1.1 (permissive, NVIDIA's own; `license: other` + `license_name: openmdw-1.1`, `license_link` points off-repo to openmdw.ai — a `LICENSE` fetch 404s, which is expected for this license, not a missing license).

## What makes it notable

The third-generation NVIDIA ACE SLM tier, released 2026-10-23 as the small end of the Nemotron 3.5 Bolt family (Super VL and Bolt 74B-A9B shipped 10-15; this is the "E4B 4GB / embedded interfaces" tier). For this tracker the value is the **tool-use provenance**: the card publishes a 22-row agentic slate run under NVIDIA's own NeMo Gym harness, scoring both the model and its baselines — τ²-Bench 55.10 (its base Gemma-4-E4B-it scores 38.50 in the same harness), MultiChallenge 53.10 (base 42.08), IHEval 84.79 (base 67.04), RoleBench 67.05 (base 49.95): consistent double-digit post-training gains well past the 5-pp bar. In-book caveat: on several rows the cheaper Qwen3.5-4B baseline is *ahead* of it (BFCL-v3 70.95, τ² 75.06, RULER 95.15, LongBench v2 59.93), so Bolt E4B's pitch is not raw tool-calling accuracy but NVIDIA's ACE/edge stack — reachy-companion demo, DGX Spark/RTX deployment, a 4 GB Q4_K_M build, and a first-party speculative drafter. And it is **not** a coding model: zero coding evals, and the card targets voice assistants, interactive personas and in-game NPCs (SkyrimNET). Included here because it is an open-weight, locally-runnable, tool-calling model with real published agentic numbers and a documented release inside the window — flagged so it is not mistaken for a coding-agent candidate.

## See also

- [[welcome]]
- Source: https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-E4B-BF16
- NVIDIA blog: https://blogs.nvidia.com/blog/nemotron-3-5-super-vl/ · RTX Spark/ACE: https://blogs.nvidia.com/blog/local-ai-rtx-spark-laptops-software-updates/
- Technical report: https://research.nvidia.com/labs/nemotron/files/NVIDIA-Nemotron-3.5-Bolt-E4B-4GB-Technical-Report.pdf
- Siblings: [4GB Q4_K_M](https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-E4B-4GB) · [DFlash NVFP4 drafter](https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-E4B-BF16-DFlash-NVFP4) · [4GB DFlash](https://huggingface.co/nvidia/NVIDIA-Nemotron-3.5-Bolt-E4B-4GB-DFlash)
- Family: [[nvidia--NVIDIA-Nemotron-3.5-Bolt-74B-A9B-BF16]] · [[nvidia--NVIDIA-Nemotron-3.5-Super-VL-120B-A12B-BF16]]
