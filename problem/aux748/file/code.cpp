// 2023.05.24

#include<bits/stdc++.h>
using namespace std;

int n,k,p[16],r[16];
double dp[102][1<<15];

int main(){
    scanf("%d%d",&k,&n);
    for(int i=1;i<=n;i++){
        scanf("%d",p+i);
        int x; scanf("%d",&x);
        while(x)
            r[i]|=1<<x-1,
            scanf("%d",&x);
    }
    for(int i=k;i>=1;i--)
        for(int j=0;j<(1<<n);j++){
            for(int t=1;t<=n;t++)
                if((j|r[t])==j)
                    dp[i][j]+=max(dp[i+1][j|(1<<(t-1))]+p[t],dp[i+1][j]);
                else dp[i][j]+=dp[i+1][j];
            dp[i][j]/=n;
        }
    printf("%.6lf\n",dp[1][0]);
    return 0;
}