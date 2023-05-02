const YAML=require('yamljs');
var Config=YAML.load('./data/config.yaml');

module.exports=(config,HTML)=>{
    return`
<!DOCTYPE html>
<html lang="zh-CN">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width">
        <title id="title">${config.title} - ${Config.title}</title>
        <link rel="shortcut icon" type="image/x-icon" href="https://topan-dev.github.io/TopanUI/favicon.ico">
        <script src="https://topan-dev.github.io/TopanUI/src/jquery.js"></script>
        <link rel="stylesheet" href="https://topan-dev.github.io/TopanUI/topan.css">
        <script src="https://topan-dev.github.io/TopanUI/topan.js"></script>
        <script src="https://kit.fontawesome.com/0d8081718e.js" crossorigin="anonymous"></script>
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.5.1/katex.min.css">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.7.0/styles/github.min.css">
        <style>
            @font-face{
                font-family: font-firacode;
                src: url("/${Config.on}/pub/FiraCode-Regular.ttf");
            }
            pre{
	            font-family: "font-firacode";
            }
        </style>
        ${config.header}
    </head>
    <body>
        <div class="topan-header">
            <div class="topan-header-home">
                <a href="/${Config.on}">
                    <button class="topan-button-ordinary topan-button-commonly topan-button-header-round-left">
                        <i class="fa fa-home"></i>
                    </button>
                </a>
            </div>
            <div class="topan-header-left">
                <span class="topan-header-text">${Config.title}&nbsp;</span>
                <a href="/${Config.on}/about">
                    <span class="topan-button-ordinary topan-button-commonly topan-button-header-block${config.onabout?"-showed":""}">
                        <i class="fa fa-solid fa-circle-info"></i>
                        <span>&nbsp;关于</span>
                    </span>
                </a>
                ${config.preview?`
                    <a href="/admin">
                        <span class="topan-button-ordinary topan-button-commonly topan-button-header-block${config.onadmin?"-showed":""}">
                            <i class="fa fa-solid fa-wrench"></i>
                            <span>&nbsp;后台</span>
                        </span>
                    </a>
                `:""}
                ${config.isadmin?`
                    <a href="/admin/logout">
                        <span class="topan-button-ordinary topan-button-commonly topan-button-header-block">
                            <i class="fa fa-solid fa-right-from-bracket"></i>
                        </span>
                    </a>
                `:''}
            </div>
            <div class="topan-header-right">
            </div>
        </div>
        <div class="topan-outer">
            <div class="topan-page">
                <div class="topan-mainpage-auto">
                    <br>
                    ${HTML}
                    <br>
                </div>
                <footer class="topan-footer">
                    <p></p>
                    <p style="text-align: center; color: #555; font-size: 12px;">
                        Powered by <a href="https://github.com/Molmin/OI.git">Molmin/OI</a>&nbsp;&nbsp;&nbsp;
                        © 2023 <a href="https://github.com/Molmin/">Milmon</a>
                    </p>
                </footer>
            </div>
        </div>
    </body>
</html>
    `;
};