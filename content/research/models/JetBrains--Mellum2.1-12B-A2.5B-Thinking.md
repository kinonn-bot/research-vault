---
title: "JetBrains/Mellum2.1-12B-A2.5B-Thinking"
org: JetBrains
model_id: JetBrains/Mellum2.1-12B-A2.5B-Thinking
date: 2026-10-09
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - tool-calling
  - moe
  - thinking
  - jetbrains
  - local
downloads: 110
likes: 32
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/JetBrains/Mellum2.1-12B-A2.5B-Thinking
params: "12B total / 2.5B active (64 experts, 8 activated; 28 layers; GQA 32/4)"
context: 131072
architecture: moe
---

# JetBrains/Mellum2.1-12B-A2.5B-Thinking

**One-line:** JetBrains' second-generation open coding-agent model — same 12B MoE / 2.5B-active architecture as Mellum2 Thinking, rebuilt around RL in real repository environments: SWE-bench Verified 47.0 (Mellum2 Thinking: 2.0), Terminal-Bench 2.1 17.4, BFCL v4 62.3, LiveCodeBench v6 82.0. Apache-2.0, 131k context, vLLM tool-calling recipe + GGUF builds — a genuine "fast sub-agent" candidate for local stacks.

Surfaced via org sweep + trending cross-check. Weights were uploaded quietly on 2026-09-20 (repo created + large-folder upload), but the public launch is **2026-10-07**: model card + full agentic eval table committed that day (12:13–23:08Z), aligned with the JetBrains AI blog post ("Mellum2.1 Gets to Work: A Fast Open Model for Coding Agents"), JetBrains' own GGUF repo (created 18:52Z), and bartowski/prithivMLmods GGUF + community FP8 variants following Oct 8. All benchmark values are self-reported by JetBrains (the card states "All values are self-reported by JetBrains"); no independent leaderboard listing yet.

## Coding benchmarks

*All lab-reported (JetBrains model card, one pipeline in thinking mode). Comparison columns as published on the card.*

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | 91.5 | lab — vs Qwen3.5-9B 89.6, Gemma 4 E4B 89.1 |
| MBPP+ | 79.4 | lab — vs Qwen3.5-9B 69.8, Gemma 4 E4B 70.9 |
| LiveCodeBench v6 | 82.0 | lab — leads comparison set (Qwen3.5-9B 75.4, Gemma 4 E4B 69.4, Mellum2 69.4) |
| Aider polyglot | — | not published |
| SWE-bench Verified | 47.0 | lab — vs Qwen3.5-9B 50.0, Gemma 4 E4B 23.0, Mellum2 2.0 |
| SWE-bench Pro | 28.0 | lab — vs Qwen3.5-9B 38.0, Gemma 4 E4B 4.0, Mellum2 0.0 |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench 2.1 | 17.4 | lab — vs Qwen3.5-9B 21.7, Gemma 4 E4B 3.4, Mellum2 0.6 |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL v4 | 62.3 | lab — leads comparison set (Qwen3.5-9B 58.5, Gemma 4 E4B 52.5, Mellum2 49.6) |
| WorkBench | 44.6 | lab |
| ToolHop | 49.1 | lab — vs Qwen3.5-9B 52.0 |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |

Agentic training provenance: "for software engineering, the model trains inside real repositories with a shell and file-editing tools and is rewarded when the tests pass" — millions of sandboxed runs during training; RL is now the main training stage (was a short final stage in Mellum2). Serving with tool calling: `vllm serve ... --reasoning-parser qwen3 --enable-auto-tool-choice --tool-call-parser hermes`.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU-Redux | 87.8 | lab |
| GPQA Diamond | 64.6 | lab — vs Qwen3.5-9B 77.8, Gemma 4 E4B 53.1 |
| MixEval-Hard | 46.4 | lab |
| AIME 25/26 | 83.3 | lab — vs Qwen3.5-9B 86.7, Gemma 4 E4B 45.0, Mellum2 60.1 |
| GSM-Plus | 88.3 | lab — vs Qwen3.5-9B 91.4 |
| IFEval | 90.6 | lab — vs Qwen3.5-9B 92.4 |
| XSTest (safe compliance) | 88.8 | lab |
| HarmBench (harmful rate, lower is better) | 8.5 | lab |

## Efficiency

- **Active params:** 2.5B active / 12B total (28 layers, hidden 2304, intermediate 7168, MoE intermediate 896, 64 experts / 8 activated, GQA 32 Q / 4 KV, vocab 98,304, bf16)
- **Context length:** 131,072 (sliding window 1,024 on 3 of every 4 layers)
- **VRAM (fp16 rough):** ~24 GB BF16 — fits a 32 GB card natively; 24 GB cards need a quant (GGUF builds for llama.cpp/Ollama/LM Studio exist; MTP head for vLLM speculative decoding listed as coming soon)
- **Runtime:** standard arch (transformers/vLLM); official GGUF sibling repo `JetBrains/Mellum2.1-12B-A2.5B-Thinking-GGUF`; community GGUF (bartowski, prithivMLmods) + FP8 variants already out

## What makes it notable

For local coding-agent stacks this is a drop-in fast sub-agent layer: 2.5B active per token with a 131k window, Apache-2.0, first-party vLLM tool-calling support, ~24 GB BF16 (or quantized below that). The RL-in-real-repos recipe produced a step-change over Mellum2 on every agentic axis — SWE-bench Verified 2.0 → 47.0, Terminal-Bench 2.1 0.6 → 17.4, SWE-bench Pro 0.0 → 28.0, BFCL v4 49.6 → 62.3 — while staying competitive with Qwen3.5-9B: it leads on LiveCodeBench v6 (82.0 vs 75.4) and BFCL v4 (62.3 vs 58.5), trails on Terminal-Bench 2.1 (17.4 vs 21.7) and SWE-bench Verified (47.0 vs 50.0). Caveats: all figures self-reported, non-agentic knowledge scores are mid-pack (GPQA-D 64.6), and downloads are still low because the public launch is <48h old at first tracking.

## See also

- [[welcome]]
- Source: https://huggingface.co/JetBrains/Mellum2.1-12B-A2.5B-Thinking
- Blog: https://blog.jetbrains.com/ai/2026/10/mellum2-1-gets-to-work-a-fast-open-model-for-coding-agents/
- GGUF: https://huggingface.co/JetBrains/Mellum2.1-12B-A2.5B-Thinking-GGUF
- Predecessor: https://huggingface.co/JetBrains/Mellum2-12B-A2.5B-Thinking
- Mellum2 technical report: https://arxiv.org/abs/2605.31268
