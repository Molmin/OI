// 2023.05.25

#include<bits/stdc++.h>
using namespace std;

double f[101],g[101];
// f/g[i]: 还剩下 i 颗石子时 Alice 为先手 / 后手，Alice 获胜的概率

int main(){
    int T; scanf("%d",&T);
    while(T--){
        int n; double p,q;
        scanf("%d%lf%lf",&n,&p,&q);
        n=min(n,100),f[0]=0,g[0]=1;
        for(int i=1;i<=n;i++){
            if(f[i-1]<g[i-1])
                f[i]=(p*g[i-1]+(1-p)*q*f[i-1])/(1-(1-p)*(1-q)),
                g[i]=(q*f[i-1]+(1-q)*p*g[i-1])/(1-(1-p)*(1-q));
            else
                f[i]=((1-p)*g[i-1]+p*(1-q)*f[i-1])/(1-p*q),
                g[i]=((1-q)*f[i-1]+q*(1-p)*g[i-1])/(1-p*q);
        }
        printf("%.6lf\n",f[n]);
    }
    return 0;
}