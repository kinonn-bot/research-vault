---
title: "OpenBMB MiniCPM5-2B"
org: openbmb
model_id: openbmb/MiniCPM5-2B
date: 2026-09-14
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - dense
  - instruct
  - reasoning
  - tool-calling
  - long-context
  - local
  - on-device
downloads: 150110
likes: 1328
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/openbmb/MiniCPM5-2B
params: "2.52B dense (2,516,756,480 total; 1,981,982,720 non-embedding)"
context: "131072 (128K native)"
architecture: dense (LlamaForCausalLM, GQA 16Q/2KV, 42 layers, hidden 2048, bf16)
---

# OpenBMB MiniCPM5-2B

**One-line:** 2.5B dense follow-up to MiniCPM5-1B (OpenBMB/Tsinghua NLP + ModelBest) — AA Intelligence Index v4.2 score of 15, the highest of any open-weight model under 4B total params (v4.1.1: 23), with class-leading agentic/coding numbers (SWE-bench Verified 46.4, LiveCodeBench v6 69.1, BFCL v4 66.6) at a size that runs fully on-device. Released ~2026-09-07 (repo created 09-06; launch coverage 09-07), surfaced via the trending window (lastModified 09-12).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 69.1 (v6) | lab (internally reproduced) |
| LCB-Pro 25Q2 Easy / Medium | 68.0 / 17.5 | lab |
| OJBench | 32.5 | lab |
| SciCode (wbg) | 26.3 | Artificial Analysis (†) — 2nd of the 5-model set, behind Granite 4.2 8B (31%) per AA article |
| Aider polyglot | — | not published |
| SWE-bench Verified | 46.4 | lab (internally reproduced) — vs 33.6 Qwen3.5-4B, 36.8 granite-4.2-3B, 6.0 LFM2.5-2.6B |
| SWE-bench Pro | 14.4 | lab |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench v2.1 | 8.6 | Artificial Analysis (†) — 8th in the measured set per AA article |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | 66.6 (v4) | lab (internally reproduced) — vs 61.1 LFM2.5-2.6B, 56.8 Qwen3.5-4B |
| τ-Bench | 97.1 (τ² Telecom), 20.8 (τ³ Banking †) | lab telecom / Artificial Analysis banking |
| ToolACE | — | not published |
| GAIA | 88.7 (Text-103) | lab |
| GDPval-AA v2 | Elo 831 (19.6) | Artificial Analysis (†) — ~110 pts ahead of Ling 3.0 Tiny (718), ~180 ahead of Granite 4.2 8B (647) |
| AA-LCR | 59.0 | Artificial Analysis (†) — 5th, one pt behind Ling 3.0 Tiny (60) |
| Claw-Gym / WildClaw / QwenClaw | 59.2 / 23.9 / 42.9 | lab (OpenClaw-family agent suites) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| AA Intelligence Index (v4.2 / v4.1.1) | 15 / 23 | Artificial Analysis (independent) — highest of any open model under 4B total params |
| MMLU-Pro | 70.8 | lab |
| GPQA Diamond | 70.2 | Artificial Analysis (†) |
| MATH-500 | 94.6 | lab |
| AIME 2025 / AIME 2026 | 86.5 / 86.5 | lab |
| HMMT Feb 2026 | 63.8 | lab |
| Humanity's Last Exam | 8.9 | Artificial Analysis (†) — 7th in the measured set per AA article |

## Efficiency

- **Active params:** 2.52B dense (no MoE, all active; 1.98B non-embedding)
- **Context length:** 131,072 tokens (128K native)
- **VRAM (fp16 rough):** ~5.0 GB weights (2.52B × 2 bytes); official GGUF repo (`openbmb/MiniCPM5-2B-GGUF`) with 4-bit ≈ ~1.5 GB; MLX 4-bit for Apple Silicon
- **Runs on:** vLLM, SGLang, Transformers, llama.cpp (GGUF), Ollama, LM Studio, MLX, FlagOS — standard `LlamaForCausalLM`, no custom kernels needed

## What makes it notable

MiniCPM5-2B is the strongest open-weight model at ≤2.5B params across both coding and agentic suites: 46.4 SWE-bench Verified is 12.8 pts over Qwen3.5-4B (33.6) — the first sub-3B model with meaningful repo-level agent coding — and BFCL v4 66.6 leads the 2B (and most 4B) class. AA's independent Index agrees: 15 on v4.2 is the best under 4B total params, with clear agentic signal (GDPval-AA Elo 831, AA-LCR 59) and 128K native context. Same hybrid think/no-think, RL + on-policy-distillation UltraData recipe as MiniCPM5-1B but with a much stronger agentic profile — the natural default for local tool-using agents on laptops/SBC-class hardware. Caveats: per-benchmark numbers are lab-reproduced unless † (AA-sourced); Aider polyglot and τ-Bench main set are unpublished, and Text-103 GAIA-type results are lab-only. SWE-bench Verified 46.4 at 2.5B should be treated as lab-reported until third-party reproduction.

## See also

- [[welcome]]
- Source: https://huggingface.co/openbmb/MiniCPM5-2B
- GGUF: https://huggingface.co/openbmb/MiniCPM5-2B-GGUF
- Artificial Analysis: https://artificialanalysis.ai/models/minicpm5-2b
- Artificial Analysis release note: https://artificialanalysis.ai/articles/openbmb-releases-minicpm5-2b
- Sibling: [[openbmb--MiniCPM5-1B]]