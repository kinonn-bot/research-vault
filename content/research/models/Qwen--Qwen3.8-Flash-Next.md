---
title: "Qwen 3.8 Flash Next"
org: Qwen
model_id: Qwen/Qwen3.8-Flash-Next
date: 2026-08-28
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - vl
  - moe
  - hybrid
  - instruct
downloads: 4810
likes: 3919
license: qwen-community-1.0
pipeline: image-text-to-text
source: https://huggingface.co/Qwen/Qwen3.8-Flash-Next
params: 6B active (125B total, +51B n-gram, +4B MTP)
context: 262144 (extensible to 1M)
architecture: hybrid MoE (Gated DeltaNet + Qwen Sparse Attention), QSA micro-block
---

# Qwen 3.8 Flash Next

**One-line:** ⚠ VL — Qwen's experimental hybrid-MoE "Flash" agentic coder (6B active / 125B total) with strong agentic-coding evals, caught by the per-org sweep (not the text-gen streams; it's `image-text-to-text`). ⚠ All scores below are **lab-reported** (Qwen's own card) — no independent source yet on this 3-day-old drop. Custom architecture `Qwen4ExpForConditionalGeneration` requires `trust_remote_code`.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | 91.9 (v6) | lab-reported |
| Aider polyglot | — | — |
| SWE-bench Verified | — (publishes **SWE-bench Pro 62.5** instead) | lab-reported |
| SWE-bench Multilingual | 81.0 | lab-reported |
| DeepSWE 1.1 (agentic stand-in) | 58.7 | lab-reported |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — (publishes **Toolathlon Verified 73.5** instead) | lab-reported |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| Toolathlon Verified (Pass@1, stand-in) | 73.5 | lab-reported |
| Agents' Last Exam (frontier agentic) | Pass@1 24.3 / Score 51.2 | lab-reported |
| CoWorkBench (long-horizon office) | 73.9 | lab-reported |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 91.7 | lab-reported |
| MATH | — | — |
| AIME 2025 | — | — |
| HLE | 35.9 | lab-reported |
| IFBench (instruction following) | 81.3 | lab-reported |

## Efficiency

- **Active params:** 6B active (125B total, +51B n-gram embedding, +4B MTP)
- **Context length:** 262,144 natively, extensible to 1,000,000 tokens
- **VRAM (fp16 rough):** ~250GB at fp16 (125B total) → ⚠ **large**; must be quantized for local/agent use. 6B active keeps inference compute low but the checkpoint download is huge.
- ⚠ **Custom architecture** (`qwen4_exp`, `Qwen4ExpForConditionalGeneration`) — stock transformers won't load it; needs `trust_remote_code` + repo code. llama.cpp/GGUF support unknown (early).

## What makes it notable

Qwen3.8-Flash-Next is an experimental "Flash" variant that pairs a 6B-active MoE body with Gated DeltaNet + Qwen Sparse Attention (QSA) hybrid attention, targeted squarely at agentic workloads — QSA cuts long-context latency, preserved-thinking keeps reasoning traces for multi-turn agents, and it natively runs 262K context (1M with RoPE/YaRN scaling). Its agentic-coding numbers are legitimately strong for a 6B-active model: SWE-bench Pro 62.5, SWE-bench Multilingual 81.0, DeepSWE 1.1 58.7, LiveCodeBench v6 91.9, Toolathlon 73.5. It edges its own larger sibling Qwen3.8-27B and DeepSeek-V4-Flash-0731 on most agentic rows. Caveats: it's a VLM (`image-text-to-text`), all numbers are lab-reported with no independent confirmation yet, and the custom architecture means local deployment requires repo model code and heavy quantization (~250GB fp16). For this user's "runs locally" bar, the 6B-active MoE is attractive but the total-param download and custom-arch requirement are real friction right now.

## See also

- [[welcome]]
- Source: https://huggingface.co/Qwen/Qwen3.8-Flash-Next
