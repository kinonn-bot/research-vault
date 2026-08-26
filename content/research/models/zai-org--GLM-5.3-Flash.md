---
title: "Zhipu GLM-5.3-Flash"
org: zai-org
model_id: zai-org/GLM-5.3-Flash
date: 2026-08-26
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - multimodal
  - hybrid-attention
  - instruct
downloads: 0
likes: 707
license: mit
pipeline: text-generation
source: https://huggingface.co/zai-org/GLM-5.3-Flash
params: 18B active (320B total)
context: ~1M
architecture: moe (hybrid sparse + linear attention)
---

# Zhipu GLM-5.3-Flash

⚠ **Lab-reported benchmarks.** All numbers below come from the z.ai blog (2026-08-26) and the zai-org HuggingFace card. Not independently verified against a third-party leaderboard yet.

**One-line:** ⚠ large (320B total / 18B active) — first natively multimodal GLM-5 model; a massively efficient agentic-coding MoE that beats GLM-5.2 by a wide margin and approaches Claude Opus 4.8, at ~1/10 the inference cost.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | 37.6 (base model only) | lab |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published |
| SWE-bench Multilingual | — | not published |
| NL2Repo | 56.3 | lab |
| DeepSWE v1.1 | 63.4 | lab (datacurve/deep-swe leaderboard) |

GLM-5.3-Flash publishes **no SWE-bench Verified / Aider / BFCL**. Its coding/agent story is carried by newer agentic-harness evals that several 2026 labs publish in place of the classic suite. DeepSWE v1.1 63.4 beats GLM-5.2 (46.2), DeepSeek-V4-Vision-Exp (59.3) and Opus 4.8 (58.0); only GPT-5.6-Terra (69.6) and Gemini 3.7 Flash (65.3) are higher.

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Terminal-Bench 2.1 | 84.3 | lab |
| Toolathlon Verified | 78.4 | lab (official service, pass@1 avg 3 runs) |
| AutomationBench v1.0.6 | 48.8 | lab |
| Agents' Last Exam | 26.3 | lab |
| HLE (w/ Tools) | 55.3 | lab |
| GDPval-AA v2 | 1773 | lab (by Artificial Analysis) |

Toolathlon Verified 78.4 and AutomationBench 48.8 both blow past GLM-5.2 (59.9 / 26.2). Terminal-Bench 2.1 84.3 leads the open-weight comparison while remaining just below Opus 4.8 (85.0), GPT-5.6 Terra (87.4), and Gemini 3.7 Flash (85.8). On z.ai's own Code Bench v1.0 at max effort: 29.0 vs Opus 4.8 29.5.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU | 88.1 (base) | lab |
| BBH | 86.6 (base) | lab |
| HellaSwag | 87.1 (base) | lab |
| LiveCodeBench-Base | 37.6 (base) | lab |
| SimpleQA | 33.5 (base) | lab |

The base (GLM-5.3-Flash-Base) MMLU/BBH/HellaSwag row is the deltas-vs-prior-base story; the deployed instruct model's own reasoning table isn't published separately. Artificial Analysis Intelligence Index v4.1.1: **57** at $0.045/task (discounted).

## Efficiency

- **Active params:** 18B (320B total; 45 layers — nearly halved vs GLM-4.5's 92)
- **Context length:** up to ~1M tokens (serving; 300K for HLE eval, 400K for DeepSWE)
- **VRAM (fp16 rough):** ~640 GB at BF16 (321B params) — not a single-GPU local model in full precision. Needs multi-GPU (SGLang/vLLM/KTransformers recipes) or a quantized build; community **GGUF / FP8 / NVFP4** quant repos appeared same-day (unsloth, vcruz305) for llama.cpp / LM Studio / Ollama.

## What makes it notable

GLM-5.3-Flash is the efficiency flagship of the GLM-5 series and the first natively multimodal GLM-5. It pairs a hybrid sparse+linear attention architecture (IndexPool to cut long-context indexer overhead) with a 30T-token multimodal corpus, delivering Opus-4.8-adjacent agentic-coding strength at roughly a tenth of the cost. For the "runs these locally / pipes into tool-using agents" user: the 18B **active** parameter count is attractive, but the 320B total means you'll be running a quant here, and the custom `Glm5NextForConditionalGeneration` architecture means stock transformers won't load it — use the SGLang / vLLM / KTransformers recipes or a community GGUF. It's a genuine frontier-adjacent coding/agent model at flash-tier price, which is why it benchmarked as "the most popular model of the week" (as `ox-alpha`) on OpenCode before release.

## See also

- [[welcome]]
- Source: https://huggingface.co/zai-org/GLM-5.3-Flash
- Blog: https://z.ai/blog/glm-5.3-flash
