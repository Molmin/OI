// 2023.05.24

#include<bits/stdc++.h>
using namespace std;

double dp[2001][13];

double work(int k,int w){
    if(!k)dp[k][w]=0;
    else if(dp[k][w]>0)return dp[k][w];
    else{
        dp[k][w]=1e10;
        if(w)for(int i=1;i<=k;i++)
            dp[k][w]=min(dp[k][w],(work(k-i,w)*(k-i+1)+work(i-1,w-1)*i)/(k+1)+1);
    }
    return dp[k][w];
}

int main(){
    int k,w;
    while(~scanf("%d%d",&k,&w)){
        if(w>12)w=12;
        printf("%.6lf\n",work(k,w));
    }
    return 0;
}