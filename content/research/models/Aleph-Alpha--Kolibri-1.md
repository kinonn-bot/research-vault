---
title: "Aleph-Alpha/Kolibri-1"
org: Aleph-Alpha
model_id: Aleph-Alpha/Kolibri-1
date: 2026-10-06
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - moe
  - reasoning
  - tool-calling
  - long-context
  - bilingual
  - eu-sovereign
downloads: 2453
likes: 603
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/Aleph-Alpha/Kolibri-1
params: "3.46B active (78.1B total; 384 experts, top-6 routed + 1 shared, 50 layers)"
context: "262,144 native; 1,048,576 by extrapolation (recommend <=262k)"
architecture: moe (4:1 sliding-window GQA : full-attention, 50 layers)
---

# Aleph-Alpha/Kolibri-1

**One-line:** Aleph Alpha's sovereign English/German MoE reasoning + tool-calling model — 78.1B total / 3.46B active, trained from scratch (20T tokens on 768x B200), 262k native context, released 2026-10-03 under Apache-2.0 (weights/config only). ⚠ Large: FP8 weights ~78 GB — needs an 80 GB-class GPU (1x H200/B200, or 2x A100/H100); not a 24 GB-consumer-GPU model. All numbers lab-reported — no independent leaderboard listing yet as of 2026-10-05; leads its comparison set on competition math + LiveCodeBench, behind Qwen3.6-35B-A3B on SWE-bench and tool use.

Surfaced via web search (release-day press + HN + Reddit), invisible to all three HF API streams: createdAt 2026-10-02 falls outside Stream A's 36h cut, and at ~2.5k downloads it never enters the top-200 fetch windows of Streams B/C — yet it satisfies the trending criteria (lastModified within 7 days, downloads >= 1000). Community GGUF quants appeared within 48h (`aparusel/kolibri-1-gguf`, `Hob-forge/Kolibri-1-GGUF`, `webmp3/Sakura-MicroQuality-Kolibri-1-*`), independently corroborating a real weight drop. BF16 sibling repo: `Aleph-Alpha/Kolibri-1-BF16` (created same day).

## Coding benchmarks

*All lab-reported (Aleph Alpha model card / tech report, evaluated at highest reasoning effort). No independent eval yet — not on Artificial Analysis or LMArena as of 2026-10-05.*

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | 92.7 | lab — vs Qwen3.6-35B-A3B 92.8, Qwen3.8 27B 94.7 |
| MBPP | — | not published |
| LiveCodeBench v6 | 85.9 | lab — vs Qwen3.6-35B-A3B 82.5, Qwen3.8 27B 93.8 |
| Aider polyglot | — | not published |
| SWE-bench Verified | 66.4 | lab — vs Qwen3.6-35B-A3B 73.8, Qwen3.8 27B 72.6, Nemotron 3 Super 60.2 |
| SWE-bench Multilingual | — | not published |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL v4 (overall) | 61.4 | lab — vs Qwen3.6-35B-A3B 67.2, Nemotron 3 Super 61.0 |
| BFCL v3 (multi-turn) | 39.8 | lab |
| τ²-Bench (Telecom / Retail / Airline) | 94.7 / 69.9 / 76.7 | lab — Telecom vs Qwen3.6 99.1 |
| τ³-Bench (Banking) | 38.1 | lab |
| TerminalBench 2.1 | 27.7 | lab — vs Qwen3.5-35B-A3B 39.7, Qwen3.8 27B 76.8 |
| BrowseComp | 29.4 | lab |
| ToolACE | — | not published |
| GAIA | — | not published |

