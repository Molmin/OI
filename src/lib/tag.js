module.exports=(tag)=>{
    var tagname=tag.split('/')[tag.split('/').length-1];
    var tagtype='alg';
    if(tag.split('/')[0]=='时间')tagtype='time';
    if(tag.split('/')[0]=='来源')tagtype='src';
    if(tag.split('/')[0]=='地区')tagtype='place';
    if(['缺题解','缺代码','缺中文题面'].includes(tag.split('/')[0]))tagtype='special';
    var search={folders: [tag]};
    var searchcode=encodeURIComponent(JSON.stringify(search));
    return `<a href="javascript:directSearch('${searchcode}')" class="tag tag-${tagtype}">${tagname}</a>`;
}