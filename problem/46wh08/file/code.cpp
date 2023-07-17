// 2023.07.14

#include<bits/stdc++.h>
using namespace std;

int n;

struct Node{
    int t,id; bool isEnd;
    bool operator<(Node tmp)const{
        if(t!=tmp.t)return t<tmp.t;
        return isEnd<tmp.isEnd;
    }
}A[200001],B[200001];

unsigned long long w[100001],tmp,sumA[100001],sumB[100001];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int sa,ea,sb,eb;
        scanf("%d%d%d%d",&sa,&ea,&sb,&eb);
        A[i*2-1]={sa,i,false};
        A[i*2]={ea,i,true};
        B[i*2-1]={sb,i,false};
        B[i*2]={eb,i,true};
    }

    sort(A+1,A+1+n*2);
    sort(B+1,B+1+n*2);
    for(int i=1;i<=n;i++)
        w[i]=rand()<<(unsigned long long)31|rand();

    tmp=0;
    for(int i=1;i<=n*2;i++)
        if(A[i].isEnd)tmp^=w[A[i].id];
        else sumA[A[i].id]^=tmp;
    tmp=0;
    for(int i=n*2;i>=1;i--)
        if(!A[i].isEnd)tmp^=w[A[i].id];
        else sumA[A[i].id]^=tmp;

    tmp=0;
    for(int i=1;i<=n*2;i++)
        if(B[i].isEnd)tmp^=w[B[i].id];
        else sumB[B[i].id]^=tmp;
    tmp=0;
    for(int i=n*2;i>=1;i--)
        if(!B[i].isEnd)tmp^=w[B[i].id];
        else sumB[B[i].id]^=tmp;

    for(int i=1;i<=n;i++)
        if(sumA[i]!=sumB[i])
            return printf("NO\n"),0;
    printf("YES\n");
    return 0;
}