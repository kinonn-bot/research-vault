---
title: "Qwen/Qwen3.8-27B"
org: Qwen
model_id: Qwen/Qwen3.8-27B
date: 2026-08-15
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - hybrid
  - vision-language
  - instruct
  - mtp
  - local-friendly
downloads: 91917
likes: 9703
license: apache-2.0
pipeline: image-text-to-text
source: https://huggingface.co/Qwen/Qwen3.8-27B
params: "27B dense"
context: "262,144 tokens (up to 1M via YaRN)"
architecture: hybrid (linear + full attention, dense)
---

# Qwen/Qwen3.8-27B

**One-line:** The open-weight member of the Qwen3.8 generation — a 27B dense hybrid-attention model with a surprise vision encoder, shipped Apache-2.0 on Aug 13-14; head and shoulders above Qwen3.6-27B on agentic coding (Terminal Bench 2.1 73.0 vs 63.4, SWE-bench Pro 61.7 vs 53.5). ⚠ note: pipeline is `image-text-to-text` (native VL), but it has published coding/agentic evals, so it qualifies for this tracker. All numbers below are lab-reported from the Qwen card (BenchLM independently echoes SWE-bench Pro 61.7 / Terminal-Bench 2.1 73.0).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | *90.3* | *lab-reported, v6 (Qwen3.6-27B 83.9, Qwen3.7-Plus 89.6)* |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (stand-in: SWE-bench Pro 61.7 below) |
| SWE-bench Multilingual | — | not published |
| SWE-bench Pro | *61.7* | *lab-reported (Qwen3.6-27B 53.5, Qwen3.7-Plus 57.6, Muse Glimmer-30B 51.2)* |
| Terminal Bench 2.1 | *73.0* | *lab-reported (Qwen3.6-27B 63.4, Qwen3.7-Plus 64.0, Opus4.6 Max 78.2)* |
| NL2Repo | *42.3* | *lab-reported (Qwen3.6-27B 36.2)* |
| DeepSWE 1.1 | *42.2* | *lab-reported (Qwen3.6-27B 13.3)* |
| QwenSWEBench | *79.0* | *lab-reported, in-house benchmark, Claude Code harness* |
| SWE-MM | *38.6* | *lab-reported, multimodal software engineering* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Agents' Last Exam | *20.4 pass@1 (42.9 score)* | *lab-reported* |
| OSWorld-Verified | *84.3* | *lab-reported (Qwen3.6-27B 63.9)* |
| WebArena-Verified | *64.8* | *lab-reported (Qwen3.6-27B 48.8)* |
| AndroidWorld | *81.9* | *lab-reported (Qwen3.6-27B 70.3)* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | *89.2* | *lab-reported (Qwen3.6-27B 87.8, Qwen3.7-Plus 90.3)* |
| MATH | — | not published |
| AIME 2025 | — | not published |
| HLE | *30.8* | *lab-reported* |
| IFBench | *79.5* | *lab-reported* |

## Efficiency

- **Active params:** 27B dense (64 layers, hidden 5120 — no MoE)
- **Context length:** 262,144 native; extensible to 1M via YaRN scaling
- **VRAM (fp16 rough):** ~54 GB → consumer GPUs need GGUF/int4 quant; the FP8 sibling (Qwen3.8-27B-FP8, 123k downloads) is the practical local pick
- **Architecture note:** Qwen3.5-style hybrid — linear attention interleaved with full attention (1 full per 4 layers) + MTP. Faster long-context inference than pure dense attention. Vision encoder present (native image/video understanding).

## What makes it notable

This is the local-runner's release of the Qwen3.8 generation: 27B dense, Apache-2.0, 262k native context, and the strongest published agentic-coding numbers of any open 27B-class model (SWE-bench Pro 61.7 and Terminal Bench 2.1 73.0 both beat Qwen3.7-Plus, the closed API model). The hybrid attention makes it cheaper to serve at long context than a plain dense 27B. Caveats: numbers are all lab-reported (no independent run yet), it ships as a VL model (vision encoder adds VRAM/complexity for text-only use), and SWE-bench Verified / BFCL are absent — the agentic claim rests on SWE-bench Pro + Terminal Bench 2.1. If you only care about text/coding, the community was already mass-producing GGUF/FP8 builds within 24h of the drop (a strong signal the weights are real and runnable).

## See also

- [[welcome]]
- [[Qwen--Qwen3.8-2.4T-A95B]]
- Source: https://huggingface.co/Qwen/Qwen3.8-27B
