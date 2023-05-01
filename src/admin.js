const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const fs=require('fs');
const Template=require('./template.js');
const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');
const Admin=require('./lib/admin.js');
const URL=require('url');
const deletedir=require('./lib/deletedir.js');

router.all('*',(req,res,next)=>{
    if(req._parsedUrl.pathname.startsWith('/login')||Admin.checkloginByReq(req))next();
    else return res.redirect('/admin/login');
});

router.get('/',(req,res)=>{
    ejs.renderFile("./src/templates/dashboard.html",(err,HTML)=>{
        res.send(Template({title: `仪表盘`,
                           header: ``,
                           preview: true,
                           onadmin: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.post('/update/db',(req,res)=>{
    require('gh-pages').publish('data',{
        branch: 'data',
        message: req.body.message
    },err=>{
        if(err)res.status(200).json({error: err});
        else res.status(200).json({message: "同步成功。"});
    });
});
router.post('/update/ghpage',(req,res)=>{
    require('./build/main.js')();
    setTimeout(()=>{
        require('gh-pages').publish('dist',{
            branch: 'gh-pages',
            message: req.body.message
        },err=>{
            if(err)res.status(200).json({error: err});
            else res.status(200).json({message: "同步成功。"});
        });
    },1000);
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
        res.send(Template({title: `创建题目`,
                           header: ``,
                           preview: true,
                           onadmin: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.get('/problem/:pid/config',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_config.html",
        {isadmin: req.logined, Config, prodata},(err,HTML)=>{
        res.send(Template({title: `修改配置 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.post('/problem/:pid/edit',(req,res)=>{
    if(req.params.pid=='0'){
        var pid="",charlist="abcdefghijklmnopqrstuvwxyz01234567890123456789";
        for(var i=0;i<6;i++)
            pid+=charlist[parseInt(Math.random()*charlist.length)];
        var problemList=fs.readFileSync('data/problem.json','utf8');
        var tmp=JSON.parse(problemList); tmp.push(pid);
        problemList=JSON.stringify(tmp,null,"  ");
        fs.writeFileSync('data/problem.json',problemList);
        fs.mkdirSync(`data/${pid}`);
        var problemConfig=JSON.parse(req.body.prodata);
        problemConfig.statement={"简体中文":"statement_zh.md"};
        fs.writeFileSync(`data/${pid}/config.json`,JSON.stringify(problemConfig,null,"  "));
        fs.writeFileSync(`data/${pid}/statement_zh.md`,req.body.statement);
        res.status(200).json({pid});
    }
    else{
        var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
        var problemConfig=JSON.parse(req.body.prodata);
        prodata.title=problemConfig.title;
        prodata.difficulty=problemConfig.difficulty;
        prodata.judge=problemConfig.judge;
        prodata.tags=problemConfig.tags;
        prodata.source=problemConfig.source;
        fs.writeFileSync(`data/${req.params.pid}/config.json`,JSON.stringify(prodata,null,"  "));
        res.status(200).json({pid});
    }
});
router.post('/problem/:pid/delete',(req,res)=>{
    deletedir(`data/${req.params.pid}`);
    var problemList=fs.readFileSync('data/problem.json','utf8');
    var tmp=JSON.parse(problemList);
    var i=0; while(tmp[i]&&tmp[i]!=req.params.pid)i++;
    tmp.splice(i,1);
    problemList=JSON.stringify(tmp,null,"  ");
    fs.writeFileSync('data/problem.json',problemList);
    res.json({});
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
router.post('/problem/:pid/statement/create',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    if(prodata.statement[req.body.name])req.body.name+=' (1)';
    prodata.statement[req.body.name]=req.body.file;
    fs.writeFileSync(`data/${req.params.pid}/${req.body.file}`,req.body.code);
    fs.writeFileSync(`data/${req.params.pid}/config.json`,JSON.stringify(prodata,null,"  "));
    res.status(200).json({});
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
router.post('/problem/:pid/statement/:statementName/delete',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    {
        var total=0;
        for(var key in prodata.statement)total++;
        if(total<2){
            res.status(200).json({});
            return;
        }
    }
    var key=req.params.statementName;
    if(!prodata.statement[key]){
        res.status(200).json({});
        return;
    }
    fs.unlinkSync(`data/${req.params.pid}/${prodata.statement[key]}`,err=>{});
    delete prodata.statement[key];
    fs.writeFileSync(`data/${req.params.pid}/config.json`,JSON.stringify(prodata,null,"  "));
    res.status(200).json({});
});
router.post('/problem/:pid/statement/:statementName/edit',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    var key=req.params.statementName;
    fs.unlinkSync(`data/${req.params.pid}/${prodata.statement[key]}`,err=>{});
    delete prodata.statement[key];
    if(prodata.statement[req.body.name])req.body.name+=' (1)';
    prodata.statement[req.body.name]=req.body.file;
    fs.writeFileSync(`data/${req.params.pid}/${req.body.file}`,req.body.newCode);
    fs.writeFileSync(`data/${req.params.pid}/config.json`,JSON.stringify(prodata,null,"  "));
    res.status(200).json({});
});

router.post('/problem/:pid/solution/:para/delete',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    fs.unlinkSync(`data/${req.params.pid}/${prodata.solution[req.params.para].file}`);
    prodata.solution.splice(req.params.para,1);
    fs.writeFileSync(`data/${req.params.pid}/config.json`,JSON.stringify(prodata,null,"  "));
    res.json({});
});
router.get('/problem/:pid/solution/:para/edit',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_solution_edit.html",
        {isadmin: req.logined, Config, fs, prodata, paraId: req.params.para},(err,HTML)=>{
        res.send(Template({title: `编辑题解 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.post('/problem/:pid/solution/:para/edit',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    fs.unlinkSync(`data/${req.params.pid}/${prodata.solution[req.params.para].file}`);
    fs.writeFileSync(`data/${req.params.pid}/${req.body.filename}`,req.body.code);
    prodata.solution[req.params.para]={title: req.body.title, file: req.body.filename};
    fs.writeFileSync(`data/${req.params.pid}/config.json`,JSON.stringify(prodata,null,"  "));
    res.json({});
});
router.get('/problem/:pid/solution/:para/insert',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    prodata.pid=req.params.pid;
    ejs.renderFile("./src/templates/problem_solution_insert.html",
        {isadmin: req.logined, Config, prodata, paraId: req.params.para},(err,HTML)=>{
        res.send(Template({title: `插入段 - ${prodata.title}`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});
router.post('/problem/:pid/solution/:para/insert',(req,res)=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${req.params.pid}/config.json`,'utf8'));
    fs.writeFileSync(`data/${req.params.pid}/${req.body.filename}`,req.body.code);
    prodata.solution.splice(req.params.para,0,{title: req.body.title, file: req.body.filename});
    fs.writeFileSync(`data/${req.params.pid}/config.json`,JSON.stringify(prodata,null,"  "));
    res.json({});
});

module.exports=router;