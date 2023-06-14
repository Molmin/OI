// 2023.06.06

#include<bits/stdc++.h>
using namespace std;

int n;

struct Edge{
    int to,nxt;
}edge[200001];
int head[100001],cntEdge;
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int dep[100001];
double answer;
void dfs(int id,int father){
    dep[id]=dep[father]+1;
    answer+=1.0/dep[id];
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father)
            dfs(edge[i].to,id);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,0);
    printf("%.6lf\n",answer);
    return 0;
}