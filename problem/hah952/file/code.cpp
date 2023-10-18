// 2023.10.18

#include<bits/stdc++.h>
using namespace std;

int n,x[501],y[501];
double dp[501][501],dis[501][501];

bool cmp1(int i,int j){return x[i]<x[j];}
bool cmp2(int i,int j){return y[i]<y[j];}

void solve(int xl,int xr,int yl,int yr,bool sortX){
    vector<int> id;
    for(int i=1;i<=n;i++)
        if(xl<=x[i]&&x[i]<=xr&&yl<=y[i]&&y[i]<=yr)id.push_back(i);
    if(id.size()==1)return;
    int cnt=id.size()>>1;
    if(sortX){
        sort(id.begin(),id.end(),cmp1);
        solve(xl,x[id[cnt]]-1,yl,yr,!sortX);
        solve(x[id[cnt]],xr,yl,yr,!sortX);
    }
    else{
        sort(id.begin(),id.end(),cmp2);
        solve(xl,xr,yl,y[id[cnt]]-1,!sortX);
        solve(xl,xr,y[id[cnt]],yr,!sortX);
    }
    vector<int> l,r;
    for(int i=0;i<cnt;i++)l.push_back(id[i]);
    for(int i=cnt;i<id.size();i++)r.push_back(id[i]);
    vector<pair<int,int> > tmp;
    // 预处理第二块中的起点终点对
    for(int i :r)for(int j :r)
        if(dp[i][j]<1e9)tmp.push_back({i,j});
    // 转移
    for(int i :l)for(int j :l)
        if(dp[i][j]<1e9)for(pair<int,int> t :tmp)
            dp[i][t.second]=min(dp[i][t.second],dp[i][j]+dis[j][t.first]+dp[t.first][t.second]);
    for(int i :l)for(int j :r)dp[j][i]=dp[i][j];
    // 把同一块中的两点距离清除，防止影响后续计算
    //（同一块中两点不能在其父块中成为起点和终点）
    for(int i :l)for(int j :l)dp[i][j]=1e9;
    for(int i :r)for(int j :r)dp[i][j]=1e9;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",x+i,y+i);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j)dp[i][j]=1e9;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dis[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
    solve(1,2000,1,2000,true);
    double answer=1e9;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            answer=min(answer,dp[i][j]);
    printf("%.2lf\n",answer);
    return 0;
}