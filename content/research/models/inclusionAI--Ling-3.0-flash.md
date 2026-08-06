---
title: "Ling-3.0-flash"
org: inclusionAI
model_id: inclusionAI/Ling-3.0-flash
date: 2026-08-06
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid
  - instruct
  - long-context
downloads: 1196
likes: 183
license: MIT
pipeline: text-generation
source: https://huggingface.co/inclusionAI/Ling-3.0-flash
params: "5.1B active / 124B total (MoE, 8/512 routed + 1 shared expert)"
context: "256K tokens (trained 8K→32K→256K; served 262144 via YaRN)"
architecture: hybrid-linear moe (KDA + MLA)
---

# Ling-3.0-flash

**One-line:** Ant Group's (InclusionAI) flash-class native hybrid-linear MoE — 124B total / 5.1B active (KDA + MLA, 5:1) — trained on 10,000+ interactive environments for agentic loops; official SWE-bench Pro 56.6 / SWE-bench Multilingual 72.4. ⚠ large: 124B total, FP8 checkpoint ≈124 GB, needs multi-GPU — not a consumer-GPU single-box model. ⚠ no SWE-bench Verified published (SWE-bench Pro used instead, OpenHands harness).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | 72.4 | lab (`.eval_results`, % resolved) |
| SWE-bench Pro | 56.6 | lab (`.eval_results`, OpenHands harness, 256K ctx) |
| SciCode | 41.24 | lab (BF16; BenchLM verified FP8 40.4) |

*SWE-bench Pro 56.6 is the card's official eval-result file value (machine-readable `.eval_results/swe-bench_pro.yaml`, also quoted in the r/LocalLLaMA thread). BenchLM independently verifies the FP8 checkpoint only (SciCode 40.4); coding category rank #60/132, score 50.5 — mid-pack for coding, not SOTA. No HumanEval/MBPP/LiveCodeBench/Aider numbers published anywhere.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published (Tau3-banking-AA exists but number only in image-only chart) |
| ToolACE | — | not published |
| GAIA | — | not published |
| Terminal-Bench 2.1 | — | evaluated under AA protocol, number in image-only chart |
| MCP-Atlas | — | evaluated (500-task public set), number in image-only chart |
| SkillsBench | — | evaluated via kilo-code (87 tasks), number in image-only chart |

*Card claims "comprehensive agentic evolution" with 10,000+ interactive training environments and strong results on Tau3-banking-AA / MCP-Atlas / SkillsBench / GDPval v2-AA / BrowseComp — but every agentic number sits in an image-only benchmark chart on an unreachable internal CDN (`intranetproxy.alipay.com`). No independent agentic verification exists yet. Treat agentic claims as unverified.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 84.97 | lab (BF16; BenchLM verified FP8 84.0) |
| MATH | — | not published |
| AIME 2026 | 93.2 | lab (`.eval_results`) |
| HLE | 22.7 | lab (`.eval_results`) |
| HMMT Feb 2026 | 87.0 | lab (`.eval_results`) |
| ArcPrize | 68.75 | lab (fp8 sibling card, BF16) |
| IFBench | 74.49 | lab (BF16; BenchLM verified FP8 73.4) |

## Efficiency

- **Active params:** 5.1B per token (8 of 512 routed experts + 1 shared expert activated; 2 dense layers; 35 KDA + 7 Gated MLA hybrid-linear, 5:1)
- **Total params:** 124B (full disk-resident weight footprint)
- **Context length:** 256K trained (8K→32K→256K schedule), served at 262,144 via YaRN
- **VRAM (fp16 rough):** ~248 GB full precision — ⚠ large, not single-GPU. FP8 checkpoint ≈ 124 GB; card's recommended serving is 4× 141GB-class GPUs (H20-3e) or 8× 80GB (H100/H800). INT4/FP4 variants exist (groupwise quant, routed-expert weights) if you must squeeze it down.

## What makes it notable

Ant Group's flash-class play: a genuinely native hybrid-linear architecture (Kimi Delta Attention + MLA stacked 5:1, 1/64 sparse MoE) from pretraining, not a retrofit — 5.1B active params per token is class-leading efficiency for a 124B-class model. The card is explicitly positioned for agentic production work (SGLang HiCache + Mooncake cluster-shared caching, TTFT reductions of 60–80%+ in long-input scenarios) and claims tested deployments across Claude Code, Kilo Code, Qwen Code, Hermes Agent, and OpenClaw. The official eval files (SWE-bench Pro 56.6, SWE-bench Multilingual 72.4, AIME 2026 93.2, GPQA-D 84.97) put it solidly in the strong-generalist band, but independent verification (BenchLM: coding #60/132, SciCode 40.4) says it is NOT a coding SOTA — the reasoning/instruction-following profile is stronger than the coding profile. For this user's local agent loops: the 5.1B-active efficiency is tempting, but 124B total means FP8 multi-GPU or heavy quant — and with zero verified agentic numbers (Tau3/MCP-Atlas are image-only claims), agent-loop suitability is unproven. Worth watching for the promised full benchmark table and community quant adoption.

## See also

- [[welcome]]
- Source: https://huggingface.co/inclusionAI/Ling-3.0-flash
