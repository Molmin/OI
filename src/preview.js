const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const fs=require('fs');
const Template=require('./template.js');
var System=JSON.parse(fs.readFileSync('./data/system.json'));
const highlightjs=require('highlight.js');
const fileSize=require('./lib/filesize.js');
const Tag=require('./lib/tag.js');
var MarkdownIt=require('./lib/markdown.js');

router.get('/',(req,res)=>{
    var problemList=fs.readFileSync('data/problem.json','utf8');
    problemList=JSON.parse(problemList);
    System=JSON.parse(fs.readFileSync('./data/system.json'));
    ejs.renderFile("./src/templates/problem_list.html",
        {isadmin: req.logined, fs, problemList, System, Tag},(err,HTML)=>{
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
    System=JSON.parse(fs.readFileSync('./data/system.json'));
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_detail.html",
    {isadmin: req.logined, System, prodata, fs, MarkdownIt, Tag},(err,HTML)=>{
        res.send(Template({title: `#${prodata.pid}. ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/solution',(req,res)=>{
    System=JSON.parse(fs.readFileSync('./data/system.json'));
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_solution.html",
        {isadmin: req.logined, System, prodata, MarkdownIt, fs, highlightjs},(err,HTML)=>{
        res.send(Template({title: `题解与代码 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/statements',(req,res)=>{
    System=JSON.parse(fs.readFileSync('./data/system.json'));
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_statements_list.html",
        {isadmin: req.logined, System, prodata, MarkdownIt, fs},(err,HTML)=>{
        res.send(Template({title: `题面列表 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/comment',(req,res)=>{
    System=JSON.parse(fs.readFileSync('./data/system.json'));
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_comment.html",
        {isadmin: req.logined, prodata, System},(err,HTML)=>{
        res.send(Template({title: `评论 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/files',(req,res)=>{
    System=JSON.parse(fs.readFileSync('./data/system.json'));
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_files.html",
        {isadmin: req.logined, fileSize, System, prodata, fs},(err,HTML)=>{
        res.send(Template({title: `文件 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/file/:filename',(req,res)=>{
    if(fs.existsSync(`data/${req.params.pid}/${req.params.filename}`))
        res.sendFile(`data/${req.params.pid}/${req.params.filename}`,{root:process.cwd()},err=>{});
    else res.sendStatus(404);
});

module.exports=router;