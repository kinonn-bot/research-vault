---
title: "bytkim/Qwen3.8-27B-pi"
org: bytkim
model_id: bytkim/Qwen3.8-27B-pi
date: 2026-10-08
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - instruct
  - dense
  - qwen
  - pi-harness
  - terminal-bench
downloads: 1577
likes: 57
license: apache-2.0
pipeline: text-generation
source: https://huggingface.co/bytkim/Qwen3.8-27B-pi
params: "27B dense (full fine-tune of Qwen3.8-27B)"
context: "262,144"
architecture: "dense (Qwen3.8-27B; native MTP head; mirrored DFlash2 speculative-decode companion)"
---

# bytkim/Qwen3.8-27B-pi

**One-line:** Harness-specific Qwen3.8-27B fine-tune for the Pi coding agent (pi.dev) — SFT on filtered successful Pi sessions + GRPO with a reasoning-efficiency reward — matching base accuracy with ~30% fewer output tokens in an independent 12-instance Claude Code SWE-bench trial, and 79.8% vs 75.3% on Terminal-Bench 2.1 xhigh (lab-reported in-card figure). ⚠ Provenance: quality numbers are lab-reported figures plus a small (test-free) third-party trial; no full SWE-bench Verified / Aider / BFCL numbers published.

Caught by the trending cross-check in the 2026-10-08 run: at 1,577 downloads it sits below the top-200 fetch cutoffs of Streams B/C, and its lastModified cleared the 7-day window by under an hour. Community traction: 17k downloads on the GGUF sibling within a week, quant repacks (e.g. signalnine/Qwen3.8-27B-pi-q27), positive r/LocalLLaMA field tests.

## Coding benchmarks

*No HumanEval / MBPP / LiveCodeBench / Aider numbers published. The SWE-bench row is a 12-instance subset trial by signalnine (third-party repacker), NOT an official SWE-bench Verified score.*

| Benchmark | Score | Source |
|:---|---:|:---|
| HumanEval | — | not published |
| HumanEval+ | — | not published |
| MBPP | — | not published |
| LiveCodeBench | — | not published |
| Aider polyglot | — | not published |
| SWE-bench Verified | 11/12 gold patches on a 12-instance subset (base: also 11/12) — 8,593 vs 12,250 output tokens, 53s vs 75s wall | third-party (signalnine, 2026-10-05; Claude Code harness, RTX 5090; "gold" = patch touched a file the reference fix touches; tests not run; per-instance swings are large) |
| SWE-bench Multilingual | — | not published |

## Agentic / tool-use benchmarks

*No BFCL / τ-Bench / ToolACE / GAIA. Terminal-Bench 2.1 rows are the card's own battery — lab-reported in-card figures, NOT third-party; the Pi-side runs used the FP8 sibling.*

| Benchmark | Score | Source |
|:---|---:|:---|
| BFCL | — | not published |
| τ-Bench | — | not published |
| ToolACE | — | not published |
| GAIA | — | not published |
| Terminal-Bench 2.1 (xhigh, 89 tasks) | 79.8% @ 55.6k output tokens (base: 75.3% @ 63.5k) | lab-reported figure (Pi at FP8) |
| Terminal-Bench 2.1 (medium) | 75.3% @ 37.4k tokens — matches base's xhigh accuracy with ~41% fewer tokens | lab-reported figure |
| Terminal-Bench 2.1 (low) | 71.9% @ 36.1k tokens | lab-reported figure |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| MMLU / MMLU-Pro | — | not published |
| GPQA Diamond | 86.36% xhigh attempt pass rate (684/792; base: 80.93%, 641/792) | lab-reported figure |
| MATH | — | not published |
| AIME 2025 | — | not published |
| SciCode | 48.37% subproblems passed (163/337; base: 45.40%, 153/337) | lab-reported figure |

## Efficiency

- **Active params:** 27B dense (full fine-tune of Qwen3.8-27B; native MTP head packaged for speculative decoding)
- **Context length:** 262,144 tokens; FP8 KV cache supported; vLLM + SGLang launch recipes in the card
- **VRAM (fp16 rough):** ≈54 GB at BF16 (~28 GB at FP8, arithmetic) — consumer GPUs need FP8/GGUF; GGUF quants are "calibrated using complete Pi coding sessions". DFlash2 draft (~3.9 GB BF16, mirrored from Inco AI) gives extra decode speedup — signalnine measured 226.8 → 242.2 tok/s decode under DFlash2
- **Serving:** vLLM quickstart with `qwen3` reasoning parser + `qwen3_xml` tool parser + MTP speculative config; default sampling baked into `generation_config.json` (thinking: temp 1.0 / top_p 0.95 / top_k 20)

## What makes it notable

The Pi harness's house model, built for exactly the loop this tracker exists for — read the repo, edit, run tools, react to feedback. Two signals say the bet is token efficiency at equal task accuracy: (a) the card's Terminal-Bench 2.1 figures (89 tasks) put xhigh at 79.8% vs base 75.3% with ~12% fewer output tokens, and the medium setting (75.3% @ 37.4k tokens) matches base's xhigh accuracy at ~41% fewer tokens — the claim that makes it attractive for long agent sessions; (b) signalnine's independent 12-instance Claude Code trial on SWE-bench Verified instances landed the same 11/12 gold patches in ~30% less wall time. Within a week of release it was being pulled locally — 17k GGUF downloads, a q27 repack, positive field reports on r/LocalLLaMA. Caveats: the headline numbers are either the author's own figures or a small, test-free trial; the 54 GB BF16 footprint needs FP8/GGUF on consumer hardware; and base Qwen3.8-27B remains the conservative pick where full ecosystem validation and untouched sampling behavior matter.

## See also

- [[welcome]]
- Source: https://huggingface.co/bytkim/Qwen3.8-27B-pi
- Formats: https://huggingface.co/bytkim/Qwen3.8-27B-pi-GGUF · https://huggingface.co/bytkim/Qwen3.8-27B-pi-FP8
- Base: [[Qwen/Qwen3.8-27B]]
- Independent trial + q27 repack: https://huggingface.co/signalnine/Qwen3.8-27B-pi-q27
