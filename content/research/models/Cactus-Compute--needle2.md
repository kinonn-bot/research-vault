---
title: "Cactus Compute Needle 2"
org: Cactus-Compute
model_id: Cactus-Compute/needle2
date: 2026-08-14
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - tool-calling
  - edge
  - on-device
downloads: 1364
likes: 104
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/Cactus-Compute/needle2
params: 45M
context: 256 (sliding window, tools pinned as KV sinks)
architecture: dense
---

# Cactus Compute Needle 2

**One-line:** ⚠ 45M-parameter edge tool-calling model (14MB binary, 28MB RAM session, ~500 tok/s on a Raspberry Pi 5) — below the 1B+ local-agent range; no published numeric benchmarks, agent-loop suitability for real coding unknown. Claim to fame: open-weights function calling / structured extraction on microcontrollers and phones.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | — |
| HumanEval+ | — | — |
| MBPP | — | — |
| LiveCodeBench | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |
| SWE-bench Multilingual | — | — |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |

⚠ No numeric benchmark tables in the card — the size-quality comparison chart is image-only (`assets/frontier.png`). Card claims it "trades wins with other small models like FunctionGemma 270M, LFM2.5 230M and Apple FM, at 5x to 70x smaller." No coding or agentic eval numbers published anywhere in markdown.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |

## Efficiency

- **Active params:** 45M (dense; Simple Attention Network — Hadamard MLP FFN, GQA, engram KV memory)
- **Context length:** 256-token sliding window; tools pinned as KV sinks keep total memory ~28MB regardless of conversation length
- **VRAM (fp16 rough):** ~90 MB full precision, but shipped pre-compressed to CQ2-bit ("Cactus Quants") as a single 14MB self-contained binary with its own engine — no runtime, no network, no downloads

## What makes it notable

Needle 2 is the whole model+engine+grammar baked into one 14MB binary targeting tool calling, device use, and structured extraction on hardware that normally can't run an LLM at all: Raspberry Pi 5 (~500 tok/s), Meta Quest 3S / Apple Vision Pro (400–1,500 tok/s), sub-$200 phones (300–700 tok/s), even the ESP32-P4 microcontroller (~11MB on ESP32-S3). Every call is grammar-constrained from a JSON schema, carries a calibrated confidence score for escalation to a bigger model, and off-topic input is refused with an empty call rather than hallucinated. Built on the Simple Attention Network recipe (arXiv:2607.18363) with a byte-level decode grammar compiled from declared tool schemas.

Positioning vs the tracker's usual 1B–70B crowd: it is not competing with SWE-bench models at all — it's the "escalation floor" layer for edge agent loops. For a user running agents on a Pi, this is the kind of model that answers tool calls locally for ~zero cost and routes hard cases to a larger model. Purely by the numbers (45M params, no coding benchmarks) it would normally be excluded; included here because it is genuinely new, genuinely open (Apache-2.0, ungated), has a paper, and is squarely in the tool-calling/agentic space the tracker targets.

## See also

- [[welcome]]
- Source: https://huggingface.co/Cactus-Compute/needle2
- Paper: https://arxiv.org/abs/2607.18363
- Repo: https://github.com/cactus-compute/needle
