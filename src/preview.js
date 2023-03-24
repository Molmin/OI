const express=require('express'),
      router=express.Router();
const ejs=require('ejs');
const Template=require('./template.js');

router.get('/',(req,res)=>{
    ejs.renderFile("./src/templates/problem_list.html",{isadmin: req.logined},(err,HTML)=>{
        res.send(Template({title: `Problem List`,
                           header: ``,
                           preview: true,
                           isadmin: req.logined
                          },HTML));
    });
});

module.exports=router;