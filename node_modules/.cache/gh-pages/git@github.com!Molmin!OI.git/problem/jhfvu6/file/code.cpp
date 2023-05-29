// 2023.05.27

#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9;

int n;
long long ans;
struct Point{
    int x,y;
    bool operator<(Point tmp)const{
        if(x==tmp.x)return y<tmp.y;
        else return x<tmp.x;
    }
}a[100001];

struct Node{
    int x,l,r;
}node[100001];
int cntNode;
map<long long,int> nodeId;

struct Edge{
    int to,nxt;
}edge[200001];
int head[100001],cntEdge;
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
    edge[++cntEdge]={u,head[v]},head[v]=cntEdge;
}

int siz[100001];
void dfs(int id,int father){
    siz[id]=node[id].r-node[id].l+1;
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father){
            dfs(edge[i].to,id);
            siz[id]+=siz[edge[i].to];
        }
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father)
            ans+=((long long)n-siz[edge[i].to])
                *siz[edge[i].to]%mod,ans%=mod;
}

void calc(){
    sort(a+1,a+1+n);
    cntNode=cntEdge=0;
    memset(head,0,sizeof head);
    memset(edge,0,sizeof edge);
    nodeId.clear();
    for(int i=1;i<=n;i++)
        if(i!=1&&a[i].x==a[i-1].x&&a[i].y==a[i-1].y+1)
            node[cntNode].r=a[i].y,
            nodeId[a[i].x*(long long)n+a[i].y]=cntNode;
        else
            node[++cntNode]={a[i].x,a[i].y,a[i].y},
            nodeId[a[i].x*(long long)n+a[i].y]=cntNode;
    for(int i=1;i<=cntNode;i++){
        bool flag=false;
        for(int j=node[i].l;j<=node[i].r;j++){
            if(nodeId[(node[i].x+1)*(long long)n+j]){
                if(!flag){
                    flag=true;
                    addEdge(i,nodeId[(node[i].x+1)*(long long)n+j]);
                }
            }
            else flag=false;
        }
    }
    dfs(1,0);
}

int main(){
    scanf("%d",&n);
    int minx=0x7fffffff,miny=0x7fffffff;
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].x,&a[i].y),
        minx=min(minx,a[i].x),
        miny=min(miny,a[i].y);
    for(int i=1;i<=n;i++)
        a[i].x-=minx-1,a[i].y-=miny-1;
    calc();
    for(int i=1;i<=n;i++)
        swap(a[i].x,a[i].y);
    calc();
    printf("%lld\n",ans);
    return 0;
}