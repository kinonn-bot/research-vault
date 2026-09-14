---
title: "OrionLLM/OxCoder-9B"
org: OrionLLM
model_id: OrionLLM/OxCoder-9B
date: 2026-09-14
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - hybrid
  - long-context
  - swe-bench
downloads: 1688
likes: 52
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/OrionLLM/OxCoder-9B
params: 9B dense
context: 262144
architecture: hybrid
---

# OrionLLM/OxCoder-9B

**One-line:** 9B agentic coding model distilled from Fable-5.1 / GLM-5.3 agent traces (Claude Code, OpenCode, Codex) — claims SWE-bench Verified 73.5 with a 262K native context.

⚠ All scores are **lab-reported** (OrionLLM model card, OpenHands harness, GLM-5.3 as judge for HLE/MCP-Atlas). No third-party reproduction found yet — treat as claims.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | 73.5 | *lab-reported* |
| SWE-bench Pro | 49.1 | *lab-reported* |
| Terminal-Bench 2.1 (Terminus-2) | 49.6 | *lab-reported* |
| Terminal-Bench 2.1 (Claude Code) | 50.8 | *lab-reported* |
| NL2Repo | 36.2 | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| MCP-Atlas | 56.7 | *lab-reported* |
| ClawEval | 67.8 | *lab-reported* |
| BrowseComp | 57.4 | *lab-reported* |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 86.9 | *lab-reported* |
| HLE (no tools) | 21.2 | *lab-reported* |
| HLE (with tools) | 32.8 | *lab-reported* |
| MATH | — | — |
| AIME 2025 | — | — |

## Efficiency

- **Active params:** 9B total (Qwen3.5-9B base; hybrid linear+full attention as per config `layer_types`)
- **Context length:** 262,144 tokens (native)
- **VRAM (fp16 rough):** ~18 GB weights + KV cache for 262K context will exceed a single consumer GPU — quant + long-context optimizations needed for local agents

## What makes it notable

- Claims SWE-bench Verified 73.5 at 9B — above Ornith-1.5-9B (70.6), Ornith-1.0-9B (69.4), Qwen3.5-9B (53.2), Gemma-4-31B (52.0) on the card's reference table.
- Positioned explicitly for agent loops: trained on read-before-write patterns, LSP-diagnostic recovery, minimal-edit diffs; Terminal-Bench 2.1 49.6–50.8 is the strongest headline for CLI/terminal agent use.
- Built on Qwen3.5-9B (hybrid attention, VL-capable arch) — runs locally at ~18 GB fp16; distilled from frontier agentic trajectories (Fable-5.1, GLM-5.3).
- Fresh release (repo created 2026-09-07, benchmark table published 2026-09-14); no independent verification yet.

## See also

- [[welcome]]
- Source: https://huggingface.co/OrionLLM/OxCoder-9B