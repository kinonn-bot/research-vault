---
title: "DeepSeek-V4-Flash-0731"
org: deepseek-ai
model_id: deepseek-ai/DeepSeek-V4-Flash-0731
date: 2026-07-31
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - deepseek-v4
  - mla
  - fp8
  - fp4
  - million-token-context
  - reasoning
  - instruct
  - dspark
downloads: 15366
likes: 1380
license: mit
pipeline: text-generation
source: https://huggingface.co/deepseek-ai/DeepSeek-V4-Flash-0731
params: "13B active / 284B total (MoE, top-6 of 256 routed + 1 shared)"
context: "1M tokens"
architecture: moe
---

# DeepSeek-V4-Flash-0731

**One-line:** Official GA of DeepSeek-V4-Flash (supersedes the preview) — a coding-agent release with massive agentic gains over the preview (Terminal Bench 2.1 61.8 → 82.7, DeepSWE 7.3 → 54.4) at ~13B active params, MIT license, ships FP8/FP4-quantized. ⚠ large (server-class).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published for this checkpoint |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published for this checkpoint |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published for this checkpoint (lab used DeepSWE/Terminal-Bench instead) |
| SWE-bench Multilingual | — | not published |
| Terminal Bench 2.1 | 82.7 | lab (DeepSeek Harness, max effort) |
| NL2Repo | 54.2 | lab (DeepSeek Harness, max effort) |
| Cybergym | 76.7 | lab (DeepSeek Harness, max effort) |
| DeepSWE | 54.4 | lab (DeepSeek Harness, max effort) |
| DSBench-FullStack † | 68.7 | lab (internal set) |
| DSBench-Hard † | 59.6 | lab (internal set) |

*All numbers lab-reported from the model card (DeepSeek Harness minimal mode, max reasoning effort, temp 1.0 / top_p 0.95). † internal full-stack test sets. No independent third-party evals published yet (released 2026-07-31).*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Toolathlon-Verified | 70.3 | lab |
| Agents' Last Exam | 25.2 | lab |
| AutomationBench Public | 25.1 | lab |

*Toolathlon-Verified 70.3 vs GLM-5.2's 59.9; Agents' Last Exam 25.2 vs GLM-5.2 23.8. The card's comparison set is GLM-5.2 and Opus-4.8 — 0731 is within ~2-3 points of Opus-4.8 on most agentic rows.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published for this checkpoint |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** ~13B (per token — top-6 of 256 routed + 1 shared; Flash family, same structure as DeepSeek-V4-Flash-DSpark)
- **Total params:** ~284B (disk-resident; 43 layers, hidden 4096, MLA-style attention with head_dim 512 + DSpark speculative draft on layers 40-42)
- **Context length:** 1,048,576 tokens (1M) via YaRN (base 64K); max output recommended 384K at high/max effort
- **VRAM (fp16 rough):** ~570 GB full precision — NOT realistic. Official distribution is FP8 (e4m3) weights + FP4 experts ≈ 160-200 GB on disk; vLLM recipe targets a 4×GB300 node with expert parallel. ⚠ large — datacenter-class, not a local workstation model.

## What makes it notable

DeepSeek's GA of V4-Flash, released 2026-07-31 and explicitly optimized for coding agents, fixes the preview's agentic weakness: Terminal Bench 2.1 jumps 61.8 → 82.7, DeepSWE 7.3 → 54.4, Cybergym 38.7 → 76.7, Toolathlon 49.7 → 70.3. It beats GLM-5.2 on every row in the card's comparison table (TB2.1 82.7 vs 81.0, DeepSWE 54.4 vs 46.2, Toolathlon 70.3 vs 59.9) and trails Opus-4.8 by only ~2-3 points on most agentic benchmarks — at a fraction of the active params (13B vs 1.6T-class peers). MIT license, 1M context, DSpark speculative decoding built into the checkpoint. Same caveat as the rest of the V4 family: FP8/FP4 official quant + custom `encoding` scripts mean stock vLLM/SGLang support is still settling; budget multi-GPU (4×GB300).

## See also

- [[welcome]]
- Sibling: [[deepseek-ai--DeepSeek-V4-Flash]], [[deepseek-ai--DeepSeek-V4-Pro]]
- Source: https://huggingface.co/deepseek-ai/DeepSeek-V4-Flash-0731
