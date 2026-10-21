---
title: "InternScience Sage-A1.5 (35B-A3B)"
org: InternScience
model_id: InternScience/Sage-A1.5
date: 2026-10-22
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - vl
  - vision
  - tool-use
  - reasoning
  - long-context
  - science
  - shanghai-ai-lab
downloads: 58
likes: 141
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/InternScience/Sage-A1.5
params: "≈3B active (35B total; 256 experts, top-8 routed + shared expert; 40 layers)"
context: "262,144 native (512k with YaRN factor 2.0)"
architecture: "VL moe — Qwen3.6-35B-A3B base (Qwen3_5MoeForConditionalGeneration); 3 linear-attention layers per full-attention layer; mRoPE; 1 MTP head; image + video input"
---

# InternScience Sage-A1.5 (35B-A3B)

**One-line:** Shanghai AI Laboratory's (InternScience) 35B MoE agentic VL model — builds on Agents-A1 with explicit agentic orchestration (parallel `spawn_subagent` fan-out), an in-chain-of-thought verification mode, and open scientific discovery; lab-reported GAIA 95.1, SWE-bench Pro 61.2, SWE-bench Multilingual 72.7, PinchBench 90.0 at ~3B active params. Weights were uploaded quietly on 2026-10-15; the public launch (card + benchmark chart + arXiv report + FP8/GGUF siblings) landed 2026-10-21.

> ⚠ All numbers below are **lab-reported** (model card, arXiv 2610.28578). SWE-bench series uses mini-swe-agent at temp 1.0 / top-p 0.95, 200K context, offline (no internet) — the same harness family reflection and the DeepSeek cards use, so the numbers are roughly comparable across those cards. No independent evaluation yet as of 2026-10-22. Comparison cells are transcribed from competitors' own reports; some are re-run by the Sage team under its own protocol, so cross-column comparisons are indicative, not controlled.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (SWE-bench Pro / Multilingual instead) |
| SWE-bench Pro | 61.2 | lab — card (vs Agents-A1 43.6, Ornith-1.5 59.6, Kimi-K3 63.3, GLM-5.3 64.6) |
| SWE-bench Multilingual | 72.7 | lab — card (vs Agents-A1 58.7, Ornith-1.5 71.4) |
| SciCode | 44.3 | lab — card |
| MLE-Lite | 65.2 | lab — card (vs Agents-A1 43.9) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | 95.1 | lab — card (vs Kimi-K3 92.2, GLM-5.3 92.2, Agents-A1 96.0) |
| BrowseComp | 81.7 (82.8 with Agentic Orchestration) | lab — card |
| Agents' Last Exam (ALE-CLI) | 19.1 | lab — card |
| VitaBench | 45.4 | lab — card |
| PinchBench | 90.0 | lab — card (vs Kimi-K3 88.2, Ornith-1.5 88.6) |
| DeepResearch-Bench2 | 43.7 (47.5 with Agentic Orchestration) | lab — card |
| Tool-use support | native function calling; `spawn_subagent` parallel sub-agent schema; opt-in verification mode via chat-template flag | card (no BFCL/τ number published) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH / AIME | — | not published |
| HLE (with tools) | 55.1 | lab — card |
| IFBench | 81.6 | lab — card (vs Kimi-K3 72.1) |
| AA-LCR v1.1 | 81.0 | lab — card |
| XBench-DS-2510 | 92.0 | lab — card |
| FrontierScience-Olympiad / Research | 81.0 / 48.3 | lab — card |
| CMT / ChemCOTBench / MatTools | 80.0 / 66.5 / 42.6 | lab — card |
| HiPhO / CritPt | 45.3 / 20.0 | lab — card |
| OmniDocBench | 91.5 | lab — card (VL input) |

## Efficiency

- **Active params:** ≈3B active / 35B total (256 experts, top-8 routed + shared expert; 40 layers, hidden 2048; A3B class)
- **Context length:** 262,144 native; 512k via YaRN (`factor: 2.0`), requires `SGLANG_ALLOW_OVERWRITE_LONGER_CONTEXT_LEN=1` / `VLLM_ALLOW_LONG_MAX_MODEL_LEN=1`
- **VRAM (fp16 rough):** ≈70 GB BF16 (14 shards) — comfortable on 2×48GB or 1×80GB; **FP8 sibling** created the same day plus **Q4_K_M / Q8_0 / F16 GGUF** siblings for local/llama.cpp paths
- **Runtime:** stock Qwen3.5-MoE path in SGLang/vLLM/transformers (no custom code needed); tool-call parser `qwen3_coder`, reasoning parser `qwen3`; MTP speculative decoding supported; temp 1.0 / top-p 0.95 / top-k 20, presence_penalty 1.5
- Text-only serving is possible (`--language-model-only`) to free the vision encoder's KV budget

## What makes it notable

The strongest published agentic-coder in the ~35B MoE class: SWE-bench Pro 61.2 and SWE-bench Multilingual 72.7 beat Agents-A1 by +17.6 / +14.0 pp and land within a few points of Kimi-K3 / GLM-5.3, while GAIA 95.1 is the top score in the card's comparison set. It is also one of the few open models that ships *agent-orchestration machinery in the weights* rather than in a harness — a documented `spawn_subagent` tool contract for parallel isolated-context sub-agents and an opt-in verification mode that runs self-review inside the chain of thought. It is a VL model (image + video tokens in config), so it fits agentic browsing/document workflows; like MiniCPM-V-4.7 and Nemotron Super VL it is tracked here because it publishes coding/agentic evals. Provenance note: the repo's commit history was super-squashed on 10-21, so the "initial upload" 10-15 vs launch 10-21 distinction comes from the file tree + sibling creation dates and the arXiv submission date.

## See also

- [[welcome]]
- Source: https://huggingface.co/InternScience/Sage-A1.5
- Technical report: https://arxiv.org/abs/2610.28578 · Homepage: https://alpha-innovator.github.io/Sage-A1.5/ · GitHub (Agents-A1): https://github.com/InternScience/Agents-A1
- Siblings (created 2026-10-21): [Sage-A1.5-FP8](https://huggingface.co/InternScience/Sage-A1.5-FP8) · [Q4_K_M-GGUF](https://huggingface.co/InternScience/Sage-A1.5-Q4_K_M-GGUF) · [Q8_0-GGUF](https://huggingface.co/InternScience/Sage-A1.5-Q8_0-GGUF) · [F16-GGUF](https://huggingface.co/InternScience/Sage-A1.5-F16-GGUF)
