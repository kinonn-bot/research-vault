---
title: "Together HybridAgent 8B Agentic"
org: togethercomputer
model_id: togethercomputer/HybridAgent-8B-Agentic
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
downloads: 1066
likes: 7
license: mit
pipeline: text-generation
source: https://huggingface.co/togethercomputer/HybridAgent-8B-Agentic
params: "8B dense (Qwen3-8B-Base backbone + HybridLink adapter)"
context: "32,768 (Qwen3-8B-Base native)"
architecture: "dense + latent-reasoning adapter — Qwen3-8B-Base backbone with a lightweight HybridLink projector (adapter.pt); interleaves continuous latent steps with text/tool-call steps"
---

# Together HybridAgent 8B Agentic

**One-line:** The 8B rung of Together AI's latent+text hybrid agent (Python interpreter + web search across turns), post-trained from Qwen3-8B-Base with HybridSFT → HybridRL under MIT — its headline claim is GAIA 43.7 avg, ahead of DeepSeek-V4.1-Flash (39.8) and Kimi-K3 (41.7) in the lab's own harness; needs the HybridAgent runtime, not plain transformers.

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

*No repo-editing or polyglot-edit lane is evaluated in the paper — the coding cells are genuinely absent.*

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA (Lv.1 / Lv.2 / Lv.3 / Avg) | 51.3 / 44.2 / 25.0 / 43.7 | paper Table 1, lab-reported — vs Kimi-K3 41.7 avg, DeepSeek-V4.1-Flash 39.8, ARPO(8B) 38.8, GRPO(8B) 32.0, ReAct 32.0 |
| WebWalker (Easy / Med / Hard / Avg) | 48.9 / 45.2 / 35.2 / 42.5 | paper — vs ARPO(8B) 32.0, GRPO(8B) 30.0 |
| HLE (NS / CE / SF / Avg) | 14.2 / 8.0 / 20.0 / 14.4 | paper — vs ARPO(8B) 8.8, GRPO(8B) 7.8 |
| SealQA (S-0 / Hard) | 22.5 / 35.8 | paper — vs ARPO(8B) 18.9 / 26.0 |
| DeepSearchQA (Acc / F1) | 20.0 / 40.7 | paper — vs ARPO(8B) 18.0 / 37.2 |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 48.0 | paper Table 2 (RL stage) — vs ARPO 46.5, GRPO 43.9 |
| MATH | MATH500 84.6 | paper — vs ARPO 82.8, GRPO 82.0, standard text SFT 78.2 |
| AIME 2025 | 39.2 (avg@16) | paper — vs ARPO 37.1, GRPO 36.3 |
| AIME 2026 | 43.3 (avg@16) | paper — vs ARPO 41.5, GRPO 39.4 |
| MedQA | 75.3 | paper — vs ARPO 74.7, GRPO 74.3 |
| MuSiQue | 32.0 | paper — vs ARPO 28.5, GRPO 27.5 |

## Efficiency

- **Active params:** 8B dense (no MoE); only the HybridLink `adapter.pt` projector is added.
- **Context length:** Qwen3-8B-Base native (32,768); multi-turn hybrid working memory instead of a long-context extension.
- **VRAM (fp16 rough):** ~16 GB bf16 — the smallest checkpoint in this release family, laptop/workstation-friendly.
- **Efficiency claims (lab, paper):** 35.5–54.7% fewer text tokens, 1.8–2.6× faster inference, 2.7–3.7× lower cost than matched text agents (cost table uses the 4B scale as its worked example).
- **Deployment caveat:** plain `transformers` loads the backbone as a **text-only base** model (Qwen3-8B-*Base*, not instruct); latent mode, the Python/web-search tool executor and latent read-out require the `togethercomputer/HybridAgent` package. Ablation in the paper shows the reward term `r_tool` matters most here — removing it costs 11.2% on GAIA and 3.5% on WebWalker.

## What makes it notable

Same recipe as the 14B sibling, one scale down: a HybridSFT → HybridRL agent that alternates latent thoughts and text inside one generation stream, with an inspectable latent trace. The 8B checkpoint is the interesting one for local work — its GAIA average (43.7) is reported *above* DeepSeek-V4.1-Flash and Kimi-K3 in the paper's own harness while running in ~16 GB bf16, and it beats every matched 8B text/latent baseline (GRPO, ARPO, Coconut, SoftThinking, Qwen3-8B thinking). Limits: no SWE-bench/Aider/LiveCodeBench/BFCL lane at all, no independent reproduction (Artificial Analysis has no entry), the frontier-baseline comparisons come from the authors' own harness, and drop-in usability is low without the custom runtime. ⚠ Treat the GAIA/WebWalker deltas as lab-reported until a third party reruns them.

## See also

- [[welcome]]
- Source: https://huggingface.co/togethercomputer/HybridAgent-8B-Agentic
- Sibling: [[togethercomputer--HybridAgent-14B-Agentic]]
- Paper: https://arxiv.org/abs/2610.18861 (Hybrid Reasoning Agents, 13 Oct 2026)
- Code: https://github.com/togethercomputer/HybridAgent
