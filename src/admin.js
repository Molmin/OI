import { Router } from 'express'
const router = Router()
import { renderFile } from 'ejs'
import { readFileSync, writeFileSync, mkdirSync, unlinkSync } from 'fs'
import Template from './template.js'
var System = JSON.parse(readFileSync('./data/system.json'))
import { checkloginByReq, checkloginByPassword, Encode } from './lib/admin.js'
import { parse } from 'url'
import deletedir from './lib/deletedir.js'
import { list, log } from './lib/logger.js'
import { backupFile, newOperationId } from './lib/backup.js'

router.all('*', (req, res, next) => {
  if (req._parsedUrl.pathname.startsWith('/login') || checkloginByReq(req)) next()
  else return res.redirect('/admin/login')
})

router.get('/', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  renderFile("./src/templates/dashboard.html", { logs: list(), System }, (err, HTML) => {
    res.send(Template({
      title: `仪表盘`,
      header: ``,
      preview: true,
      onadmin: true,
      isadmin: req.logined
    }, HTML))
  })
})

import ChildProcess from 'child_process'
import GitHubPages from 'gh-pages'
import Builder from './build/main.js'

router.post('/update/db', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  ChildProcess.spawnSync('npx', ['gh-pages-clean'])
  GitHubPages.publish('data', {
    branch: System.repository.db.branch,
    message: req.body.message,
    repo: System.repository.db.repo
  }, err => {
    if (err) {
      res.status(200).json({ error: err.message })
      log(req, `failed to update database to github: ${err}`)
    }
    else {
      res.status(200).json({ message: "同步成功。" })
      log(req, `updated database to github`)
    }
  })
})
router.post('/update/ghpage', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  Builder()
  setTimeout(() => {
    ChildProcess.spawnSync('npx', ['gh-pages-clean'])
    GitHubPages.publish('dist', {
      branch: System.repository.ghpage.branch,
      message: req.body.message,
      repo: System.repository.ghpage.repo
    }, err => {
      if (err) {
        res.status(200).json({ error: err.message })
        log(req, `failed to update github page: ${err}`)
      }
      else {
        res.status(200).json({ message: "同步成功。" })
        log(req, `updated github page`)
      }
    })
  }, 1000)
})

router.get('/settings', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  renderFile("./src/templates/settings.html", { System, fs }, (err, HTML) => {
    res.send(Template({
      title: `系统设置`,
      header: ``,
      preview: true,
      onadmin: true,
      isadmin: req.logined
    }, HTML))
  })
})

router.get('/login', (req, res) => {
  if (req.logined) {
    res.redirect("/")
    return
  }
  renderFile("./src/templates/login.html", (err, HTML) => {
    res.send(Template({
      title: `Login`,
      header: ``,
      preview: true,
      onadmin: true,
      isadmin: req.logined
    }, HTML))
  })
})
router.post('/login/try', (req, res) => {
  if (req.logined) {
    res.status(200).json({ error: '已经登录成功。' })
    return
  }
  if (checkloginByPassword(req.body.password)) {
    res.cookie("oiblog-cookie", Encode(req.body.password), { maxAge: 1000 * 60 * 60 * 24 })
    res.status(200).json({ success: true })
  }
  else res.status(200).json({ error: '密码错误。' })
})
router.get('/logout', (req, res) => {
  if (req.logined) {
    res.cookie("oiblog-cookie", '')
    if (!req.headers.referer) return res.redirect("/")
    var direct = parse(req.headers.referer)
    if (direct.host != req.headers.host) res.redirect("/")
    else res.redirect(direct.href)
  }
  else res.redirect('/')
})

