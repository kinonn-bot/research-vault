---
title: "Moonshot AI / Kimi K3"
org: moonshotai
model_id: moonshotai/Kimi-K3
date: 2026-07-27
tags:
  - huggingface
  - text-generation
  - coding
  - agentic
  - multimodal
  - instruct
  - moe
  - mla
  - thinking
downloads: 2850
likes: 0
license: kimi-k3
pipeline: image-text-to-text
source: https://huggingface.co/moonshotai/Kimi-K3
params: 104B active (2.8T total)
context: 1048576
architecture: moe
---

# Moonshot AI / Kimi K3

**One-line:** World's first open 3T-class model — 2.8T MoE with 104B active params, native multimodal, 1M context, frontier-level coding and agentic benchmarks.

⚠ **Lab-reported benchmarks only** — no independent third-party evaluations published yet. All numbers below are from Moonshot's own tech report (July 2026). Treat with appropriate skepticism.

## Coding benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| DeepSWE | 67.5 | lab |
| ProgramBench | 77.8 | lab |
| Terminal-Bench 2.1 | 88.3 | lab |
| FrontierSWE | 81.2 | lab |
| SWE-Marathon | 42.0 | lab |
| PostTrainBench | 36.6 | lab |
| MLS-Bench-Lite | 48.3 | lab |
| SciCode | 58.7 | lab |
| Kimi Code Bench 2.0 | 72.9 | lab |
| HumanEval | — | — |
| Aider polyglot | — | — |
| SWE-bench Verified | — | — |

## Agentic / tool-use benchmarks

| Benchmark | Score | Source |
|:---|---:|:---|
| BrowseComp | 91.2 | lab |
| DeepSearchQA (F1) | 95.0 | lab |
| ResearchRubrics | 76.2 | lab |
| GDPval-AA v2 (Elo) | 1686 | lab (via Artificial Analysis) |
| Toolathlon-Verified | 76.5 | lab (via Artificial Analysis) |
| MCPMark-Verified | 94.5 | lab |
| MCP-Atlas | 84.2 | lab |
| AutomationBench | 30.8 | lab |
| JobBench | 54.3 | lab |
| AA-Briefcase (Elo) | 1548 | lab (via Artificial Analysis) |
| Agents' Last Exam | 28.3 | lab (via official leaderboard) |
| APEX-Agents | 41.0 | lab (via Mercor leaderboard) |
| τ³-Banking | 33.4 | lab (via Artificial Analysis) |
| OSWorld-Verified | 84.8 | lab |
| OSWorld 2.0 | 58.3 | lab |
| SaaS-Bench | 60.1 | lab |
| Harvey Lab-AA | 94.6 | lab (via Artificial Analysis) |
| CorpFin v2 | 71.6 | lab (via Vals AI) |
| Finance Agent v2 | 54.4 | lab (via Vals AI) |
| Legal Research Bench | 44.2 | lab (via Vals AI) |
| SpreadsheetBench 2 | 34.8 | lab |
| BFCL | — | — |
| τ-Bench | — | — |
| ToolACE | — | — |
| GAIA | — | — |

## Reasoning (context only)

| Benchmark | Score | Source |
|:---|---:|:---|
| GPQA Diamond | 93.5 | lab |
| CritPt | 23.4 | lab |
| AA-LCR | 74.7 | lab |
| HLE-Full | 43.5 / 56.0 | lab |

## Efficiency

- **Active params:** 104B (total 2.8T MoE — 896 experts, 16 active + 2 shared)
- **Context length:** 1,048,576 tokens (1M)
- **VRAM (fp16 rough):** ⚠ ~208 GB for active params alone; shipped as MXFP4 weights so actual deployment VRAM depends on quantization support. Requires multi-GPU cluster.
- **Architecture:** MoE with Kimi Delta Attention (KDA) + Gated MLA, 93 layers, SiTU-GLU activation, MoonViT-V2 vision encoder (401M)
- **Quantization:** MXFP4 weights / MXFP8 activations (quantization-aware training from SFT stage)

## What makes it notable

Kimi K3 is the world's first open-weight 3T-class model. At 104B active parameters, it's in the same ballpark as DeepSeek-V3/V4 active params but with 2.8T total — roughly 2.5× scaling efficiency improvement over Kimi K2 via the Stable LatentMoE framework. The coding benchmarks are competitive with GPT-5.6 and Claude Fable 5 on several tasks (Terminal-Bench 2.1: 88.3 vs 88.8 GPT-5.6; FrontierSWE: 81.2 vs 71.3 GPT-5.6). The agentic benchmarks are strong but not uniformly frontier-beating — BrowseComp 91.2 leads the field, but Agents' Last Exam 28.3 trails GPT-5.6's 29.6. The license is MIT-like with revenue thresholds ($20M+ MaaS or 100M+ MAU triggers separate agreement). This is NOT a local/edge model — the 104B active params require a multi-GPU inference cluster. The weights ship as MXFP4 quantized, which helps but still demands serious hardware. Worth tracking for anyone evaluating open-weight frontier models for agent loops at scale.

## See also

- [[welcome]]
- Source: https://huggingface.co/moonshotai/Kimi-K3
- Tech report: https://github.com/MoonshotAI/Kimi-K3/blob/main/k3_tech_report.pdf
- Blog: https://www.kimi.com/blog/kimi-k3
