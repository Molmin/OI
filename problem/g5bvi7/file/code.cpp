// 2023.05.22

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
long long fac[20000001],invfac[20000001];
void initfac(int N){
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=fac[i-1]*i%mod;
    invfac[N]=power(fac[N]);
    for(int i=N;i>=1;i--)
        invfac[i-1]=invfac[i]*i%mod;
}
long long C(int m,int n){
    if(n<0||m<0||n>m)return 0;
    return fac[m]*invfac[n]%mod*invfac[m-n]%mod;
}

int n,m,k;

int main() {
    scanf("%d%d%d",&n,&m,&k);
    initfac(n+m);
    long long answer=0;
    for(int i=1,maxi=min(n,k?m/k:n);i<=maxi;i++){
        long long tmp=i&1?1:-1;
        tmp*=C(n,i)*C(m-i*k+n-1,n-1)%mod;
        answer+=tmp,answer%=mod;
    }
    answer*=power(n*C(m-k+n-1,n-1)%mod);
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}