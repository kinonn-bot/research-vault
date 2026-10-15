---
title: "StepFun Step 5 Preview"
org: stepfun-ai
model_id: stepfun-ai/Step-5-Preview
date: 2026-10-16
tags:
  - huggingface
  - coding
  - agentic
  - moe
  - vision-language
  - long-context
  - fp8
  - instruct
  - finance
downloads: 144
likes: 63
license: "StepFun Model License 1.0 (permissive; attribution required if >100M MAU or >$20M/month revenue)"
pipeline: "step5_vl (multimodal MoE; text output)"
source: https://huggingface.co/stepfun-ai/Step-5-Preview
params: "600B total / 27B active (sparse MoE; expert count not disclosed)"
context: "1,048,576 (1M tokens)"
architecture: "sparse moe VL (step5_vl / Step5ForConditionalGeneration; FP8 main checkpoint + BF16 and NVFP4 siblings; MTP speculative decoding)"
---

# StepFun Step 5 Preview

**One-line:** StepFun's flagship agentic model — 600B-total / 27B-active MoE with 1M context and vision input, positioned for software engineering and finance; **open weights released 2026-10-15** (API since Sep 20; NVIDIA publicly congratulated the drop as StepFun's "largest open weights release"). ⚠ Benchmark chart is image-only and **lab-reported**; ⚠ 650.3 GB FP8 across 22 shards — data-center serving only (4-8 GPU vLLM/SGLang recipes), no local path at release.

> ⚠ All numbers below come from the card's single image chart (read/verified via vision extraction, two passes); no SWE-bench Verified / LiveCodeBench / BFCL / τ-Bench numbers published. GDPval-AA v2.1 row is sourced by StepFun **from Artificial Analysis** (as of 2026-09-20). Cross-model comparisons shown: Kimi K3 (Max), GLM-5.3 (Max), GPT-6 Astra (Max), Claude Opus 5 (Max).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (DeepSWE v1.1 used instead) |
| SWE-bench Multilingual | — | not published |
| DeepSWE v1.1 | 67.7 | lab — card chart (SWE-agent harness); vs Kimi K3 67.5, GLM-5.3 66.9, GPT-6 Astra 74.1, Claude Opus 5 74.0 |
| StepCodeBench (in-house) | 49.0 | lab — card chart; vs Kimi K3 43.9, GLM-5.3 40.2, GPT-6 Astra 61.0, Claude Opus 5 63.9 |
| ProgramBench | 80.5 | lab — card chart; vs Kimi K3 77.8, GLM-5.3 72.0, GPT-6 Astra 85.4, Claude Opus 5 82.3 |
| Terminal-Bench v4 | 33.3 | lab — card chart; vs Kimi K3 12.6, GLM-5.3 41.9, GPT-6 Astra 57.9, Claude Opus 5 52.3 |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Agents' Last Exam (ALE-CLI) | 29.5 | lab — card chart; vs Kimi K3 27.6, GLM-5.3 28.6, Claude Opus 5 28.6, GPT-6 Astra 33.3 |
| GDPval-AA v2.1 | 1566 | lab — card chart, from Artificial Analysis as of 2026-09-20; vs GLM-5.3 1645, Claude Opus 5 1708, GPT-6 Astra 1542, Kimi K3 1524 |
| FrontierFinance | 66.4 | lab — card chart; vs Claude Opus 5 69.7, GLM-5.3 64.1, Kimi K3 62.6 |
| DRACO (deep research) | 83.3 | lab — card chart; vs Claude Opus 5 87.6, GLM-5.3 82.3, Kimi K3 78.5 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2024/2025 | — | not published |
| HLE | — | not published |

## Efficiency

- **Active params:** 27B per token of 600B total (sparse MoE; expert count not disclosed)
- **Context length:** 1,048,576 (1M); card claims max output up to 1M (third-party pages cite 64k practical output)
- **VRAM:** FP8 main checkpoint = **650.3 GB across 22 shards (verified; main repo IS the FP8 release)**; BF16 and NVFP4 siblings on HF + ModelScope. Serving recipes: vLLM TEP4 (4 GPUs, `--spec-tokens 3`, tool parser `step5`, max-model-len 1048576) or DEP4; SGLang TP8 + EAGLE spec decode. ⚠ Not a local model — 4-8 GPU-class; watch for community int4/GGUF quants.
- **Release mechanics:** repos/weights staged since 2026-09-20 (API launch), made public with the open-weights release 2026-10-15 (README/final card commits 10-13 → 10-15 01:28Z); 144 downloads / 63 likes at note time (launch day).

## What makes it notable

StepFun's biggest open release and a credible open challenger in the "long-horizon agentic work" class: 600B/27B MoE at 1M context with vision, roughly matching Kimi K3 on DeepSWE (67.7 vs 67.5) and beating GLM-5.3 on StepCodeBench / ProgramBench / DRACO rows, while trailing both on Terminal-Bench v4 (33.3 vs 41.9 vs Claude Opus 5 52.3). Its differentiation is finance (FrontierFinance 66.4, "particular strength in finance") and cheap API pricing ($1 / $2.70 per M in/out) as the hosted preview. For this user's coding/agent loop: no SWE-bench Verified, no BFCL — the published suite is custom-heavy (DeepSWE, StepCodeBench, ProgramBench) and 650 GB FP8 rules out local runs; interesting mainly as an OpenRouter-hosted agent backend and as a signal for the 600B-class open field. Watch for: SWE-bench Verified / BFCL numbers, community quants, and independent (AA) full re-evaluation of the open checkpoint.

## See also

- [[welcome]]
- Source: https://huggingface.co/stepfun-ai/Step-5-Preview
- Model page: https://www.stepfun.com/step-5-preview (open weights announced for 2026-10-15)
