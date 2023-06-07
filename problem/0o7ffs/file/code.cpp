// 2023.05.31

#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
long long power(long long a,long long n=mod-2){
    long long res=1;
    while(n){
        if(n&1)res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
long long fac[1000001],invfac[1000001];
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
    initfac(1000000);
    int T; scanf("%d",&T);
    for(int caseId=1;caseId<=T;caseId++){
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        long long answer=0;
        for(int i=k;i>=1;i--)
            answer+=((k-i)&1?-1:1)*C(k,i)*i%mod*power(i-1,n-1)%mod;
        long long cmk=1;
        for(int i=1;i<=k;i++)
            cmk*=(m-i+1)*power(i)%mod,cmk%=mod;
        printf("Case #%d: %lld\n",caseId,(answer%mod*cmk%mod+mod)%mod);
    }
    return 0;
}