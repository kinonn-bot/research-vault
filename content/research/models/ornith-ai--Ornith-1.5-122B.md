---
title: "Ornith 1.5 122B"
org: ornith-ai
model_id: ornith-ai/Ornith-1.5-122B
date: 2026-10-21
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - instruct
  - reasoning
  - tool-use
  - large
  - ornith
downloads: 32
likes: 70
license: mit
pipeline: text-generation
source: https://huggingface.co/ornith-ai/Ornith-1.5-122B
params: "122B total / 125.1B BF16 params; active count unreported (256 experts, top-8 routed + shared)"
context: "262,144 (256k tokens)"
architecture: "moe — Qwen3.5-MoE base (Qwen3_5MoeForConditionalGeneration), 48 layers, 3 linear-attention layers per full-attention layer, 1 MTP head"
---

# Ornith 1.5 122B

**One-line:** The 122B MoE member of Ornith's self-improving 1.5 family — MIT weights, 256k context, and lab-reported SWE-bench Verified 84.5 / SWE-bench Pro 76.9 / Terminal-Bench 2.1 81.2 that top Qwen3.8-Flash-Next at the same ~125B scale, with day-one GGUF/FP8/MLX/NVFP4 builds and a card claim of single-80GB-GPU serving; ⚠ >70B and every number is lab-reported (no independent eval yet).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 84.5 (non-hack) | lab card, lab-reported — OpenHands harness, 256K eval context, anti-hacking safeguards; vs Qwen3.8-Flash-Next-125B 82.8, Qwen3.8-27B 76.8, Nemotron 3.5 Super VL-120B 61.2 |
| SWE-bench Pro (no-hack) | 76.9 | lab — vs Qwen3.8-27B 65.5, Qwen3.8-Flash-Next 43.9, Nemotron Super VL 42.5, Beam 57.0 |
| SWE-bench Multilingual (non-hack) | 76.4 | lab — vs Qwen3.8-Flash-Next 73.0, Qwen3.8-27B 70.3, Nemotron Super VL 48.0 |
| Terminal-Bench 2.1 | 81.2 | lab — Claude Code 2.1.126 harness, 5-run average; vs Qwen3.8-Flash-Next 83.4, DeepSeek-V4-Flash-0731 82.7, Beam 80.1, Qwen3.8-27B 71.9 |
| CyberGym | 80.0 | lab — vs Qwen3.8-Flash-Next 78.0, DeepSeek-V4-Flash-0731 76.7, Qwen3.8-27B 55.0 |
| NL2Repo | 51.2 | lab — 400K eval context, repos/pip blocked to prevent reward hacking; vs DeepSeek-V4-Flash-0731 54.2, Beam 49.4 |

*The card publishes its eval suite as an HTML table (no image OCR needed); values cross-checked against BenchLM's mirror of the same rows, which are identical and explicitly flagged "outside general rankings". No HumanEval/MBPP/LiveCodeBench/Aider number is published at all — this is an agent-harness-first card.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| MCP-Atlas | 74.6 | lab — thinking mode, 500-task public subset, 10-min task timeout, Claude 4.8 Opus judge; vs Qwen3.8-Flash-Next 74.1, DeepSeek-V4-Flash-0731 74.6, Qwen3.8-27B 69.0 |
| Toolathlon-Verified | 70.8 | lab — official eval service, 128K token limit; vs Qwen3.8-Flash-Next 71.4, Qwen3.8-27B 67.1, Nemotron Super VL 60.1 |
| ClawEval | 79.4 | lab — agentic code benchmark over real-user task distributions, temp 0.6, 256K context; vs Qwen3.8-Flash-Next 76.5, Qwen3.8-27B 75.4 |
| WideSearch | 75.2 | lab — vs DeepSeek-V4-Flash-0731 77.3, Qwen3.8-Flash-Next 71.8, Nemotron Super VL 69.2 |
| BrowseComp | 78.5 | lab — vs DeepSeek-V4-Flash-0731 80.2, Qwen3.8-Flash-Next 75.3, Nemotron Super VL 61.0 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |
| HLE (with tools) | 48.0 | lab — Claude 4.6 Opus judge; vs Beam 51.1, DeepSeek-V4-Flash-0731 50.8, Qwen3.8-Flash-Next 38.0 |
| HLE (w/o tools) | 37.68 | lab — vs Qwen3.8-Flash-Next 34.16, Nemotron Super VL 31.79 |
| SciCode | 53.8 | lab — vs Qwen3.8-Flash-Next 47.5, Nemotron Super VL 47.1, Qwen3.8-27B 43.6 |

