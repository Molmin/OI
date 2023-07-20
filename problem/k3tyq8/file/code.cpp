// 2023.07.20

#include<bits/stdc++.h>
using namespace std;

int n,m,h,a[150001],b[150001],lastby[150001];

struct Node{
    int value,id;
    bool operator<(Node tmp)const{
        return value<tmp.value;
    }
}c[150001];

namespace SegmentTree{
    int val[610001],lazy[610001];
    void pushup(int id){
        val[id]=min(val[id<<1],val[(id<<1)+1]);
    }
    void pushdown(int id){
        if(lazy[id]){
            lazy[id<<1]+=lazy[id];
            val[id<<1]+=lazy[id];
            lazy[(id<<1)+1]+=lazy[id];
            val[(id<<1)+1]+=lazy[id];
            lazy[id]=0;
        }
    }

    void build(int id,int l,int r){
        if(l==r){
            if(l)val[id]=m-l+1;
            return;
        }
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build((id<<1)+1,mid+1,r);
        pushup(id);
    }

    void updateAdd(int id,int l,int r,int x,int y,int v){
        if(y==0)x=0; // 防止右端点为 0
        if(x<=l&&r<=y){
            lazy[id]+=v,val[id]+=v;
            return;
        }
        int mid=l+r>>1;
        pushdown(id);
        if(x<=mid)updateAdd(id<<1,l,mid,x,y,v);
        if(mid<y)updateAdd((id<<1)+1,mid+1,r,x,y,v);
        pushup(id);
    }

    int queryMin(int id,int l,int r,int x,int y){
        if(x<=l&&r<=y)return val[id];
        int mid=l+r>>1,res=0x7fffffff;
        pushdown(id);
        if(x<=mid)res=min(res,queryMin(id<<1,l,mid,x,y));
        if(mid<y)res=min(res,queryMin((id<<1)+1,mid+1,r,x,y));
        return res;
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&h);
    for(int i=1;i<=m;i++)
        scanf("%d",b+i);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    sort(b+1,b+1+m);
    for(int i=1;i<=n;i++)
        c[i]={h-a[i],i};
    sort(c+1,c+1+n);
    if(b[1]<c[1].value)
        return printf("0\n"),0;

    int tmp=1;
    for(int i=1;i<=m;i++)
        while(tmp<=n&&c[tmp].value<=b[i])
            lastby[c[tmp++].id]=i;
    SegmentTree::build(1,0,m);
    for(int i=1;i<=m;i++)
        SegmentTree::updateAdd(1,0,m,1,lastby[i],-1);
    int answer=0;
    answer+=SegmentTree::queryMin(1,0,m,0,m)>=0;
    for(int i=m+1;i<=n;i++){
        SegmentTree::updateAdd(1,0,m,1,lastby[i-m],1);
        SegmentTree::updateAdd(1,0,m,1,lastby[i],-1);
        answer+=SegmentTree::queryMin(1,0,m,0,m)>=0;
    }
    printf("%d\n",answer);
    return 0;
}