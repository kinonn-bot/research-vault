---
title: "Thinking Machines Inkling-2-Small"
org: thinkingmachines
model_id: thinkingmachines/Inkling-2-Small
date: 2026-11-14
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - vl
  - instruct
  - long-context
downloads: 1064
likes: 219
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/thinkingmachines/Inkling-2-Small
params: 17B active / 594B total MoE
context: 1048576
architecture: moe (custom `inkling2` — needs repo model code; VL-native)
---

# Thinking Machines Inkling-2-Small

**One-line:** Thinking Machines' second-gen open-weight flagship (594B / 17B-active MoE, 1M context, Apache-2.0) — DeepSWE 72.1 and SWE-bench Pro 86.3/97.7 put it at the open agentic-coding frontier, but it is a rack-tier NVFP4-native checkpoint, not a local runner.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (lab uses DeepSWE/SWE-Pro harness family instead) |
| SWE-bench Multilingual | 81.2 | lab (.eval_results, machine-readable) |
| DeepSWE v1.1 | 72.1 | lab (mini-swe-agent v2.4.6; .eval_results date 2026-11-13) |
| SWE-Atlas v1.1 | 61.9 | lab (mini-swe-agent v2.4.6) |
| SWE-bench Pro v2 (Hard/Full) | 86.3 / 97.7 | lab (mini-swe-agent v2.4.6; .eval_results confirms Hard 86.3) |
| Terminal-Bench 2.1 | 81.3 | lab (Terminus 2 harness; .eval_results) |
| Terminal-Bench 4.0 | 13.1 | lab (mini-swe-agent v2.4.6; Vals independently measured 12.63%) |
| Terminal-Bench Science | 5.7 | lab (mini-swe-agent v2.4.6; .eval_results) |
| Vibe Code Bench v1.1 | 81.6 | lab (openhands vals harness; Vals measured 81.55%) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | main suite not published (τ³ Banking 40.4 via lab card — see below) |
| ToolACE | — | not published |
| GAIA | — | not published |
| MCP Atlas (Full / Public) | 85.4 / 85.0 | lab |
| τ³ Banking (τ-Bench family) | 40.4 | lab |
| BrowseComp (w/ compaction) | 90.2 | lab |
| DeepSearchQA (w/ compaction) | 90.9 | lab |
| EnterpriseBench-CoreCraft | 71.8 | lab (3rd overall incl. closed models, per VentureBeat) |
| EnterpriseOps-Gym | 46.8 | lab |
| Finance Agent v2.1 | 67.5 | lab (#1 open-weight per Vals: 67.54%) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| AA Intelligence Index (v5.0) | 30.6 | lab card "Third Party Index" row (AA article: highest open-weights score outside China at weights release) |
| Vals Index (v2.2) | 56.1 | lab card; Vals independently measured 56.08% (#19/34, #7 open-weight) |
| GPQA Diamond | 93.0 | lab (.eval_results, machine-readable) |
| HMMT Feb 2026 | 95.8 | lab (.eval_results, machine-readable) |
| HLE-Diamond | 28.7 | lab |
| LongBench v2 | 70.6 | lab |
| AA-LCR v1.1 | 83.3 | lab |
| ARC-AGI (v1 / v2) | 96.5 / 81.7 | lab |

## Efficiency

- **Active params:** 17B active / 594B total (sparse MoE, 8 of 384 experts per token, 48 layers, hybrid local/global attention)
- **Context length:** 1,048,576 tokens (1M; Tinker serverless offers 256K)
- **VRAM (native precision rough):** NVFP4-native ≈ 0.5 B/param → ~300 GB weights; card requires 500 GB aggregated (2× B300 or 4× H200). MXFP8 alt needs 800 GB aggregated — ⚠ large / rack tier, not a local runner
- **Custom architecture:** `model_type: inkling2` (`Inkling2ForConditionalGeneration`) — stock transformers will NOT load it; use SGLang / vLLM / TokenSpeed / Unsloth recipes or the MXFP8/NVFP4 first-party quants

## What makes it notable

Successor to Inkling-Small (vaulted 2026-08-01 run: SWE-V 80.2) with the same VL-native recipe scaled to 594B total params. The eval suite moves off classic SWE-bench Verified/Aider/BFCL onto the newer agent-harness family (DeepSWE, SWE-Atlas, SWE-Pro, Terminal-Bench 2.1/4.0, Vibe Code Bench) where it leads or nearly leads every open-weight row except DeepSeek-V4.1-Flash-1017. Independent signal exists (Vals Index 56.08, Finance Agent #1 open-weight) but the headline coding numbers are lab-harness runs — treat cross-lab comparisons as lab-reported until third-party reproductions land. No SWE-bench Verified, Aider, BFCL, or τ-Bench main-suite numbers published. Released 2026-11-05 (llm-stats; HF repo staged 11-04); surfaced via trending window (lastModified 11-13).

## See also

- [[welcome]]
- Source: https://huggingface.co/thinkingmachines/Inkling-2-Small
- MXFP8 sibling: https://huggingface.co/thinkingmachines/Inkling-2-Small-MXFP8
- Launch post: https://thinkingmachines.ai/news/inkling-2-small/
- Artificial Analysis: https://artificialanalysis.ai/articles/thinking-machines-releases-inkling-2-small-highest-scoring-open-weights-model-outside-of-chinia-upon-weights-release-it
- Vals profile: https://www.vals.ai/models/thinkingmachines_inkling-2-small
- Predecessor: [[thinkingmachines--Inkling-Small]]
