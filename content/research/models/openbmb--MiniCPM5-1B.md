---
title: "OpenBMB MiniCPM5-1B"
org: openbmb
model_id: openbmb/MiniCPM5-1B
date: 2026-08-18
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - dense
  - instruct
  - on-device
  - tool-calling
  - long-context
  - local
downloads: 1086153
likes: 1066
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/openbmb/MiniCPM5-1B
params: "1.08B dense (1,080,632,832 total; 679.6M non-embedding)"
context: "131072 (128K native)"
architecture: dense (LlamaForCausalLM, GQA 16Q/2KV, 24 layers, head_dim 128)
---

# OpenBMB MiniCPM5-1B

**One-line:** 1B-class open-source SOTA on-device model (OpenBMB/Tsinghua NLP + ModelBest) — AA Intelligence Index 17.9, the top open-weight model at ≤1B params by 7.4 pts — with hybrid think/no-think modes, native XML tool calling, and 128K context. ⚠ not a new release (weights dropped 2026-05-19); surfaced via the trending window (08-17 repo touch = card/packaging update, no new checkpoint per GitHub changelog, latest commit 07-27).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published (lab table is image-only) |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |

*The lab's comparison table is a single image (GitHub asset `public_leaderboard_en.png`) and the repo ships no `.eval_results/` YAMLs — no per-benchmark coding numbers in extractable form. Cells left `—` rather than invented.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| AA Agentic Index | — | not published (agentic strength claimed in AA composite only) |

*Lab claims its advantage is "most visible in agentic tool use, code, and competition math"; average 42.57 across reasoning/knowledge/code/instruction-following/math/logic/agentic benchmarks vs 35.61 best for strong open-source models in the same size class — lab-reported, italicized, no independent per-benchmark split found. Tool calling is real and first-class: XML-style calls, native `minicpm5` parser in SGLang, vLLM tool-parser plugin — suitable for agent loops on tiny hardware.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| AA Intelligence Index | 17.9 | Artificial Analysis (independent — highest open-weight score at ≤1B params, +7.4 over Qwen3.5-0.8B Reasoning 10.5; beats Qwen3.5-2B Reasoning 16.3 at under half the params) |
| AA-Omniscience | -1 | Artificial Analysis (independent — best in class, earned by abstaining rather than hallucinating; sub-2B peers sit at -70 to -89) |
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published (part of AA composite only) |
| MATH / AIME | — | lab table image-only |

## Efficiency

- **Active params:** 1.08B dense (no MoE, all active)
- **Context length:** 131,072 tokens (128K native, no rope scaling needed)
- **VRAM (fp16 rough):** ~2.2 GB weights (2.16 GB safetensors); q4 quant ~0.9 GB with 1–3% accuracy loss (lab-reported); ~200 ms inference on a modern laptop (AA/LinkedIn reporting)
- **Runs on:** llama.cpp (GGUF), Ollama, LM Studio, MLX (4-bit, Apple Silicon), vLLM (≥0.21), SGLang (≥0.5.12, recommended for tool calling), Transformers ≥5.6 — standard `LlamaForCausalLM`, no custom kernels/model-code fork needed

## What makes it notable

MiniCPM5-1B extends the open-weights Pareto frontier for Intelligence-vs-Params at the sub-2B scale: 17.9 AA Intelligence Index with dense 1B params beats every open model ≤2B and nearly matches Qwen3.5-2B with half the parameters. Post-training is RL + On-Policy Distillation on OpenBMB's UltraData tiered corpus (SFT 200B deep-thinking + 200B hybrid-thinking tokens), and the same checkpoint serves both fast assistant and deliberate reasoner via `enable_thinking`. For local agent loops this is the strongest genuinely tiny tool-calling model: 128K context, XML tool calls with first-class SGLang/vLLM parsers, and an agent-skills/cookbook ecosystem (Cursor/Claude Code style, Ollama, desktop pet) maintained by the lab. Watch that it is text-only (no native multimodal input) and that the headline 42.57 average is lab-reported with the detail chart image-only — treat specific coding/agent numbers as unverified until third-party splits appear. For the local runner: fits in ~1–2 GB, deployable on CPU, M-series, or any small GPU.

## See also

- [[welcome]]
- Source: https://huggingface.co/openbmb/MiniCPM5-1B
- GitHub: https://github.com/openbmb/minicpm
- Artificial Analysis: https://artificialanalysis.ai/models/minicpm5-1b