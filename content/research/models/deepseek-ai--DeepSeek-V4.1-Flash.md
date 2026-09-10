---
title: "DeepSeek-V4.1-Flash"
org: deepseek-ai
model_id: deepseek-ai/DeepSeek-V4.1-Flash
date: 2026-09-10
tags:
  - huggingface
  - image-text-to-text
  - coding
  - agentic
  - moe
  - deepseek-v4-1
  - csa2
  - ced
  - million-token-context
  - reasoning
  - instruct
  - vl
downloads: 6
likes: 1235
license: mit
pipeline: image-text-to-text
source: https://huggingface.co/deepseek-ai/DeepSeek-V4.1-Flash
params: "8B active prefill / 16B decode of 552B total (MoE, 1 shared + 384 routed, 6 active)"
context: "1M tokens"
architecture: moe
---

# DeepSeek-V4.1-Flash

**One-line:** New open-weight agentic frontrunner — 552B MoE (8B active prefill / 16B decode, CED + CSA2 sparse attention) with 1M context, MIT: Terminal-Bench 2.1 **90.6** (tops the frontier comparison incl. Opus-5.0/GPT-5.6), DeepSWE v1.1 74.2, KV cache ~1/8 of V4-Flash. ⚠ large — server-class, ~550-600GB at FP8, multi-GPU only. First tracked 2026-09-10 (same-day release, 1235 likes).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | 79.4 | lab (base model, 0-shot) — instruct checkpoint not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (lab uses DeepSWE / Terminal-Bench) |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench 2.1 | 90.6 | lab (DeepSeek Harness Minimal, max effort, 1M ctx) |
| Terminal-Bench 3.0 | 30.0 | lab |
| Terminal-Bench 4.0 | 31.2 lab / 27 AA (Artificial Analysis TB v4.0 chart) |
| DeepSWE v1.1 | 74.2 | lab (mini-SWE harness; best in comparison after Muse-Spark-like set) |
| NL2Repo | 64.0 card / 65.4 tech report | lab |
| ProgramBench | 20.3 | lab (Almost@1) |
| Codeforces | 3471 rating | lab |
| BigCodeBench | 60.6 | lab (base model, 3-shot) |

*All coding/agentic numbers lab-reported (model card + tech report, DeepSeek Harness minimal mode, max reasoning effort, temp 1.0 / top_p 0.95). Independent checkpoints: benchlm.ai profile confirms card values (22 rows, "Provider exact"); Artificial Analysis ran the model on AutomationBench-AA (63%, chart best) and Terminal-Bench v4.0 (27%).*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| AutomationBench-AA | 63 | Artificial Analysis (independent) |
| AutomationBench | 54.8 | lab |
| CyberGym | 88.1 | lab |
| SEC-Bench Pro | 62.8 | lab (Claude Code harness) |
| Agent's Last Exam | 31.8 | lab |
| HLE w/ tools | 63.9 | lab |
| ExploitGym | 15.3 | lab |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | 74.1 | lab (base model, 5-shot) |
| GPQA Diamond | 90.9 | lab (instruct, max effort) |
| MATH | 61.1 | lab (base model, 4-shot) |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** 8B per token during prefill, 16B during decode (CED: decoder KV projected from encoder final states)
- **Total params:** 552B (1 shared + 384 routed experts, 6 activated; plus 196B Engram conditional memory, sparsely accessed)
- **Context length:** 1M tokens (sparse attention trained at 64K, extended at 34T tokens)
- **VRAM (fp16 rough):** ~1.1 TB — ships native FP8 (~550-600GB weights): ≈8×80GB or 4×141GB-class GPUs minimum; not single-GPU hardware. Quant beyond FP8 not yet available.

## What makes it notable

Leads the open-weight field on Terminal-Bench 2.1 (90.6 vs GLM-5.3 88.2, Kimi K3 88.3, Opus-5.0 89.1) and CyberGym (88.1 vs GPT-5.6 84.5) at a fraction of the decode cost of dense rivals — the 8B/16B active split and 890-byte/token KV cache are explicitly aimed at input-heavy agentic workloads with 1M-token histories. Reasoning effort is continuously controllable (1-100), trading cost for accuracy. Caveats: pipeline_tag is image-text-to-text (multimodal input — vision encoder trained from scratch); custom `deepseek_v41` architecture with custom prompt encoding (no Jinja template — `encoding.py` + deepseek-recipe), so expect integrations (vLLM/SGLang/Ollama) to lag the paper; DeepSWE is DeepSeek's own benchmark family, so preference the independent AA numbers where they exist.

## See also

- [[welcome]]
- Source: https://huggingface.co/deepseek-ai/DeepSeek-V4.1-Flash
- API/announcement: https://api-docs.deepseek.com/news/news260910
- Artifact Analysis: https://artificialanalysis.ai/models/deepseek-v4-1-flash
- BenchLM: https://benchlm.ai/models/deepseek-v4-1-flash