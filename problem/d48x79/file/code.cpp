// 2023.07.26

#include<bits/stdc++.h>
using namespace std;
const int mod=201314;

int n,m,fa[50001],ans[50001];

struct Edge{
    int to,nxt;
}edge[50001];
int cntEdge,head[50001];
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int siz[50001],dep[50001],heavy[50001];
void init(int id){
    siz[id]=1;
    for(int i=head[id];i;i=edge[i].nxt){
        dep[edge[i].to]=dep[id]+1;
        init(edge[i].to);
        if(siz[edge[i].to]>siz[heavy[id]])
            heavy[id]=edge[i].to;
        siz[id]+=siz[edge[i].to];
    }
}

int cntdfn,dfn[50001],rnk[50001];
int top[50001];
void decomposition(int id,int x){
    // x 为当前链顶端
    top[id]=x,dfn[++cntdfn]=id,rnk[id]=cntdfn;
    if(!heavy[id])return;
    decomposition(heavy[id],x);
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=heavy[id])
            decomposition(edge[i].to,edge[i].to);
}

namespace SegmentTree{
    int sum[200001],lazy[200001],len[200001];
    void pushdown(int id){
        if(lazy[id]){
            sum[id<<1]+=len[id<<1]*lazy[id];
            lazy[id<<1]+=lazy[id];
            sum[(id<<1)+1]+=len[(id<<1)+1]*lazy[id];
            lazy[(id<<1)+1]+=lazy[id];
            sum[id<<1]%=mod,sum[(id<<1)+1]%=mod;
            lazy[id]=0;
        }
    }
    void pushup(int id){
        sum[id]=(sum[id<<1]+sum[(id<<1)+1])%mod;
    }

    void build(int id,int l,int r){
        sum[id]=lazy[id]=0;
        len[id]=r-l+1;
        if(l<r){
            int mid=l+r>>1;
            build(id<<1,l,mid);
            build((id<<1)+1,mid+1,r);
        }
    }

    void updateAddOne(int id,int l,int r,int x,int y){
        if(x<=l&&r<=y){
            lazy[id]++; sum[id]+=len[id];
            sum[id]%=mod; return;
        }
        int mid=l+r>>1;
        pushdown(id);
        if(x<=mid)updateAddOne(id<<1,l,mid,x,y);
        if(mid<y)updateAddOne((id<<1)+1,mid+1,r,x,y);
        pushup(id);
    }
    void updateList(int x,int y){
        // 将 x 到 y 这条链加 1
        int topx=top[x],topy=top[y];
        while(topx!=topy){
            if(dep[topx]<dep[topy])
                swap(x,y),swap(topx,topy);
            updateAddOne(1,1,n,rnk[topx],rnk[x]);
            x=fa[topx],topx=top[x];
        }
        if(dep[x]>dep[y])swap(x,y);
        updateAddOne(1,1,n,rnk[x],rnk[y]);
    }

    int querySum(int id,int l,int r,int x,int y){
        if(x<=l&&r<=y)return sum[id];
        int mid=l+r>>1,res=0;
        pushdown(id);
        if(x<=mid)res+=querySum(id<<1,l,mid,x,y);
        if(mid<y)res+=querySum((id<<1)+1,mid+1,r,x,y);
        return res%mod;
    }
    int queryList(int x,int y){
        // 查询将 x 到 y 这条链的总和
        int res=0,topx=top[x],topy=top[y];
        while(topx!=topy){
            if(dep[topx]<dep[topy])
                swap(x,y),swap(topx,topy);
            res+=querySum(1,1,n,rnk[topx],rnk[x]);
            x=fa[topx],topx=top[x];
        }
        if(dep[x]>dep[y])swap(x,y);
        res+=querySum(1,1,n,rnk[x],rnk[y]);
        return res%=mod;
    }
}

struct Query{
    int id,weight;
    int pos,x; // pos 表示询问 [1,pos] 区间，x 为结点 z
    bool operator<(Query tmp)const{
        return pos<tmp.pos;
    }
}Q[100001];
int cntQuery;

int main(){
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++){
        scanf("%d",fa+i),fa[i]++;
        addEdge(fa[i],i);
    }
    for(int i=1;i<=m;i++){
        int l,r,z;
        scanf("%d%d%d",&l,&r,&z);
        l++,r++,z++;
        Q[++cntQuery]={i,-1,l-1,z};
        Q[++cntQuery]={i,1,r,z};
    }

    sort(Q+1,Q+1+cntQuery);
    dep[1]=1; init(1);
    SegmentTree::build(1,1,n);
    decomposition(1,1);
    
    int nowpos=0;
    for(int i=1;i<=cntQuery;i++){
        while(nowpos<Q[i].pos)
            SegmentTree::updateList(1,++nowpos);
        ans[Q[i].id]+=Q[i].weight*SegmentTree::queryList(1,Q[i].x);
    }
    for(int i=1;i<=m;i++)
        printf("%d\n",(ans[i]%mod+mod)%mod);
    return 0;
}