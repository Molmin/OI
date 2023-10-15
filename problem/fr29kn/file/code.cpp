// 2023.05.29

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

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    long long ans=1;
    for(int i=1;i<=2*m+n-1;i++)
        ans*=i,ans%=mod;
    for(int i=1;i<=(m<<1);i++)
        ans*=power(i),ans%=mod;
    for(int i=1;i<n;i++)
        ans*=power(i),ans%=mod;
    printf("%lld\n",ans);
    return 0;
}