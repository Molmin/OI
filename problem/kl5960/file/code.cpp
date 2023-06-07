// 2023.05.01

#include<bits/stdc++.h>
using namespace std;

int n;
long long a[1000001],b[1000001],d[1000002];

void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",a+i);
    for(int i=1;i<=n;i++)
        scanf("%lld",b+i);
    {
        long long sumA=0,sumB=0;
        for(int i=1;i<=n;i++)sumA+=a[i];
        for(int i=1;i<=n;i++)sumB+=b[i];
        if(sumA!=sumB){
            printf("NO\n");
            return;
        }
    }
    d[2]=a[1]-b[1];
    long long l=-d[2],r=-d[2];
    for(int i=2;i<=n;i++){
        l=max(l,-d[i]);
        if(l>r){
            printf("NO\n");
            return;
        }
        d[i+1]=d[i]+a[i]-b[i];
        if(i<n){
            l=max(-(d[i]+a[i]-b[i]),(l-(a[i]-b[i]+d[i])+1)>>1);
            if(l<0)l=0;
            r=(r<<1)-(a[i]-b[i]);
            if(r>((1ll<<60)))r=((1ll<<60));
        }
    }
    long long tmp=-(a[n]-b[n]);
    printf(l<=0&&0<=r&&l+d[n]<=tmp&&tmp<=r+d[n]?"YES\n":"NO\n");
}

int main(){
    freopen("move.in","r",stdin);
    freopen("move.out","w",stdout);
    int T; scanf("%d",&T);
    while(T--)solve();
    return 0;
}