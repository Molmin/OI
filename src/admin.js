const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const fs=require('fs');
const Template=require('./template.js');
const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');
const Admin=require('./lib/admin.js');
const URL=require('url');

router.all('*',(req,res,next)=>{
    if(req._parsedUrl.pathname.startsWith('/login')||Admin.checkloginByReq(req))next();
    else return res.redirect('/admin/login');
});
router.get('/login',(req,res)=>{
    if(req.logined){
        res.redirect("/");
        return;
    }
    ejs.renderFile("./src/templates/login.html",(err,HTML)=>{
        res.send(Template({title: `Login`,
                           header: ``,
                           preview: true,
                           onadmin: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.post('/login/try',(req,res)=>{
    if(req.logined){
        res.status(200).json({error: '已经登录成功。'});
        return;
    }
    if(Admin.checkloginByPassword(req.body.password)){
        res.cookie("oiblog-cookie",Admin.Encode(req.body.password),{maxAge: 1000*60*60*24});
        res.status(200).json({success: true});
    }
    else res.status(200).json({error: '密码错误。'})
});
router.get('/logout',(req,res)=>{
    if(req.logined){
        res.cookie("oiblog-cookie",'');
        if(!req.headers.referer)return res.redirect("/");
        var direct=URL.parse(req.headers.referer);
        if(direct.host!=req.headers.host)res.redirect("/");
        else res.redirect(direct.href);
    }
    else res.redirect('/');
});

router.get('/create',(req,res)=>{
    ejs.renderFile("./src/templates/problem_create.html",(err,HTML)=>{
        res.send(Template({title: `Create`,
                           header: ``,
                           preview: true,
                           onadmin: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.post('/problem/:id/edit',(req,res)=>{
    if(req.params.id=='0'){
        var randomId="",charlist="abcdefghijklmnopqrstuvwxyz01234567890123456789";
        for(var i=0;i<6;i++)
            randomId+=charlist[parseInt(Math.random()*charlist.length)];
        req.params.id=randomId;
        var problemList=fs.readFileSync('data/problem.json','utf8');
        var tmp=JSON.parse(problemList);
        tmp.push(randomId);
        problemList=JSON.stringify(tmp,null,"  ");
        fs.writeFileSync('data/problem.json',problemList);
        fs.mkdirSync(`data/${randomId}`);
    }
    var pid=req.params.id,problemConfig=JSON.parse(req.body.prodata);
    problemConfig.statement={"简体中文":"statement_zh.md"};
    fs.writeFileSync(`data/${pid}/config.json`,JSON.stringify(problemConfig,null,"  "));
    fs.writeFileSync(`data/${pid}/statement_zh.md`,req.body.statement);
    res.status(200).json({pid});
});
router.get('/problem/:pid/statement/create',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_statement_create.html",
        {isadmin: req.logined, Config, prodata},(err,HTML)=>{
        res.send(Template({title: `创建题面 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/statement/:statementName/edit',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_statement_edit.html",
        {isadmin: req.logined, Config, prodata, statementName: req.params.statementName, fs},(err,HTML)=>{
        res.send(Template({title: `编辑题面 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});

module.exports=router;