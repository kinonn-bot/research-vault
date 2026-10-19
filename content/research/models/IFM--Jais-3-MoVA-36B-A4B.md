---
title: "IFM Jais-3-MoVA-36B-A4B"
org: IFM
model_id: IFM/Jais-3-MoVA-36B-A4B
date: 2026-10-20
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - multilingual
  - arabic
  - long-context
  - tool-use
  - ifm
  - k2-horizon
downloads: 1374
likes: 9
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/Jais-3-MoVA-36B-A4B
params: "36B stored / 4B active (recipe page shows 37.44B / 5.95B — embeddings counted differently)"
context: "524,288 (512K tokens)"
architecture: "sparse MoE with Mixture-of-Values attention, 36B-A4B (custom code — model_type k2_horizon, K2HorizonForCausalLM)"
---

# IFM Jais-3-MoVA-36B-A4B

**One-line:** The efficient member of the Jais-3 (Arabic-native K2 Horizon) fleet — 36B stored / 4B active MoE that posts the family's best agentic numbers (SWE-bench Verified offline 72.8, Terminal-Bench 2.1 67.3, MCPMark 69.3) within a ~75 GB bf16 footprint (TP=2), so roughly Qwen3.8-27B-class repo work at MoE serving cost. All numbers vendor-reported; no third-party replication.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 72.8 (Offline, Pass@1) | lab card, lab-reported — vs Jais-3-32B 72.4, Qwen3.8-27B 73.5, Muse-Glimmer-30B 71.4, Gemma-4-31B-it 59.0 |
| SWE-bench Multilingual | — | not published |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA (GAIA v2 lit, Arabic) | 51.5 (Pass@1) | lab — ties Jais-3-32B; vs Qwen3.8-27B 55.8 |
| Terminal-Bench 2.1 | 67.3 (Avg@3) | lab — vs Jais-3-32B 63.7, Qwen3.8-27B 79.8 |
| MCPMark | 69.3 (Pass@1) | lab — vs Jais-3-32B 66.1, Qwen3.8-27B 49.6 |
| GDPVal (@75% threshold) | 67.7 | lab — Qwen3.8-27B 78.2 |
| BrowseComp-Plus | 71.8 | lab — vs Qwen3.8-27B 53.0 |
| WildClawBench (EN text-only subset) | 40.3 (mean @3) | lab |
| Apex-Agents (420 text-only subset, loop agent) | 23.6 (Pass@1) | lab — weak spot, slightly below Jais-3-32B 25.2 |
| Arabic File Processing (@75% threshold) | 52.3 | lab |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| Arabic MMLU (cleaned Arabic set) | 87.7 | lab — not a standard MMLU score |
| Dialectal Arabic MMLU | 87.3 | lab |
| Arabic MMLU with diacritics | 86.8 | lab |
| IFBench (Arabic, prompt-level strict) | 92.0 | lab — best in the family (32B 88.7) |
| Arabic GSM8K | — | not published on this card |
| GPQA Diamond | — | not published |
| MATH | — | not published |

## Efficiency

- **Active params:** 4B active / 36B stored (recipe page: 5.95B / 37.44B) — MoE, so serving cost tracks active params while VRAM tracks stored params
- **Context length:** 524,288 tokens (512K)
- **VRAM (fp16 rough):** ~75 GB bf16 for all experts resident (IFM recipe: `--tensor-parallel-size 2` with expert parallelism enabled); FP8 build ≈38 GB; GGUF and MLX builds published in the same org, so a single-GPU or Mac Studio path exists at reduced precision
- **Custom architecture:** `model_type: k2_horizon` with remote code, and MoVA attention means vLLM/SGLang recipes (rather than stock transformers) are the practical path
- **Serving:** vLLM ≥0.30 — `--reasoning-parser k2_horizon`, `--tool-call-parser k2_horizon` (`json` / `xml` / `xml_typed`, default `xml`), `reasoning_effort` per request (default `high`); language-dependent sampling (temp 1.0 English vs 0.7 Arabic in thinking mode); ≥32K output budget recommended

## What makes it notable

The best agent-harness numbers IFM has published for an Arabic-native open model, at a footprint a two-GPU box can serve — and it beats its own 32B dense sibling on every agentic row except Apex-Agents. Read against Qwen3.8-27B it is a tool-selection-first model: MCPMark 69.3 vs 49.6 and BrowseComp-Plus 71.8 vs 53.0, while giving up 12.5 points on Terminal-Bench 2.1. Caveats: SWE-bench numbers are "offline" harness runs, all rows are vendor-reported with no independent replication, the benchmark suite is IFM's own audited Arabic set, and the card's param counts disagree with the recipe page's (36B/4B vs 37.44B/5.95B).

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/Jais-3-MoVA-36B-A4B
- Family: [[IFM--Jais-3-32B]], [[IFM--K2-Horizon-MoVA-36B-A4B]], https://huggingface.co/IFM/Jais-3-375B-A23B
- Deploy: https://huggingface.co/IFM/Jais-3-MoVA-36B-A4B-GGUF · https://huggingface.co/IFM/Jais-3-MoVA-36B-A4B-FP8
- Lab blog: https://ifm.ai/blog/jais3/
