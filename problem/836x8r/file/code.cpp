// 2023.07.19

#include<bits/stdc++.h>
using namespace std;

int n,m,t,w[30001];
int ans_max=-1; long long ans_sum;

set<pair<int,int> > Edges;
vector<int> unidirEdge[30001];
struct Edge{
    int to,nxt;
}edge[60001];
int cntEdge,head[30001],deg[30001];
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
    Edges.insert({u,v}),deg[u]++;
}

bool comparator(int u,int v){
    return w[u]>w[v];
}

int main(){
    scanf("%d%d%d",&n,&m,&t);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",w+i);

    for(int i=1;i<=n;i++){
        // 枚举中间的结点
        int tmp[30001]={},total=0;
        for(int j=head[i];j;j=edge[j].nxt)
            tmp[++total]=edge[j].to;
        sort(tmp+1,tmp+1+total,comparator);
        int exitAt=total;
        for(int j=1;j<=exitAt;j++){
            int NodeId=j+1;
            for(;NodeId<=exitAt;NodeId++)
                if(Edges.find({tmp[j],tmp[NodeId]})==Edges.end())
                    break;
            if(NodeId>exitAt)continue;
            ans_max=max(ans_max,w[tmp[j]]*w[tmp[NodeId]]);
            exitAt=NodeId-1;
        }
        long long sum=0;
        for(int j=1;j<=total;j++)
            ans_sum+=sum*w[tmp[j]],
            sum+=w[tmp[j]];
    }
    
    for(int i=1;i<=n;i++)
        for(int j=head[i];j;j=edge[j].nxt)
            if(deg[edge[j].to]>deg[i])
                unidirEdge[i].push_back(edge[j].to);
            else if(deg[edge[j].to]==deg[i]&&edge[j].to>i)
                unidirEdge[i].push_back(edge[j].to);
    for(int i=1;i<=n;i++)
        for(int j :unidirEdge[i])
            for(int k :unidirEdge[j])
                if(Edges.find({i,k})!=Edges.end())
                    ans_sum-=w[i]*w[j]+w[j]*w[k]+w[k]*w[i];
    if(t==1)ans_sum=0;
    if(t==2)ans_max=0;
    printf("%d\n%lld\n",ans_max,ans_sum*2);
    return 0;
}