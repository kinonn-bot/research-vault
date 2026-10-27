---
title: "inclusionAI Ling-3.1-flash-1019 (560B-A25B)"
org: inclusionAI
model_id: inclusionAI/Ling-3.1-flash-1019
date: 2026-10-28
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - hybrid
  - reasoning
  - long-context
  - dated-release
downloads: 0
likes: 54
license: mit
pipeline: text-generation
source: https://huggingface.co/inclusionAI/Ling-3.1-flash-1019
params: "25B active (560B total)"
context: "1048576 (1M)"
architecture: "hybrid-linear moe (63 KDA + 9 gated MLA at 7:1, 512 routed + 1 shared experts, top-8; custom bailing arch, trust_remote_code)"
---

# inclusionAI Ling-3.1-flash-1019 (560B-A25B)

**One-line:** Ant's dated GA of Ling-3.1-flash (weights 2026-10-27, MIT) — same 560B/25B hybrid-linear MoE, post-training gains claimed on AA-Briefcase (1524 Elo), AutomationBench-AA (68%) and AA Index v4.3.2 (44); ⚠ large and every number is lab-reported (AA profile is live and matches, but Speed is N/A — likely lab-fed, no independent repro yet).

> ⚠ All scores below are **lab-reported** (model card, 2026-10-27). Artificial Analysis has a live profile (`ling-3-1-flash-1019`) showing Intelligence Index 44 — consistent with the lab's claim — but with no Speed data and no verified-row breakdown yet, so treat the AA page as corroborating, not independent. No SWE-bench / LiveCodeBench / Aider / BFCL published. Predecessor deltas (vs Ling-3.1-flash): AA-Briefcase ~1400 → 1524, AutomationBench-AA 62% → 68%, CritPt 18% → 26%, SciCode 54% → 57%, AA Index 41 → 44.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (SWE-bench Pro used instead — no value stated on this card; predecessor 68.74) |
| SWE-bench Multilingual | — | not published |
| SciCode | 57 | *lab-reported* (vs predecessor 54) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| AA-Briefcase (Elo) | 1524 | *lab-reported* (vs predecessor ~1400) |
| AutomationBench-AA | 68% | *lab-reported* (vs predecessor 62%) |
| CritPt | 26% | *lab-reported* (vs predecessor 18%) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |
| AA Intelligence Index v4.3.2 | 44 | *lab-reported*; AA profile live and consistent (vs predecessor 41) |

## Efficiency

- **Active params:** 25B (560B total)
- **Context length:** 1048576 (1M) tokens
- **VRAM (fp8 rough):** ≈560 GB — 8×H200-class serving or wait for community quants; custom `bailing` arch needs repo model code (`trust_remote_code`)

## What makes it notable

Dated checkpoint re-release of Ling-3.1-flash (created 2026-10-27T05:46Z, 54 safetensors + index verified present), following the family's FP8-native pattern — no BF16 sibling, the main repo IS the shipped checkpoint. Gains over the 10-13 predecessor are all on AA-suite and science numbers, not the classic coding suite, so agent-loop relevance is inferred (AutomationBench, Briefcase) rather than measured (no SWE/BFCL). For local runs it is server-class only; the practical artifact to watch is the community quant wave.

## See also

- [[welcome]]
- Source: https://huggingface.co/inclusionAI/Ling-3.1-flash-1019
- Predecessor: https://huggingface.co/inclusionAI/Ling-3.1-flash
