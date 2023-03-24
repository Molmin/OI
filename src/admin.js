const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const Template=require('./template.js');
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

module.exports=router;