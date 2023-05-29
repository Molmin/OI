// 2023.05.27

#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;

int n,a[1000001],pre[1000001],id[1000001];
// pre[i]: a[i] 上一次出现的位置
// id[i]: i 在数列中的位置

namespace Binary{
    long long a[1000001],b[1000001];
    int lowbit(int x){
        return x&-x;
    }
    long long query(int id){
        long long sum=0;
        for(int i=id;i;i-=lowbit(i))
            sum+=a[i]*(id+1)-b[i];
        return sum;
    }
    void add(int id,int val){
        for(int i=id;i<=n;i+=lowbit(i))
            a[i]+=val,b[i]+=id*val;
    }
}

int disc[1000001],cntdisc;
int finddisc(int x){
    return lower_bound(disc+1,disc+1+cntdisc,x)-disc-1;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),
        disc[++cntdisc]=a[i];
    sort(disc+1,disc+1+cntdisc);
    cntdisc=unique(disc+1,disc+cntdisc+1)-disc-1;
    for(int i=1;i<=n;i++){
        a[i]=finddisc(a[i]);
        pre[i]=id[a[i]],id[a[i]]=i;
    }
    long long now=0,sum=0;
    for(int i=1;i<=n;i++){
        now+=i-pre[i]+((Binary::query(i)
            -Binary::query(pre[i]))<<1);
        now%=mod,sum+=now,sum%=mod;
        Binary::add(pre[i]+1,1);
        Binary::add(i+1,-1);
    }
    printf("%lld\n",sum);
    return 0;
}