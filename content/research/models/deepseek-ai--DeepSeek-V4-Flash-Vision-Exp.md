---
title: "DeepSeek-V4-Flash-Vision-Exp"
org: deepseek-ai
model_id: deepseek-ai/DeepSeek-V4-Flash-Vision-Exp
date: 2026-08-31
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - vision-language
  - moe
  - deepseek-v4
  - mla
  - fp8
  - fp4
  - million-token-context
  - reasoning
  - instruct
downloads: 133024
likes: 587
license: mit
pipeline: image-text-to-text
source: https://huggingface.co/deepseek-ai/DeepSeek-V4-Flash-Vision-Exp
params: "13B active / ~284B total (MoE, top-6 of 256 routed + 1 shared) + 32-layer vision tower"
context: "1M tokens"
architecture: moe
---

# DeepSeek-V4-Flash-Vision-Exp

**One-line:** First multimodal DeepSeek-V4 variant — same 13B-active MoE core as V4-Flash with an added vision tower; text-agent scores hold parity with V4-Flash-0731 while multimodal agent evals jump (ApexBench 36.5 vs 26.2). All agentic numbers lab-reported.

> ⚠ Vision-language model (pipeline_tag: image-text-to-text) — included because it publishes a full text-agent eval suite. All benchmark numbers below are lab-reported from the model card / `.eval_results/` YAMLs; no independent source verified yet.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published for this variant |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (DeepSWE stand-in below) |
| DeepSWE | *59.3* | *lab (model card + .eval_results/deep-swe.yaml)* |
| NL2Repo | *57.7* | *lab (model card)* |
| DSBench-Hard | *63.6* | *lab (model card)* |
| AutomationBench (Public) | *25.7* | *lab (model card)* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Terminal Bench 2.1 | *83.9* | *lab (model card + .eval_results/terminal-bench-2.1.yaml)* |
| Toolathlon-Verified | *75.9* | *lab (model card)* |
| Cybergym | *75.3* | *lab (model card)* |
| ApexBench (Pass@1) | *36.5* | *lab (multimodal agent; 0731 text sibling: 26.2†)* |
| Agents' Last Exam | *27.3* | *lab (multimodal agent; 0731 text sibling: 25.2†)* |
| Chartography | *64.3* | *lab (multimodal agent)* |
| ZeroBench (Pass@5) | *35.0* | *lab (multimodal agent)* |

*† DeepSeek-V4-Flash-0731 ignored multimodal content in those inputs.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published for this variant (sibling DeepSeek-V4-Flash: 86.2 lab) |
| GPQA Diamond | — | not published for this variant (sibling DeepSeek-V4-Flash: 88.1 lab) |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** ~13B per token (MoE, top-6 of 256 routed + 1 shared) — same core as DeepSeek-V4-Flash
- **Total params:** ~284B disk footprint + 32-layer vision tower (vision_dim 1024, patch 14, max 384 visual tokens)
- **Context length:** 1,048,576 tokens (1M) via YaRN rope scaling (base 64K, factor 16)
- **VRAM (fp16 rough):** ~26 GB active-params equivalent at runtime; full weights ~284 GB on disk — checkpoint ships FP4 experts + FP8 elsewhere (quantization_config fp8, expert_dtype fp4), so stock transformers vLLM support is preliminary; official recipe: vLLM on 4×GB300 or SGLang with DSpark speculative decoding
- **Architecture:** DeepseekV4ForCausalLM — MoE + Compressed Sparse Attention (CSA) / Heavily Compressed Attention (HCA), 3 nextn-predict layers, DSpark speculative path

## What makes it notable

DeepSeek's first open multimodal V4 release: the text-agent suite is unchanged in spirit from V4-Flash (Terminal Bench 2.1 83.9 vs 82.7, DeepSWE 59.3 vs 54.4, Toolathlon-Verified 75.9 vs 70.3) while the added vision tower unlocks real multimodal agent gains (ApexBench 36.5 vs 26.2, chart/ZeroBench numbers in Opus-4.8 territory). For local agent loops, the caveats from V4-Flash carry over: FP4/FP8 mixed weights need DeepSeek's custom inference path (vLLM recipe targets a 4×GB300 node), so this is a big-host model — but MIT license and 1M context make it the strongest open-text-agent+vision combo in the Flash size class. Sits between the text-only [[deepseek-ai--DeepSeek-V4-Flash]] and the larger [[deepseek-ai--DeepSeek-V4-Pro]] siblings.

## See also

- [[welcome]]
- Sibling: [[deepseek-ai--DeepSeek-V4-Flash]] (text-only, same core, more benchmarks)
- Source: https://huggingface.co/deepseek-ai/DeepSeek-V4-Flash-Vision-Exp