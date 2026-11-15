---
title: "Meituan LongCat-2.5"
org: meituan-longcat
model_id: meituan-longcat/LongCat-2.5
date: 2026-11-16
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - multimodal
downloads: 1573
likes: 269
license: mit
pipeline: image-text-to-text
source: https://huggingface.co/meituan-longcat/LongCat-2.5
params: 48B active (1.6T total MoE)
context: 524288
architecture: moe
---

# Meituan LongCat-2.5

**One-line:** Meituan's 1.6T/48B-active native-multimodal MoE for long-horizon agentic coding — Terminal-Bench 2.1 88.4, DeepSWE 64.6 *(all lab-reported)*. ⚠ large — rack/NPU-class, not locally runnable in fp16.

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
| Terminal-Bench v2.1 | *88.4* | *lab-reported (model card; BenchLM ledger mirrors as reported-only)* |
| Terminal-Bench v4.0 | *38.5* | *lab-reported* |
| DeepSWE v1.1 | *64.6* | *lab-reported* |
| Program Bench (Almost Resolved) | *25.5* | *lab-reported* |
| PaperBench | *82.1* | *lab-reported* |
| SWE Atlas — Codebase QnA / Refactoring / Test Writing | *58.3 / 55.2 / 47.8* | *lab-reported* |
| NL2Repo | *60.5* | *lab-reported* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| BrowseComp | *91.9* | *lab-reported* |
| HLE (w/ tools) | *63.1* | *lab-reported* |
| MCP Atlas | *83.1* | *lab-reported* |
| AutomationBench v1.0.6 | *51.8* | *lab-reported* |
| JobBench (Main 65) | *65.4* | *lab-reported* |
| SkillsBench v1.1 | *63.3* | *lab-reported* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |
| FrontierScience | *77.0* | *lab-reported* |

## Efficiency

- **Active params:** 48B (1.6T total MoE, 768 routed experts, top-12)
- **Context length:** 524288 tokens per `config.json` (`max_position_embeddings`); eval harnesses run up to 1M, BenchLM lists 1M documented
- **VRAM (fp16 rough):** ~3.2 TB for full weights — NPU/rack-only in practice; card documents native W4A4 expert quantization + deployment via SGLang-FluentLLM on domestic accelerators
- **Architecture note:** custom `pro_v` / `LongcatCausalLM` with MLA attention — needs the repo's custom model code, stock transformers will not load it

## What makes it notable

Massive generational jump over LongCat-2.0 (DeepSWE 9.7 → 64.6, TB-2.1 70.8 → 88.4) puts it roughly at GPT-5.5/GLM-5.3/Kimi-K3 level on terminal-agent tasks, though it still trails DeepSeek-V4.1-Flash (DeepSWE 74.2) and Claude-Opus-5 (TB-4.0 53.9). Positioned as an agentic-coding + visual-understanding model (3DCodeBench Text→3D 55.4, Vision2Web 78.6), so it is the rare VL entry that belongs on a coding/agent tracker. Practical caveat for local runners: 1.6T fp16 weights plus custom arch plus NPU-oriented serving means this is a reference/API model, not something to pull into Ollama.

## See also

- [[welcome]]
- Source: https://huggingface.co/meituan-longcat/LongCat-2.5
- Tech blog: https://longcat.ai/blog/longcat-2.5/
- Independent ledger (reported-only, not verified): https://benchlm.ai/models/longcat-2-5
