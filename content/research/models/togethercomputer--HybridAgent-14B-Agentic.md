---
title: "Together HybridAgent 14B Agentic"
org: togethercomputer
model_id: togethercomputer/HybridAgent-14B-Agentic
date: 2026-10-21
tags:
  - huggingface
  - text-generation
  - agentic
  - tool-use
  - reasoning
  - latent-reasoning
  - hybrid-reasoning
  - research
  - instruct
downloads: 1064
likes: 11
license: mit
pipeline: text-generation
source: https://huggingface.co/togethercomputer/HybridAgent-14B-Agentic
params: "14B dense (Qwen3-14B-Base backbone + HybridLink adapter)"
context: "32,768 (Qwen3-14B-Base native)"
architecture: "dense + latent-reasoning adapter — Qwen3-14B-Base backbone with a lightweight HybridLink projector (adapter.pt); interleaves continuous latent steps with text/tool-call steps"
---

# Together HybridAgent 14B Agentic

**One-line:** Together AI's research agent that interleaves *latent* reasoning steps with text and tool calls in one generation stream (Python interpreter + web search across turns), post-trained from Qwen3-14B-Base with HybridSFT then HybridRL — MIT, but it needs the HybridAgent runtime: stock transformers loads only a text-only (base) backbone.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |

*The paper evaluates math/science/medicine/search/agentic reasoning — there is no repo-editing or polyglot-edit lane at all, so the classic coding cells are genuinely absent, not merely unlisted.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA (Lv.1 / Lv.2 / Lv.3 / Avg) | 53.8 / 55.8 / 33.3 / 52.4 | paper Table 1, lab-reported — vs Kimi-K3 41.7 avg, DeepSeek-V4.1-Flash 39.8, ARPO(14B) 43.7, GRPO(14B) 36.9, GLM-5.3-Flash 30.1, QwQ-32B 18.9, ReAct 32.0 |
| WebWalker (Easy / Med / Hard / Avg) | 48.9 / 52.4 / 46.5 / 49.5 | paper — vs ARPO(14B) 40.5, GRPO(14B) 38.5 |
| HLE (NS / CE / SF / Avg) | 16.1 / 13.3 / 17.9 / 16.0 | paper — vs ARPO(14B) 10.0, GRPO(14B) 8.6 |
| SealQA (S-0 / Hard) | 24.3 / 37.8 | paper — vs ARPO(14B) 17.1 / 22.8 |
| DeepSearchQA (Acc / F1) | 21.7 / 46.8 | paper — vs ARPO(14B) 16.3 / 38.2 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 55.1 | paper Table 2 (RL stage) — vs GRPO 52.5, ARPO 54.0 |
| MATH | MATH500 88.2 | paper — vs GRPO 87.4, ARPO 87.0, standard text SFT 83.8 |
| AIME 2025 | 43.3 (avg@16) | paper — vs GRPO 40.8, ARPO 42.1 |
| AIME 2026 | 45.8 (avg@16) | paper — vs GRPO 42.5, ARPO 43.3 |
| MedQA | 81.7 | paper — vs GRPO 81.0 |
| MuSiQue | 34.5 | paper — vs GRPO 32.0, ARPO 31.5 |

## Efficiency

- **Active params:** 14B dense (no MoE); the only added weights are the HybridLink `adapter.pt` projector.
- **Context length:** Qwen3-14B-Base native (32,768); the paper evaluates with a shared multi-turn working memory, not a long-context extension.
- **VRAM (fp16 rough):** ~28 GB bf16 backbone + adapter — comfortably single-GPU, and the cheapest scale in the family.
- **Efficiency claims (lab, paper):** 35.5–54.7% fewer text tokens than matched text agents, 1.8–2.6× faster inference, 2.7–3.7× lower cost; the cost table (Table 9) lists a 4B-scale comparison of 51.2 → 13.9 TFLOP per question.
- **Deployment caveat:** the card is explicit — loading the backbone with plain `transformers` gives a **text-only model**, and the backbone is Qwen3-14B-*Base* (not instruct). Hybrid latent mode, the tool executor (Python + web search, Tavily key) and the interpretable latent read-out all require `git clone https://github.com/togethercomputer/HybridAgent && pip install -e .`. For a drop-in agent loop, plain Qwen3-14B-Instruct-class models are simpler; this one is for the hybrid-latent experiment.

## What makes it notable

HybridAgent is the open release of a genuinely different agent training recipe rather than another SFT/DPO pass: the model switches between continuous latent thoughts and text within one autoregressive stream, keeps a lossless hybrid working memory across turns, and can read its latent steps back out as pseudo-text for debugging. Training is HybridSFT (learn to coordinate with the HybridLink projector) then HybridRL (learn *when* to think in latent space vs act in text), on Qwen3-8B/14B/4B-Base backbones. The paper reports the 14B checkpoint beating the strongest agentic baseline in its own suite by 17.4% on average and matched text/latent baselines by 10.4% at the RL stage, at a fraction of the tokens. Limits to weigh: the GAIA Lv.2 figure (55.8) is higher than the frontier closed baselines the paper itself measures (GPT-5.6-Luna 32.7, Kimi-K3 42.3) — a lab-harness result that no third party has reproduced, and Artificial Analysis has no entry; there is no SWE-bench/Aider/LiveCodeBench/BFCL number at all, so this is not a repo-editing agent; and the useful mode needs the custom runtime. It qualifies here on the "novel post-training algorithm + published agentic evals" rule, not on drop-in usability.

## See also

- [[welcome]]
- Source: https://huggingface.co/togethercomputer/HybridAgent-14B-Agentic
- Sibling: [[togethercomputer--HybridAgent-8B-Agentic]]
- Paper: https://arxiv.org/abs/2610.18861 (Hybrid Reasoning Agents, 13 Oct 2026)
- Code: https://github.com/togethercomputer/HybridAgent
