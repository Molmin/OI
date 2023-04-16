const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const fs=require('fs');
const Template=require('./template.js');

var MarkdownIt=require('markdown-it')({
    html: true,
    linkify: true
});
MarkdownIt.use(require('markdown-it-katex'));

router.get('/',(req,res)=>{
    ejs.renderFile("./src/templates/problem_list.html",{isadmin: req.logined},(err,HTML)=>{
        res.send(Template({title: `Problem List`,
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
        res.send(Template({title: `About`,
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
    ejs.renderFile("./src/templates/problem_detail.html",{isadmin: req.logined, prodata, fs, MarkdownIt},(err,HTML)=>{
        res.send(Template({title: `#${prodata.pid}. ${prodata.title}`,
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
        {isadmin: req.logined, prodata, MarkdownIt, fs},(err,HTML)=>{
        res.send(Template({title: `题面列表 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/statement/create',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_statement_create.html",
        {isadmin: req.logined, prodata},(err,HTML)=>{
        res.send(Template({title: `创建题面 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});

module.exports=router;