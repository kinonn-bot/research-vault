---
title: "Ornith 1.5 35B A3B"
org: ornith-ai
model_id: ornith-ai/Ornith-1.5-35B-A3B
date: 2026-08-29
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - instruct
  - reasoning
  - self-improvement
downloads: 106562
likes: 495
license: mit
pipeline: text-generation
source: https://huggingface.co/ornith-ai/Ornith-1.5-35B-A3B
params: 3B active (35B total)
context: 262144
architecture: moe
---

# Ornith 1.5 35B A3B

**One-line:** Self-improving 3B-active MoE that beats every same-size peer and many larger dense models on agentic coding (SWE-bench Verified 79, MCP-Atlas 70.2) — the strongest genuinely local-runnable coding agent in this sweep.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | 79 | lab (OpenHands harness, lab-reported) |
| SWE-bench Multilingual | 71.4 | lab (OpenHands harness, lab-reported) |
| SWE-bench Pro | 59.6 | lab (OpenHands harness, lab-reported) |
| Terminal-Bench 2.1 | 67.8 | lab (Terminus-2 framework, lab-reported) |
| DeepSWE | 22 | lab (Claude Code harness, lab-reported) |
| NL2Repo | 46.2 | lab (lab-reported) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| MCP-Atlas | 70.2 | lab (lab-reported) |
| Toolathlon-Verified | 48.7 | lab (official eval service, lab-reported) |
| ClawEval | 72.5 | lab (lab-reported) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | 89.2 | lab |
| MATH | — | — |
| AIME 2025 | — | — |
| HLE (no tools) | 25.6 | lab |
| HLE (with tools) | 33.4 | lab |

## Efficiency

- **Active params:** ~3B active per token (35B total; 256 experts, top-8 routed + shared)
- **Context length:** 262,144 tokens (256k); YaRN ×4 → ~1M
- **VRAM (fp16 rough):** ~70 GB in bf16 for full 256k context — README recommends 2×80GB GPUs; GGUF build available for llama.cpp / Ollama
- **Architecture:** MoE on Qwen3.5-MoE base with hybrid linear-attention layers (global full attention every 4 layers), bf16
- **Runtime:** Requires Transformers ≥ 5.8.1, vLLM ≥ 0.19.1, SGLang ≥ 0.5.9; emits `<think>` reasoning + `<tool_call>` blocks for OpenAI-style tool_calls

## What makes it notable

Ornith-1.5-35B-A3B is the strongest coding/agentic result at the 3B-active MoE scale in this sweep. It significantly outruns its direct peer Qwen3.6-35B-A3B (SWE-bench Verified 79 vs 73.4; Terminal-Bench 2.1 67.8 vs 52.5) and beats dense models like Gemma 4-31B and Muse Glimmer-30B on agentic coding by wide margins. The claim to fame is end-to-end self-improvement: the lab joint-optimizes task generation, harness construction, and solution rollouts via RL rather than fixed human-curated tasks — an extension of the Ornith-1.0 self-scaffolding loop. Tool-calling is first-class (MCP-Atlas 70.2, Toolathlon 48.7) and it ships OpenAI-compatible serving recipes for vLLM/SGLang with a tool-call parser. ⚠ All benchmark numbers are lab-reported (5-run averages) — no independent third-party confirmation found yet. Note its base (Qwen3.5-MoE) carries a vision config, but published evals are text/agentic-only.

## See also

- [[welcome]]
- Source: https://huggingface.co/ornith-ai/Ornith-1.5-35B-A3B
- Blog: https://deep-reinforce.com/ornith.html