## Efficiency

- **Active params:** unreported by the lab; checkpoint is 125.1B BF16 parameters (safetensors metadata), MoE with 256 experts and top-8 routing + shared expert. BenchLM also lists "MoE active count unreported".
- **Context length:** 262,144 tokens native (`max_position_embeddings`); card notes longer contexts need optional scaling.
- **VRAM (fp16 rough):** ~250 GB bf16 (62 shards). The card claims the 122B MoE "serves on a **single 80GB GPU**" and "runs on a single DGX" — that implies the published FP8 (~125 GB) or NVFP4 (~63 GB) build, not bf16. ⚠ large: bf16 needs ~3–4×80GB, so a local agent loop realistically runs `Ornith-1.5-122B-FP8` / `-NVFP4` / `-GGUF`.
- **Runtime:** Transformers ≥5.8.1, vLLM ≥0.19.1, SGLang ≥0.5.9; reasoning parser returns CoT in `reasoning_content`, tool-call parser surfaces `<tool_call>` blocks as OpenAI-style `tool_calls`. Recommended sampling: temp 0.6 / top_p 0.95 / top_k 20 / presence_penalty 0.0 for precise coding; temp 1.0 / presence_penalty 1.5 general.
- **Day-one artifacts (all created 2026-10-20):** `ornith-ai/Ornith-1.5-122B-GGUF`, `-FP8`, `-NVFP4`, `-MLX`, `-MLX-4bit`, `-MLX-8bit`, plus `unsloth/Ornith-1.5-122B-GGUF`. Card also references an `Ornith-1.5-122B-Mobile` quantized variant that is **not yet published**.
- **Family:** Ornith-1.5-9B (dense), 35B-A3B, 122B, 397B — see [[ornith-ai--Ornith-1.5-35B-A3B]]. Ornith-1.5-397B (Aug) is the larger sibling; BenchLM's lineage lists this 122B as newest.

## What makes it notable

Ornith (DeepReinforce) shipped the 122B rung of the 1.5 family as a weights-early / card-late launch: weights were uploaded 2026-10-16, then the public event landed 2026-10-20 — eval chart, rewritten card, first-party GGUF/FP8/MLX/NVFP4 builds and an unsloth GGUF all inside one day. The card's positioning is agentic coding at ~125B scale for single-GPU serving: it beats Qwen3.8-Flash-Next (same size class) on SWE-bench Verified (84.5 vs 82.8), SWE-bench Pro (76.9 vs 43.9) and CyberGym (80.0 vs 78.0), trails it slightly on Terminal-Bench 2.1 (81.2 vs 83.4) and Toolathlon (70.8 vs 71.4), and beats the 120B Nemotron Super VL across every coding row. Limits to weigh before trusting it in an agent loop: every number is lab-reported and self-harnessed (OpenHands for SWE, Claude Code for Terminal-Bench, Claude Opus judges for HLE/MCP-Atlas), the anti-hack methodology is self-disclosed rather than independently audited, no HumanEval/LiveCodeBench/Aider number exists, and there is no third-party eval yet — Artificial Analysis 404s for the slug and BenchLM only mirrors the card rows (it also notes the `license_link` LICENSE file was unavailable at the reviewed revision; the frontmatter and card both declare MIT, and the rest of the family ships MIT). ⚠ 122B total — for a local loop, treat the FP8/NVFP4/GGUF builds as the deployable path.

## See also

- [[welcome]]
- Source: https://huggingface.co/ornith-ai/Ornith-1.5-122B
- Sibling: [[ornith-ai--Ornith-1.5-35B-A3B]]
- Family repo: https://huggingface.co/ornith-ai
- Quant builds: https://huggingface.co/ornith-ai/Ornith-1.5-122B-GGUF · https://huggingface.co/ornith-ai/Ornith-1.5-122B-FP8 · https://huggingface.co/ornith-ai/Ornith-1.5-122B-NVFP4 · https://huggingface.co/unsloth/Ornith-1.5-122B-GGUF
- Independent coverage: https://benchlm.ai/models/ornith-1-5-122b (mirrors the card's 14 rows, unranked; no AA entry)
- Lab forum thread (family): https://forums.developer.nvidia.com/t/deepreinforce-ornith-1-5-family-released/380623
