---
title: "InternLM Atria Dawn Preview"
org: internlm
model_id: internlm/Atria-Dawn-Preview
date: 2026-09-16
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - custom-architecture
  - glm-5.2-base
  - preview
downloads: 546
likes: 125
license: mit
pipeline: text-generation
source: https://huggingface.co/internlm/Atria-Dawn-Preview
params: 744B MoE (active not disclosed)
context: 262144
architecture: moe
---

# InternLM Atria Dawn Preview

**One-line:** Shanghai AI Lab's new-generation agentic model, built on the 744B MoE GLM-5.2 foundation — best-in-row BFCL v4 77.0, AutomationBench 53.8, CyberGym 86.5, BrowseComp 92.5. ⚠ large — server-class only. ⚠ lab-reported numbers only so far; surfaced via aggregator (invisible to the HF streams: no pipeline_tag, 546 downloads).

> Released 2026-09-11 (llm-stats lists Sep 10), preview + arXiv 2609.15818. Missed by Streams A/B/C because `pipeline_tag` is empty and downloads (546) sit far below Stream B's 1000 cutoff; caught via the llm-stats aggregator + per-org sweep. High engagement for a fresh lab drop (125 likes / 546 dl).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (card uses SWE-bench Pro) |
| SWE-bench Pro | 59.6 | *lab* |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench 2.1 | 78.3 | *lab* |
| MLE-bench Lite | 86.2 | *lab* |
| SkillsBench | 66.4 | *lab* |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL v4 | **77.0** (best in row) | *lab* |
| τ-Bench | — | not published |
| τ³-Bench Banking | 41.2 | *lab* |
| ToolACE | — | not published |
| GAIA | — | not published |
| AutomationBench | **53.8** (best in row) | *lab* |
| CyberGym | **86.5** (best in row) | *lab* |
| Workspace-Bench | 65.0 | *lab* |
| BrowseComp | **92.5** (best in row) | *lab* |
| DeepSearchQA | **96.0** (best in row) | *lab* |
| DeepResearch Bench II | 51.1 | *lab* |
| JobBench | 50.3 | *lab* |
| GDPval | 1583 | *lab* |

*All numbers lab-reported from the model card's comparison table (vs DeepSeek V4 Pro 0813, Kimi K3, Qwen3.8 Max, GLM-5.3, GPT-5.6 sol, Claude Opus 5). No independent source (Artificial Analysis / BenchLM) found yet — treat as unverified.*

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |

## Efficiency

- **Active params:** not disclosed (744B-total MoE; config `glm_moe_dsa`, 78 layers, hidden 6144, 64 KV heads — DSA = dense/sparse attention variant of the GLM-5.2 family)
- **Context length:** 256K shipped (config layout allows 1M `max_position_embeddings`)
- **VRAM (fp16 rough):** ~1.5 TB — ⚠ large, multi-GPU/server-class only; official FP8 variant (`internlm/Atria-Dawn-Preview-FP8`) ≈ 745 GB; not single-80GB-GPU hardware
- **Note:** custom architecture `GlmMoeDsaForCausalLM` — run via SGLang ≥0.5.13.post1 or vLLM ≥0.23.0 (GLM-5.2 recipes); text-input only (not multimodal)

## What makes it notable

Atria Dawn Preview is the strongest open-weight agentic release of the week and the only one the HF streams missed: Shanghai AI Lab's answer to DeepSeek V4 Pro / Kimi K3 / GLM-5.3, it takes the best-in-row slot on BFCL v4 (77.0 vs V4 Pro 71.4, GLM-5.3 74.1), AutomationBench (53.8), CyberGym (86.5 vs V4 Pro 83.3), BrowseComp (92.5) and Workspace-Bench (65.0), while trailing on Terminal-Bench 2.1 (78.3 vs Qwen3.8 Max 89.3) — so it skews toward research/office/browser agent loops more than terminal-first coding. It ships first-party Codex / Claude Code / Kimi Code integration docs and a hosted API (atria-asi.ai) — unusually agent-native for a lab drop. Caveats: all numbers lab-reported, preview status, active-params undisclosed, and the custom architecture means local serving rides on SGLang/vLLM GLM-5.2 recipes rather than stock transformers.

## See also

- [[welcome]]
- Source: https://huggingface.co/internlm/Atria-Dawn-Preview
- Paper: https://arxiv.org/abs/2609.15818
- Base model: [[zai-org--GLM-5.2]]
- Related: [[deepseek-ai--DeepSeek-V4.1-Flash]]