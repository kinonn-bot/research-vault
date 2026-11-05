---
title: "Moonshot AI / Kimi K3.1 Pro"
org: moonshotai
model_id: moonshotai/Kimi-K3.1-Pro
date: 2026-11-06
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - multimodal
  - instruct
  - moe
downloads: 11658
likes: 880
license: kimi-k3.1-pro
pipeline: image-text-to-text
source: https://huggingface.co/moonshotai/Kimi-K3.1-Pro
params: 104B active (2.8T total)
context: 1000000
architecture: moe
---

# Moonshot AI / Kimi K3.1 Pro

**One-line:** First of the K3.1 series — 2.8T/104B natively multimodal MoE, 1M context; API launched Oct 23, open weights dropped ~Nov 2–4; leads open models on Terminal-Bench 4.0 (65.7) and DeepSWE (75.5).

⚠ **Lab-reported benchmarks only** — no independent third-party evaluations published yet. All numbers below are from Moonshot's own card (Nov 2026). Treat with appropriate skepticism. License is custom "Kimi K3.1-Pro" (permissive + Model-as-a-Service $20M/12mo revenue cap + attribution above 100M MAU / $20M monthly revenue); fine for personal/local use.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| Terminal-Bench 4.0 | *65.7 (Claude Code harness)* | *lab* |
| Terminal-Bench-Science 0.1 | *38.1* | *lab* |
| SWE Marathon v1.1 | *51.7* | *lab* |
| DeepSWE v1.1 | *75.5* | *lab* |
| ProgramBench | *31.5* | *lab* |
| Kimi Code Bench 2.0 | *77.1 (internal)* | *lab* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |
| HLE w/ tools | *70.0* | *lab* |
| BrowseComp | *92.1* | *lab* |
| APEX-Agents | *69.4* | *lab* |
| AutomationBench-AA | *73.3* | *lab* |
| OSWorld V2.1 | *79.6* | *lab* |
| GDPval-AA v2.1 | *1846 Elo* | *lab (via Artificial Analysis)* |
| AA-Briefcase v1.1 | *1678 Elo* | *lab (via Artificial Analysis)* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| HLE-Full | *51.1* | *lab* |
| HLE-Diamond | *39.4* | *lab* |
| GPQA Diamond | — | — |
| AIME 2025 | — | — |

## Efficiency

- **Active params:** 104B (2.8T total MoE; 69 KDA + 24 Gated DSA attention layers)
- **Context length:** 1000000 tokens
- **VRAM (fp16 rough):** ⚠ large — ships MXFP4 weights (quantization-aware training), so ~1.4 TB even quantized; datacenter-only, no local path until community quants land

## What makes it notable

Post-trained from Kimi K3 with large-scale joint RL across hundreds of domains; Gated MLA replaced by Gated DeepSeek Sparse Attention for cheaper long context. Versus K3: Terminal-Bench-family numbers move to the newer 4.0 harness (65.7, ahead of DeepSeek-V4.1-Flash-1017's 42.3 on the same card). Notable safety posture: Moonshot says it stripped hacking-related training data (TNW reports the open model still solves 81% of their cyber eval vs K3's 33.3%). Weights-after-API pattern again (blog Oct 23 → weights by Nov 4) — the HF repo (created Nov 2) is what made it trackable.

## See also

- [[welcome]]
- [[moonshotai--Kimi-K3]]
- Source: https://huggingface.co/moonshotai/Kimi-K3.1-Pro
- Tech blog: https://www.kimi.ai/blog/kimi-k3-1-pro
