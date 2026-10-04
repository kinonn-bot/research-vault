---
title: "Microsoft FrogNano-4B-2609"
org: microsoft
model_id: microsoft/FrogNano-4B-2609
date: 2026-10-05
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - dense
  - hybrid
  - gated-deltanet
  - rl
  - leaf-harness
  - local
downloads: 408
likes: 98
license: mit
pipeline: text-generation
source: https://huggingface.co/microsoft/FrogNano-4B-2609
params: "~4.66B dense (32 layers, hidden 2560, +1 MTP layer)"
context: 262144 (config max_position_embeddings; evaluated agent config ~131k)
architecture: dense hybrid (24 Gated DeltaNet linear-attention + 8 full-attention layers, Qwen3.5 arch)
---

# Microsoft FrogNano-4B-2609

**One-line:** Microsoft Research Montréal's compact repo-level coding agent — 4.66B dense, RL post-trained (no stronger-model distillation) on ~1,500 TaskPilot-synthesized SWE tasks, 61.5% SWE-bench Verified Avg@3 (+22.1pp over its Qwen3.5-4B base's 39.4). All numbers lab-reported; no independent eval seen yet. License mit (card YAML; body states Apache-2.0), not gated, weights downloadable.

Surfaced via the lab-org author sweep: at 408 downloads it sits below Stream B's 1000-download cutoff, but lastModified 2026-10-02 falls inside the 7-day window and the community-quant signal (bartowski FrogNano-4B-2609-GGUF 7.5k+ downloads, mradermacher GGUF, MLX-oQ4e/oQ5e/oQ6e/oQ8e, all created 10-02/10-03) independently confirms a real, hot-as-of-this-week weight drop. Card release date: 22-SEP-2026; repo created 09-17; arXiv 2609.07925 companion.

## Coding benchmarks

*All lab-reported (Microsoft card + arXiv 2609.07925, Leaf harness, 150 interaction steps, ~131k context, Temp 0.6).*

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 61.5 Avg@3 (71.0 Pass@3) | lab — base Qwen3.5-4B: 39.4 Avg@3 |
| SWE-bench Multilingual | — | not published |
| SWE-bench Pro | 37.6 Avg@3 (47.6 Pass@3) | lab |
| Terminal-Bench 2.0 | 31.1 Avg@3 | lab |
| PatchEval-Verified | 47.3 Avg@3 | lab |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |

(Harness-coupled agentic eval instead: 5-tool Leaf harness — file read/write/edit, glob search, shell. RL reward = executable tests over complete multi-turn trajectories, 150 tool turns max.)

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not evaluated (card: explicitly not separately evaluated) |
| GPQA Diamond | — | not evaluated |
| MATH | — | not evaluated |
| AIME 2025 | — | not evaluated |

## Efficiency

- **Active params:** ~4.66B total, dense (no MoE); 32 layers, hidden 2560, intermediate 9216, 16 heads/4 KV, RoPE-mrope, +1 MTP layer, tied embeddings
- **Context length:** 262,144 tokens max position embeddings (Qwen3.5 config); evaluated coding-agent config ≈131k combined (150 steps, 8,192 gen tokens/turn)
- **VRAM (fp16 rough):** ~9.3 GB weights (4.66B × 2 B), card states ≈9.3 GB for weights alone; add KV/runtime — fits a 24 GB card comfortably
- **Runtime:** Qwen3.5 arch — transformers / vLLM / SGLang / KTransformers; quantized GGUFs + MLX exist in community repos; served with TensorRT-LLM/llama.cpp via quants
- ⚠ Vision components inherited from Qwen3.5-4B but NOT post-trained or supported — text-only model in practice

## What makes it notable

Positioning vs current leaders: at 4.66B it posts the strongest small-model repo-agent numbers of the open-weight set — MiniCPM5-2B is 46.4 SWE-bench Verified (2.5B), FrogNano's 61.5 Avg@3 at 4.66B is the only sub-5B score in the 60s (Pass@3 71.0), rivaling models several times its size (per Microsoft's claim of matching much larger agents). The RL-on-synthetic-task recipe (TaskPilot task synthesis, executable-test rewards, no behavioral distillation) makes it a genuinely post-training-new release, not a fine-tune. Caveats: Python-heavy, English-only, optimized for the Leaf harness loop (harness-sensitive performance), patches still need human review. For a local agent box: 9-10 GB BF16 on a 24 GB GPU with 131k context is comfortably feasible — a real candidate for the "runs these locally" setup.

## See also

- [[welcome]]
- Source: https://huggingface.co/microsoft/FrogNano-4B-2609
- arXiv: https://arxiv.org/abs/2609.07925
- GitHub: https://github.com/microsoft/FrogNano