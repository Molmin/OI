// 2023.07.22

#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int CAN_GET_GOLD=1<<0,
          CAN_GET_SILVER=1<<1,
          CAN_GET_BRONZE=1<<2;

int n,m,q,cnt[81][10001],maxScore[81],minScore[81];

int C[101][101];
void initC(int n){
    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
}

int main(){
    initC(100);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++){
        minScore[i]=10000;
        for(int j=1;j<=m;j++){
            int x; scanf("%d",&x);
            cnt[i][x]=true;
            maxScore[i]=max(maxScore[i],x);
            minScore[i]=min(minScore[i],x);
        }
        for(int j=1;j<=10000;j++)
            cnt[i][j]+=cnt[i][j-1];
    }
    while(q--){
        int gold_sum,silver_sum,bronze_sum;
        scanf("%d%d%d",&gold_sum,&silver_sum,&bronze_sum);
        long long answer=0;
        gold_sum--,bronze_sum--; // 排除枚举的 i 和 j
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                // 枚举 i 作为金牌最低分，j 作为铜牌最高分
                if(i==j)continue;
                if(maxScore[i]<minScore[j]
                    ||(maxScore[i]==minScore[j]&&j>=i))continue;
                int cntStatus[1<<3]={};
                for(int k=1;k<=n;k++){
                    if(k==i||k==j)continue;
                    int status=0;
                    if(maxScore[k]>maxScore[i]
                        ||(maxScore[k]==maxScore[i]&&k>i))
                        status|=CAN_GET_GOLD;
                    if(minScore[k]<minScore[j]
                        ||(minScore[k]==minScore[j]&&k<j))
                        status|=CAN_GET_BRONZE;
                    int silver_max=maxScore[i],
                        silver_min=minScore[j];
                    if(k>i)silver_max--;
                    if(k<j)silver_min++;
                    if(cnt[k][silver_max]-cnt[k][silver_min-1]>0)
                        status|=CAN_GET_SILVER;
                    cntStatus[status]++;
                }

                int gold=gold_sum-cntStatus[CAN_GET_GOLD],
                    silver=silver_sum-cntStatus[CAN_GET_SILVER],
                    bronze=bronze_sum-cntStatus[CAN_GET_BRONZE];
                if(gold<0||silver<0||bronze<0)continue;
                int can_gold_silver=cntStatus[CAN_GET_GOLD|CAN_GET_SILVER],
                    can_gold_bronze=cntStatus[CAN_GET_GOLD|CAN_GET_BRONZE],
                    can_silver_bronze=cntStatus[CAN_GET_SILVER|CAN_GET_BRONZE],
                    can_all=cntStatus[CAN_GET_GOLD|CAN_GET_SILVER|CAN_GET_BRONZE];
                for(int x=0;x<=gold;x++){
                    // 枚举能拿金银的人拿金的数量
                    if(!(can_gold_silver-x<=silver))continue;
                    if(x>can_gold_silver)break;
                    for(int y=0;x+y<=gold;y++){
                        // 枚举能拿金铜的人拿金的数量
                        if(!(can_gold_bronze-y<=bronze))continue;
                        if(y>can_gold_bronze)break;
                        int needGold=gold-x-y,
                            needSilver=silver-(can_gold_silver-x);
                        if(needGold>can_all)continue;
                        answer+=1ll*C[can_gold_silver][x]
                            *C[can_gold_bronze][y]%mod
                            *C[can_all][needGold]%mod
                            *C[can_silver_bronze+(can_all-needGold)][needSilver]%mod;
                    }
                }
            }
        printf("%lld\n",answer%mod);
    }
    return 0;
}