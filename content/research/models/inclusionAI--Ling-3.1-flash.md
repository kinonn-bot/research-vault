---
title: "inclusionAI Ling-3.1-flash"
org: inclusionAI
model_id: inclusionAI/Ling-3.1-flash
date: 2026-10-15
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid
  - instruct
  - long-context
  - fp8
downloads: 8
likes: 30
license: MIT
pipeline: text-generation
source: https://huggingface.co/inclusionAI/Ling-3.1-flash
params: "25B active / 560B total (MoE, 8/512 routed + 1 shared expert)"
context: "262,144 tokens (config.json + OpenRouter); card claims 1M-token context"
architecture: "hybrid-linear moe (63 KDA + 9 gated MLA, 7:1; 72 layers, 4 dense)"
---

# inclusionAI Ling-3.1-flash

**One-line:** Ant Group's biggest flash-class model yet — 560B total / 25B active hybrid-linear MoE with native hybrid reasoning, open weights dropped 2026-10-13 (API since ~Oct 2), MIT; lab-reported SWE-bench Pro 68.74 and frontier agentic scores — but ⚠ every number comes from image-only card charts (no `.eval_results` shipped yet), and the SWE-bench Pro / Terminal-Bench 4.0 / DeepSWE / SWE Atlas runs used LingCode, a Pi-based harness the lab has not open-sourced. ⚠ very large: FP8 checkpoint ≈574 GB — 8×H200-class serving or wait for community quants.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (SWE-bench Pro used instead) |
| SWE-bench Multilingual | 88.50 | lab — card chart; vs Kimi K3 90.33, DeepSeek-V4.1-Flash 90.00, GLM-5.3 90.67, Claude Opus 5 89.50 |
| SWE-bench Pro | 68.74 | lab — card chart, LingCode harness; vs Kimi K3 64.84, GLM-5.3 61.83, DeepSeek-V4.1-Flash 56.77, Claude Opus 5 79.20 |
| SWE Atlas — Codebase QnA | 64.51 | lab — card chart, LingCode harness; vs Kimi K3 66.00, GLM-5.3-flash 61.29 |
| DeepSWE | 59.70 | lab — card chart, LingCode harness; trails set (DeepSeek-V4.1-Flash 74.20, GPT-5.6 Sol 72.67, Kimi K3 67.50) |
| FrontierSWE | 75.16 | lab — card chart; leads set (GLM-5.3 74.34, Kimi K3 73.52, GPT-5.6 Sol 71.30) |
| Terminal-Bench 2.1 | 81.18 | lab — card chart; trails set (DeepSeek-V4.1-Flash 90.60, Claude Opus 5 89.10) |
| Terminal-Bench 4.0 | 46.03 | lab — card chart, LingCode harness; best-open in set (GLM-5.3 41.90, GPT-5.6 Sol 39.90). ⚠ Artificial Analysis independently measured 33.3 under its protocol — harness-dependent, treat 46.03 with care |
| CyberGym | 87.90 | lab — card chart; vs DeepSeek-V4.1-Flash 88.10, GLM-5.3 84.50 |

