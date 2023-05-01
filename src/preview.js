const express=require('express'),
      router=express.Router();
const path=require('path');
const ejs=require('ejs');
const fs=require('fs');
const Template=require('./template.js');
const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');
const highlightjs=require('highlight.js');
const fileSize=require('./lib/filesize.js');

var MarkdownIt=require('markdown-it')({
    html: true,
    linkify: true
});
MarkdownIt.use(require('markdown-it-katex'));

router.get('/',(req,res)=>{
    var problemList=fs.readFileSync('data/problem.json','utf8');
    problemList=JSON.parse(problemList);
    ejs.renderFile("./src/templates/problem_list.html",
        {isadmin: req.logined, fs, problemList, Config},(err,HTML)=>{
        res.send(Template({title: `题目列表`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/about',(req,res)=>{
    ejs.renderFile("./src/templates/about.html",
        {html: MarkdownIt.render(fs.readFileSync('data/readme.md','utf8'))},
    (err,HTML)=>{
        res.send(Template({title: `关于`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined,
                           onabout: true
                          },HTML));
    });
});

router.get('/problem/:pid',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_detail.html",{isadmin: req.logined, Config, prodata, fs, MarkdownIt},(err,HTML)=>{
        res.send(Template({title: `#${prodata.pid}. ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/solution',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_solution.html",
        {isadmin: req.logined, Config, prodata, MarkdownIt, fs, highlightjs},(err,HTML)=>{
        res.send(Template({title: `题解与代码 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/statements',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_statements_list.html",
        {isadmin: req.logined, Config, prodata, MarkdownIt, fs},(err,HTML)=>{
        res.send(Template({title: `题面列表 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/files',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_files.html",
        {isadmin: req.logined, fileSize, Config, prodata, fs},(err,HTML)=>{
        res.send(Template({title: `文件 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});

module.exports=router;