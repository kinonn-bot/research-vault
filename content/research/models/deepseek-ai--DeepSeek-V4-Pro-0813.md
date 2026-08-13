---
title: "DeepSeek-V4-Pro-0813"
org: deepseek-ai
model_id: deepseek-ai/DeepSeek-V4-Pro-0813
date: 2026-08-13
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - deepseek-v4
  - mla
  - fp8
  - million-token-context
  - reasoning
  - instruct
  - dspark
downloads: 0
likes: 244
license: mit
pipeline: text-generation
source: https://huggingface.co/deepseek-ai/DeepSeek-V4-Pro-0813
params: "~49B active / 1.6T total (MoE, top-6 of 384 routed + 1 shared)"
context: "1M tokens"
architecture: moe
---

# DeepSeek-V4-Pro-0813

**One-line:** GA of DeepSeek-V4-Pro (supersedes the April preview) with a major agentic upgrade — Terminal Bench 2.1 87.9 (+15.8pp vs preview), DeepSWE 62.7 (from 12.8), Toolathlon 74.1 — shipped under MIT with official FP8 weights and a built-in DSpark speculative-decoding module. ⚠ large: 1.6T total params, server-class only. ⚠ no SWE-bench Verified / BFCL published — agentic numbers come from the lab's DeepSeek-Harness suite (lab-reported).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published for 0813 |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published for 0813 |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (agentic stand-in: DeepSWE below) |
| SWE-bench Multilingual | — | not published |
| Terminal Bench 2.1 | *87.9* | *lab-reported (preview 72.1, Flash-0731 82.7, GLM-5.2 81.0, Kimi K3 88.3, Opus-4.8 85.0)* |
| NL2Repo | *61.5* | *lab-reported (preview 38.5)* |
| Cybergym | *83.3* | *lab-reported (preview 52.7, Flash-0731 76.7)* |
| DeepSWE | *62.7* | *lab-reported (preview 12.8 — biggest single jump)* |
| DSBench-FullStack † | *71.1* | *lab-reported, internal test set (preview 41.8)* |
| DSBench-Hard † | *67.2* | *lab-reported, internal test set (preview 31.1)* |

*† Internal full-stack / hard coding-agent test sets — treat as lab-internal, not leaderboard-comparable.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Toolathlon-Verified | *74.1* | *lab-reported (preview 55.9, Flash-0731 70.3)* |
| Agents' Last Exam | *25.7* | *lab-reported (preview 16.5)* |
| AutomationBench (Public) | *31.8* | *lab-reported (preview 12.8)* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published for 0813 |
| GPQA Diamond | — | not published for 0813 |
| MATH | — | not published |
| AIME 2025 | — | not published |
| HLE (wo / w tools) | *42.7 / 60.0* | *lab-reported (preview 37.7 / 48.2)* |

## Efficiency

- **Active params:** ~49B per token (top-6 of 384 routed + 1 shared) — same structure as V4-Pro preview (config verified identical: 61 layers, hidden 7168)
- **Total params:** ~1.6T (full disk footprint)
- **Context length:** 1,048,576 tokens (1M) via YaRN ×16 from 64k native; recommends ≥384K output budget for high/max reasoning effort
- **VRAM (fp16 rough):** ~98 GB active-params equivalent at runtime; full weights ~1.6 TB on disk — official weights are **FP8 e4m3** (quantization_config in config.json), no BF16 variant published yet
- **Architecture:** custom `deepseek_v4` (DeepseekV4ForCausalLM) — needs `trust-remote-code`; hybrid CSA+HCA attention, hash layers + nextn-predict layer, DSpark speculative decoding module (`--speculative-config '{"method":"dspark",...}'` in vLLM / `--speculative-algorithm DSPARK` in SGLang)
- **Deployment:** vLLM recipe targets a 4×GB300 node; local single-machine path exists via the `inference/` folder (weight conversion + chat demo)

## What makes it notable

This is the production GA of DeepSeek-V4-Pro, and the delta over the April preview is the story: +15.8pp on Terminal Bench 2.1 (87.9 vs 72.1), DeepSWE 12.8 → 62.7, Cybergym 52.7 → 83.3, Toolathlon 55.9 → 74.1 — the lab's own table now puts it broadly competitive with Kimi K3 (Terminal Bench 88.3, DeepSWE 67.5) and GLM-5.2 (81.0 / 46.2), within a few points of Opus-4.8 and Fable-5 (w/ fallback) on the same suite. Like the preview it ships MIT with 1M-token context, and the DSpark speculative module is now bundled in the same checkpoint (no separate draft model). Caveats for agent-loop users: no SWE-bench Verified or BFCL published — the agentic numbers are all lab-reported via DeepSeek Harness, two of them (DSBench) on internal test sets; and an early HN report flags pass@1 reliability concerns (works well at pass@3, "horrendous" at pass@1 with temperature 1.0) — sample or lower temperature in production. It is emphatically not a local model: 1.6T total params, FP8 weights, multi-node deployment. Replaces the API preview build; OpenRouter lists it as the GA.

## See also

- [[welcome]]
- Sibling: [[deepseek-ai--DeepSeek-V4-Pro]] (April preview), [[deepseek-ai--DeepSeek-V4-Flash-0731]]
- Source: https://huggingface.co/deepseek-ai/DeepSeek-V4-Pro-0813
