// 2023.10.17

#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int P_COUNT=25,TEST_COUNT=10;
double P[P_COUNT],precalc[P_COUNT],precalc2[P_COUNT][1000001];
ull randull(){
    ull x=rand(),y=rand();
    return (x<<31ull)|y;
}

int n,m,q,z[1000001];
ull w[1000001];
ull noww[1000001][TEST_COUNT],val[1000001][TEST_COUNT];
vector<int> x[1000001];
int total[1000001][P_COUNT];

int main(){
    srand(time(0));
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++){
        int k,v; scanf("%d",&k);
        while(k--)scanf("%d",&v),x[i].push_back(v);
    }
    for(int i=1;i<=q;i++)scanf("%d",z+i);
    for(int i=1;i<=m;i++)w[i]=randull();
    for(int _=0;_<P_COUNT;_++){
        P[_]=_==0?1:(P[_-1]*0.55);
        precalc[_]=log(1-P[_]);
        for(int i=1;i<=m;i++)precalc2[_][i]=log(1-pow(1-P[_],i));
        memset(noww,0,sizeof noww);
        memset(val,0,sizeof val);
        if(P[_]>=0.1){
            for(int i=1;i<=m;i++)
                for(int j=0;j<TEST_COUNT;j++)
                    if(_==0||randull()%(ull)(1000000/P[_])<1000000)noww[i][j]=w[i];
        }
        else{
            int total=m*TEST_COUNT*P[_];
            while(total--){
                int id=rand()%m+1,testId=rand()%TEST_COUNT;
                if(noww[id][testId])total++;
                else noww[id][testId]=w[id];
            }
        }
        for(int i=1;i<=n;i++)
            for(int v :x[i]){
                if(v<0)for(int j=0;j<TEST_COUNT;j++)
                    val[i][j]^=noww[-v][j];
                else for(int j=0;j<TEST_COUNT;j++)
                    val[i][j]^=val[v][j];
            }
        ull current[TEST_COUNT]={};
        for(int i=1;i<=q;i++){
            for(int j=0;j<TEST_COUNT;j++)
                current[j]^=val[z[i]][j],
                total[i][_]+=current[j]!=0;
        }
    }
    for(int i=1;i<=q;i++){
        if(total[i][0]==0){
            printf("0\n");
            continue;
        }
        double tmp=0;
        for(int j=1;j<P_COUNT;j++)
            tmp+=(TEST_COUNT-total[i][j])*precalc[j];
        auto calcP=[&](double x){
            double ret=x*tmp;
            for(int j=1;j<P_COUNT;j++)ret+=total[i][j]*precalc2[j][int(x)];
            return ret;
        };
        double l=1,r=m;
        while(l<r*0.98){
            // 注意到答案在对数坐标上均匀分布
            double mid1=cbrt(l*l*r),mid2=cbrt(l*r*r);
            if(calcP(mid1)<calcP(mid2))l=mid1;
            else r=mid2;
        }
        printf("%d\n",min(m,int(sqrt(l*r))));
    }
    return 0;
}