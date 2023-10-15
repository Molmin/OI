// 2023.05.27

#include<bits/stdc++.h>
using namespace std;

int n,k[200001];
int blocklen,blockId[200001];
int f[200001],g[200001];
// f[i]: 从 i 位置出发要被弹几次弹出所在块
// g[i]: 从 i 位置出发被弹出所在块后到达的位置

int main(){
    scanf("%d",&n);
    blocklen=sqrt(n);
    for(int i=1;i<=n;i++)
        scanf("%d",k+i),
        blockId[i]=(i-1)/blocklen+1;
    for(int i=n;i>=1;i--){
        if(i+k[i]>n||blockId[i+k[i]]!=blockId[i])
            f[i]=1,g[i]=i+k[i];
        else f[i]=f[i+k[i]]+1,g[i]=g[i+k[i]];
    }

    int m; scanf("%d",&m);
    while(m--){
        int op,x;
        scanf("%d%d",&op,&x),x++;
        if(op==1){
            // 从 x 出发被弹几次后弹飞
            int now=x,ans=0;
            while(now<=n)ans+=f[now],now=g[now];
            printf("%d\n",ans);
        }
        else{
            int y; scanf("%d",&y);
            // 第 x 个弹力装置的系数修改成 y
            k[x]=y;
            int l=(blockId[x]-1)*blocklen+1,
                r=blockId[x]*blocklen;
            for(int i=r;i>=l;i--)
                if(i+k[i]>n||blockId[i+k[i]]!=blockId[i])
                    f[i]=1,g[i]=i+k[i];
                else f[i]=f[i+k[i]]+1,g[i]=g[i+k[i]];
        }
    }
    return 0;
}