// 2023.05.31

#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
long long power(long long a,long long n=mod-2){
    long long res=1;
    while(n){
        if(n&1)res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
long long fac[4001],invfac[4001],invpower2[4001];
void initfac(int N){
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=fac[i-1]*i%mod;
    invfac[N]=power(fac[N]);
    for(int i=N;i>=1;i--)
        invfac[i-1]=invfac[i]*i%mod;
    invpower2[0]=1;
    long long inv2=power(2);
    for(int i=1;i<=N;i++)
        invpower2[i]=invpower2[i-1]*inv2%mod;
}

int n;

struct Edge{
    int to,nxt;
}edge[8001];
int head[4001],cntEdge;
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int siz[4001];
long long dp[4001][4001][2];
void dfs(int id,int father){
    dp[id][0][0]=siz[id]=1;
    for(int t=head[id];t;t=edge[t].nxt)
        if(edge[t].to!=father){
            int to=edge[t].to;
            dfs(to,id);
            long long f[4001][2]={};
            for(int i=0;i<=siz[id];i++)
                for(int j=0;j<=siz[to];j++)
                    f[i+j][0]+=dp[id][i][0]*dp[to][j][0],f[i+j][0]%=mod,
                    f[i+j][0]+=dp[id][i][0]*dp[to][j][1],f[i+j][0]%=mod,
                    f[i+j][1]+=dp[id][i][1]*dp[to][j][0],f[i+j][1]%=mod,
                    f[i+j][1]+=dp[id][i][1]*dp[to][j][1],f[i+j][1]%=mod,
                    f[i+j+1][1]+=dp[id][i][0]*dp[to][j][0],f[i+j+1][1]%=mod;
            siz[id]+=siz[to];
            for(int i=0;i<=siz[id];i++)
                dp[id][i][0]=f[i][0],dp[id][i][1]=f[i][1];
        }
}

int main(){
    initfac(4000);
    scanf("%d",&n);
    for(int i=1;i<(n<<1);i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }

    dfs(1,0);
    long long answer=0;
    for(int i=0;i<=n;i++)
        answer+=(i&1?-1:1)*fac[(n-i)*2]*invfac[n-i]%mod
            *invpower2[n-i]%mod*(dp[1][i][1]+dp[1][i][0])%mod;
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}