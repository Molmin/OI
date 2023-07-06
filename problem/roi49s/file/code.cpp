// 2023.07.05

#include<bits/stdc++.h>
using namespace std;

int n,m,a[100001],pre[100001],nxt[100001];
bool vis[100001];
priority_queue<
    pair<int,int>,
    vector<pair<int,int> >,
    greater<pair<int,int> >
> Q;

void deleteinList(int x){
    vis[x]=true;
    pre[nxt[x]]=pre[x];
    nxt[pre[x]]=nxt[x];
}

int main(){
    scanf("%d%d",&n,&m);
    int tmp=0;
    for(int i=1;i<=n;i++){
        int x; scanf("%d",&x);
        if(x==0)continue;
        if(!tmp||1ll*a[tmp]*x<0)a[++tmp]=x;
        else a[tmp]+=x;
    }
    n=tmp;
    int total=0,sum=0;
    for(int i=1;i<=n;i++)
        if(a[i]>0)total++,sum+=a[i];
    for(int i=1;i<=n;i++)
        pre[i]=i-1,nxt[i]=i+1,Q.push({abs(a[i]),i});
    while(total>m){
        while(vis[Q.top().second])Q.pop();
        int x=Q.top().second; Q.pop();
        if(a[x]>0||(a[x]<0&&pre[x]!=0&&nxt[x]!=n+1)){
            total--,sum-=abs(a[x]);
            a[x]=a[pre[x]]+a[nxt[x]]+a[x];
            Q.push({abs(a[x]),x});
            deleteinList(pre[x]);
            deleteinList(nxt[x]);
        }
        else deleteinList(x);
    }
    printf("%d\n",sum);
    return 0;
}