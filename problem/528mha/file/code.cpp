// 2023.07.26

#include<bits/stdc++.h>
using namespace std;

int n,q,w[30001];

struct Edge{
    int to,nxt;
}edge[60001];
int cntEdge,head[30001];
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int fa[30001],siz[30001],dep[30001],heavy[30001];
void init(int id){
    siz[id]=1;
    for(int i=head[id];i;i=edge[i].nxt){
        if(edge[i].to==fa[id])continue;
        fa[edge[i].to]=id;
        dep[edge[i].to]=dep[id]+1;
        init(edge[i].to);
        if(siz[edge[i].to]>siz[heavy[id]])
            heavy[id]=edge[i].to;
        siz[id]+=siz[edge[i].to];
    }
}

int cntdfn,dfn[30001],rnk[30001];
int top[30001];
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
    long long sum[120001];
    int maxn[120001],len[120001];
    void pushup(int id){
        sum[id]=sum[id<<1]+sum[(id<<1)+1];
        maxn[id]=max(maxn[id<<1],maxn[(id<<1)+1]);
    }

    void build(int id,int l,int r){
        len[id]=r-l+1;
        if(l==r)sum[id]=maxn[id]=w[rnk[l]];
        else{
            int mid=l+r>>1;
            build(id<<1,l,mid);
            build((id<<1)+1,mid+1,r);
            pushup(id);
        }
    }

    void updateSetOne(int id,int l,int r,int x,int y){
        if(l==r){
            sum[id]=maxn[id]=y;
            return;
        }
        int mid=l+r>>1;
        if(x<=mid)updateSetOne(id<<1,l,mid,x,y);
        else updateSetOne((id<<1)+1,mid+1,r,x,y);
        pushup(id);
    }

    long long querySum(int id,int l,int r,int x,int y){
        if(x<=l&&r<=y)return sum[id];
        int mid=l+r>>1; long long res=0;
        if(x<=mid)res+=querySum(id<<1,l,mid,x,y);
        if(mid<y)res+=querySum((id<<1)+1,mid+1,r,x,y);
        return res;
    }
    int queryMax(int id,int l,int r,int x,int y){
        if(x<=l&&r<=y)return maxn[id];
        int mid=l+r>>1,res=0x80000000;
        if(x<=mid)res=max(res,queryMax(id<<1,l,mid,x,y));
        if(mid<y)res=max(res,queryMax((id<<1)+1,mid+1,r,x,y));
        return res;
    }
    long long queryListSum(int x,int y){
        long long res=0; int topx=top[x],topy=top[y];
        while(topx!=topy){
            if(dep[topx]<dep[topy])
                swap(x,y),swap(topx,topy);
            res+=querySum(1,1,n,dfn[topx],dfn[x]);
            x=fa[topx],topx=top[x];
        }
        if(dep[x]>dep[y])swap(x,y);
        res+=querySum(1,1,n,dfn[x],dfn[y]);
        return res;
    }
    int queryListMax(int x,int y){
        int res=0x80000000,topx=top[x],topy=top[y];
        while(topx!=topy){
            if(dep[topx]<dep[topy])
                swap(x,y),swap(topx,topy);
            res=max(res,queryMax(1,1,n,dfn[topx],dfn[x]));
            x=fa[topx],topx=top[x];
        }
        if(dep[x]>dep[y])swap(x,y);
        res=max(res,queryMax(1,1,n,dfn[x],dfn[y]));
        return res;
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);
    init(1); decomposition(1,1);
    SegmentTree::build(1,1,n);

    scanf("%d",&q);
    while(q--){
        int u,v; string op; op.resize(10);
        scanf("%s%d%d",&op[0],&u,&v);
        if(op[1]=='H')SegmentTree::updateSetOne(1,1,n,dfn[u],v);
        if(op[1]=='M')printf("%d\n",SegmentTree::queryListMax(u,v));
        if(op[1]=='S')printf("%lld\n",SegmentTree::queryListSum(u,v));
    }
    return 0;
}