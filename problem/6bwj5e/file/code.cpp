// 2023.07.15

#include<bits/stdc++.h>
#include <iterator>
using namespace std;

int n,q,a[6000001];
int nxt[6000001],w[6000001]; // 单向链表
int fa[6000001];
int find(int x){
    if(fa[x]==x)return x;
    else return fa[x]=find(fa[x]);
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),
        nxt[i]=n+1,w[i]=-1,
        fa[i]=i;
    int lastId=0;
    for(int i=1;i<=n;i++)
        if(a[i]<a[lastId])
            fa[i]=lastId;
        else{
            nxt[lastId]=i;
            w[lastId]=a[i]-a[lastId];
            lastId=i;
        }
    while(q--){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1){
            lastId=find(x),w[lastId]-=y;
            while(nxt[lastId]!=n+1&&w[lastId]<0){
                int nextId=nxt[lastId];
                w[lastId]+=w[nextId];
                nxt[lastId]=nxt[nextId],fa[nextId]=lastId;
                w[nextId]=-1,nxt[nextId]=n+1;
            }
        }
        if(op==2)
            printf("%d\n",max(0,x-find(y)));
    }
    return 0;
}