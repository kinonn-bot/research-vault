---
title: "Z.ai GLM-5.2"
org: zai-org
model_id: zai-org/GLM-5.2
date: 2026-09-01
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - mla
  - indexshare
  - long-context
downloads: 1452214
likes: 5065
license: mit
pipeline: text-generation
source: https://huggingface.co/zai-org/GLM-5.2
params: ~25B active (~480B total, est)
context: 1048576
architecture: moe
---

# Z.ai GLM-5.2

**One-line:** Flagship long-horizon MoE with solid native 1M-token context via IndexShare sparse attention — MIT, no regional limits. ⚠ large (~480B total, ~25B active est).

> Surfaced via Trending window 2026-09-01 (lastModified bump = benchmark card update). Superseded by GLM-5.3-BF16 but was never previously tracked in this vault. Lab-reported benchmarks only — no independent source yet.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| SWE-bench Pro | 62.1 | lab (OpenHands) |
| SWE-bench Multilingual | — | — |
| Terminal Bench 2.1 (Terminus-2) | 81.0 | lab |
| Terminal Bench 2.1 (best harness) | 82.7 | lab |
| DeepSWE | 46.2 | lab (mini-swe-agent) |
| FrontierSWE (Dominance) | 74.4 | Proximal |
| ProgramBench | 63.7 | lab |
| SWE-Marathon | 13.0 | lab |

Note: lists SWE-bench **Pro** (62.1), not the classic SWE-bench Verified. Uses the modern agentic suites (Terminal-Bench 2.1, DeepSWE, FrontierSWE) instead.

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| MCP-Atlas (Public Set) | 76.8 | lab |
| Tool-Decathlon | 48.2 | lab |

MCP-Atlas 76.8 and Tool-Decathlon 48.2 are the tool-use signals; no classic BFCL/τ-Bench/ToolACE/GAIA published.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 91.2 | lab |
| MATH | — | — |
| HLE | 40.5 | lab |
| HLE (w/ Tools) | 54.7 | lab |
| AIME 2026 | 99.2 | lab |
| HMMT Feb 2026 | 92.5 | lab |

## Efficiency

- **Active params:** ~25B active (estimated from config; total ~480B with 256 routed experts, 8/tok, hidden 6144 × 78 layers)
- **Context length:** 1,048,576 (native 1M)
- **VRAM (fp16 rough):** ~50–60 GB for active weights (needs heavy quantization for single-GPU local use) ⚠ **large — not practical on consumer local GPU in fp16**

## What makes it notable

GLM-5.2 is the long-horizon flagship that first delivered "solid" 1M-token context on an open model, using IndexShare — reusing one indexer across every four sparse-attention layers to cut per-token FLOPs ~2.9× at 1M context. For the agentic/coding user it's a mix: SWE-bench Pro 62.1 and Terminal-Bench 2.1 at 81 are strong and comfortably beat Qwen3.7-Max and MiniMax M3 on the card's own table, but the model is huge (~480B total, ~25B active) and lab-reported numbers aren't yet independently confirmed. MIT with no regional limits makes it the most permissive big-lab flagship this cycle; practical local deployment needs MoE-aware quantization (KTransformers/Unsloth paths are published). Successor GLM-5.3 is already tracked here.

## See also

- [[welcome]]
- Source: https://huggingface.co/zai-org/GLM-5.2