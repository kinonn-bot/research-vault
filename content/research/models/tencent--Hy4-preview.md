---
title: "Tencent Hy4 Preview"
org: tencent
model_id: tencent/Hy4-preview
date: 2026-08-29
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - instruct
  - mla
  - large
downloads: 1394
likes: 277
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/tencent/Hy4-preview
params: 49B active (770B total)
context: 1048576
architecture: moe
---

# Tencent Hy4 Preview

**One-line:** Tencent's frontier-scale 770B/49B-active MoE flagship (Gated DSA + MLA, 1M context) with strong agentic-coding numbers — ⚠ large, not local-runnable, but at the open-source coding frontier.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| SWE-bench Multilingual | 82.9 | lab (Tencent benchmark appendix, lab-reported) |
| SWE-bench Pro | 65.7 | lab (Tencent benchmark appendix, lab-reported) |
| Terminal-Bench 2.1 | 70.8 | lab (Tencent benchmark appendix, lab-reported) |
| DeepSWE | 64.3 | lab (Tencent benchmark appendix, lab-reported) |
| NL2Repo-Bench | 43.8 | lab (Tencent benchmark appendix, lab-reported) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| MCP-Atlas | 73.0 | lab (Tencent benchmark appendix, lab-reported) |
| Toolathlon-Verified | 56.2 | lab (Tencent benchmark appendix, lab-reported) |
| WideSearch | 81.9 | lab (Tencent benchmark appendix, lab-reported) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 90.9 | lab (Tencent benchmark appendix, lab-reported) |
| MATH | — | — |
| HLE (no tools, text-only) | 34.4 | lab |
| HLE (with tools, text-only) | 51.9 | lab |

## Efficiency

- **Active params:** 49B active per token (770B total; 256 routed experts, top-8 + 1 shared)
- **Context length:** 1,048,576 tokens (1M)
- **VRAM (fp16 rough):** ~98 GB for active weights alone; full model needs 8×80GB GPUs (README ships tp-size-8 recipes) — ⚠ not local-runnable
- **Architecture:** MoE with Gated DeepSeek Sparse Attention (DSA) + MLA, IndexCache cross-layer sparse index reuse, iHC residual stream; 78 layers; 1 native MTP layer (10B/0.7B active) for speculative decoding
- **Also available:** Hy4-preview-FP8 (quantized), finetuning pipeline, AngelSlim compression toolkit

## What makes it notable

Hy4 preview is Tencent's flagship open-weight MoE and claims to sit at the open-source frontier for long-horizon software engineering. Its coding/agentic numbers are strong for the open-weight space — Terminal-Bench 2.1 70.8, SWE-bench Multilingual 82.9, MCP-Atlas 73.0 — and it positions itself slightly ahead of GLM 5.3 and Kimi K3 in a blind internal expert eval (163 experts, 203 engineering tasks). ⚠ Large (>70B): 770B total / 49B active, requiring 8×80GB GPUs — not for local/agent-loop deployment on consumer/homelab hardware. ⚠ Benchmarks are lab-reported from Tencent's own image appendix (no SWE-bench Verified, Aider, or BFCL published); an independent leaderboard (BenchLM) verified SWE-bench Pro 65.7 and SWE-Multilingual 82.9 against that same appendix. Early/preview build: it over-reasons on complex tasks and over-verifies its own work.

## See also

- [[welcome]]
- Source: https://huggingface.co/tencent/Hy4-preview
- GitHub: https://github.com/Tencent-Hunyuan/Hy4-preview
