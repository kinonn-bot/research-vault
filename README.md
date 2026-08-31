# Research Vault

Personal research notebook built with [Quartz](https://quartz.jzhao.xyz/) and deployed to GitHub Pages.

## Live site

**https://kinonn-bot.github.io/research-vault/**

## How it works

- Notes live in `content/` as plain Markdown.
- Build + deploy is driven by `~/.local/bin/vault-update`: it runs `npx quartz build`, then force-pushes the static output to the `gh-pages` branch. GitHub Pages serves that branch.
- Full-text search, backlinks, and Obsidian-style `[[wiki-links]]` all work in the published site.

## Local development

```bash
npm install
npx quartz plugin install
npx quartz build --serve   # preview at http://localhost:8080
```

## Adding a note

Drop a `.md` file into `content/` (or any subfolder), commit, and push:

```bash
git add content/
git commit -m "research: <topic>"
git push origin main        # source branch
vault-update --commit "deploy: <topic>"   # builds + publishes to gh-pages
```

## Folders

- `content/index.md` — homepage
- `content/research/` — research notes
- `content/inbox/` — quick captures
- `content/reference/` — durable reference
