const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const Template=require('./template.js');
const Admin=require('./lib/admin.js');

router.get('/login',(req,res)=>{
    if(req.logined){
        res.redirect("/");
        return;
    }
    ejs.renderFile("./src/templates/login.html",{_: req.body._},(err,HTML)=>{
        res.send(Template({title: `Login`,
                           header: ``,
                           preview: true,
                           onadmin: true
                          },HTML));
    });
});
router.post('/login/try',(req,res)=>{
    if(req.logined){
        res.status(200).json({error: '已经登录成功。'});
        return;
    }
    if(Admin.checkloginByPassword(req.body.password)){
        res.cookie("oiblog-cookie",Admin.Encode(req.body.password));
        res.status(200).json({});
    }
});

module.exports=router;