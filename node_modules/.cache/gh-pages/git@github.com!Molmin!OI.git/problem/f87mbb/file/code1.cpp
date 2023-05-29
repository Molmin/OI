findcircle(1,0);
initcircle(tag,0);
for(int i=1;i<=len;i++)
    dpdown(idoncir[i],0);
for(int i=1;i<=len;i++){
    int id=idoncir[i];
    double mul=0.5; // 向顺时针下一个点走的概率占在环上走的一半
    for(int j=cir::nxt(i);j!=i;j=cir::nxt(j)){
        int v=idoncir[j];
        if(j+1==i||(j==len&&i==1)) // 顺时针下一个结点就是起点 i，特殊处理
            up[id]+=(ldis[j]+down[v])*mul;
        else up[id]+=(down[v]*son[v]/(son[v]+1)+ldis[j])*mul;
        mul*=1.0/(son[v]+1);
    }
    mul=0.5; // 向逆时针下一个点走的概率占在环上走的一半
    for(int j=cir::pre(i);j!=i;j=cir::pre(j)){
        int v=idoncir[j];
        if(j-1==i||(j==1&&i==len)) // 逆时针下一个结点就是起点 i，特殊处理
            up[id]+=(rdis[j]+down[v])*mul;
        else up[id]+=(down[v]*son[v]/(son[v]+1)+rdis[j])*mul;
        mul*=1.0/(son[v]+1);
    }
    for(int j=head[id];j;j=edge[j].nxt)
        if(!oncir[edge[j].to])
            dpup(edge[j].to,id,edge[j].w);
}