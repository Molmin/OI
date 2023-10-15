// 2023.09.28

#include<bits/stdc++.h>
using namespace std;

int n,a[700001],pos[700001];

struct BIT{
    int v[700001];
    inline int lowbit(int x){return x&-x;}
    inline void clear(int x){for(;x<=n;x+=lowbit(x))v[x]=0;}
    inline void add(int x,int val){for(;x<=n;x+=lowbit(x))v[x]+=val;}
    inline int query(int x){int sum=0;for(;x;x-=lowbit(x))sum+=v[x];return sum;}
}T;

inline int find(int v){
    int l=1,r=n;
    while(l<r){
        int mid=l+r>>1;
        if(v<=T.query(mid))r=mid;
        else l=mid+1;
    }
    return l;
}

long long solve(int l,int r,bool shouldInit){
    if(l>r)return 0;
    if(l==r){
        if(!shouldInit)T.add(pos[l],-1);
        return 0;
    }
    if(shouldInit)for(int i=l;i<=r;i++)T.add(pos[i],1);
    long long ret=r-l+1;
    int midId=find((r-l)/2+1),mid=a[midId];
    T.add(midId,-1);
    if(r-mid>mid-l){
        for(int i=l;i<mid;i++)T.add(pos[i],-1);
        ret+=solve(mid+1,r,false);
        ret+=solve(l,mid-1,true);
        for(int i=l;i<mid;i++)T.clear(pos[i]);
    }
    else{
        for(int i=mid+1;i<=r;i++)T.add(pos[i],-1);
        ret+=solve(l,mid-1,false);
        ret+=solve(mid+1,r,true);
        for(int i=mid+1;i<=r;i++)T.clear(pos[i]);
    }
    return ret;
}

int main(){
    freopen("sort.in","r",stdin);
    freopen("sort.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),pos[a[i]]=i;
    printf("%lld",solve(1,n,true));
    return 0;
}