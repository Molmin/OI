// 2023.05.29

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

long long S2[2001][2001];
void initStirling2(int N){
    S2[1][1]=1;
    for(int i=2;i<=N;i++)
        for(int j=1;j<=i;j++)
            S2[i][j]=(S2[i-1][j-1]+j*S2[i-1][j])%mod;
}

int main(){
    initStirling2(2000);
    int T; scanf("%d",&T);
    while(T--){
        int n,m,k,x;
        scanf("%d%d%d",&n,&m,&k);
        x=m-m/2;
        long long answer=0,power_m=power(m),
            tmp=(long long)n*x%mod*power(m,n-1)%mod;
        for(int i=1;i<=k&&i<=n;i++)
            answer+=tmp*S2[k][i]%mod,
            tmp*=(n-i)*(long long)x%mod
                *power_m%mod,tmp%=mod;
        printf("%lld\n",answer%mod);
    }
    return 0;
}