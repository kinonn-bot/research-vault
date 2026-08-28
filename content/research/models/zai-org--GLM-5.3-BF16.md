---
title: "Zhipu GLM-5.3"
org: zai-org
model_id: zai-org/GLM-5.3-BF16
date: 2026-08-29
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - hybrid-attention
  - instruct
downloads: 0
likes: 17
license: GLM-5.3 (MIT-style, $10B MaaS cap)
pipeline: text-generation
source: https://huggingface.co/zai-org/GLM-5.3-BF16
params: ~40B active (744B total)
context: 1M
architecture: moe (hybrid GatedDeltaNet + attention, glm_moe_dsa)
---

# Zhipu GLM-5.3

⚠ **Lab-reported benchmarks.** All coding/agentic numbers below come from the zai-org HuggingFace card (2026-08-25), unless noted. GDPval-AA v2 is evaluated by Artificial Analysis. No independent third-party leaderboard verification of the coding rows yet.

**One-line:** ⚠ large (744B total / ~40B active) — the flagship open-weight coding model of the GLM-5 series; ~50% above GLM-5.2 on Z.ai's in-house Code Bench, open-source SOTA on Terminal-Bench 3.0 and Agents' Last Exam, and SOTA on CyberGym for vulnerability discovery.

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
| NL2Repo | 58.0 | lab |
| DeepSWE v1.1 | 66.9 | lab (mini-swe-agent, 400K ctx) |
| FrontierSWE | 78.1 | lab (by Proximal, 1M ctx) |
| SWE-Marathon (v1.1) | 42.5 | lab |
| PostTrainBench | 39.8 | lab |

GLM-5.3 (full) publishes **no SWE-bench Verified / Aider / BFCL** — the same pattern as its Flash sibling. Its repo-level coding story is carried by harder agentic harnesses: DeepSWE v1.1 66.9 (vs GLM-5.2 46.2, Kimi K3 67.5, DeepSeek-V4-Pro-0813 62.7, Qwen3.8-Max 56.6), and Terminal-Bench 2.1 88.2 (vs GLM-5.2 81.0, Kimi K3 88.3, DeepSeek-V4-Pro-0813 87.9). FrontierSWE 78.1. On Terminal-Bench 3.0 it's the open-weight SOTA at 28.3 (GLM-5.2 was 4.6; Claude Fable-5 w/ fallback 33.7, GPT-5.6-Sol 34.6).

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Terminal-Bench 2.1 | 88.2 | lab (Claude Code 2.1.207) |
| Terminal-Bench 3.0 | 28.3 | lab (avg@3) |
| Toolathlon Verified | 73.0 | lab (official service, pass@1 avg 3 runs) |
| AutomationBench v1.0.6 | 48.2 | lab |
| Agents' Last Exam (ALE-CLI) | 28.5 | lab |
| CyberGym | 84.5 | lab (SOTA — vulnerability discovery) |
| ExploitBench | 54.4 | lab |
| ExploitGym (2h / 6h) | 105 / 130 | lab |
| HLE (w/ Tools) | 62.5 | lab |
| GDPval-AA v2 | 1769 | Artificial Analysis |

The emergent-cyber row is the standout: CyberGym 84.5 (top of table vs GLM-5.2 77.2, Kimi K3 80.0, Qwen3.8-Max 78.5, Claude Fable-5 83.8), and ExploitGym 105/130 more than doubles GLM-5.2 (29/39) — Z.ai notes gains grow further up the exploitation chain. Toolathlon Verified 73.0 and AutomationBench 48.2 beat GLM-5.2 (59.9 / 26.2) decisively and stay competitive with the closed frontier. On the classic-suite proxies it trails Claude Fable-5 (w/ fallback) and GPT-5.6-Sol on most rows but is the strongest open-weight entry.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU | — | not published (deployed instruct) |
| GPQA Diamond | — | not published |
| MATH | — | not published |
| AIME 2025 | — | not published |

The card ships no deployed-instruct reasoning table (its base reuse of GLM-5.2 is the story — "every gain comes from post-training"). GDPval-AA v2 1769 (by Artificial Analysis) is the one reasoning-adjacent independent number.

## Efficiency

- **Active params:** ~40B (744B total; 78 layers, hidden 6144, 256 experts top-8)
- **Context length:** up to 1M tokens (`max_position_embeddings: 1048576`)
- **VRAM (fp16 rough):** ~1.5 TB at BF16 — **not single-GPU local in full precision.** Needs multi-GPU (SGLang / vLLM / KTransformers recipes) or a quantized build. Custom `GlmMoeDsaForCausalLM` architecture → stock transformers needs the dedicated `glm_moe_dsa` model code, not a from-scratch load.

## What makes it notable

GLM-5.3 is Zhipu's flagship coding release and the most capable open-weight model for coding as of this drop, per the lab: a 50% improvement over GLM-5.2 on their in-house Code Bench and open-source SOTA on Terminal-Bench 3.0 and Agents' Last Exam. It reuses the GLM-5.2 base (744B/40B, 1M ctx, GatedDeltaNet+attention hybrid) — all gains come from post-training, which is why it tracks so close to the closed frontier's per-row numbers while staying open-weight. For the "runs these locally / pipes into tool-using agents" user: the ~40B active count sounds tractable but 744B total means a quant is mandatory and the custom architecture rules out naive llama.cpp loading — realistically a vLLM/SGLang quant deployment. The cyber capability (CyberGym 84.5, ExploitGym doubling) is the headline differentiator vs its peers. It's the stronger-params sibling to the already-tracked GLM-5.3-Flash (320B/18B).

## See also

- [[zai-org--GLM-5.3-Flash]]
- [[welcome]]
- Source: https://huggingface.co/zai-org/GLM-5.3-BF16
- Blog: https://z.ai/blog/glm-5.3
