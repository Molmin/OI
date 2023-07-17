// 2023.07.04

#include<bits/stdc++.h>
using namespace std;

int n,m,pos[300001],minpos[300001],maxpos[300001];

namespace SegmentTree{
    int a[2400001],tag[2400001];
    void pushdown(int id,int l,int r){
        if(tag[id]){
            a[id<<1]+=((l+r>>1)-l+1)*tag[id];
            a[(id<<1)+1]+=(r-(l+r>>1))*tag[id];
            tag[id<<1]+=tag[id];
            tag[(id<<1)+1]+=tag[id];
            tag[id]=0;
        }
    }
    void pushup(int id){
        a[id]=a[id<<1]+a[(id<<1)+1];
    }
    void update(int id,int l,int r,int x,int val){
        if(l==x&&r==x)a[id]+=val;
        else{
            pushdown(id,l,r);
            int mid=l+r>>1;
            if(x<=mid)update(id<<1,l,mid,x,val);
            else update((id<<1)+1,mid+1,r,x,val);
            pushup(id);
        }
    }
    int query(int id,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr)return a[id];
        pushdown(id,l,r);
        int mid=l+r>>1,res=0;
        if(ql<=mid)res+=query(id<<1,l,mid,ql,qr);
        if(qr>mid)res+=query((id<<1)+1,mid+1,r,ql,qr);
        return res;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    int treelength=n+m;
    for(int i=1;i<=n;i++)
        pos[i]=i+m,minpos[i]=maxpos[i]=i;
    for(int i=1;i<=n;i++)
        SegmentTree::update(1,1,treelength,pos[i],1);
    while(m--){
        int x; scanf("%d",&x);
        maxpos[x]=max(maxpos[x],SegmentTree::query(1,1,treelength,1,pos[x]));
        SegmentTree::update(1,1,treelength,pos[x],-1);
        pos[x]=m+1;
        SegmentTree::update(1,1,treelength,pos[x],1);
        minpos[x]=1;
    }
    for(int i=1;i<=n;i++)
        maxpos[i]=max(maxpos[i],SegmentTree::query(1,1,treelength,1,pos[i]));
    for(int i=1;i<=n;i++)
        printf("%d %d\n",minpos[i],maxpos[i]);
    return 0;
}