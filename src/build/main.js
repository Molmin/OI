module.exports=()=>{

const fs=require('fs');
const path=require('path');
const ejs=require('ejs');
const Template=require('./../template.js');
const highlightjs=require('highlight.js');

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
fs.mkdirSync("dist/pub");
fs.copyFileSync("src/assets/public/FiraCode-Regular.ttf","dist/pub/FiraCode-Regular.ttf");

var problemList=fs.readFileSync('data/problem.json','utf8');
problemList=JSON.parse(problemList);

{
    ejs.renderFile("./src/templates/problem_list.html",
        {isadmin: false, problemList, fs, Config},(err,HTML)=>{
        fs.writeFileSync("dist/index.html",
            Template({title: `题目列表`,
                    header: ``},HTML)
        );
    });
}

ejs.renderFile(
    "./src/templates/about.html",
    {html: MarkdownIt.render(fs.readFileSync('data/readme.md','utf8'))},
    (err,HTML)=>{
        fs.writeFileSync("dist/about.html",
            Template({title: `关于`,
                      header: ``,
                      onabout: true
                     },HTML)
        );
    }
);

problemList.forEach(pid=>{
    var prodata=JSON.parse(fs.readFileSync(`data/${pid}/config.json`,'utf8'));
    prodata.pid=pid;
    ejs.renderFile("./src/templates/problem_detail.html",{isadmin: false, Config, prodata, fs, MarkdownIt},(err,HTML)=>{
        fs.writeFileSync(`dist/problem/${prodata.pid}.html`,
            Template({title: `#${prodata.pid}. ${prodata.title}`,
                      header: ``},HTML)
        );
    });
    fs.mkdirSync(`dist/problem/${prodata.pid}`);
    ejs.renderFile("./src/templates/problem_solution.html",
        {isadmin: false, Config, prodata, fs, MarkdownIt, highlightjs},(err,HTML)=>{
        fs.writeFileSync(`dist/problem/${prodata.pid}/solution.html`,
            Template({title: `题解与代码 - ${prodata.title}`,
                      header: ``},HTML)
        );
    });
});

}