---
title: "Maxwell Maxwell-V1-Flash"
org: maxwell-model
model_id: maxwell-model/Maxwell-V1-Flash
date: 2026-11-19
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
downloads: 1052
likes: 223
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/maxwell-model/Maxwell-V1-Flash
params: "35B total / 3B active MoE (excl. embeddings)"
context: "256K tokens"
architecture: "moe (MBSA sparse attention + manifold-constrained hyper-connections)"
---

# Maxwell Maxwell-V1-Flash

**One-line:** 35B-total / 3B-active MoE (Apache-2.0, 256K) with first-class agentic evals — *SWE-bench Verified 65.40, Terminal-Bench 58.65, Tau3-Bench 67.37, LCB-v6 85.66 (all lab-reported, Claude Code / Harbor / Terminus-2 harnesses)* — beating same-scale Qwen3.6-35B-A3B on every agent/code row.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | *78.05 (base-model table)* | *lab* |
| HumanEval+ | *71.95 (base-model table)* | *lab* |
| MBPP | *65.37 (base-model table)* | *lab* |
| LiveCodeBench | *v6 pass@1 85.66 / pass@8 93.74* | *lab* |
| Aider polyglot | — | — |
| SWE-bench Verified | *65.40 pass@1 (Claude Code harness 2.1.212, 256K ctx, 240 turns)* | *lab* |
| SWE-bench Multilingual | — | — |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | — |
| τ-Bench | *Tau3-Bench 67.37 pass@1* | *lab* |
| ToolACE | *MCP-Mark 37.30 mean@8 (tool-use proxy)* | *lab* |
| GAIA | — | — |
| Terminal-Bench-2.1 | *58.65 mean@5 (Harbor + Terminus-2 harness)* | *lab* |
| BrowseComp / HLE w/ Tools | *76.30 (82.20 w/ ctx-mgmt) / 46.10 (55.10 w/ ctx-mgmt)* | *lab* |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | *85.46 (Pro accuracy)* | *lab* |
| GPQA Diamond | *86.52 pass@1* | *lab* |
| MATH | *MATH-500 71.40 (base table)* | *lab* |
| AIME 2025 | *100.00 pass@8 / 96.25 mean@8* | *lab* |
| HLE (128K) | *24.79* | *lab* |
| MultiChallenge / IFBench | *72.20 / 64.80* | *lab* |

## Efficiency

- **Active params:** 3B active (35B total, excl. embeddings) — ~70 GB fp16, quant or 2-GPU for local
- **Context length:** 256K tokens (RULER 93.35 at 256K, HELMET 56.55 at 128K)
- **VRAM (fp16 rough):** ~70 GB (3B-active MoE; GGUF/quant path not yet published by lab)
- **Serving caveat:** requires custom vLLM fork (`maxwellmodel/vllm-openai:v0.30.0`, `--trust-remote-code`), NVIDIA driver >= 580 (CUDA 13.0)

## What makes it notable

Unknown-lab debut that out-scores the same-scale Qwen3.6-35B-A3B on every agent/code row that matters for tool-using loops: SWE-V 65.40 vs 63.40, Terminal-Bench 58.65 vs 47.42, Tau3 67.37 vs 64.00, LCB-v6 85.66 vs 85.32, plus a search-eval sweep (BrowseComp, WideSearch, DeepSearchQA all lead the 5-model comp set incl. Gemma-4-26B-A4B-it and Muse-Glimmer-30B). Caveats: (1) every number is lab-reported under the lab's own harness config — no Artificial Analysis / independent replication yet, though community chatter (Reddit LocalLLaMA thread, X, explainx.ai writeup, mindstudio.ai hands-on local test) corroborates the release; (2) repo created 2026-10-13 but weights first pushed public 2026-11-13 with card table fix 11-14 (staged-private pattern) — treat 11-13 as the release; (3) custom `maxwell_moe` modeling code + custom vLLM fork means stock transformers/llama.cpp will not load it day-one. For 35B-class agent work this is the strongest new open-weight option since the Qwen3.6/GLM-5.3 wave, gated only on harness trust.

## See also

- [[welcome]]
- Source: https://huggingface.co/maxwell-model/Maxwell-V1-Flash
- Tech report: https://github.com/maxwell-model/Maxwell-V1-Flash/blob/main/Maxwell_v1_flash_tech_report.pdf
- Playground: https://maxwell-llm.ai/playground
