void dpup(int id,int father,int w){
    if(fa[father]+son[father]>1)
        up[id]=(up[father]*fa[father]+down[father]*son[father]-
            (down[id]+w))/(fa[father]+son[father]-1)+w;
    else up[id]=w;
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father)
            dpup(edge[i].to,id,edge[i].w);
}