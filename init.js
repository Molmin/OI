import { existsSync, writeFileSync } from 'fs'
import { ensureDirSync } from 'fs-extra'

ensureDirSync('data')
if (!existsSync('data/problem.json')) writeFileSync('data/problem.json', '[]')
if (!existsSync('data/readme.md')) writeFileSync('data/readme.md', '# Hi, there!')
if (!existsSync('data/system.json')) writeFileSync('data/system.json', JSON.stringify({
    port: 8299,
    eachPage: 30,
    commentHtml: `
<script
    src="https://giscus.app/client.js"
    data-repo="Molmin/giscus"
    data-repo-id="R_kgDOJozg2g"
    data-category="Discussions"
    data-category-id="DIC_kwDOJozg2s4CWzyJ"
    data-mapping="pathname"
    data-strict="1"
    data-reactions-enabled="1"
    data-emit-metadata="1"
    data-input-position="top"
    data-theme="light"
    data-lang="zh-CN"
    data-loading="lazy"
    crossorigin="anonymous"
    async
></script>`,
    repository: {
        "db": {
            "repo": "git@github.com:Molmin/OI-data.git",
            "branch": "data"
        },
        "ghpage": {
            "repo": "git@github.com:Molmin/OI.git",
            "branch": "gh-pages"
        }
    },
    on: "OI",
    title: "OI Problems"
}, null, "    "))
if (!existsSync('data/system.log')) writeFileSync('data/system.log', '')