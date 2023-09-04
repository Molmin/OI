// 2023.09.04

#include<bits/stdc++.h>
using namespace std;

int n,a[2005][2005],c[2005][2005];
long long sum[5][2005][2005],dp[5][2005][2005];
// dp[k][i][j]: 表示在矩形的角 k 上到 i 行 j 列为止的最小花费
// k = 1(左上), 2(右上), 3(左下), 4(右下)

long long getsum(int k,int x1,int y1,int x2,int y2){
    return sum[k][x2][y2]-sum[k][x1-1][y2]-sum[k][x2][y1-1]+sum[k][x1-1][y1-1];
}

int main(){
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&c[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            for(int k=1;k<=4;k++)
                sum[k][i][j]=sum[k][i-1][j]+sum[k][i][j-1]-sum[k][i-1][j-1]+a[i][j];
            sum[c[i][j]][i][j]-=a[i][j];
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dp[1][i][j]=min(dp[1][i-1][j]+getsum(4,i,1,i,j),dp[1][i][j-1]+getsum(1,1,j,i,j));
    for(int i=1;i<=n;i++)
        for(int j=n;j>=1;j--)
            dp[2][i][j]=min(dp[2][i-1][j]+getsum(2,i,j,i,n),dp[2][i][j+1]+getsum(1,1,j,i,j));
    for(int i=n;i>=1;i--)
        for(int j=1;j<=n;j++)
            dp[3][i][j]=min(dp[3][i+1][j]+getsum(4,i,1,i,j),dp[3][i][j-1]+getsum(3,i,j,n,j));
    for(int i=n;i>=1;i--)
        for(int j=n;j>=1;j--)
            dp[4][i][j]=min(dp[4][i+1][j]+getsum(2,i,j,i,n),dp[4][i][j+1]+getsum(3,i,j,n,j));
    long long answer=0x7fffffffffffffff;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            answer=min(answer,dp[1][i][j]+dp[2][i][j+1]+dp[3][i+1][j]+dp[4][i+1][j+1]);
    printf("%lld\n",answer);
    return 0;
}