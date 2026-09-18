---
title: "Open-weight LLM Weekly Recap — week of 2026-09-14–2026-09-20"
date: 2026-09-19
week_start: 2026-09-14
week_end: 2026-09-20
release_count: 1
tracker_total: 39
tags: [research, llm, open-weight, weekly-recap]
source: /home/pi/projects/llm-tracker/releases.md
---

## Open-weight LLM week of 2026-09-14–2026-09-20 (1 release)

### Headline

A quiet week with a single tracked release — but it's a distinctive one: Shanghai AI Lab GA'd **Intern-S2-397B**, a 397B Apache-2.0 scientific multimodal foundation model whose FrontierScience-Olympiad score of 87.0 beats GPT-5.5 (77.0) and Claude Opus 4.8 (68.0), with MMLU-Pro 89.77 the best open-weight score in the tracker's chart. The first open model this week that wins on *science*, not agentic coding.

### Releases (ranked by impact)

───────────────

**Shanghai AI Lab Intern-S2-397B** (397B MoE, ~17B active — Qwen3.5-397B-A17B arch; Apache 2.0; 2026-09-13)

• Key: MMLU-Pro 89.77 (best open in chart) · FrontierScience-Olympiad 87.0 · MMMU-Pro 81.68 · SWE-bench-Pro 68.54 · SWE-bench-Multilingual 84.0 (#1 in chart) · Terminal-Bench 2.1 64.04
• Beats: Qwen3.5-397B-A17B on MMLU-Pro (89.77 vs 87.80), DeepSeek-V4-Pro (86.86), GLM-5.2 (87.22); GPT-5.5 and Opus 4.8 on FrontierScience-Olympiad (87.0 vs 77.0 / 68.0); DeepSeek-V4-Pro on SWE-bench-Pro (68.54 vs 49.98); GLM-5.2 on SWE-bench-Multilingual (84.0 vs 82.0)
• Loses to: GLM-5.2 on Terminal-Bench 2.1 (64.04 vs 77.9); general agentic front-runners (Qwen3.8-Max, GLM-5.3) on SWE-bench/TB; no independent evals yet (llm-stats/BenchLM pages absent — vendor OpenCompass/VLMEvalKit chart)
• Why it matters: open-weight scientific model trained on rendered paper pages with 20+ science-domain RL — the strongest science-first capability profile yet, at flagship scale under Apache 2.0
🔗 https://huggingface.co/internlm/Intern-S2-397B · https://huggingface.co/internlm/Intern-S2-397B-FP8 · https://x.com/intern_lm/status/2099425184587370976

───────────────

### Trends this week

• Quiet week — 1 release in window; the tracker's Sep 17 sweep also caught same-lab **Atria Dawn Preview** (744B agentic MoE, dated Sep 11, just outside the window) whose arXiv report landed Sep 15.
• Specialization over scale: after weeks of agentic-coding MoE flagships (V4.1-Flash, GLM-5.3), this drop is a science/paper-trained multimodal model, and **Apache 2.0** remains the license of choice for Chinese-lab flagship weights (Hy4 preview, MiniCPM5 series, Intern-S2).
• Preview→GA cycle is now routine: Intern-S2 previewed Jul 16, GA'd Sep 13 — two months, consistent with Tencent Hy4's preview pattern.

### Looking ahead

DeepSeek **V4.1-Pro** is the clearest near-term signal — V4-Pro traffic has been rerouted to V4.1-Flash since Sep 14 pending the Pro release (per tracker). Watch also for independent evals of Intern-S2 (llm-stats/BenchLM pages absent so far) and FP8-sibling coverage of Atria Dawn.

### See also

- [[welcome]]
- Tracker: `/home/pi/projects/llm-tracker/releases.md` (39 cumulative releases)