// 2023.10.17

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

int power(int x,int y=mod-2){
    if(y<=0)return 1;
    int tmp=power(x,y>>1);
    tmp=1ll*tmp*tmp%mod;
    if(y&1)return 1ll*tmp*x%mod;
    return tmp;
}

int n,m,k;
vector<int> E[100001],E1[100001];
int deg[100001];
long long answer[100];
bool vis[100001];

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
        deg[u]++,deg[v]++;
    }

    // k = 1
    answer[11]=m;

    // k = 2
    // 1. 重边
    answer[21]=m;
    // 2. 链状
    for(int i=1;i<=n;i++)
        answer[22]+=1ll*deg[i]*(deg[i]-1)%mod;
    // 3. 两条不连通的边
    answer[23]=(1ll*m*m-answer[21]-answer[22])%mod;

    // k = 3
    // 1. 重边
    answer[31]=m;
    // 2. 三元环
    for(int i=1;i<=n;i++)
        for(int v :E[i])if(deg[v]>deg[i]||(deg[v]==deg[i]&&v>i))
            E1[i].push_back(v);
    for(int i=1;i<=n;i++){
        for(int v :E1[i])vis[v]=true;
        for(int v :E1[i])for(int w :E1[v]){
            answer[32]+=vis[w];
        }
        for(int v :E1[i])vis[v]=false;
    }
    answer[32]=answer[32]*6%mod;
    // 3. 一条重边 + 一条独立边
    answer[33]=answer[23]*3%mod;
    // 4. 一条重边的端点连一条边
    answer[34]=answer[22]*3%mod;
    // 5. 菊花状
    for(int i=1;i<=n;i++)
        answer[35]+=1ll*deg[i]*(deg[i]-1)%mod*(deg[i]-2)%mod;
    answer[35]=answer[35]%mod;
    // 6. 链状
    for(int i=1;i<=n;i++)
        for(int v :E1[i])
            answer[36]+=1ll*(deg[i]-1)*(deg[v]-1)%mod;
    answer[36]=(6*answer[36]-3*answer[32])%mod;
    // 7. 两条边的链与一条边不连通
    answer[37]=(3*m*answer[22]%mod-3*answer[32]-2*answer[34]-3*answer[35]-2*answer[36])%mod;
    // 8. 三条边不连通
    answer[38]=1ll*m*m%mod*m%mod;
    for(int i=31;i<=37;i++)answer[38]-=answer[i];

    int vs[100]={};
    vs[11]=vs[21]=vs[31]=2;
    vs[22]=vs[32]=vs[34]=3;
    vs[23]=vs[33]=vs[35]=vs[36]=4;
    vs[37]=5;
    vs[38]=6;

    for(int i=k*10+1;i<=(k+1)*10;i++)
        answer[0]+=answer[i]%mod*power(2,n-vs[i])%mod;
    printf("%lld\n",(answer[0]%mod+mod)%mod);
    return 0;
}