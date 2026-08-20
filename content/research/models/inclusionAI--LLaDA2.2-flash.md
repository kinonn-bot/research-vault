---
title: "inclusionAI LLaDA2.2-flash"
org: inclusionAI
model_id: inclusionAI/LLaDA2.2-flash
date: 2026-08-20
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - diffusion
  - dllm
  - long-context
  - tool-use
downloads: 1203
likes: 82
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/inclusionAI/LLaDA2.2-flash
params: "~100B total (MoE, non-embedding)"
context: "131072 (128K)"
architecture: moe diffusion (MoE diffusion LM w/ Levenshtein Editing, RoPE)
---

# inclusionAI LLaDA2.2-flash

**One-line:** Agent-oriented MoE **diffusion** language model making the LLaDA2 series' first step into agentic use via Levenshtein Editing (DELETE/INSERT control tokens) — SWE-bench Verified 49.28, BFCL-V4 60.78, τ²-Bench 80.33, 128K context. ⚠ large (~100B total MoE); ⚠ diffusion runtime (custom_code, SGLang support pending). LLaDA2.2 announced July 2026; flash variant surfaced via the trending/lastModified window (08-20).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 49.28 | lab-reported (card; Claude Code scaffold, avg of 5 runs) |
| SWE-bench Pro | 30.10 | lab-reported (card; Claude Code scaffold) |
| SWE-bench Multilingual | 25.00 | lab-reported (card; Claude Code scaffold) |

*SWE-bench series evaluated with the Claude Code scaffold — lab numbers, italicized provenance. No standard generative coding table (HumanEval/MBPP/LiveCodeBench) published.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | 60.78 (BFCL-V4) | lab-reported (card) |
| τ-Bench | 80.33 (τ²-Bench) | lab-reported (card) |
| ToolACE | — | not published |
| GAIA | — | not published |
| MCP-Atlas | 46.21 | lab-reported (card) |

*Also Claw-Eval 64.22, PinchBench 81.66 — all lab-reported from the model card, no independent confirmation yet.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** ~100B total MoE (card lists "total parameters (non-embedding): 100B"); active count not stated
- **Context length:** 131,072 tokens (128K native)
- **VRAM (fp16 rough):** ~200 GB for full weights (100B × 2 bytes) — ⚠ large, needs quant + large GPU cluster; not a laptop model
- **Runtime:** needs `trust_remote_code` (custom `llada2_moe` architecture, diffusion decode with `block_length`/`threshold`/`editing_threshold` knobs); SGLang serving support listed as "coming soon" — no ready vLLM/Ollama path yet

## What makes it notable

LLaDA2.2-flash is a genuinely novel direction for agentic coding: diffusion language modeling rather than the standard autoregressive next-token loop, extended with Levenshtein Editing so the model can DELETE and INSERT tokens during decoding for long-context tool use, multi-turn interaction, and error correction. It carries real agentic/coding numbers (SWE-bench Verified 49.28, τ²-Bench 80.33, BFCL-V4 60.78, MCP-Atlas 46.21) that land in the mid-tier of open agentic models, and it reports ~1.7× higher throughput than Ling-2.6-flash on the same agentic benchmarks (519 vs 303 TPS on SWE-bench Verified). Trade-offs: every number is lab-reported with no independent replication yet, the model is large (~100B MoE) with no production serving backend announced, the architecture is custom (not loadable by stock transformers without remote code), and deployment is unproven for real agent loops. For the local runner this is one to watch for the coming diffusion-agent serving story (SGLang) rather than something to drop into an agent today.

## See also

- [[welcome]]
- Source: https://huggingface.co/inclusionAI/LLaDA2.2-flash
- GitHub: https://github.com/inclusionAI/LLaDA2.X
