---
title: "Qwen Qwen3.8-2.4T-A95B"
org: Qwen
model_id: Qwen/Qwen3.8-2.4T-A95B
date: 2026-08-13
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid
  - mla
  - large
downloads: 978
likes: 394
license: qwen3.8-max
pipeline: text-generation
source: https://huggingface.co/Qwen/Qwen3.8-2.4T-A95B
params: 95B active (2.4T total)
context: 262144
architecture: moe
---

# Qwen3.8-2.4T-A95B (Qwen3.8-Max)

**One-line:** The Qwen3.8-Max weight drop — first open release of a Qwen-Max-class model; 2.4T-param MoE (95B active) built for long-horizon coding and agentic tasks. ⚠ large — datacenter-class, not locally runnable.

> ⚠ This resolves the "weights next week" watch from the 2026-08-06 run: Qwen announced Qwen3.8-Max (API-only) Aug 3, and the open weights landed on HF 2026-08-08 (`createdAt` 08-08 01:50 UTC). The Qwen blog still said "next week" at announcement time — this repo is the actual drop. Confirmed by Reddit r/LocalLLaMA "Qwen3.8-2.4T-A95B Released" thread.
> ⚠ All benchmark numbers below are **lab-reported** (Qwen's own card, HTML table). No independent re-run exists yet — the model is 5 days old. Treat as unverified.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (uses SWE-bench Pro / QwenSWEBench instead) |
| SWE-bench Pro | *67.7* | *lab-reported* |
| Terminal Bench 2.1 | *86.6* | *lab-reported* |
| DeepSWE 1.1 | *56.6* | *lab-reported* |
| FrontierSWE | *73.5* | *lab-reported* |
| NL2Repo-Bench | *55.9* | *lab-reported* |
| PaperBench | *93.0* | *lab-reported* |
| AndroidBench | *75.1* | *lab-reported* |
| QwenSWEBench | *80.7* | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published (uses Toolathlon / MCP-style instead) |
| Toolathlon Verified (Pass@1) | *72.5* | *lab-reported* |
| CoWorkBench | *74.8* | *lab-reported* |
| SkillsBench | *70.2* | *lab-reported* |
| Agents' Last Exam | *27.0 / 52.4* | *lab-reported* |
| Automation-Bench (Pass@1) | *27.3* | *lab-reported* |
| WideSearch | *81.9* | *lab-reported* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | *92.6* | *lab-reported* |
| HLE | *43.6* | *lab-reported* |
| IFBench | *82.8* | *lab-reported* |
| MRCR v2 256K (8-needle) | *92.9* | *lab-reported* |

## Efficiency

- **Active params:** 95B (2.4T total, 512 experts, 10 routed + 1 shared)
- **Context length:** 262,144 native, extensible to ~1,010,000 tokens
- **VRAM (fp16 rough):** ~4.8 TB — ⚠ datacenter-only. The FP8 sibling (`Qwen/Qwen3.8-2.4T-A95B-FP8`, 3.8k downloads) still needs ~2.4 TB. Not runnable on consumer hardware; the locally-relevant sibling Qwen3.8-27B is announced but its official weights are NOT on HF yet (only community quants exist).

## What makes it notable

Architecturally it's a hybrid MoE: 92 layers of `Gated DeltaNet → MoE` blocks with periodic `Gated Attention → MoE` (23×(3×(DeltaNet→MoE)→1×(Attn→MoE))), 512 experts with 11 active, plus multi-token prediction — a linear-attention/attention hybrid in the Qwen3.5 lineage at 2.4T scale. On Qwen's own numbers it beats Qwen3.7-Max on nearly every coding/agentic row (Terminal Bench 2.1 86.6 vs 74.5, DeepSWE 56.6 vs 21.6, FrontierSWE 73.5 vs 40.7, Toolathlon 72.5 vs 49.7) and roughly matches or beats Opus 4.8 on most agentic rows. Position vs current open-weight leaders (DeepSeek-V4-Pro, GLM-5.2, Kimi-K3): Qwen claims top open-weight agentic performance, though that claim is entirely lab-reported so far. For this user's local/agent workflow this is a **watch, not a deploy** — the 27B sibling is the one to watch for local use. License is the custom Qwen3.8-Max license: permissive for personal/local/internal use; requires attribution display above 100M MAU / $20M monthly revenue, and a separate commercial license for large MaaS/AI-assistant businesses above $50M/12mo — fine for individual use.

## See also

- [[welcome]]
- Source: https://huggingface.co/Qwen/Qwen3.8-2.4T-A95B
- Qwen blog: https://qwen.ai/blog?id=qwen3.8
