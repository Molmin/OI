$(document).ready(()=>{
    var prelist=$("pre");
    prelist.each(function(){
        let button=$("<span class='button-copy btn'></span>");
        button.attr("onclick","copyCode(this);");
        button.prependTo($(this));
    });
    var idlist=new Array();
    for(var i=0;i<=100;i++)
        idlist.push(i);
    for(var i in idlist){
        if($(`.language-input${i}`).length && $(`.language-output${i}`).length){
            $(`.language-input${i}`).parent().before(`<div class="row problem-sample${i}"></div>`);
            var rowElement=$(`.problem-sample${i}`);
            rowElement.append(`<div class="column-one-second"><div style="padding-right: 10px;" class="problem-sample${i}-input"><h2>样例输入 ${i}</h2></div></div><div class="column-one-second"><div style="padding-left: 10px;" class="problem-sample${i}-output"><h2>样例输入 ${i}</h2></div></div>`);
            $(`.language-input${i}`) .parent().insertAfter(`.problem-sample${i}-input>h2`);
            $(`.language-output${i}`).parent().insertAfter(`.problem-sample${i}-output>h2`);
        }
    }
});
var copyCode=(obj)=>{
    navigator.clipboard.writeText($(obj).parent().text())
        .then(()=>{
            $(obj).text('复制成功！');
            $(obj).addClass('button-copy-success');
            setTimeout(()=>{
                $(obj).removeClass('button-copy-success');
                $(obj).text('');
            },1000);
        })
        .catch(err=>{
            $(obj).text('复制失败。');
            console.log(err);
            $(obj).addClass('button-copy-fail');
            setTimeout(()=>{
                $(obj).removeClass('button-copy-fail');
                $(obj).text('');
            },1000);
        });
}