// 2023.05.31

#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;

int n,m,a[200001];

int main(){
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i);
        long long answer=1;
        for(int i=2;i<=n&&answer;i++){
            int x=m/a[i],y=a[i-1]/a[i];
            if(a[i-1]%a[i])answer=0;
            // 只需要求 1~x 中与 y 互质的数即可
            vector<long long> result;
            for(int j=2;j*j<=y;j++)
                if(y%j==0){
                    for(long long k :result)
                        result.push_back(-k*j);
                    result.push_back(j);
                    while(!(y%j))y/=j;
                }
            if(y>1){
                for(long long k :result)
                    result.push_back(-k*y);
                result.push_back(y);
            }
            long long sum=0;
            for(long long j :result)
                sum+=x/j,sum%=mod;
            answer*=x-sum,answer%=mod;
        }
        printf("%lld\n",(answer+mod)%mod);
    }
    return 0;
}