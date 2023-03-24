const express=require('express'),
      app=express();
const path=require('path');
const cors=require('cors');
app.use(cors());
const bodyParser=require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));
const cookieParser=require('cookie-parser');
app.use(cookieParser());
const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');
const Admin=require('./src/lib/admin.js');

app.all('*',(req,res,next)=>{
    if(Admin.checkloginByReq(req))
        req.logined=true;
    else
        res.cookie('oiblog-cookie',''),
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
app.use("/file",express.static(path.join(__dirname,'src/assets')));
app.use(`/${Config.on}`,require('./src/preview.js'));
app.use(`/admin`,require('./src/admin.js'));

app.listen(8299,()=>{
    console.log('Port :8299 is opened');
});