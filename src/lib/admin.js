const crypto=require('crypto');
const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');
const encode=(str)=>{
    // second time
    const MD5=crypto.createHash('md5');
    const SHA256=crypto.createHash('sha256');
    var md5=MD5.update(str,'utf8').digest('hex');
    var sha256=SHA256.update(str,'utf8').digest('hex');
    return sha256.substr(0,32)+md5+sha256.substr(32);
};
const Encode=(str)=>{
    // first time
    return encode(`oiblog_${str}`);
}
const checkloginByReq=req=>{
    if(req.cookies==undefined)return false;
    var cookie=req.cookies['oiblog-cookie'];
    if(cookie==undefined)return false;
    return encode(cookie)==Config.admin;
}
const checkloginByPassword=password=>encode(Encode(password))==Config.admin;
module.exports={
    encode,
    Encode,
    checkloginByReq,
    checkloginByPassword
};