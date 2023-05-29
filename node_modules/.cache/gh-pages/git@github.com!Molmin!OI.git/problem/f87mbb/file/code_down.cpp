void dpdown(int id,int father){
    // 求 fa/son/down[id]
    down[id]=0;
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father&&!oncir[edge[i].to]){
            son[id]++;
            fa[edge[i].to]++;
            dpdown(edge[i].to,id);
            down[id]+=down[edge[i].to]+edge[i].w;
        }
    if(son[id])down[id]/=son[id];
}