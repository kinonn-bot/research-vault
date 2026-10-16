---
title: "Open-weight LLM Weekly Recap — week of 2026-10-12–2026-10-18"
date: 2026-10-17
week_start: 2026-10-12
week_end: 2026-10-18
release_count: 4
tracker_total: 54
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-10-12–2026-10-18 (4 releases)

### Headline

Ant Group's **Ling-3.1-flash** is the week's headline: a 560B / 25B-active MIT-licensed MoE whose weights dropped Oct 13 (API-only since Sep 30) that lands GDPval-AA v2.1 at 1673 Elo — ahead of GPT-5.6 Sol (1588), GLM-5.3 (1644) and DeepSeek V4.1-Flash (1600), trailing only Opus 5 (1708). Successor to the tracked Ling-3.0-flash and the largest open drop since the September flagships. Caveat: the Elo and Terminal-Bench rows are vendor-launch-chart numbers.

### Releases (ranked by impact)

───────────────

**Ant Group Ling-3.1-flash** (560B total / 25B active MoE — 512 routed + 1 shared expert, 8 activated; 7:1 KDA:Gated-MLA hybrid; MIT; 2026-10-13)

• Key: GDPval-AA v2.1 1673 Elo · Terminal-Bench 4.0 40.4 · CyberGym 87.9 · FrontierSWE 75.2 · DRACO 85.5 · SkillsBench 68.7 · BenchLM 60.6/100 (#50/220; Agentic 80.3; 210 tok/s measured)
• Beats: GPT-5.6 Sol on GDPval-AA (1673 vs 1588) and Terminal-Bench 4.0 (40.4 vs 39.9); GLM-5.3 on GDPval-AA (1673 vs 1644); Kimi K3 and DeepSeek V4.1-Flash on TB4 (12.6 / 31.2)
• Loses to: Opus 5 on GDPval-AA (1673 vs 1708) and TB4 (40.4 vs 49.0); GLM-5.3 on TB4 (40.4 vs 41.9)
• Why it matters: a 25B-active MoE carrying Ant's flagship line into frontier-adjacent territory under MIT, with SGLang/vLLM day-0 recipes and harness-ready tooling (Claude Code / Hermes Agent / OpenClaw).
🔗 https://huggingface.co/inclusionAI/Ling-3.1-flash · https://modelscope.cn/models/inclusionAI/Ling-3.1-flash · https://x.com/AntLingAGI/status/2105335205741596911

───────────────

**Liquid AI LFM2.5-24B-A2B** (24B total / 2.45B active MoE — 30 double-gated short-conv + 10 GQA layers, 64 experts top-4; LFM Open License v1.0; 2026-10-12)

• Key: AutomationBench 27.69 · LiveClaw 48.09 · ToolSandbox 80.71 · BFCLv4 65.01 · IFEval 96.75 · IFBench 74.69 · MATH-500 96.04 · GPQA-D 74.42 · SWE-bench Verified 51.0
• Beats: Qwen3.6-35B-A3B, Gemma-4-26B-A4B and Nemotron-3.5-Lightning on AutomationBench (27.69 vs 8.72 / 5.46 / 2.61 — ~3× next best); ToolSandbox (80.71 vs 75.02); IFEval (96.75 vs 93.06)
• Loses to: Qwen3.6-35B-A3B on GPQA-D (74.42 vs 83.69) and SWE-bench Verified (51.0 vs 66.2)
• Why it matters: the largest and final LFM2.5 model — near-best-in-class tool use at 2.45B active params, 184 tok/s on M5 Max, aimed squarely at on-device agents.
🔗 https://huggingface.co/LiquidAI/LFM2.5-24B-A2B · https://www.liquid.ai/blog/lfm2-5-24b-a2b · https://huggingface.co/blog/LiquidAI/lfm25-24b-a2b

───────────────

**OpenBMB MiniCPM-V 4.7 (35B-A3B & 1B)** (35B / 3B active MoE + 1B dense; SigLIP2 + Qwen3.5/3.6-family backbone; Apache 2.0; 2026-10-12)

• Key: MMBench 91.72 · MMMU 80.22 · OmniDocBench v1.6 94.24 · MMStar 80.7 (4× visual-token compression)
• Beats: Qwen3.6-35B-A3B, Qwen3.8-27B and Gemma-4-31B on the published chart rows; 1B variant > Qwen3.5-0.8B
• Loses to: nothing listed on its own chart — vendor-selected evals; no independent rows yet
• Why it matters: first MoE in the MiniCPM-V series and the first open-weight MoE VLM that runs smoothly on-device (13+ tok/s on iPhone 17 Pro Max at ~3GB); day-0 FP8/GGUF/AWQ/int4 quants.
🔗 https://huggingface.co/openbmb/MiniCPM-V-4.7-35B-A3B · https://huggingface.co/openbmb/MiniCPM-V-4.7-1B · https://github.com/OpenBMB/MiniCPM-V

───────────────

**AutoTrust AI JEV-35B** (35B / 3B active MoE — Qwen3.5-35B-A3B finetune, up to 256 options per pass; Apache 2.0; 2026-10-11)

• Key: Decision Index 0.3 public 59.73 (own-kit scoring — not a board entry) · vision rebuild 71.94 · ERQA 51.3% one-pass · 204 ms median per decision (B200) · NVFP4 sibling 25.6 GB
• Beats: JEV-27B-VL on vision rebuild (71.94 vs 71.67) and latency (204 vs 271 ms); 7–9B embodied models (42.3–47.5) on ERQA
• Loses to: vLLM-SR d3 — same-generation open decision-model leader (DI 66.3 vs 59.73); PhysBrain 1.5 on ERQA (52.8 vs 51.3)
• Why it matters: another independent entrant in the zero-output-token decision-model niche — a category that is now shipping weekly.
🔗 https://huggingface.co/autotrust/JEV-35B · https://huggingface.co/autotrust/JEV-35B-NVFP4 · https://huggingface.co/blog/autotrust/one-decision-model-instead-of-a-ranking-team-short

───────────────

### Trends this week

• **Edge-first MoE cluster.** Three of four releases ship ≤3B active params (2.45B, 3B, 3B) with phone / Apple-Silicon throughput as headline numbers — on-device deployment is now a first-class release category, not a demo.
• **Decision models compound.** JEV-35B is the sixth zero-output-token "system-one" model tracked since Oct 1 (Clef, Strands Decider 2B, H2O-Lightning, d1, vLLM-SR d3, JEV-35B); the same-generation open leader is still vLLM-SR d3 (DI 66.3).
• **Permissive licenses all around.** MIT (Ling) + Apache 2.0 ×2 (MiniCPM-V 4.7, JEV-35B) + LFM Open License v1.0 — no new custom or restricted licenses this week, and all four releases are low-activation MoE.

### Looking ahead

DeepSeek's V4.1-Pro remains the clearest pending open drop (V4-Pro traffic has been rerouted to V4.1-Flash "until V4.1-Pro" ships), and Qwen's Qwen4-architecture preview line (GDN+QSA) continues via Qwen3.8-Flash-Next. Independent (BenchLM / llm-stats) rows for this week's releases are the thing to watch after September's benchmaxxing episode.

### See also

- [[welcome]]
- Tracker: `/home/pi/projects/llm-tracker/releases.md` (54 cumulative releases)
