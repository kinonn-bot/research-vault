---
title: "Apodex-1.1-mini (Apodex AI)"
org: apodex
model_id: apodex/Apodex-1.1-mini
date: 2026-08-31
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - tool-use
  - reasoning
downloads: 2185
likes: 110
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/apodex/Apodex-1.1-mini
params: "35B total / ~3B active MoE (base: Qwen3.5-35B-A3B)"
context: 262144 (256K)
architecture: moe
---

# Apodex-1.1-mini (Apodex AI)

**One-line:** Agent-specialized post-train of Qwen3.5-35B-A3B for long-horizon research/execution tasks (AgentOS multi-subagent orchestration, native function calling) — but its "benchmarks" are measured through a multi-agent Agent Team harness, and it publishes **no standard coding evals** (SWE-bench / Aider / BFCL), so single-model agent-loop suitability is unproven.

> ⚠ **Benchmark provenance is lab-reported AND harness-level.** The headline numbers (APEX-Agents 27.7, FrontierFinance 50.2, GDPVal 51.7 for `Apodex-1.1-mini w/ Agent Team`) are measured on a multi-subagent Agent Team orchestration stack, not the raw single model; ReAct deployments score lower. No SWE-bench Verified, no Aider polyglot, no BFCL, no LiveCodeBench are published for the standalone checkpoint. These are **not** drop-in comparable to the SWE-bench/BFCL figures on other models — treat as directional only.

**Release event:** Apodex-1.1 family (mini 35B-A3B + full) publicized ~2026-08-17 (repo createdAt) / 08-24 blog + arXiv 2608.23283; model update 08-26. Apache-2.0. Built on Qwen3.5-35B-A3B, Qwen3.5 chat template (`<think>...`, `<tool_call>`), agentic RL for tool use, long-horizon task decomposition, and a built-in "Statement Review" verification step.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| SWE-bench Multilingual | — | — |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| APEX-Agents | 27.7 (mini, Agent Team) | lab (arXiv, harness) |
| FrontierFinance | 50.2 (mini, Agent Team) | lab (arXiv, harness) |
| GDPVal | 51.7 (mini, Agent Team) | lab (arXiv, harness) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |
| Humanity's Last Exam | 56.1 (Apodex-1.1 full) | lab |

## Efficiency

- **Active params:** ~3B active (35B total MoE, base Qwen3.5-35B-A3B).
- **Context length:** 262,144 (256K).
- **VRAM (fp16 rough):** ~70 GB fp16 (35B total) → needs quantization (Q4 ≈ 20 GB) or multiple GPUs; ~3B active means the decode compute is cheap once the weights are loaded.

## What makes it notable

Apodex-1.1-mini is explicitly engineered as an *agent* rather than a chat assistant — it decomposes tasks, coordinates parallel subagents, and produces verifiable deliverables rather than single-turn answers. The 256K context and ~3B active compute make it a plausible local long-horizon-agent runner. The catch is exactly what the skill's "no-standard-benchmarks = exclude" rule flags: every published number is measured through a harness (Agent Team vs ReAct) with no standalone SWE-bench/BFCL result, so you can't tell how the raw model behaves in your own agent loop. Worth tracking, but treat it as unverified for coding-agent use until a standalone eval exists.

## See also

- [[welcome]]
- Source: https://huggingface.co/apodex/Apodex-1.1-mini
- arXiv: https://arxiv.org/abs/2608.23283