*Footnote on the card: "DeepSWE, Terminal-Bench-4.0, SWE Atlas – Codebase QnA and SWE-bench Pro: Evaluated using LingCode, a harness extensively customized from Pi." LingCode supports long-horizon runs (hundreds of tool-call rounds, repeated context compaction); open-sourcing is "considered". These four numbers are therefore harness-specific, not direct model comparisons.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | τ³-Banking 47.8 | lab — card chart; vs GLM-5.3 50.30, Kimi K3 46.00, Claude Opus 5 42.10 |
| ToolACE | — | not published |
| GAIA | — | not published |
| MCP-Atlas | 83.00 | lab — card chart; vs Claude Opus 5 85.80, Kimi K3 84.20 |
| SkillsBench | 68.70 | lab — card chart; mid-pack (GPT-5.6 Sol 73.50, DeepSeek-V4.1-Flash 71.30) |
| AutomationBench (public) | 52.50 | lab — card chart |
| GDPval-AA v2.1 | 1673 (Elo) | lab — card chart; 2nd in set (Claude Opus 5 1708, GLM-5.3 1644, GPT-5.6 Sol 1600) |
| GDPval-AA (AA measure) | 55.9% | Artificial Analysis (independent; different metric from the lab's Elo figure) |

*The card positions the model for "general-purpose agents, search, office productivity, and software engineering" and lists tested frameworks: Claude Code, Kilo Code, Qwen Code, Hermes Agent, and OpenClaw. OpenRouter's traffic breakdown confirms real agent use: Kilo Code (163B tokens), Claude Code (116B), Hermes Agent (18.7B) are among the top apps sending traffic to it.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 / 2026 | — | not published |
| HLE | 37.44 | lab — card chart (AA: 39.4) |
| CritPt | 16.29 | lab — card chart (AA: 18.0) |
| HealthBench Professional | 65.35 | lab — card chart; leads set (GPT-5.6 Sol 60.76, Claude Opus 5 59.80) |
| Supermatbench (QA / Agent) | 51.23 / 31.75 | lab — materials-chemistry benchmark co-developed with Peking University |
| MultiChallenge | 69.78 | lab — card chart |
| BrowseComp / Draco / WideSearch | 91.67 / 85.49 / 83.32 | lab — card chart; BrowseComp leads set |
| Finance Agent v2 / FinSearch | 57.87 / 81.74 | lab — card chart |

**Independent verification (Artificial Analysis, via OpenRouter):** Intelligence Index 41.1; AA-LCR 83.0; AA-Omniscience 29.1% accuracy / 62.1% non-hallucination; SciCode 54.1; Terminal-Bench 4.0 33.3. No BenchLM page found as of this run.

## Efficiency

- **Active params:** 25B per token (8 of 512 routed experts + 1 shared; 72 layers = 63 KDA linear-attention + 9 gated-MLA, 7:1; 4 dense layers; hidden 4096)
- **Context length:** 262,144 (config.json `max_position_embeddings` + OpenRouter); card claims 1M-token window
- **VRAM:** FP8 checkpoint ≈574 GB across 54 safetensors shards (~1 byte/param; `fp8` tag, FP8-native main checkpoint — no BF16 sibling). Official recipes: 8×H200 (TP8+EP8) or 4×GB300 (TP4+EP4), MTP/NEXTN speculative decoding; SGLang day-0 image + vLLM (`--tool-call-parser ling3`). ⚠ Not local-single-GPU; INT4/community GGUF needed for anything smaller — AtomicChat + AMAImedia GGUF repos already appeared on drop day (untested at note time).

## What makes it notable

Ant Group's flash-class flagship jumped a full class: 124B/5.1B (Ling-3.0) → 560B/25B here, with SWE-bench Pro 56.6 → 68.74 and a redesigned agentic stack (LingCode harness built on the open-source coding agent Pi, long-horizon runs with context compaction). On the card's chart it beats Kimi K3, GLM-5.3, and DeepSeek-V4.1-Flash on SWE-bench Pro, FrontierSWE, and GDPval-AA, while trailing Claude Opus 5 on most coding rows. Two caveats matter for this user: (1) the four headline coding numbers were produced with a custom, not-yet-open harness (LingCode) — AA's independent Terminal-Bench 4.0 of 33.3 vs the lab's 46.03 shows the spread this can create; (2) 560B total means local runs need 574 GB FP8 or aggressive quants — not an agent-loop model for a single box. It is however explicitly used inside Hermes Agent (card-listed framework; OpenRouter shows 18.7B tokens via Hermes Agent), and OpenRouter hosting is cheap. Watch for: `.eval_results` YAMLs, LingCode open-sourcing, and whether community quants (AtomicChat) reach usable quality.

## See also

- [[welcome]]
- Prior generation: [[inclusionAI--Ling-3.0-flash]]
- Source: https://huggingface.co/inclusionAI/Ling-3.1-flash
