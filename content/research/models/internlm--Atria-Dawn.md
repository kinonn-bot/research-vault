---
title: "InternLM Atria Dawn"
org: internlm
model_id: internlm/Atria-Dawn
date: 2026-10-24
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - tool-calling
  - long-context
  - cybersecurity
  - science-agents
  - china-lab
  - custom-architecture
  - glm-5.2-base
downloads: 0
likes: 5
license: mit
pipeline: text-generation
source: https://huggingface.co/internlm/Atria-Dawn
params: "744B total MoE (active count not disclosed)"
context: "524,288 (512K tokens)"
architecture: "moe — GLM-5.2 base, custom model_type glm_moe_dsa (GlmMoeDsaForCausalLM), 78 layers, hidden 6144, 256 routed experts / 8 active, vocab 154,880"
---

# InternLM Atria Dawn

**One-line:** The **full release** of Shanghai AI Lab's Atria Dawn agentic model (the September `Atria-Dawn-Preview` was the preview) — 744B MoE built on GLM-5.2, MIT-licensed, 512K context, best-in-row BFCL v4 78.4, CyberGym 86.8, AutomationBench 54.7, DeepSearchQA 96.5 and WideSearch 84.6 against DeepSeek V4 Pro 0813 / Kimi K3 / Qwen3.8 Max / GLM-5.3 / GPT-5.6 sol / Opus 5. ⚠ large — BF16 ≈1.5 TB, first-party FP8 sibling ≈745 GB; server-class only. ⚠ lab-reported numbers only; 0 downloads at capture (launch-day).

> Repo created 2026-10-23 03:21Z (16.6h before this run) with the full weight set (368 files) and the first-party FP8 sibling (`internlm/Atria-Dawn-FP8`, 192 files) created 2026-10-23 01:23Z. Separate model IDs from the already-tracked [[internlm--Atria-Dawn-Preview]] (Preview: 256K ctx, released 2026-09-11). Independent coverage exists (explainx.ai, datastudios.org, Instagram/Twitter launch posts) but no independent benchmark re-run has been found — BenchLM has no page for it.

> ⚠ All benchmark numbers below are **lab-reported** from the model card's comparison table (which the card states matches the official table at atria-asi.ai). No Artificial Analysis / BenchLM / LMArena listing found as of 2026-10-24.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (card uses SWE-bench Pro) |
| SWE-bench Pro | 61.7 | lab — vs Kimi K3 62.0, Qwen3.8 Max 65.3, Claude Opus 5 76.5 |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench 2.1 | 81.0 | lab — vs Qwen3.8 Max 89.6, Opus 5 90.2 |
| DeepSWE | 49.3 | lab — trails DeepSeek V4 Pro 0813 54.9, Kimi K3 70.6 |
| NL2Repo-Bench | 50.0 | lab — trails Kimi K3 63.1, Qwen3.8 Max 63.2 |
| Harbor-Index | 17.3 | lab — trails Kimi K3 24.3, Opus 5 41.0 |
| MLE-bench Lite | 88.2 | lab — vs Qwen3.8 Max 81.3, GPT-5.6 sol 88.9 |
| SpreadsheetBench 2 | 33.0 | lab — vs Kimi K3 35.8 |
| SkillsBench | 67.8 | lab — **best in row** (vs DeepSeek V4 Pro 65.0, Qwen3.8 Max 66.7) |
| PaperBench | 89.6 | lab — vs Qwen3.8 Max 94.1 |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL v4 | 78.4 | lab — **best in row** (vs GLM-5.3 74.1, DeepSeek V4 Pro 71.4, Kimi K3 69.1) |
| τ-Bench | τ³-bench Banking 43.3 | lab — vs Qwen3.8 Max 55.2, Opus 5 48.7 |
| ToolACE | — | not published |
| GAIA | — | not published |
| AutomationBench | 54.7 | lab — **best in row** (vs GLM-5.3 52.5, Qwen3.8 Max 49.7) |
| CyberGym | 86.8 | lab — **best in row** (vs GLM-5.3 84.5, GPT-5.6 sol 83.6) |
| DeepSearchQA | 96.5 | lab — **best in row** (vs Kimi K3 95.9, GLM-5.3 94.7) |
| WideSearch | 84.6 | lab — **best in row** (vs Opus 5 84.0, GPT-5.6 sol 83.3) |
| BrowseComp | 91.3 | lab — vs Kimi K3 91.2, GPT-5.6 sol 92.2 |
| Workspace-Bench / -Lite | 66.1 / 70.0 | lab — -Lite trails GLM-5.3 71.7 |
| JobBench | 57.5 | lab — vs Claude Opus 5 68.0 |
| Harvey LAB | 27.5 | lab — **best in row** (vs Kimi K3 25.4, DeepSeek V4 Pro 6.7) |
| DeepResearch Bench II | 51.2 | lab — vs Opus 5 54.1 |
| OfficeQA Pro | 67.1 | lab — vs Opus 5 67.2 |
| GDPval | 1594.2 | lab — judge score, vs Opus 5 1714.0 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 / 2026 | — | not published |

