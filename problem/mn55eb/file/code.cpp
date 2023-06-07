// 2023.05.27

#include<bits/stdc++.h>
using namespace std;

struct Mode{
    int val,t;
    void merge(int x,int y){
        if(y>t)val=x,t=y;
        else if(y==t&&x<val)val=x;
    }
};

int n,m,a[40001],lastAnswer;
int blocklen,blockId[40001];
Mode f[201][201]; int g[201][40001];
// f[i][j]: 第 i 个块到第 j 个块的最小众数
// g[i][j]: 前 i 个块中 j 出现的次数
int tot[40001];

int disc[1000001],cntdisc;
int finddisc(int x){
    return lower_bound(disc+1,disc+1+cntdisc,x)-disc;
}

int main(){
    scanf("%d%d",&n,&m);
    blocklen=sqrt(n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i),
        disc[++cntdisc]=a[i],
        blockId[i]=(i-1)/blocklen+1;
    sort(disc+1,disc+1+cntdisc);
    cntdisc=unique(disc+1,disc+cntdisc+1)-disc-1;
    for(int i=1;i<=n;i++)
        a[i]=finddisc(a[i]);

    // Calculate f[i][j]
    for(int i=1;i<=blockId[n];i++){
        memset(tot,0,sizeof tot);
        for(int j=(i-1)*blocklen+1;j<=n;j++){
            if(blockId[j]!=blockId[j-1])
                f[i][blockId[j]]=f[i][blockId[j]-1];
            tot[a[j]]++;
            f[i][blockId[j]].merge(a[j],tot[a[j]]);
        }
    }

    // Calculate g[i][j]
    for(int i=1;i<=n;i++)
        g[blockId[i]][a[i]]++;
    for(int j=1;j<=n;j++)
        for(int i=1;i<=blockId[n];i++)
            g[i][j]+=g[i-1][j];

    while(m--){
        int l,r;
        scanf("%d%d",&l,&r);
        l=(l+lastAnswer-1)%n+1,
        r=(r+lastAnswer-1)%n+1;
        if(l>r)swap(l,r);

        if(blockId[r]-blockId[l]<=1){
            for(int i=l;i<=r;i++)tot[a[i]]=0;
            for(int i=l;i<=r;i++)tot[a[i]]++;

            Mode ans={0,0};
            for(int i=l;i<=r;i++)
                ans.merge(a[i],tot[a[i]]);
            lastAnswer=disc[ans.val];
        }
        else{
            int L=blockId[l]*blocklen,
                R=(blockId[r]-1)*blocklen+1;
            int mode=f[blockId[l]+1][blockId[r]-1].val;
            tot[mode]=0;
            for(int i=l;i<=L;i++)tot[a[i]]=0;
            for(int i=R;i<=r;i++)tot[a[i]]=0;

            for(int i=l;i<=L;i++)tot[a[i]]++;
            for(int i=R;i<=r;i++)tot[a[i]]++;
            Mode ans={0,0};
            for(int i=l;i<=L;i++){
                ans.merge(a[i],tot[a[i]]
                    +g[blockId[r]-1][a[i]]
                    -g[blockId[l]][a[i]]);
            }
            for(int i=R;i<=r;i++){
                ans.merge(a[i],tot[a[i]]
                    +g[blockId[r]-1][a[i]]
                    -g[blockId[l]][a[i]]);
            }
            ans.merge(mode,tot[mode]
                +g[blockId[r]-1][mode]
                -g[blockId[l]][mode]);
            lastAnswer=disc[ans.val];
        }
        printf("%d\n",lastAnswer);
    }
    return 0;
}