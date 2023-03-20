const express=require('express'),
      app=express();
const cors=require('cors');
app.use(cors());
const path=require('path');
const bodyParser=require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));
const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');
const Admin=require('./lib/admin.js');

app.all('*',(req,res,next)=>{
    if(Admin.checkloginByReq(req))
        req.logined=true;
    else res.cookie("oiblog-cookie",""),
        req.logined=false;
    res.set('Access-Control-Allow-Origin','*');
    res.set('Access-Control-Allow-Methods','GET');
    res.set('Access-Control-Allow-Headers','X-Requested-With, Content-Type');
    if ('OPTIONS'==req.method)return res.send(200);
    next();
});

app.get("/",(req,res)=>{
    res.redirect(`/${Config.on}`);
});
app.use(`/${Config.on}`,require('./preview.js'));
app.use(`/admin`,require('./admin.js'));

app.listen(8499,()=>{
    console.log('Port :8499 is opened');
});