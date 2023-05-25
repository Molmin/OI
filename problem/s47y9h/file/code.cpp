// 2023.05.25

#include<bits/stdc++.h>
using namespace std;

int A,B,C,D;
double dp[14][14][14][14][5][5];
bool vis[14][14][14][14][5][5];

double work(int a,int b,int c,int d,int e,int f){
    if(vis[a][b][c][d][e][f])
        return dp[a][b][c][d][e][f];
    else vis[a][b][c][d][e][f]=true;
    if(a+(e==1)+(f==1)>=A && b+(e==2)+(f==2)>=B
        && c+(e==3)+(f==3)>=C && d+(e==4)+(f==4)>=D)
        return dp[a][b][c][d][e][f]=0;
    int sum=54-a-b-c-d-bool(e)-bool(f);
    double answer=0;
    if(a<13)answer+=(13.0-a)/sum*(work(a+1,b,c,d,e,f)+1);
    if(b<13)answer+=(13.0-b)/sum*(work(a,b+1,c,d,e,f)+1);
    if(c<13)answer+=(13.0-c)/sum*(work(a,b,c+1,d,e,f)+1);
    if(d<13)answer+=(13.0-d)/sum*(work(a,b,c,d+1,e,f)+1);
    if(!e){
        double minn=1e15;
        for(int p=1;p<=4;p++)
            minn=min(minn,work(a,b,c,d,p,f));
        minn++,answer+=minn/sum;
    }
    if(!f){
        double minn=1e15;
        for(int p=1;p<=4;p++)
            minn=min(minn,work(a,b,c,d,e,p));
        minn++,answer+=minn/sum;
    }
    return dp[a][b][c][d][e][f]=answer;
}

int main(){
    int T; scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%d%d%d%d",&A,&B,&C,&D);
        memset(dp,0,sizeof dp);
        memset(vis,false,sizeof vis);
        if(max(13,A)+max(13,B)+max(13,C)+max(13,D)>54)
            printf("Case %d: -1.000\n",i);
        else printf("Case %d: %.3f\n",i,work(0,0,0,0,0,0));
    }
    return 0;
}