// 2023.07.05

#include<bits/stdc++.h>
using namespace std;

queue<int> Q,Q1,Q2;
int n,m,q,u,v,t,a[100001];

void debug(int x){
    int n=Q.size();
    for(int i=1;i<=n;i++){
        int v=Q.front();
        printf("%lld ",v+1ll*x*q);
        Q.pop();Q.push(v);
    }
    printf("\n");
    n=Q1.size();
    for(int i=1;i<=n;i++){
        int v=Q1.front();
        printf("%lld ",v+1ll*x*q);
        Q1.pop();Q1.push(v);
    }
    printf("\n");
    n=Q2.size();
    for(int i=1;i<=n;i++){
        int v=Q2.front();
        printf("%lld ",v+1ll*x*q);
        Q2.pop();Q2.push(v);
    }
    printf("\n");
}

int main(){
    scanf("%d%d%d%d%d%d",&n,&m,&q,&u,&v,&t);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    sort(a+1,a+1+n);
    for(int i=n;i>=1;i--)
        Q.push(a[i]);
    for(int i=1;i<=m;i++){
        int maxlen=-2e9,from;
        if(!Q .empty()&&Q .front()>maxlen)maxlen=Q .front(),from=0;
        if(!Q1.empty()&&Q1.front()>maxlen)maxlen=Q1.front(),from=1;
        if(!Q2.empty()&&Q2.front()>maxlen)maxlen=Q2.front(),from=2;
        if(from==0)Q .pop();
        if(from==1)Q1.pop();
        if(from==2)Q2.pop();
        long long reallength=maxlen+(i-1ll)*q;
        if(!(i%t))printf("%lld ",reallength);
        Q1.push(int(reallength*u/v-(i-1ll)*q-q));
        Q2.push(int(reallength-reallength*u/v-(i-1ll)*q-q));
    }
    printf("\n");
    for(int i=1;i<=n+m;i++){
        int maxlen=-2e9,from;
        if(!Q .empty()&&Q .front()>maxlen)maxlen=Q .front(),from=0;
        if(!Q1.empty()&&Q1.front()>maxlen)maxlen=Q1.front(),from=1;
        if(!Q2.empty()&&Q2.front()>maxlen)maxlen=Q2.front(),from=2;
        if(from==0)Q .pop();
        if(from==1)Q1.pop();
        if(from==2)Q2.pop();
        long long reallength=maxlen+1ll*m*q;
        if(!(i%t))printf("%lld ",reallength);
    }
    printf("\n");
    return 0;
}