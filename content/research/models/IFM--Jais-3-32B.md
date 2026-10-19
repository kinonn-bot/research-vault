---
title: "IFM Jais-3-32B"
org: IFM
model_id: IFM/Jais-3-32B
date: 2026-10-20
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - multilingual
  - arabic
  - long-context
  - tool-use
  - ifm
  - k2-horizon
downloads: 1855
likes: 6
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/IFM/Jais-3-32B
params: "32B dense"
context: "524,288 (512K tokens)"
architecture: "dense decoder-only, K2 Horizon base (custom code — model_type k2_horizon, K2HorizonForCausalLM)"
---

# IFM Jais-3-32B

**One-line:** IFM/MBZUAI + Inception42's Arabic-native 32B dense model (K2 Horizon adapted to Arabic), Apache 2.0 with a 512K context — SWE-bench Verified (offline) 72.4 and Terminal-Bench 2.1 63.7 put it within ~1pp of Qwen3.8-27B on repo work while leading it on tool-use harnesses (MCPMark 66.1 vs 49.6); every number is vendor-reported and the Arabic eval suite is their own audited set, not standard lanes.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 72.4 (Offline, Pass@1) | lab card, lab-reported — vs Qwen3.8-27B 73.5, Muse-Glimmer-30B 71.4, Gemma-4-31B-it 59.0, Falcon-H1-34B-Instruct 0.4; BenchLM lists the same row (provider-exact, unranked) |
| SWE-bench Multilingual | — | not published |

*The card's agentic section is table-image/HTML only in the HF card; values above were parsed from that table's HTML. It publishes no HumanEval / MBPP / LiveCodeBench / Aider number at all, so this is an agent-harness-first eval suite.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA (GAIA v2 lit, Arabic) | 51.5 (Pass@1) | lab — vs Qwen3.8-27B 55.8, Gemma-4-31B-it 42.4 |
| Terminal-Bench 2.1 | 63.7 (Avg@3) | lab — vs Qwen3.8-27B 79.8, Muse-Glimmer-30B 51.7, Gemma-4-31B-it 43.5; BenchLM sources this row |
| MCPMark | 66.1 (Pass@1) | lab — vs Qwen3.8-27B 49.6, Gemma-4-31B-it 48.8 |
| GDPVal (@75% threshold) | 75.5 | lab — vs Qwen3.8-27B 78.2 |
| BrowseComp-Plus | 71.9 | lab — vs Qwen3.8-27B 53.0 |
| WildClawBench (EN text-only subset) | 42.0 (mean @3) | lab |
| Apex-Agents (420 text-only subset, loop agent) | 25.2 (Pass@1) | lab — the honest weak spot; Qwen3.8-27B 28.6 |
| Arabic File Processing (@75% threshold) | 71.8 | lab — vs Gemma-4-31B-it 4.5 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| Arabic MMLU (cleaned Arabic set) | 88.6 | lab — not a standard MMLU score |
| AraSTEM | 95.2 | lab |
| Arabic GSM8K | 94.3 | lab |
| GATmath | 98.5 | lab |
| IFBench (Arabic, prompt-level strict) | 88.7 | lab — vs Gemma-4-31B-it 80.8 |
| Arabic IFEval | 80.0 | lab |
| AA-LCR (Arabic, long context) | 75.0 | lab — vs Qwen3.8-27B 79.0 |
| FLORES200+ (LLM-as-judge translation) | 91.5 | lab |
| HalluScore | 67.3 | lab |
| SimpleQA Verified (Arabic, aggregate) | 28.1 | lab |

## Efficiency

- **Active params:** 32B dense (no MoE)
- **Context length:** 524,288 tokens (512K); the 0.9B sibling is 128K only
- **VRAM (fp16 rough):** ~64 GB bf16 — IFM's vLLM recipe uses `--tensor-parallel-size 2` (2×80 GB). FP8 build ≈32 GB; GGUF (`IFM/Jais-3-32B-GGUF`, llama.cpp/Ollama) and MLX 4-bit/8-bit/bf16 builds for Apple silicon are already published. BenchLM estimates a self-host floor of ~24 GB (quantized path).
- **Custom architecture:** `model_type: k2_horizon` / `K2HorizonForCausalLM` with remote code — stock transformers for other archs will not load it; use the repo's own model code or a framework that ships it.
- **Serving:** vLLM ≥0.30 (`--reasoning-parser k2_horizon`, `--tool-call-parser k2_horizon` with `json`/`xml`/`xml_typed` formats, default `xml`) and SGLang ≥0.5.20 recipes were checked in ~10 days *before* the 15 Oct press release. Reasoning depth is a per-request `reasoning_effort` (default `high`; every published number assumes it). Sampling is language-dependent — temp 0.2 / top_p 0.95 / top_k 20 default, temp 1.0 English vs 0.7 Arabic in thinking mode. Card recommends ≥32,768 output tokens, so budget long traces.
- **Family:** Jais-3-0.9B / 3.7B / 7B / 32B dense, MoVA-36B-A4B, 375B-A23B — same recipe and tool-calling format; separate `Jais-ASR` speech model in the same org.

## What makes it notable

The first adaptation of IFM's K2 Horizon fleet to a new language, and the first open model family that publishes an *agentic* eval suite as its headline (SWE-bench offline, Terminal-Bench 2.1, MCPMark, GDPVal, BrowseComp-Plus, GAIA-Arabic) rather than MMLU. For a local agent loop the interesting cell is the pair (SWE-bench Verified 72.4, MCPMark 66.1): near-Qwen3.8-27B repo performance with clearly *better* tool-selection harness scores, at 32B dense and Apache 2.0 with no gating and day-zero vLLM/SGLang/GGUF/MLX builds. Limits to weigh: Terminal-Bench 2.1 is 16 points behind Qwen3.8-27B, Apex-Agents (loop-agent subset) is only 25.2, the Arabic benchmark suite is IFM's own audited set and not comparable to standard MMLU/GSM8K/IFEval lanes, and no third party has reproduced any number (Artificial Analysis has no entry; BenchLM carries only the two model-card rows).

## See also

- [[welcome]]
- Source: https://huggingface.co/IFM/Jais-3-32B
- Family: https://huggingface.co/collections/IFM/jais-3-6abba9df4f1173ec7ce2929d
- Siblings: [[IFM--K2-Horizon-32B]], https://huggingface.co/IFM/Jais-3-375B-A23B, https://huggingface.co/IFM/Jais-3-MoVA-36B-A4B
- Deploy: https://huggingface.co/IFM/Jais-3-32B-GGUF · https://huggingface.co/IFM/Jais-3-32B-FP8
- Independent coverage: https://benchlm.ai/models/jais-3-32b (2 source-linked rows, unranked)
- Lab blog: https://ifm.ai/blog/jais3/
