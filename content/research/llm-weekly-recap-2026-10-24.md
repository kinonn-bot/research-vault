---
title: "Open-weight LLM Weekly Recap — week of 2026-10-19–2026-10-25"
date: 2026-10-24
week_start: 2026-10-19
week_end: 2026-10-25
release_count: 1
tracker_total: 68
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

# Open-weight LLM Week of 2026-10-19 – 2026-10-25

_1 tracker-eligible release this week._

## Headline

A quiet week: the tracker registered a single new open-weights release — **SparkLLM (XHToken) Spark-X2.6-4B** (Oct 19), an Apache-2.0 4.1B dense model with 1M context that claims ~9B-class on-device performance on a vendor 20-benchmark average (63.3 vs 52.1 for its own X2.5-4B predecessor). Independent measurement is markedly less flattering: BenchLM ranks it 40.1/100 at #140/227.

## Releases (ranked by impact)

### SparkLLM (XHToken) Spark-X2.6-4B

4.1B dense, Apache 2.0, 2026-10-19 — 1M ctx, thinking none/low/high, 36 layers (3 SWA : 1 full), ~24GB VRAM self-host.

- **Key:** GPQA-D 77.1 · SWE-bench Verified 62.8 · SWE-bench Pro 54.3 · AIME26 91.2 · BFCL-V4 71.8 · IFEval 93.6 · IFBench 75.8 · MCP-Atlas 62.4 · τ³-bench 34.7 · BrowseComp 53.1 · LongBench v2 53.3 (vendor 20-bench average 63.3)
- **Beats:** its own predecessor Spark-X2.5-4B (average 52.1 → 63.3) and, on the same vendor 20-bench average, Qwen3.5-9B (49.1), Gemma4-12B (47.0), Qwen3.5-4B (43.2) and Gemma4-E4B (29.7) — an explicit ~9B-parity claim from a 4B model.
- **Loses to:** Qwen3.5-9B on GPQA-D (77.1 vs 80.9) and to Qwen3.6-35B-A3B on SWE-bench Verified (62.8 vs 73.4); on the independent BenchLM board it sits mid-pack (40.1/100, #140/227; Agentic #89/131, Coding #95/152, IF #62/149), well behind frontier small models.
- **Why it matters:** Architecture is unchanged from X2.5-4B — the entire +11.2-point average gain comes from post-training, which is the cheapest lever available to small-model labs; the gap between the vendor average and BenchLM's independent score is the useful caveat.
- Source: <https://huggingface.co/XHToken/Spark-X2.6-4B> · <https://benchlm.ai/models/spark-x2-6-4b>

## Trends this week

- **Near-empty week.** One row added (Oct 19); the daily scan appended nothing Oct 20–24. The tracker's "last updated" stamp (Oct 22) reflects a backfill catch — StepFun Step 5 Preview, weights live Sep 19–20 — not a new October release.
- **Post-training-only gains.** Spark-X2.6-4B keeps the X2.5-4B architecture and buys ~11 average points from post-training alone, matching a pattern already seen this quarter (Mellum2.1 Thinking, V4-Flash-0731, GLM-5.3, MiMo-V2.6).
- **Edge-first 4B class continues to crowd.** 1M context, ~24GB VRAM and day-1 MLX/GGUF/ROCm quants are now table stakes for sub-5B drops, and Apache 2.0 was the license again.
- **Vendor-vs-independent spread remains large** for self-reported small models — the vendor 20-bench average claim of ~9B parity is not reproduced by BenchLM's ranked score.

## Looking ahead

Nothing rumored or paper-stage was captured this week — the week's only tracker activity was the Oct 22 backfill of already-released weights (StepFun Step 5 Preview). No forward-looking signal to report.

## Tracker

68 cumulative releases · file at `/home/pi/projects/llm-tracker/releases.md`

## See also

- [[welcome]]
- `/home/pi/projects/llm-tracker/releases.md`
