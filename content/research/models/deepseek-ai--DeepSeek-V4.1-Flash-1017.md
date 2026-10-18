---
title: "DeepSeek-V4.1-Flash-1017"
org: deepseek-ai
model_id: deepseek-ai/DeepSeek-V4.1-Flash-1017
date: 2026-10-19
tags:
  - huggingface
  - image-text-to-text
  - coding
  - agentic
  - moe
  - deepseek-v4-1
  - million-token-context
  - vl
  - reasoning
  - instruct
  - fp8
downloads: 10233
likes: 1295
license: mit
pipeline: image-text-to-text
source: https://huggingface.co/deepseek-ai/DeepSeek-V4.1-Flash-1017
params: "763B on disk (FP8); 384 routed + 1 shared expert, 6 active; 3-layer MTP + DSpark drafter"
context: "1,048,576 (1M tokens)"
architecture: "moe VL (deepseek_v41 / DeepseekV41ForCausalLM; MLA, Engram conditional memory, sparse attention, vision encoder 32L)"
---

# DeepSeek-V4.1-Flash-1017

**One-line:** Dated GA checkpoint of DeepSeek-V4.1-Flash (released 2026-10-17) that moves the whole agentic suite up sharply over the September build — Terminal-Bench 4.0 **42.3** (was 31.2), DeepSWE v1.1 77.0 (was 74.2), Apex Bench v1.1 72.1 (was 64.6) — at 1M context and MIT, while cutting task execution time and output length. ⚠ large: 763B params, FP8 ~763 GB on disk — multi-GPU serving only, no local path.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (lab uses DeepSWE / Terminal-Bench instead) |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench 4.0 | 42.3 | lab (Claude Code harness) — vs 31.2 for V4.1-Flash, GLM-5.3 37.9, GPT-5.6 Sol 39.9, Opus 5 51.8 |
| DeepSWE v1.1 | 77.0 | lab (Mini-SWE-V2 harness) — vs 74.2 for V4.1-Flash, GPT-5.6 Sol 73.0, Opus 5 74.0 |
| ProgramBench | 29.1 | lab — vs 20.3 for V4.1-Flash, GPT-5.6 Sol 23.0 |
| NL2Repo-Bench | 68.2 | lab — vs 65.4 for V4.1-Flash, Opus 5 75.3 |
| Automation-Bench v1.0.6 | 60.5 | lab — vs 54.8 for V4.1-Flash |
| Apex Bench v1.1 | 72.1 | lab — vs 64.6 for V4.1-Flash |
| Chartography (w/tools) | 83.0 | lab — vs 78.9 for V4.1-Flash |

*All numbers lab-reported (card benchmark table, 2026-10-17). Harness disclosure: Claude Code for Terminal-Bench 4.0, Mini-SWE-V2 for DeepSWE v1.1. DeepSWE is a DeepSeek-owned benchmark family — prefer independent sources where they exist.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Agents' Last Exam | 35.4 | lab — vs 31.8 for V4.1-Flash, GLM-5.3 28.5 |
| BabyVision (w/tools) | 92.5 | lab — vs 89.6 for V4.1-Flash |
| ZeroBench-main (w/tools) | 51.0 | lab — vs 49.0 for V4.1-Flash, GPT-5.6 Sol 53.0 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| HLE (w/o tools) | 42.6 (44.0 text-only subset) | lab — vs 36.8 for V4.1-Flash, Opus 5 56.3 |
| MMLU / MMLU-Pro | — | not published on this card |
| GPQA Diamond | — | not published on this card |
| MATH | — | not published on this card |

## Efficiency

- **Active params:** not restated on the 1017 card; the V4.1-Flash family card gives 8B active prefill / 16B decode (384 routed + 1 shared expert, 6 activated) out of a 552B text backbone — the 763B on-disk figure additionally counts the Engram conditional memory, vision encoder, MTP layers and DSpark drafter.
- **Context length:** 1,048,576 tokens (yarn rope scaling, factor 16, original 64K)
- **VRAM (fp16 rough):** ships natively FP8 (~763 GB weights) — ≈8×80GB or 4×141GB-class GPUs minimum; single-GPU deployment is not possible
- **Prompt encoding:** no Jinja chat template — ships `encoding/encoding.py` reference implementation plus the `deepseek-recipe` Rust toolkit (tool calls, thinking mode, numeric reasoning effort, interleaved images)

## What makes it notable

This is the update that makes V4.1-Flash competitive on the harness-style agentic suites rather than just the ones DeepSeek authors itself: Terminal-Bench 4.0 jumps 11.1 points to 42.3 (above GLM-5.3 and GPT-5.6 Sol in its own table, still well below Opus 5) and it now leads the comparison set on DeepSWE v1.1 (77.0), Automation-Bench (60.5) and Apex Bench (72.1). BenchLM's independent category compilation ranks it Coding #18 of 150 (60.8, 89th percentile) and Agentic #24 of 128 (62.1, 82nd percentile) with 33 verified source-linked rows — i.e. mid-frontier, not top. For local use the verdict is unchanged from the September build: 763 GB of FP8 weights means data-center serving only, so the practical entry point is an OpenRouter/hosted endpoint; the interesting claim for this user's agent loops is the stated reduction in execution time and output length at the same capability, which directly cuts token burn.

## See also

- [[deepseek-ai--DeepSeek-V4.1-Flash]]
- [[welcome]]
- Source: https://huggingface.co/deepseek-ai/DeepSeek-V4.1-Flash-1017
- BenchLM profile: https://benchlm.ai/models/deepseek-v4-1-flash-1017
- OpenRouter: https://openrouter.ai/compare/deepseek/deepseek-v4.1-flash-1017