router.get('/create', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  renderFile("./src/templates/problem_create.html", { System }, (err, HTML) => {
    res.send(Template({
      title: `创建题目`,
      header: ``,
      preview: true,
      onadmin: true,
      isadmin: req.logined
    }, HTML))
  })
})
router.get('/problem/:pid/config', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  prodata.pid = req.params.pid
  renderFile("./src/templates/problem_config.html",
    { isadmin: req.logined, System, prodata }, (err, HTML) => {
      res.send(Template({
        title: `修改配置 - ${prodata.title}`,
        header: ``,
        preview: true,
        isadmin: req.logined
      }, HTML))
    })
})
router.post('/problem/:pid/edit', (req, res) => {
  if (req.params.pid == '0') {
    var pid = "", charlist = "abcdefghijklmnopqrstuvwxyz01234567890123456789"
    for (var i = 0; i < 6; i++)
      pid += charlist[parseInt(Math.random() * charlist.length)]
    var problemList = readFileSync('data/problem.json', 'utf8')
    var tmp = JSON.parse(problemList)
    tmp.push(pid)
    problemList = JSON.stringify(tmp, null, "  ")
    writeFileSync('data/problem.json', problemList)
    mkdirSync(`data/${pid}`)
    var problemConfig = JSON.parse(req.body.prodata)
    problemConfig.statement = { "简体中文": "statement_zh.md" }
    problemConfig.solution = []
    writeFileSync(`data/${pid}/config.json`, JSON.stringify(problemConfig, null, "  "))
    writeFileSync(`data/${pid}/statement_zh.md`, req.body.statement)
    log(req, `created a problem (${pid})`)
    res.status(200).json({ pid })
  }
  else {
    var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
    var problemConfig = JSON.parse(req.body.prodata)
    prodata.title = problemConfig.title
    prodata.difficulty = problemConfig.difficulty
    prodata.judge = problemConfig.judge
    prodata.tags = problemConfig.tags
    prodata.source = problemConfig.source
    var opId = newOperationId()
    backupFile(opId, `${req.params.pid}/config.json`)
    writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
    log(req, `edited a problem (${req.params.pid})`, opId)
    res.status(200).json({ pid })
  }
})
router.post('/problem/:pid/delete', (req, res) => {
  var opId = newOperationId()
  backupFile(opId, `${req.params.pid}`, true)
  deletedir(`data/${req.params.pid}`)
  var problemList = readFileSync('data/problem.json', 'utf8')
  var tmp = JSON.parse(problemList)
  var i = 0
  while (tmp[i] && tmp[i] != req.params.pid) i++
  tmp.splice(i, 1)
  problemList = JSON.stringify(tmp, null, "  ")
  writeFileSync('data/problem.json', problemList)
  log(req, `deleted a problem (${req.params.pid})`, opId)
  res.json({})
})

router.get('/problem/:pid/statement/create', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  prodata.pid = req.params.pid
  renderFile("./src/templates/problem_statement_create.html",
    { isadmin: req.logined, System, prodata }, (err, HTML) => {
      res.send(Template({
        title: `创建题面 - ${prodata.title}`,
        header: ``,
        preview: true,
        isadmin: req.logined
      }, HTML))
    })
})
router.post('/problem/:pid/statement/create', (req, res) => {
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  if (prodata.statement[req.body.name]) req.body.name += ' (1)'
  prodata.statement[req.body.name] = req.body.file
  var opId = newOperationId()
  backupFile(opId, `${req.params.pid}/${req.body.file}`)
  backupFile(opId, `${req.params.pid}/config.json`)
  writeFileSync(`data/${req.params.pid}/${req.body.file}`, req.body.code)
  writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
  log(req, `created a statement (${req.params.pid}/${req.body.file})`, opId)
  res.status(200).json({})
})
router.get('/problem/:pid/statement/:statementName/edit', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  prodata.pid = req.params.pid
  renderFile("./src/templates/problem_statement_edit.html",
    { isadmin: req.logined, System, prodata, statementName: req.params.statementName, fs }, (err, HTML) => {
      res.send(Template({
        title: `编辑题面 - ${prodata.title}`,
        header: ``,
        preview: true,
        isadmin: req.logined
      }, HTML))
    })
})
router.post('/problem/:pid/statement/:statementName/delete', (req, res) => {
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  {
    var total = 0
    for (var key in prodata.statement) total++
    if (total < 2) {
      res.status(200).json({})
      return
    }
  }
  var key = req.params.statementName
  if (!prodata.statement[key]) {
    res.status(200).json({})
    return
  }
  var opId = newOperationId()
  backupFile(opId, `${req.params.pid}/${prodata.statement[key]}`)
  backupFile(opId, `${req.params.pid}/config.json`)
  unlinkSync(`data/${req.params.pid}/${prodata.statement[key]}`, err => { })
  delete prodata.statement[key]
  writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
  log(req, `deleted a statement (${req.params.pid}/${prodata.statement[key]})`, opIdd)
  res.status(200).json({})
})
router.post('/problem/:pid/statement/:statementName/edit', (req, res) => {
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  var key = req.params.statementName
  var opId = newOperationId()
  backupFile(opId, `${req.params.pid}/${prodata.statement[key]}`)
  backupFile(opId, `${req.params.pid}/config.json`)
  unlinkSync(`data/${req.params.pid}/${prodata.statement[key]}`, err => { })
  delete prodata.statement[key]
  if (prodata.statement[req.body.name]) req.body.name += ' (1)'
  prodata.statement[req.body.name] = req.body.file
  writeFileSync(`data/${req.params.pid}/${req.body.file}`, req.body.newCode)
  writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
  log(req, `edited a statement (${req.params.pid}/${prodata.statement[key]})`, opId)
  res.status(200).json({})
})

