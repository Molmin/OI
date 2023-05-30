// 2023.05.30

#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;

int n,m; long long a[51];
long long dp[8][51];

int main(){
    int T; scanf("%d",&T);
    for(int caseId=1;caseId<=T;caseId++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
            int k; a[i]=0;
            scanf("%d",&k);
            while(k--){
                int x; scanf("%d",&x);
                a[i]|=1ll<<(x-1);
            }
        }
        long long answer=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++){
                    memset(dp,0,sizeof dp);
                    dp[0][0]=1;
                    for(int t=1;t<=m;t++){
                        long long state=0;
                        if(a[t]&(1ll<<(i-1)))state|=1;
                        if(a[t]&(1ll<<(j-1)))state|=2;
                        if(a[t]&(1ll<<(k-1)))state|=4;
                        for(long long s=0;s<8;s++)
                            dp[s][t]+=dp[s][t-1],
                            dp[s][t]+=dp[s^state][t-1];
                    }
                    answer+=dp[7][m],answer%=mod;
                }
        printf("Case #%d: %lld\n",caseId,answer);
    }
    return 0;
}