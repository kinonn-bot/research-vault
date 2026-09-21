---
title: "Cactus Compute Needle 3"
org: Cactus-Compute
model_id: Cactus-Compute/needle3
date: 2026-09-21
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - tool-calling
  - function-calling
  - edge
  - on-device
downloads: 46399
likes: 165
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/Cactus-Compute/needle3
params: 121M (laddered 29M-121M subnetworks)
context: 1024-token sliding window (global attention at layers 4/9/14/19)
architecture: dense
---

# Cactus Compute Needle 3

**One-line:** ⚠ no published benchmarks — agent-loop suitability unknown. 121M edge tool-calling foundation model (single 8-29MB CQ2-bit binary, apache-2.0, ungated), sequel to the tracked Needle 2; claims to beat models 10x its size on mobile tool calls and match 2-3x bigger models on structured extraction, with only image-only benchmark charts — no numeric scores published in markdown.

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

⚠ The benchmark charts are image-only (`assets/benchmarks.svg`, release page figure). The card names the evaluation suites — BFCL v4 (3,641 rows, AST match, no call on irrelevant), DroidCall (200 rows, exact calls in order), Mobile Actions (961 rows, exact call), DSTC8 (1,813 turns, field F1), SNIPS slot-filling + 7-way — but publishes zero numbers in text, and no third-party eval exists. Lab-reported claims without values: "beats models 10x its size on mobile tool calls", "matches 2-3x bigger models on extraction", "a fine-tuned 4L subnetwork can match DeepSeek V4 Flash on downstream tasks" — none verifiable from the card.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |

## Efficiency

- **Active params:** 121M total (20-layer; 70.8M of them in engram n-gram tables). "Intelligence ladder" — every depth from 2 to 20 layers is a deployable subnetwork (29M-121M), pickable per device.
- **Context length:** 1024-token sliding window with global attention at layers 4/9/14/19 (up from Needle 2's 256).
- **VRAM (fp16 rough):** ~0.24 GB fp16 equivalent, but shipped pre-compressed CQ2-bit ("Cactus Quants") as one 8-29MB self-contained binary with a per-platform engine (~1MB) — iOS/Android/WASM/macOS/Linux/Windows. 400-4k tok/s decode on a Raspberry Pi 5.

## What makes it notable

Needle 3 is the direct sequel to Needle 2 (tracked 2026-08-14), and the first genuinely trending entry of this run: 46.4k downloads and 165 likes within 5 days of the 2026-09-16 release — ~34x Needle 2's download base. Architecture is the Laddered Simple Attention Network (Monarch Hadamard MLP FFN, GQA + 3-tap causal conv, engram memory, multi-lane hyper-connections), trained on 360B tokens of proprietary structured data; output is grammar-constrained to exact JSON function calls with a calibrated confidence head, off-topic requests return an empty call list rather than a guess.

Positioning: like Needle 2, it is not a SWE-bench competitor — it is the "escalation floor" for edge agent loops: tool calling, structured extraction, and local embeddings on hardware that can't run a 1B+ model (Pi 5, Quest 3S, phones, ESP32-class MCUs, AR glasses, automotive). For a user running agents on a Pi with smart-home automation, this is a genuinely useful local tool-calling layer at ~zero cost, with hard cases routed to a bigger model. Included under the same precedent as Needle 2 (genuinely new, genuinely open, squarely tool-calling/agentic) despite no numeric benchmarks and being below the 1B-70B preferred range — flagged ⚠ accordingly.

## See also

- [[welcome]]
- Source: https://huggingface.co/Cactus-Compute/needle3
- Release/benchmark page: https://cactuscompute.com/needle
- Repo: https://github.com/cactus-compute/needle
- Predecessor: https://huggingface.co/Cactus-Compute/needle2