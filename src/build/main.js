const fs=require('fs');
const path=require('path');
const ejs=require('ejs');
const Template=require('./../template.js');

var MarkdownIt=require('markdown-it')({
    html: true,
    linkify: true
});
MarkdownIt.use(require('markdown-it-katex'));

const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');

var deleteDir=(url)=>{
    if(fs.existsSync(url)){
        var files=[];
        files=fs.readdirSync(url);
        files.forEach((file,index)=>{
            var curPath=path.join(url,file);
            if(fs.statSync(curPath).isDirectory())
                deleteDir(curPath);
            else fs.unlinkSync(curPath);
        });
        fs.rmdirSync(url);
    }
}

deleteDir("dist");
fs.mkdirSync("dist");
fs.mkdirSync("dist/problem");

ejs.renderFile("./src/templates/problem_list.html",{isadmin: false},(err,HTML)=>{
    fs.writeFileSync("dist/index.html",
        Template({title: `Problem List`,
                  header: ``},HTML)
    );
});

var problemList=fs.readFileSync('data/problem.json','utf8');
problemList=JSON.parse(problemList);

problemList.forEach(pid=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${pid}/config.json`,'utf8'));
    prodata.pid=pid,prodata.statementHtml={};
    var mdcode=fs.readFileSync(`data/${pid}/${prodata.statement['简体中文']}`,'utf8');
    prodata.statementHtml['简体中文']=MarkdownIt.render(mdcode);
    ejs.renderFile("./src/templates/problem_detail.html",{isadmin: false, prodata},(err,HTML)=>{
        fs.writeFileSync(`dist/problem/${prodata.pid}.html`,
            Template({title: `#${prodata.pid}. ${prodata.title}`,
                      header: ``},HTML)
        );
    });
});

const ghpages=require('gh-pages');
ghpages.publish('dist',function(err){});