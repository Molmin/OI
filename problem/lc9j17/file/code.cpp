// 2023.05.31

#include<bits/stdc++.h>
using namespace std;
long long mod;
long long power(long long a,long long n=mod-2){
    long long res=1;
    while(n){
        if(n&1)res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
long long fac[3000001],invfac[3000001];
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

int main(){
    int n;
    scanf("%d%lld",&n,&mod);
    initfac(n*3);
    long long count0=1,
        count1=2*fac[n<<1]-fac[n],
        count2=2*C(n<<1,n)*fac[n]%mod*fac[n<<1]%mod,
        count3=fac[n*3];
    long long tmp=fac[n]*fac[n]%mod*fac[n]%mod;
    // 2n+1 ~ 3n 中有 i 个在 [n+1, 2n] 上
    for(int i=0;i<=n;i++)
        count2-=tmp*C(n,i)%mod*C(n,n-i)%mod*C(2*n-i,n)%mod;
    long long answer=1*(count1-count0)+2*(count2-count1)+3*(count3-count2);
    printf("%lld\n",(answer%mod+mod)%mod);
    return 0;
}