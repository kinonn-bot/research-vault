---
title: "Reflection Beam 1.0 (501B-A23B)"
org: reflection
model_id: reflection/Beam-1.0-501B-A23B
date: 2026-10-17
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - reasoning
  - tool-calling
  - long-context
  - us-lab
downloads: 440
likes: 90
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/reflection/Beam-1.0-501B-A23B
params: "23.4B active (501.3B total; 256 experts, top-8 routed, 52 layers)"
context: "1,048,576 (1M tokens)"
architecture: "moe (3 dense + 49 MoE layers; gated GQA + sliding-window 512 hybrid attention; custom model_type beam)"
---

# Reflection Beam 1.0 (501B-A23B)

**One-line:** Reflection's first model — a 501B-param / 23.4B-active MoE built for coding, reasoning and agentic work, Apache-2.0 with BF16/FP8/NVFP4 checkpoints; weights went public 2026-10-16 (repo staged 2026-10-07), lab-reported SWE-bench Verified 81.6 (BF16) and LiveCodeBench 88.3. ⚠ 501B: ≈1,003 GB BF16 across 188 shards (verified downloadable) — needs 8×H200/B200-class serving; it decodes at 23B speed but all 256 experts must stay resident.

> ⚠ All benchmark numbers below are **lab-reported** (model card + repo `.eval_results` YAML + HF launch blog; evals at temp 0.7, top_p 0.99). No independent evaluation yet as of 2026-10-17 — third-party coverage (TechCrunch via aggregators) explicitly flags the claims as unverified. BF16 column shown; FP8/NVFP4 within ~1–2 pts (FP8 is slightly ahead on several rows). The launch blog's comparison table quotes slightly different values (SWE-V 80.9, SWE-Pro v2-Hard 77.2) — the card + `.eval_results` (81.6 / 76.5) are canonical.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 88.3 | lab — card + .eval_results (BF16) |
| Aider polyglot | — | not published |
| SWE-bench Verified | 81.6 | lab — card + .eval_results; vs Inkling-Small 77.6, Nemotron 3 Ultra 70.7 |
| SWE-bench Multilingual | 78.3 | lab — card |
| SWE-bench Pro v1 | 66.1 | lab — card; vs Qwen3.8-Max 67.7, Inkling 54.3 |
| SWE-bench Pro v2-Hard | 76.5 | lab — card; trails Kimi K3 88.2, GLM-5.3 84.3 |
| DeepSWE v1.1 | 43.3 | lab — card + .eval_results |
| Terminal Bench 2.1 | 80.1 | lab — card + .eval_results |
| SWE Atlas Codebase QnA | 31.8 | lab — card |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | τ³-Banking 36.1 | lab — card |
| ToolACE | — | not published |
| GAIA | — | not published |
| MCP-Atlas | 80.8 | lab — card |
| BrowseComp | 76.8 | lab — with context management |
| DeepSearchQA | 80.5 | lab — with context management |
| AutomationBench | 39.3 | lab — public split only |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 90.6 | lab — card + .eval_results |
| MATH | — | not published |
| AIME 2026 | 97.7 | lab — card + .eval_results |
| HLE | 36.0 (no tools) / 51.1 (with tools) | lab — card + .eval_results |
| SciCode | 49.2 | lab — card |
| CriPT AA | 16.3 | lab — card |
| AA-LCR / LongBench v2 / IFBench | 78.2 / 67.5 / 79.6 | lab — card |
| AA Omniscience (index) | 10.8 | lab — public split |

## Efficiency

- **Active params:** 23.4B active / 501.3B total (256 experts per MoE layer, 8 routed via DeepSeek-V3-style group-limited routing — 8 groups × 32, top-4 groups; no shared expert; routed scaling 2.5; 52 layers = 3 dense + 49 MoE; hidden 5120; vocab 152k)
- **Context length:** 1,048,576 (1M); hybrid attention — 43 sliding-window (512-token) + 9 global layers; KV cache ≈36.08 GiB per sequence at 1M (vs ≈208 GiB if all layers were global) — the long-context serving edge
- **VRAM:** ⚠ **BF16 ≈1,003 GB** (188 safetensors shards, ~5.4 GB each; tree + range-GET 206 verified). **FP8 sibling ≈0.5 TB** (Hopper/Ampere-friendly); **NVFP4 sibling** (~4-bit, some BF16 kept) for Blackwell — the realistic local path. Compute cost runs at 23B speed; memory cost is full frontier-scale.
- **Runtime:** custom architecture — `model_type: beam`, `BeamForCausalLM`; day-0 support in transformers (native implementation per HF blog), SGLang, vLLM; ships its own open-source Rust harness ("Mirror"); DFlash2 speculative drafter sibling (`reflection/Beam-1.0-501B-A23B-DFlash2`); full-parameter RL with Miles. Chat template = modified Harmony; reasoning effort low→max; `preserve_thinking` keeps reasoning across turns; dedicated tool-calling grammar. Knowledge cutoff 2026-06-30. Text-only.

## What makes it notable

Reflection's debut (the $2B-funded US lab positioned as an open-frontier challenger) and one of the largest open-weight releases from a US lab — 501B, Apache-2.0, no gates of any kind. It targets exactly the agentic-coding use case: repo-level work, terminal/CLI operation, MCP tool use and browsing, with a "~3× fewer reasoning tokens" efficiency claim. On paper it lands near the open-weight frontier: SWE-bench Verified 81.6 (ahead of Inkling-Small 77.6 and Nemotron 3 Ultra 70.7; behind only the Chinese frontier on SWE-bench Pro v2-Hard — Kimi K3 88.2, GLM-5.3 84.3 vs 76.5), LiveCodeBench 88.3, Terminal Bench 2.1 80.1 (best in the comparison set), MCP-Atlas 80.8, HLE-with-tools 51.1, GPQA-D 90.6. Two caveats: (1) every number is lab-reported and independently unverified at note time; (2) 501B total params means frontier-class memory requirements regardless of the cheap decode — plan on NVFP4 on Blackwell, multi-GPU FP8, or the hosted API/harness until community quants mature. Watch for: a technical report ("coming"), independent (AA / LMArena) listings, and the community quant wave.

## See also

- [[welcome]]
- Source: https://huggingface.co/reflection/Beam-1.0-501B-A23B
- Launch blog: https://reflection.ai/blog/introducing-beam · HF blog: https://huggingface.co/blog/reflection-beam
- Siblings: [FP8](https://huggingface.co/reflection/Beam-1.0-501B-A23B-FP8) · [NVFP4](https://huggingface.co/reflection/Beam-1.0-501B-A23B-NVFP4) · [DFlash2 drafter](https://huggingface.co/reflection/Beam-1.0-501B-A23B-DFlash2)