router.post('/problem/:pid/solution/:para/delete', (req, res) => {
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  var tmp = prodata.solution[req.params.para]
  var opId = newOperationId()
  backupFile(opId, `${req.params.pid}/config.json`)
  backupFile(opId, `${req.params.pid}/${prodata.solution[req.params.para].file}`)
  unlinkSync(`data/${req.params.pid}/${prodata.solution[req.params.para].file}`)
  if (prodata.solution[req.params.para].code)
    unlinkSync(`data/${req.params.pid}/${prodata.solution[req.params.para].code}`),
      backupFile(opId, `${req.params.pid}/${prodata.solution[req.params.para].code}`)
  prodata.solution.splice(req.params.para, 1)
  writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
  log(req, `deleted a section of solutions (${req.params.pid}/${tmp.file}${tmp.code ? `,${tmp / code}` : ''})`, opId)
  res.json({})
})
router.get('/problem/:pid/solution/:para/edit', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  prodata.pid = req.params.pid
  renderFile("./src/templates/problem_solution_edit.html",
    { isadmin: req.logined, System, fs, prodata, paraId: req.params.para }, (err, HTML) => {
      res.send(Template({
        title: `编辑题解 - ${prodata.title}`,
        header: ``,
        preview: true,
        isadmin: req.logined
      }, HTML))
    })
})
router.post('/problem/:pid/solution/:para/edit', (req, res) => {
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  var opId = newOperationId()
  backupFile(opId, `${req.params.pid}/config.json`)
  backupFile(opId, `${req.params.pid}/${prodata.solution[req.params.para].file}`)
  unlinkSync(`data/${req.params.pid}/${prodata.solution[req.params.para].file}`)
  writeFileSync(`data/${req.params.pid}/${req.body.filename}`, req.body.code)
  prodata.solution[req.params.para].title = req.body.title
  prodata.solution[req.params.para].file = req.body.filename
  prodata.solution[req.params.para].author = req.body.author
  writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
  log(req, `edited a section of solutions (${req.params.pid}/${prodata.solution[req.params.para].file})`, opId)
  res.json({})
})
router.get('/problem/:pid/solution/:para/editcode', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  prodata.pid = req.params.pid
  renderFile("./src/templates/problem_solution_editcode.html",
    { isadmin: req.logined, System, fs, prodata, paraId: req.params.para }, (err, HTML) => {
      res.send(Template({
        title: `编辑附加代码 - ${prodata.title}`,
        header: ``,
        preview: true,
        isadmin: req.logined
      }, HTML))
    })
})
router.post('/problem/:pid/solution/:para/editcode', (req, res) => {
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8')),
    tmp = prodata.solution[req.params.para]
  var opId = newOperationId()
  backupFile(opId, `${req.params.pid}/config.json`)
  if (prodata.solution[req.params.para].code)
    unlinkSync(`data/${req.params.pid}/${prodata.solution[req.params.para].code}`),
      backupFile(opId, `${req.params.pid}/${prodata.solution[req.params.para].code}`),
      delete prodata.solution[req.params.para].code
  if (req.body.code.length > 0) {
    prodata.solution[req.params.para].code = req.body.filename
    writeFileSync(`data/${req.params.pid}/${req.body.filename}`, req.body.code)
  }
  writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
  log(req, `edited a code of solutions (${req.params.pid}/${tmp.file},/${tmp.code})`, opId)
  res.json({})
})
router.get('/problem/:pid/solution/:para/insert', (req, res) => {
  System = JSON.parse(readFileSync('./data/system.json'))
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  prodata.pid = req.params.pid
  renderFile("./src/templates/problem_solution_insert.html",
    { isadmin: req.logined, System, prodata, paraId: req.params.para }, (err, HTML) => {
      res.send(Template({
        title: `插入段 - ${prodata.title}`,
        header: ``,
        preview: true,
        isadmin: req.logined
      }, HTML))
    })
})
router.post('/problem/:pid/solution/:para/insert', (req, res) => {
  var prodata = JSON.parse(readFileSync(`data/${req.params.pid}/config.json`, 'utf8'))
  writeFileSync(`data/${req.params.pid}/${req.body.filename}`, req.body.code)
  prodata.solution.splice(req.params.para, 0, {
    title: req.body.title,
    file: req.body.filename, author: req.body.author
  })
  writeFileSync(`data/${req.params.pid}/config.json`, JSON.stringify(prodata, null, "  "))
  log(req, `inserted a section of solutions (${req.params.pid}/${req.body.filename})`)
  res.json({})
})

export default router