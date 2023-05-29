// 2023.05.29

#include<bits/stdc++.h>
using namespace std;

long double C[2501][2501];
void initC(int N){
    C[0][0]=1;
    for(int i=1;i<=N;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
}

int n,k;
struct Point{
    long double x,y;
}a[2501];

long double calc(Point A,Point B){
    return (long double)A.x*B.y-(long double)A.y*B.x;
}

int main(){
    initC(2500);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%Lf%Lf",&a[i].x,&a[i].y);
    long double sum=0;
    for(int i=1;i<=n;i++)
        for(int t=k-1;t<n;t++){
            int j=i+t; if(j>n)j-=n;
            sum+=calc(a[i],a[j])*C[t-1][k-2]/C[n][k];
        }
    printf("%.7Lf\n",sum/2);
    return 0;
}