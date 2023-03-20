const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const Template=require('./template.js');

router.get('/login',(req,res)=>{
    if(req.logined){
        res.redirect("/");
        return;
    }
    ejs.renderFile("./src/templates/login.html",{_: req.body._},(err,HTML)=>{
        res.send(Template({title: `${req.body._('login')}`,
                           header: ``
                          },HTML));
    });
});

module.exports=router;