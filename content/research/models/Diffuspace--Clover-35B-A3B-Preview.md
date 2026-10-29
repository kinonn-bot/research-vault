---
title: "DiffuSpace Clover-35B-A3B-Preview (diffusion MoE agent)"
org: Diffuspace
model_id: Diffuspace/Clover-35B-A3B-Preview
date: 2026-10-28
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - moe
  - diffusion
  - tool-use
downloads: 1030
likes: 136
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/Diffuspace/Clover-35B-A3B-Preview
params: "35B MoE, ~3B active (256 experts, top-8 + 1 shared/layer, 40 layers)"
context: "131072 (128K, prompt + response combined)"
architecture: "moe-diffusion (hybrid Gated DeltaNet / full-attention; bidirectional GDN + block diffusion, LowConfidence decoding)"
---

# DiffuSpace Clover-35B-A3B-Preview (diffusion MoE agent)

**One-line:** First release from DiffuSpace (HKU Dream-team spinout) — a 35B/3B-active block-diffusion MoE that beats its autoregressive twin Qwen3.6-35B-A3B on every agent eval it reports, lab-reported SWE-bench Verified 73.6 and Terminal-Bench 2.1 51.7, Apache-2.0, ~69 GB BF16.

> ⚠ All scores below are **lab-reported** (launch blog diffuspace.ai/blog/clover-35b, 2026-10-28; blog carries both Chinese and English text and the two agree on every number quoted here). No independent evaluation yet as of 2026-10-30 (no Artificial Analysis / BenchLM / LMArena entry found). Novel architecture — first diffusion LM at 35B scale — so treat the margins as provisional until a third party reproduces them.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 73.6 | lab — blog (vs Qwen3.6-35B-A3B, Qwen3.5-35B-A3B, LLaDA2.2-flash, Mercury 2.5) |
| SWE-bench Multilingual | — | not published |
| Terminal-Bench 2.1 | 51.7 | lab — blog (vs MiniCPM-V-4.7 +15.7) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL-V4 | 67.9 | lab — blog (on-device section) |
| τ-Bench | — | not published (τ³ below is a different suite — do not compare) |
| τ³ Overall | 65.3 | lab — blog (vs diffusion + autoregressive peers, highest in row) |
| τ³ Banking | 14.4 | lab — blog (on-device section) |
| ToolACE | — | not published |
| GAIA | — | not published |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU-Pro | 84.8 | lab — blog |
| GPQA Diamond | 83.8 | lab — blog |
| ZebraLogic | 95.8 | lab — blog |
| AA-LCR | 72.0 | lab — blog |
| MATH / AIME | — | not published |

## Efficiency

- **Active params:** ~3B (35B total MoE; 256 routed experts, top-8 + 1 shared expert per layer)
- **Context length:** 131,072 tokens (prompt + response combined)
- **VRAM (fp16 rough):** ~69 GB BF16 (per card); INT4 on-device build ran on a 16 GB RTX 5070 Ti at 101.8 tok/s MATH-500
- **Throughput (lab):** 680 tok/s on 1×GB300 BF16 (bs=1, agent workloads); 515 tok/s on 1×H200 vs 365 tok/s for DFlash2-accelerated Qwen

## What makes it notable

Diffusion LMs graduate to mid-scale MoE: derived from Qwen3.6-35B-A3B with the attention stack reworked (bidirectional GDN, learnable block-size calibration, zero-init right-context conv branch) and decoded in parallel blocks instead of left-to-right. If the lab numbers reproduce, SWE-bench Verified 73.6 at 3B active params is the best agent-per-active-param open figure in the 30B class, and the speed story (diffusion parallelism compounding over multi-step agent loops: 28 steps/170 s vs Qwen3.6-Flash 30 steps/578 s on their browser demo) is the real pitch. Caveats: custom `trust_remote_code` diffusion sampler (needs Transformers 5.19+, SGLang/llama.cpp via their repo — stock vLLM will not run it), preview-stage stability on long-horizon tasks flagged by the lab itself, and zero third-party numbers so far.

## See also

- [[welcome]]
- Source: https://huggingface.co/Diffuspace/Clover-35B-A3B-Preview
- Launch blog: https://diffuspace.ai/blog/clover-35b/
- Code: https://github.com/DiffuSpace/Clover-35B-A3B-Preview