## Efficiency

- **Active params:** not disclosed (744B-total MoE on GLM-5.2; 256 routed experts, 8 active per token; 78 layers; hidden 6144; vocab 154,880)
- **Context length:** 512K (card) — the Preview shipped 256K; `max_position_embeddings` in config is 1,048,576
- **VRAM:** ⚠ **BF16 ≈1.5 TB** across 368 files; first-party FP8 sibling `internlm/Atria-Dawn-FP8` (192 files) ≈745 GB. Not single-80GB-GPU hardware.
- **Runtime:** custom architecture (`model_type: glm_moe_dsa`, `GlmMoeDsaForCausalLM`) — SGLang ≥v0.5.13.post1 or vLLM ≥v0.23.0 using the GLM-5.2 recipes; no stock-transformers path. Text input only (not multimodal). Card ships Codex / Anthropic-compatible / SystemOne client configs plus a hosted API (`discovery-api.intern-ai.org.cn`) and an international token plan.

## What makes it notable

Atria Dawn is Shanghai AI Lab's agent-native frontier release and the strongest open-weight agentic model on the board by breadth: best in row for BFCL v4 (78.4), AutomationBench (54.7), CyberGym (86.8), DeepSearchQA (96.5), WideSearch (84.6), SkillsBench (67.8) and Harvey LAB (27.5) against a comparison set of DeepSeek V4 Pro 0813, Kimi K3, Qwen3.8 Max, GLM-5.3, GPT-5.6 sol and Claude Opus 5 — while *trailing* clearly on the terminal/repo-first axes (Terminal-Bench 2.1 81.0 vs Qwen3.8 Max 89.6; DeepSWE 49.3 vs Kimi K3 70.6; NL2Repo 50.0 vs 63.2). That shape says research/office/browser agent loops rather than terminal-first coding agents, but the full release improves on the Preview on nearly every row (BFCL 77.0→78.4, CyberGym 86.5→86.8, AutomationBench 53.8→54.7, Terminal-Bench 78.3→81.0) and doubles context to 512K. Caveats: 744B means frontier memory (FP8 sibling ≈745 GB is the practical path), the custom `glm_moe_dsa` architecture needs SGLang/vLLM GLM-5.2 recipes, and every number is lab-reported with no independent re-run yet. Included despite 0 downloads because launch-day low counts are not a disqualifier for an established lab (JetBrains Mellum precedent).

## See also

- [[welcome]]
- Source: https://huggingface.co/internlm/Atria-Dawn
- Paper: https://arxiv.org/abs/2609.15818
- Preview (already tracked): [[internlm--Atria-Dawn-Preview]]
- Base model: [[zai-org--GLM-5.2]]
- FP8 sibling: https://huggingface.co/internlm/Atria-Dawn-FP8 · Official table: https://atria-asi.ai/
- Related: [[deepseek-ai--DeepSeek-V4-Pro-0813]] · [[moonshotai--Kimi-K3]] · [[Qwen--Qwen3.8-2.4T-A95B]]
