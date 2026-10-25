---
title: "Nanbeige/Nanbeige4.3-33B"
org: Nanbeige
model_id: Nanbeige/Nanbeige4.3-33B
date: 2026-10-26
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - tool-use
  - reasoning
  - long-context
  - teacher-model
  - chinese-lab
downloads: 0
likes: 297
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/Nanbeige/Nanbeige4.3-33B
params: "33.1B dense (all active); 52 layers, hidden 7168, 56 Q / 8 KV heads (GQA), ffn 22016, vocab 166912"
context: "524,288 (512K)"
architecture: "dense — LlamaForCausalLM (stock transformers/vLLM/SGLang; rope_theta 1.2e8; no custom model code in repo)"
---

# Nanbeige/Nanbeige4.3-33B

**One-line:** Nanbeige's flagship 33B dense "teacher" agent — lab-reported 80.9 Terminal-Bench 2.1, 65.5 DeepSWE and 70.4 Toolathlon-Verified, Apache-2.0 with a 512K context, in a plain Llama architecture that loads in stock transformers/llama.cpp-style stacks.

> ⚠ All scores below are **lab-reported** (the model card's HTML table); **no independent reproduction exists yet** — Artificial Analysis has no page, BenchLM 404s, and both third-party write-ups (explainx.ai, startupfortune) explicitly note every number is self-reported. The comparison columns are the lab's own re-runs of Qwen3.8-27B / Muse-Glimmer-30B / Gemma4-31B under its own harness, so cross-column comparisons are indicative, not controlled.
>
> Released 2026-10-24 (repo `createdAt` 2026-10-24T02:49Z; card `lastModified` 2026-10-25T11:11Z). Surfaced **outside** the strict 36h window (41.2h at run time) via the per-org sweep + unfiltered `trendingScore` and promoted under the soft-boundary rule: 297 likes in 41h, 20+ same-day community quant repos, Reddit >140 points, X + press coverage. It was missed by prior runs only because Stream A's `downloads >= 50` floor excludes brand-new large repos (HF shows 0 downloads at capture).

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | — | not published (card uses Terminal-Bench 2.1/4.0 + DeepSWE + SWE-Bench Pro instead) |
| SWE-bench Multilingual | — | not published |
| SWE-Bench Pro | 60.3 | lab — card (vs Qwen3.8-27B 61.7, Muse-Glimmer-30B 36.9, Gemma4-31B 51.2) |
| Terminal-Bench 2.1 | 80.9 | lab — card, Terminus 2 harness (vs Qwen3.8-27B 73.0) |
| Terminal-Bench 4.0 | 23.8 | lab — card, mini-swe-agent v2.4.6 (vs Qwen 6.3) |
| DeepSWE | 65.5 | lab — card, mini-swe-agent v2.4.6 (vs Qwen 42.5) |
| SWE-Atlas-QnA | 50.8 | lab — card, mini-swe-agent v2.4.6; 1,304 rubric tasks judged by GPT-6 Sol |
| NL2Repo | 53.0 | lab — card, Claude Code harness (vs Qwen 48.3) |
| SciCode | 52.6 | lab — card (vs Qwen 46.7) |
| SkillsBench | 61.1 | lab — card (vs Qwen 56.4) |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published (Tau3-Bench instead, below) |
| ToolACE | — | not published |
| GAIA | — | not published |
| Tau3-Bench | 48.8 | lab — card, official repo (vs Qwen 48.5) |
| Toolathlon-Verified | 70.4 | lab — card, no max_tokens cap (vs Qwen 68.5) |
| Automation Bench | 54.2 | lab — card, v1.0.6, 600 public tasks (vs Qwen 38.3) |
| JobBench | 44.8 | lab — card, Claude Code harness + search tool (vs Qwen 34.5) |
| GDPval | 84.8 | lab — card, revised rubrics (vs Qwen 86.4) |
| Claw-Eval (pass³) | 78.3 | lab — card, Claw-Eval General subset, 157 single-turn tasks |
| DeepPlanning | 63.3 | lab — card, official repo |
| EnterpriseOps-Gym | 41.0 | lab — card, official repo |
| YC-bench | $1,025,437 | lab — card, long-horizon business sim scored in dollars (vs Qwen $641,290) |
| Tool-use contract | XML (recommended) or JSON; `enable_thinking` / `preserve_thinking` chat-template switches; `qwen3_coder` tool parser, `qwen3` reasoning parser | card (no BFCL/τ number published) |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 89.5 | lab — card (trails Gemma4-31B's 91.3) |
| MATH | — | not published |
| AIME 2026 | 95.2 | lab — card (vs Qwen 94.5 — effectively a tie) |
| AA-LCR | 84.0 | lab — card (vs Qwen 82.0) |

## Efficiency

- **Active params:** 33.1B dense — all layers active (52 layers, hidden 7168, 56 query / 8 KV heads GQA, ffn 22016, vocab 166912). No MoE routing.
- **Context length:** 524,288 tokens (512K) native.
- **VRAM (fp16 rough):** ~66 GB (14 BF16 shards, 66.2 GB measured). Comfortable on 2×48 GB or 1×80 GB; the card's own SGLang/vLLM examples use `--tp-size 4`. A 4-bit quant (~17 GB) fits a single 24 GB consumer card — community MLX/GGUF/oQ*/EXL3 quants appeared within hours of the drop.
- **Runtime:** plain **Llama** architecture (`LlamaForCausalLM`, standard `model_type: llama`) — unlike the custom-arch Nanbeige4.2-3B, this needs no repo model code; the card's `trust_remote_code=True` is vestigial (no `modeling_*.py` in the repo). Recommended sampling: agentic/tool use temp 1.0 / top_p 0.95 / 65,536 new tokens; reasoning/chat temp 0.6 / top_p 0.95 / 262,144 new tokens. Evaluated with `preserve_thinking=true`.

## What makes it notable

It is the strongest published agentic dense model in the ~30B class on the harnesses labs actually use for agents in late 2026: 80.9 on Terminal-Bench 2.1 (`Terminus 2`), 65.5 on DeepSWE and 70.4 on Toolathlon-Verified — margins over Qwen3.8-27B of +7.9 / +23.0 / +1.9 points — paired with a 512K context and an XML/JSON tool contract that is explicitly designed for multi-turn agent loops. It is candid where it loses (SWE-Bench Pro 60.3 vs Qwen 61.7; GDPval 84.8 vs 86.4; GPQA Diamond 89.5 vs Gemma4-31B 91.3), and its reasoning numbers are essentially ties rather than wins — the differentiation is specifically long-horizon agent work, not raw knowledge. Two caveats matter for local use: everything is lab-reported with zero third-party verification as of 2026-10-26, and the harnesses (Terminus 2, mini-swe-agent v2.4.6, Claude Code) do not transfer automatically to Claude Code/Codex-style scaffolds. Deployment friction is low — stock Llama arch, Apache-2.0, no gate — but 33B dense at BF16 is a 66 GB footprint, so local runs mean a quant. It is also positioned as the *teacher* of a planned Nanbeige4.3-3B distillation (not yet released), which is the variant that would matter most for on-device agents.

## See also

- [[welcome]]
- Source: https://huggingface.co/Nanbeige/Nanbeige4.3-33B
- Base variant (skip — pretrain): https://huggingface.co/Nanbeige/Nanbeige4.3-33B-Base
- Prior family entry: [[Nanbeige--Nanbeige4.2-3B]]
- Coverage: https://explainx.ai/blog/nanbeige-4-3-33b-open-agentic-model-guide-2026 · https://startupfortune.com/nanbeiges-new-33b-open-model-takes-aim-at-qwen-and-gemma-on-coding/
- Community quants (created 2026-10-24/25, corroborate the drop date): MLX (`pratikgx`, `kapitsaprime`, `fcmeyer`), GGUF (`Razor3D`, `anik-jha`), oQ* (`pyros-vault`, `a-gordo`), EXL3 (`lxe`), W3A16 (`stuchapin`)