Agentic training provenance: mid-training mix was 15.4% agentic code & tool use (~0% in pre-training); SFT included generated software-engineering datasets for code patches and bug fixing as a Terminus 2 agent; RL ran over tool-calling, SWE and terminal environments with randomized harnesses. Native "Hermes-style" tool calling via `--tool-call-parser kolibri1 --enable-auto-tool-choice`. Reasoning effort selectable: none / low / medium / high.

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | 80.0 (MMLU-Pro CoT, EN) | lab |
| GPQA Diamond | 84.3 (EN) / 81.3 (DE) | lab — leads comparison set (Qwen3.6 83.4, Nemotron 3 Super 78.0) |
| MATH | — | not published (GSM8K base variant: 89.8 EN) |
| AIME 2025 | 96.9 (EN) / 87.5 (DE) | lab — leads comparison set |
| AIME 2026 | 96.0 (EN) / 90.0 (DE) | lab — leads comparison set |
| HLE | 21.5 (EN) | lab |
| AA-Omniscience non-hallucination rate | 44.0 (public set) | lab — up from 14.8 predecessor; Qwen3.6 56.7 |

## Efficiency

- **Active params:** 3.46B active / 78.1B total (384 experts per layer, top-6 routed + 1 shared; expert hidden 512; hidden 2560; 50 layers; vocab 128k; UniBPE tokenizer)
- **Context length:** 262,144 native (trained), validated up to 1,048,576 by RoPE-free extrapolation; Aleph Alpha recommends <=262k for serving efficiency. RULER (base variant): 67.9 @128k → 63.2 @1M.
- **VRAM (fp8):** ~78 GB model memory. Minimum 2x A100 80GB / 2x H100 SXM5 / 1x H200 / 1x B200-B300. BF16 sibling ~156 GB. Field report: ~170 tok/s in FP8 on a single RTX Pro 6000 (HN).
- **Runtime:** custom architecture (`Kolibri1ForCausalLM`, model_type `kolibri1`) — needs Aleph Alpha's vLLM plugin (`pip install "aleph-alpha-inference>=1"`; container `ghcr.io/aleph-alpha/aleph-alpha-inference`). Stock vLLM will not load it. Community GGUF ports appeared 2026-10-05. Sampling: temp 1.0, top_p 0.97, top_k 128.
- Deployment note: text-only; knowledge cutoff 2026-06-18; FP8 is the primary released precision (quantization-aware trained — not a community re-quant).

## What makes it notable

Aleph Alpha's from-scratch European answer to the open-weight field: fully bilingual DE/EN (21.3% German pre-training tokens, custom UniBPE tokenizer that compresses German better than GPT-5's), Apache-2.0 weights, trained on 768x B200 in Germany/Finland, positioned on quality-per-serving-cost (3.46B active) and sovereignty (EU AI Act + GDPR documentation, fully air-gappable) rather than raw capability. It leads its own comparison set on math (AIME 2025/26: 96.9/96.0) and competitive coding (LiveCodeBench v6: 85.9, ahead of Qwen3.6-35B-A3B's 82.5) — but trails Qwen3.6 on SWE-bench Verified (66.4 vs 73.8), BFCL v4 (61.4 vs 67.2) and multi-turn tool use, and sits well behind the current frontier open models (Qwen3.8-27B 72.6; GLM-5.3 / Kimi K3 / MiMo-V2.6-Pro at the top). Third-party read (Trending Topics, 2026-10-03): not yet independently ranked; estimated ~15-20 on the Artificial Analysis Intelligence Index — behind 20+ open models. For agent-loop use: native tool calling + reasoning-effort control + 3.5B active decoding make it an efficient runner if you have >=80 GB-class VRAM, but validate BFCL-class reliability on your own harness — its tool-use numbers are mid-pack, and one field report notes heavy token spend from overthinking.

## See also

- [[welcome]]
- Source: https://huggingface.co/Aleph-Alpha/Kolibri-1
- BF16 sibling: https://huggingface.co/Aleph-Alpha/Kolibri-1-BF16
- Tech report: https://aleph-alpha.com/downloads/tech-report.pdf
- Release blog: https://aleph-alpha.com/en/blog/kolibri-has-landed-a-sovereign-open-weight-model/
