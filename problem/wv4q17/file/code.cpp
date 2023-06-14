// 2023.06.14

#include<bits/stdc++.h>
using namespace std;

int n,m,a[101][101];
bool cmp(int x,int y){
    return a[y][x]==0;
}
int ansx[101],ansy[101],totx,toty;

int fa[101];
int find(int id){
    if(fa[id]==id)return id;
    else return fa[id]=find(fa[id]);
}

int main(){
    int T,TestId; scanf("%d%d",&TestId,&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",a[i]+j);
        for(int i=1;i<=n;i++)fa[i]=i;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(a[i][j]==0&&i!=j&&find(i)!=find(j))
                    fa[find(i)]=find(j);
        bool flag=true;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++)
                    if(i!=j&&j!=k&&k!=i&&a[i][j]==0&&a[j][k]==0&&a[i][k]==1)
                        flag=false;
        totx=toty=0;
        int total=0;
        for(int i=1;i<=n&&flag;i++)
            if(find(i)==i){
                total++;
                vector<int> ids; ids.clear();
                for(int j=1;j<=n;j++)
                    if(find(j)==i)ids.push_back(j);
                int rank[101]={};
                for(int j=0;j<ids.size();j++)
                    rank[j]=ids.size();
                for(int j=0;j<ids.size();j++)
                    for(int k=0;k<ids.size();k++)
                        if(j!=k&&a[ids[k]][ids[j]])rank[j]--;
                for(int j=0;j<ids.size();j++)
                    for(int k=0;k<ids.size();k++)
                        if(j!=k&&rank[j]==rank[k])flag=false;
                if(!flag)continue;
                sort(ids.begin(),ids.end(),cmp);
                for(int j :ids)
                    totx++,ansx[j]=n-totx+1;
                reverse(ids.begin(),ids.end());
                for(int j :ids)
                    toty++,ansy[j]=toty;
            }
        if(m==1&&total==1&&flag){
            puts("YES");
            for(int i=1;i<=n;i++)
                printf("%d\n",ansy[i]);
        }
        else if(m==1)puts("NO");
        else if(flag){
            puts("YES");
            for(int i=1;i<=n;i++){
                for(int j=2;j<=m;j++)
                    printf("%d ",ansx[i]);
                printf("%d\n",ansy[i]);
            }
        }
        else puts("NO");
    }
    return 0;
}