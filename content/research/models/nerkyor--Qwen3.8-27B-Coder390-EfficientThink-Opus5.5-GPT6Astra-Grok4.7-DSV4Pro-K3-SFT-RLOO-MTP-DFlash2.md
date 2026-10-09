---
title: "nerkyor/Qwen3.8-27B-Coder390-EfficientThink-Opus5.5-GPT6Astra-Grok4.7-DSV4Pro-K3-SFT-RLOO-MTP-DFlash2"
org: nerkyor
model_id: nerkyor/Qwen3.8-27B-Coder390-EfficientThink-Opus5.5-GPT6Astra-Grok4.7-DSV4Pro-K3-SFT-RLOO-MTP-DFlash2
date: 2026-10-10
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - reasoning
  - community
  - rl
  - sft-rloo
  - vision-language
  - speculative-decoding
  - gguf
  - qwen
downloads: 8873
likes: 115
license: apache-2.0
pipeline: image-text-to-text
source: https://huggingface.co/nerkyor/Qwen3.8-27B-Coder390-EfficientThink-Opus5.5-GPT6Astra-Grok4.7-DSV4Pro-K3-SFT-RLOO-MTP-DFlash2
params: "27B dense"
context: "262,144 (base spec; author evals ran at 100K context with a 94,208-token generation cap)"
architecture: "hybrid (linear + full attention, dense), natively multimodal; bundled MTP head + DFlash2 draft"
---

# nerkyor/Qwen3.8-27B-Coder390-EfficientThink-Opus5.5-GPT6Astra-Grok4.7-DSV4Pro-K3-SFT-RLOO-MTP-DFlash2

**One-line:** Community post-train of Qwen3.8-27B aimed at a failure mode that matters in agent loops — the base's habit of re-deriving past the 94K generation cap and returning an empty answer; the Coder390 build cuts LCB 94K-truncations 13→3 and lifts LiveCodeBench 83→90/100 with no GPQA/MMLU regression, shipping five precision tiers plus INT8/INT4/GGUF Q2–Q8 with speculative decoding.

⚠ Everything below is **author-reported** (single-author eval protocol: SGLang on 2× RTX PRO 6000, C8, 100K context, 94,208-token generation cap, no client timeout; empty = wrong, truncated-but-correct = correct, failed samples stay in the denominator). No independent evaluation. Community provenance: post-trained through the author's own SFT/RLOO pipeline, and an ancestor checkpoint is an "Uncensored" variant. Not a Qwen release. `pipeline_tag` is `image-text-to-text` (native VL) but it publishes coding evals, so it qualifies for this tracker.

## Coding benchmarks

*All author-run (card "Scores" section; BF16 / static FP8 tiers unless noted). "Original" = official Qwen/Qwen3.8-27B FP8 under the same protocol.*

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 90/100 (original: 83/100) | author — 100-problem protocol |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |

Truncation fix (the headline): 94K-cap hits drop 13 → 2–4 on LCB and 4 → 1–2 on GPQA across plain tiers; on the original, all 13 LCB truncations ended with empty code, on Coder390 tiers 2–4 do. LCB reasoning length P50: 8,388 → ~4,500–5,100 tokens.

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU | 450/500 (original: 444) | author — static FP8 |
| GPQA Diamond | 178/198 (original: 177) | author — static FP8 |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** 27B dense (plus vision encoder) — same family as base Qwen3.8-27B
- **Context length:** 262,144 base spec; author protocol ran at 100K with a 94,208-token generation cap
- **VRAM (fp16 rough):** ~54 GB BF16 package (55.6 GB on disk); static FP8 ≈31 GB; NVFP4 tiers ≈21–24 GB; INT8 W8A8 ≈30 GB; INT4 W4A16 ≈19 GB; GGUF Q2/Q3/Q4 LynnStyle + Q6_K + Q8_0 for llama.cpp (vision via mmproj)
- **Runtime:** SGLang patch-free for all safetensors tiers; FP8 smoke-tested on vLLM 0.28; NVFP4/DFlash2 validated on SGLang only; INT8/INT4 on vLLM; GGUF on llama.cpp + NInfer. Single-request speed, author-measured: ≈180 tok/s with DFlash2, ≈91 tok/s with MTP, ≈46 tok/s without speculation (BF16, 2× RTX PRO 6000)

## What makes it notable

For anyone running Qwen3.8-27B in a tool-using loop, this targets the failure that wastes the most context: the base keeps re-deriving an answer it already has until it fills the window and emits empty output. Under a fixed protocol the Coder390 build cuts those truncations 13→3 on LCB (4→1 on GPQA) and lifts LCB to 90/100 while MMLU and GPQA stay at or above the original — with the author's own limitation notes (long-tail ≥48K reasoning accuracy still lower; 3 LCB problems still cap out). It is also the most deployment-friendly packaging of this base seen here: five precision tiers, INT8/INT4, GGUF Q2–Q8, bundled MTP head + DFlash2 draft, and a sibling GGUF-NInfer repo already at ~16k downloads. Caveats: every number is author-run with no independent eval, the lineage passes through an "Uncensored" variant, and it is a community artifact — verify before trusting in production routing.

## See also

- [[welcome]]
- Source: https://huggingface.co/nerkyor/Qwen3.8-27B-Coder390-EfficientThink-Opus5.5-GPT6Astra-Grok4.7-DSV4Pro-K3-SFT-RLOO-MTP-DFlash2
- GGUF / GGUF-NInfer sibling: https://huggingface.co/nerkyor/Qwen3.8-27B-Coder390-EfficientThink-Opus5.5-GPT6Astra-Grok4.7-DSV4Pro-K3-SFT-RLOO-GGUF-NInfer
- NVFP4-NInfer sibling: https://huggingface.co/nerkyor/Qwen3.8-27B-Coder390-EfficientThink-Opus5.5-GPT6Astra-Grok4.7-DSV4Pro-K3-SFT-RLOO-NVFP4-NInfer
- Base: https://huggingface.co/Qwen/Qwen3.8-27B
