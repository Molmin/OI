const YAML=require('yamljs');
// var Config=YAML.load('./data/config.yaml');

module.exports=(tag)=>{
    var tagname=tag.split('/')[tag.split('/').length-1];
    var tagtype='alg';
    if(tag.split('/')[0]=='时间')tagtype='time';
    if(tag.split('/')[0]=='来源')tagtype='src';
    if(tag.split('/')[0]=='地区')tagtype='place';
    if(['缺题解','缺代码','缺中文题面'].includes(tag.split('/')[0]))tagtype='special';
    var search={folders: [tag]};
    var searchcode=new Buffer.from(JSON.stringify(search)).toString('base64');
    return `<a href="javascript:directTag('${encodeURIComponent(searchcode)}')" class="tag tag-${tagtype}">${tagname}</a>`;
}