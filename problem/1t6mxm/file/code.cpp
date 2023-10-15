// 2023.10.13

#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;

int n,w[4001],sum[4001];
long long dp[4001][4001][2],f[4001],g[4001];
// dp[i][j][0] 表示处理到 a[i] 满足 a[i-1]<=a[i]=j，且右端点可能情况已计算
// dp[i][j][1] 表示处理到 a[i] 满足 j=a[i-1]>a[i]，且右端点可能情况未计算

int main(){
    freopen("sequence.in","r",stdin);
    freopen("sequence.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",w+i),sum[i]=(sum[i-1]+w[i])%mod;
    for(int i=1;i<=n;i++){
        dp[3][i][0]=(1ll*i*w[i]%mod+sum[n]-sum[i])%mod*i%mod;
        dp[3][i][1]=(1ll*i*w[i]%mod+sum[n]-sum[i])%mod;
    }
    for(int i=4;i<=n;i++){
        for(int j=1;j<=n;j++)
            dp[i][j][1]=dp[i-1][j][0]*w[j]%mod;
        for(int j=1;j<=n;j++){
            f[j]=(f[j-1]+dp[i-1][j][0]+dp[i-1][j][1]*(j-1))%mod;
            g[j]=(g[j-1]+dp[i-1][j][1]*w[j])%mod;
        }
        for(int j=1;j<=n;j++){
            dp[i][j][0]=f[j]*w[j]%mod,
            dp[i][j][0]+=(g[n]-g[j])*j%mod;
            dp[i][j][1]+=g[n]-g[j];
        }
        for(int j=1;j<=n;j++)
            dp[i][j][0]%=mod,dp[i][j][1]%=mod;
    }
    long long answer=0;
    for(int i=1;i<=n;i++)
        answer+=dp[n][i][0]+dp[n][i][1]*(i-1)%mod;
    printf("%lld\n",answer%mod);
    return 0;
}