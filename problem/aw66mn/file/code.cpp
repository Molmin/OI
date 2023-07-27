// 2023.07.27

#include<bits/stdc++.h>
using namespace std;

int n,q,w[100001];

struct Edge{
    int to,nxt;
}edge[200001];
int cntEdge,head[100001];
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int fa[100001],siz[100001],dep[100001],heavy[100001];
void init(int id){
    siz[id]=1;
    for(int i=head[id];i;i=edge[i].nxt){
        if(edge[i].to==fa[id])continue;
        dep[edge[i].to]=dep[id]+1;
        init(edge[i].to);
        if(siz[edge[i].to]>siz[heavy[id]])
            heavy[id]=edge[i].to;
        siz[id]+=siz[edge[i].to];
    }
}

int cntdfn,dfn[100001],rnk[100001];
int top[100001];
void decomposition(int id,int x){
    // x 为当前链顶端
    top[id]=x,dfn[id]=++cntdfn,rnk[cntdfn]=id;
    if(!heavy[id])return;
    decomposition(heavy[id],x);
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=heavy[id]&&edge[i].to!=fa[id])
            decomposition(edge[i].to,edge[i].to);
}

namespace SegmentTree{
    struct Node{
        int l,r,lval,rval;
        int up,l_up,r_up;
        int down,l_down,r_down;
        void init(int _l=0,int _r=0){
            lval=rval=0;
            up=l_up=r_up=0;
            down=l_down=r_down=0;
            l=_l,r=_r;
        }
        void reverse(){
            swap(lval,rval); swap(up,down);
            swap(l_up,r_down); swap(l_down,r_up);
        }
    }x[400001];

    Node pushup(Node &x,Node lson,Node rson){
        int lenl=lson.r-lson.l+1,lenr=rson.r-rson.l+1;
        x.lval=lson.lval,x.rval=rson.rval;
        x.up=max(lson.up,rson.up);
        if(lson.rval<rson.lval)x.up=max(x.up,lson.r_up+rson.l_up);
        x.l_up=lson.l_up;
        if(lson.l_up==lenl&&lson.rval<rson.lval)
            x.l_up+=rson.l_up;
        x.r_up=rson.r_up;
        if(rson.r_up==lenr&&lson.rval<rson.lval)
            x.r_up+=lson.r_up;
        x.down=max(lson.down,rson.down);
        if(lson.rval>rson.lval)
            x.down=max(x.down,lson.r_down+rson.l_down);
        x.l_down=lson.l_down;
        if(lson.l_down==lenl&&lson.rval>rson.lval)
            x.l_down+=rson.l_down;
        x.r_down=rson.r_down;
        if(rson.r_down==lenr&&lson.rval>rson.lval)
            x.r_down+=lson.r_down;
        return x;
    }
    void build(int id,int l,int r){
        x[id]={l,r,w[rnk[l]],w[rnk[l]],1,1,1,1,1,1};
        if(l!=r){
            int mid=l+r>>1;
            build(id<<1,l,mid);
            build((id<<1)+1,mid+1,r);
            x[id]=pushup(x[id],x[id<<1],x[(id<<1)+1]);
        }
    }

    Node mergeNodes(Node L,Node R){
        if(!L.l)return R;
        if(!R.l)return L;
        Node res; res.init(L.l,R.r);
        return pushup(res,L,R);
    }

    Node queryNode(int id,int l,int r){
        if(l<=x[id].l&&x[id].r<=r)return x[id];
        int mid=x[id].l+x[id].r>>1;
        if(r<=mid)return queryNode(id<<1,l,r);
        if(mid<l)return queryNode((id<<1)+1,l,r);
        Node L=queryNode(id<<1,l,r),
             R=queryNode((id<<1)+1,l,r),res;
        res.init(L.l,R.r);
        return pushup(res,L,R);
    }
    int queryMaxLength(int x,int y){
        bool flag=false;
        Node res1,res2; res1.init(),res2.init();
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]])
                swap(x,y),swap(res1,res2),flag=!flag;
            res1=mergeNodes(queryNode(1,dfn[top[x]],dfn[x]),res1);
            x=fa[top[x]];
        }
        if(dep[x]>dep[y])swap(x,y),swap(res1,res2),flag=!flag;
        res2=mergeNodes(queryNode(1,dfn[x],dfn[y]),res2);
        if(flag)swap(res1,res2);
        res1.reverse(); res1=mergeNodes(res1,res2);
        return res1.up;
    }
}

int main(){
    int T;
    scanf("%d",&T);
    for(int caseId=1;caseId<=T;caseId++){
        printf("Case #%d:\n",caseId);
        cntEdge=cntdfn=0;
        memset(heavy,0,sizeof heavy);
        memset(head,0,sizeof head);

        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",w+i);
        for(int i=2;i<=n;i++){
            scanf("%d",fa+i);
            addEdge(fa[i],i);
        }
        init(1); decomposition(1,1);
        SegmentTree::build(1,1,n);

        scanf("%d",&q);
        while(q--){
            int u,v;
            scanf("%d%d",&u,&v);
            printf("%d\n",SegmentTree::queryMaxLength(u,v));
        }
        printf("\n");
    }
    return 0;
}