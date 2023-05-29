// 2023.05.25

#include<bits/stdc++.h>
using namespace std;

int n;

namespace SegmentTree{
    struct Node{
        int l,r,sum;
        long long cnt;
    }a[50000001];
    int n;

    int build(int x,int l,int r){
        int id=++n;
        a[id].sum=1;
        if(l==r)return n;
        int mid=l+r>>1;
        if(x<=mid)a[n].l=build(x,l,mid);
        else a[n].r=build(x,mid+1,r);
        return id;
    }
    long long x,y;
    int merge(int i,int j,int l,int r){
        if(i==0)return x=y=0,j;
        if(j==0)return x=y=0,i;
        a[i].cnt+=a[j].cnt;
        long long A=1ll*a[a[i].r].sum*a[a[j].l].sum,
                  B=1ll*a[a[i].l].sum*a[a[j].r].sum;
        int mid=l+r>>1;
        a[i].l=merge(a[i].l,a[j].l,l,mid); A+=x,B+=y;
        a[i].r=merge(a[i].r,a[j].r,mid+1,r); A+=x,B+=y;
        a[i].sum=a[a[i].l].sum+a[a[i].r].sum;
        a[i].cnt+=min(A,B), x=A,y=B;
        return i;
    }
}

int work(){
    int x;
    scanf("%d",&x);
    if(x)return SegmentTree::build(x,1,n);
    else return SegmentTree::merge(work(),work(),1,n);
}

int main(){
    scanf("%d",&n);
    printf("%lld\n",SegmentTree::a[work()].cnt);
    return 0;
}