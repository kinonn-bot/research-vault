---
title: "NousResearch Arete-27B"
org: NousResearch
model_id: NousResearch/Arete-27B
date: 2026-11-11
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - sft
  - value-alignment
  - qwen
downloads: 3431
likes: 391
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/NousResearch/Arete-27B
params: "27B dense (SFT of Qwen/Qwen3.8-27B, all LM weights trained, vision encoder frozen)"
context: "64K training context (inherits Qwen3.8-27B config)"
architecture: "dense (Qwen3.8 decoder, MTP head disabled during training)"
---

# NousResearch Arete-27B

**One-line:** Value-alignment SFT of Qwen3.8-27B (Apache-2.0, 27B dense) that cuts CCP-framed answers from 22% to 0.9% with no meaningful capability regression — *Terminal-Bench-2.1 70% (lab-reported, Nous harness; lab disclaims improvement credit)*, no SWE-bench/BFCL published.

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
| Terminal-Bench-2.1 | *70% (lab-reported, Nous harness; base 67% same harness)* | *lab* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | — |
| GPQA Diamond | — | — |
| MATH | — | — |
| AIME 2025 | — | — |
| Hermes Bench (internal general-capability) | *65.60% (base 65.77%, within noise)* | *lab* |

## Efficiency

- **Active params:** 27B dense (single checkpoint, 18 safetensors)
- **Context length:** 64K training context; inference config inherits Qwen3.8-27B
- **VRAM (fp16 rough):** ~54 GB (fits 2x24GB only quantized; GGUF available via bartowski, 53.9k downloads day-one)

## What makes it notable

NousResearch SFT'd Qwen3.8-27B on ~52.8M tokens (34,878 published arete-data-pairs prompts, teacher: Inkling) across seven value categories to remove CCP framing — fact score 2.32 to 2.98/5, propaganda rate 22% to 0.9%, holding across all categories. For agent loops the point is narrower: a Western-values-aligned Qwen3.8-27B that holds its agentic capability (TB-2.1 70% vs 67% same-harness, Hermes Bench within noise). Caveats: (1) no SWE-bench/BFCL/τ-Bench published, so agent-loop suitability beyond TB-2.1 is unknown; (2) Nous explicitly disclaims the +3pp TB-2.1 delta ("differences from official benchmark results can come from different inference configurations"); (3) marktechpost notes the base scores 73.0 official vs 67% on the Nous harness — compare harness-to-harness only. Position vs competition: same weights class as Qwen3.8-27B with different values; propaganda-eval table puts it at 0.9% vs GLM-5.3 15% and DeepSeek-V4.1-Flash 16%.

## See also

- [[welcome]]
- Source: https://huggingface.co/NousResearch/Arete-27B
- Blog: https://nousresearch.com/arete
- Eval set: https://huggingface.co/datasets/NousResearch/Propaganda_Eval
