// 2023.5.23

#include<bits/stdc++.h>
using namespace std;

int n;
struct circle{
    int x,r;
    bool operator<(circle tmp)const{
        return r<tmp.r;
    }
}c[300001];

int disc[600001],cntdisc;
int finddisc(int x){
    return lower_bound(disc+1,disc+1+cntdisc,x)-disc-1;
}

namespace SegmentTree{
    struct Node{
        int l,r; bool tag;
    }a[900001];
    void pushup(int id){
        a[id].tag=a[id<<1].tag & a[(id<<1)+1].tag;
    }
    void pushdown(int id){
        a[id<<1].tag|=a[id].tag;
        a[(id<<1)+1].tag|=a[id].tag;
    }

    void build(int id, int l, int r){
        a[id].l=l,a[id].r=r;
        if(l==r)return;
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build((id<<1)+1,mid+1,r);
    }
    bool query(int id,int l,int r){
        pushdown(id); 
        if(l<=a[id].l&&a[id].r<=r)
            return a[id].tag;
        int mid=a[id].l+a[id].r>>1,res=1;
        if(l<=mid)res&=query(id<<1,l,r);
        if(r>mid) res&=query((id<<1)+1,l,r);
        return res;
    }
    void add(int id,int l,int r){
        pushdown(id);
        if(l<=a[id].l&&a[id].r<=r){
            a[id].tag=true; return;
        } 
        int mid=a[id].l+a[id].r>>1;
        if(l<=mid)add(id<<1,l,r);
        if(r>mid) add((id<<1)+1,l,r);
        pushup(id); 
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&c[i].x,&c[i].r);
        disc[++cntdisc]=c[i].x-c[i].r;
        disc[++cntdisc]=c[i].x+c[i].r;
    }
    sort(disc+1,disc+1+cntdisc);
    cntdisc=unique(disc+1,disc+cntdisc+1)-disc-1;
    sort(c+1,c+1+n);

    SegmentTree::build(1,1,cntdisc);
    int answer=n+1;
    for(int i=1;i<=n;i++){
        int l=finddisc(c[i].x-c[i].r),
            r=finddisc(c[i].x+c[i].r);
        answer+=SegmentTree::query(1,l+1,r),
        SegmentTree::add(1,l+1,r);
    }
    printf("%d\n",answer);
    return 0;
}