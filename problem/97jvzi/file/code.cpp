// 2023.09.04

#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;

int n,m,q,a[500001];
int sum[500001],nxt[500001],pre[500001];
long long sumnxt[500001];

int main(){
    freopen("freeze.in","r",stdin);
    freopen("freeze.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    for(int i=1;i<n;i++)sum[i]=sum[i-1]+(a[i]!=a[i+1]);
    nxt[n]=n;
    for(int i=n-1;i>=1;i--)
        if(a[i]==a[i+1])nxt[i]=i;
        else if(i+2<=n&&a[i]==a[i+2])nxt[i]=nxt[i+1];
        else nxt[i]=i+1;
    for(int i=1;i<=n;i++)
        if(nxt[i]==nxt[i-1]&&i>1)pre[i]=pre[i-1];
        else pre[i]=i;
    for(int i=1;i<n;i++)sumnxt[i]=(nxt[i]-i+sumnxt[i-1])%mod;
    while(q--){
        int l,r; scanf("%d%d",&l,&r);
        long long answer=0;
        answer+=(r-l+1ll)*(m-1)%mod; // 情况 1：最长公共前缀与最长公共后缀长度和为 r-l
        // 情况 2：最长公共前缀与最长公共后缀长度和小于 r-l
        answer+=(r-l+1ll)*(m-1)%mod*(sum[r-1]-sum[l-1])%mod; // 基础情况
        answer-=sumnxt[r-1]-sumnxt[l-1]; // 算重的部分
        if(nxt[r-1]>r&&l!=r)
            answer+=1ll*(nxt[r-1]-r)*(r-max(pre[r-1],l))%mod; // nxt 值多出 r 的部分
        printf("%lld\n",(answer%mod+mod)%mod);
    }
    return 0;
}