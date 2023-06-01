// 2023.06.01

#include<bits/stdc++.h>
using namespace std;

int n,answer=0x7ffffff;
struct Edge{
    int to,nxt;
}edge[400001];
int head[200001],cntEdge;
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int siz[200001];
void calcSize(int id,int father){
    siz[id]=1;
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father){
            calcSize(edge[i].to,id);
            siz[id]+=siz[edge[i].to];
        }
}

multiset<int> hissiz,othsiz;
// hissiz: 路径上的所有点的子树大小集合
// othsiz: 其它支路上的所有点的子树大小集合

void work(int id,int father){
    if(!hissiz.empty()){
        // 取路径上的另一条边
        auto tmp=hissiz.lower_bound(siz[id]+(n-siz[id])/2);
        if(tmp!=hissiz.end()){
            // 取比目标值大的第一个
            int x=siz[id],y=*tmp-siz[id],z=n-*tmp;
            answer=min(answer,max(x,max(y,z))-min(x,min(y,z)));
        }
        if(tmp!=hissiz.begin()){
            // 取比目标值小的第一个
            tmp--;
            int x=siz[id],y=*tmp-siz[id],z=n-*tmp;
            answer=min(answer,max(x,max(y,z))-min(x,min(y,z)));
        }
    }
    if(!othsiz.empty()){
        // 不取路径上的边
        auto tmp=othsiz.lower_bound((n-siz[id])/2);
        if(tmp!=othsiz.end()){
            // 取比目标值大的第一个
            int x=siz[id],y=*tmp,z=n-x-y;
            answer=min(answer,max(x,max(y,z))-min(x,min(y,z)));
        }
        if(tmp!=othsiz.begin()){
            // 取比目标值小的第一个
            tmp--;
            int x=siz[id],y=*tmp,z=n-x-y;
            answer=min(answer,max(x,max(y,z))-min(x,min(y,z)));
        }
    }
    if(id>1)hissiz.insert(siz[id]);
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=father)
            work(edge[i].to,id);
    if(id>1)
        hissiz.erase(hissiz.find(siz[id])),
        othsiz.insert(siz[id]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    calcSize(1,0);
    work(1,0);
    printf("%d\n",answer);
    return 0;
}