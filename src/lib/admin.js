const crypto=require('crypto');
const YAML=require('yamljs');
const fs=require('fs');
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
const checkloginByReq=req=>req.cookies['oiblog-cookie']
    &&req.cookies['oiblog-cookie']==Encode(fs.readFileSync('password','utf8'));
const checkloginByPassword=password=>password==fs.readFileSync('password','utf8');
module.exports={
    encode,
    Encode,
    checkloginByReq,
    checkloginByPassword
};

//localStorage.cp6_player_id='f6d7c421-bf86-455d-9453-18fa63f68638'
// window.localStorage.setItem("cp6_player_id","551ee072-105e-49e5-b438-316f912993c2");