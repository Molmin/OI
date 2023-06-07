// 2023.05.23

#include<bits/stdc++.h>
using namespace std;

int n,m;
bool Map[1001][1001];
int l[1001][1001],r[1001][1001],up[1001][1001];
// l/r/up[i][j]: 坐标 (i,j) 向左 / 右 / 上能到达的最小列数

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            char ch;
            scanf(" %c",&ch);
            Map[i][j]=ch=='F';
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            l[i][j]=r[i][j]=j,up[i][j]=1;
    for(int i=1;i<=n;i++)
        for(int j=2;j<=m;j++)
            if(Map[i][j]&&Map[i][j-1])
                l[i][j]=l[i][j-1];
    for(int i=1;i<=n;i++)
        for(int j=m-1;j>=1;j--)
            if(Map[i][j]&&Map[i][j+1])
                r[i][j]=r[i][j+1];
    
    int answer=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(i>1&&Map[i][j]&&Map[i-1][j])
                l[i][j]=max(l[i][j],l[i-1][j]),
                r[i][j]=min(r[i][j],r[i-1][j]),
                up[i][j]=up[i-1][j]+1;
            if(Map[i][j])
                answer=max(answer,(r[i][j]-l[i][j]+1)*up[i][j]);
        }
    printf("%d\n",answer*3);
    return 0;
}