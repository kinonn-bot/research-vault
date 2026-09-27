---
title: "XiaomiMiMo/MiMo-V2.6-Pro-MOPD"
org: XiaomiMiMo
model_id: XiaomiMiMo/MiMo-V2.6-Pro-MOPD
date: 2026-09-27
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - multimodal
  - rl
  - long-context
downloads: 0
likes: 4
license: MIT
pipeline: text-generation
source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Pro-MOPD
params: 1.02T (42B active)
context: 1M
architecture: moe (hybrid SWA+GA, no shared experts)
---

# XiaomiMiMo/MiMo-V2.6-Pro-MOPD

**One-line:** MOPD (Multi-teacher On-Policy Distillation) upgrade of MiMo-V2.6-Pro-RL — flagship 1.02T/42B-active omnimodal with tool-call-repetition fix, MIT, 1M ctx.

⚠ **large** — 1.02T total params; datacenter-only (see Efficiency).
⚠ Lab-reported benchmarks below are the MiMo-V2.6 technical-report numbers measured on the **RL checkpoint**; the MOPD checkpoint's card publishes no new eval tables, but Xiaomi's blog (2026-09-27) states the broader benchmark suite "held steady" after MOPD. Released Sep 27, 2026 (weights on HF 04:00Z, API since Sep 25).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | — |
| DeepSWE v1.1 (agentic SWE stand-in) | 71.9 | lab (V2.6 report, RL ckpt — holds steady) |
| ProgramBench | 26.5 | lab (V2.6 report, RL ckpt) |
| MiMo Code Bench (in-house) | 63.2 | lab (V2.6 report, RL ckpt) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| Toolathlon-Verified | 76.9 | lab (V2.6 report, RL ckpt) |
| AutomationBench v1.0.6 | 53.1 | lab (V2.6 report, RL ckpt) |
| Terminal Bench 2.1 | 89.9 | lab (V2.6 report, RL ckpt) |
| Agents' Last Exam | 31.6 | lab (V2.6 report, RL ckpt) |
| JobBench | 62.0 | lab (V2.6 report, RL ckpt) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| AA Intelligence Index | 46 (#1/114 open-weight) | Artificial Analysis (independent, on Pro-RL) |
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2026 | — | — |

## Efficiency

- **Active params:** 42B (of 1.02T total; 384 routed experts, 8 active; ~70 layers hybrid full+SWA, no shared experts, MTP)
- **Context length:** 1M tokens
- **VRAM (fp16 rough):** ~2TB fp16 — NOT locally runnable; on-disk weights ~1TB (fp8/bf16 mix), needs multi-node expert-parallel or API.

## What makes it notable

The flagship V2.6 checkpoint now has a production-grade agentic patch: Pro-RL's exact within-turn tool-call repetition rate (0.54% under OpenCode, 0.10% under Claude Code) drops substantially after MOPD across every harness and context-length bucket, per Xiaomi's published heatmaps, while the broader suite holds steady — the #1 open-weight AA Intelligence Index position (46) carries over from Pro-RL. The MOPD2 recipe (mixRL + SFT teacher fusion, teacher-prefix and SFT-prefix on-policy distillation) is a genuinely novel post-training algorithm that generalizes beyond the repetition fix to domains with unreliable verification (long-horizon game dev, science, embodied). For the user's local/agent use case this remains a datacenter heavyweight — the 15B-active Flash-MOPD sibling is the realistic self-hosted pick; both are worth running via API given the agent-harness reliability fix.

## See also

- [[welcome]]
- Source: https://huggingface.co/XiaomiMiMo/MiMo-V2.6-Pro-MOPD
- Technical blog: https://mimo.xiaomi.com/blog/mimo-v2-6-tool-call-repetition
- Siblings: [[XiaomiMiMo/MiMo-V2.6-Pro-RL]], [[XiaomiMiMo/MiMo-V2.6-Flash-MOPD]], [[XiaomiMiMo/MiMo-V2.6-Distill-Qwen-9B]]