---
title: "inclusionAI LLaDA2.2-mini"
org: inclusionAI
model_id: inclusionAI/LLaDA2.2-mini
date: 2026-09-07
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
  - lightweight
downloads: 0
likes: 9
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/inclusionAI/LLaDA2.2-mini
params: "16B total / 1.4B active (MoE)"
context: 131072
architecture: moe diffusion (llada2_moe, Levenshtein editing, RoPE)
---

# inclusionAI LLaDA2.2-mini

**One-line:** The lightweight variant of the LLaDA2.2 agentic **diffusion** LLM — 16B total / 1.4B active, Levenshtein Editing (DELETE/INSERT control tokens), 128K context — with real agentic numbers (τ²-Bench 57.50, BFCL-v4 47.68) and a step-change long-context gain (LongBench v2 34.99). ⚠ custom `llada2_moe` architecture + diffusion runtime (trust_remote_code, SGLang for serving) — no vLLM/Ollama path; all benchmarks lab-reported. Surfaced via lab-org sweep (created 2026-09-05, ~3h outside the 36h cutoff; 0 downloads as of 09-07).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 28.14 (v6) | lab (card) |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |
| MultiPL-E | 65.26 | lab (card) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | 47.68 (v4) / 69.02 (v3) | lab (card) |
| τ-Bench | 57.50 (τ²-Bench) | lab (card) |
| ToolACE | — | not published |
| GAIA | — | not published |
| Claw-Eval | 57.16 | lab (card) |
| PinchBench | 62.33 | lab (card) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 44.41 | lab (card; slight dip vs LLaDA2.1-mini 48.36) |
| MATH | — | not published |
| AIME 2026 | 35.05 | lab (card) |
| OlympiadBench | 61.11 | lab (card) |
| LongBench v2 | 34.99 | lab (card; up from 12.13 on 2.1-mini) |

## Efficiency

- **Active params:** 1.4B active / 16B total (incl. embeddings ~; card: 16B excl. embedding) — 256 experts, 8 active per token, 20 layers
- **Context length:** 131,072 tokens (128K native)
- **VRAM (fp16 rough):** ~32 GB (16B × 2) + overhead — fit on a 40-48GB GPU at fp16; realistic local use needs 8-bit/4-bit or a 24GB card with quant
- **Runtime:** custom `llada2_moe` (LLaDA2MoeModelLM) — needs `trust_remote_code` + transformers ≥ 5.2.0; card recommends SGLang for 128K agentic serving; no vLLM/Ollama path yet; diffusion decode knobs (block_length=32, threshold, editing_threshold)

## What makes it notable

LLaDA2.2-mini is the local-runnable tier of inclusionAI's agentic diffusion LLaDA2.2 line (flash sibling is ~100B MoE). The interesting signals: Levenshtein Editing (token DELETE/INSERT during diffusion decode) plus L-EBPO agentic RL lift BFCL-v4 from 25.05 (LLaDA2.0-mini) to 47.68, and LongBench v2 jumps 12.13 → 34.99 with the 128K Block Routing — the strongest evidence so far that the post-training, not the base architecture, is what makes the agentic numbers. Caveats: every number is lab-reported with no independent replication, no SWE-bench/Aider published (agent-loop repo-editing suitability unproven), the custom diffusion runtime works only in transformers/SGLang (no llama.cpp — GGUF builds are the fallback, none exist yet), and 0 downloads so far means zero community validation. For a local agent runner it's a watch-listed experiment, not a daily driver — but it is the only genuinely new lab release with agentic benchmarks in the last ~40h.

## See also

- [[welcome]]
- Source: https://huggingface.co/inclusionAI/LLaDA2.2-mini
- Sibling: https://huggingface.co/inclusionAI/LLaDA2.2-flash
- GitHub: https://github.com/inclusionAI/LLaDA2.X