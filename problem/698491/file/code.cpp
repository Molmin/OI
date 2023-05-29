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
long long fac[200001],invfac[200001];
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
long long Stirling2(int n,int m){
    long long res=0;
    for(int i=0;i<m;i++)
        if(i&1)res-=C(m,i)*power(m-i,n)%mod,res%=mod;
        else res+=C(m,i)*power(m-i,n)%mod,res%=mod;
    return res*invfac[m]%mod;
}

int main(){
    int n; long long k;
    scanf("%d%lld",&n,&k);
    initfac(n);
    if(k>=n)return printf("0\n"),0;
    if(k==0)return printf("%lld\n",fac[n]),0;
    printf("%lld\n",(2*C(n,k)*fac[n-k]%mod
        *Stirling2(n,n-k)%mod+mod)%mod);
    return 0;
}