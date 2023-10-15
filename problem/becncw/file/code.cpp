// 2023.09.27

#include<bits/stdc++.h>
using namespace std;

int n,q; long long ans[500001];
int l[500001],r[500001];
int cnt[500001];

struct BIT{
    int v[500001];
    void add(int id){
        while(id<=n)v[id]++,id+=id&(-id);
    }
    int query(int id){
        int sum=0;
        while(id)sum+=v[id],id-=id&(-id);
        return sum;
    }
}T;

struct Query{
    int x,y,y1;
    int mul,qid;
    bool operator<(Query q)const{
        return x==q.x?mul<q.mul:x<q.x;
    }
};
vector<Query> Q;

int main(){
    freopen("badge.in","r",stdin);
    freopen("badge.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d%d",l+i,r+i);
        Q.push_back({l[i],r[i]});
    }
    for(int id=1;id<=q;id++){
        int m; scanf("%d",&m);
        vector<int> x;
        for(int i=1;i<=m;i++){
            int v; scanf("%d",&v);
            x.push_back(v);
        }
        if(m>sqrt(n)){
            for(int i=1;i<=n;i++)cnt[i]=0;
            for(int i :x)cnt[i]++;
            for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
            for(int i=1;i<=n;i++)
                if((cnt[r[i]]-cnt[l[i]-1])&1)ans[id]++;
        }
        else{
            sort(x.begin(),x.end());
            for(int i=0;i<m;i++)
                for(int j=i;j<m;j+=2){
                    int lx=i==0?1:x[i-1]+1,
                        rx=x[i],ly=x[j],
                        ry=j==m-1?n:x[j+1]-1;
                    Q.push_back({lx,ly,ry,-1,id});
                    Q.push_back({rx,ly,ry,1,id});
                }
        }
    }
    sort(Q.begin(),Q.end());
    for(Query q :Q)
        if(q.mul==0)T.add(q.y);
        else ans[q.qid]+=q.mul*(T.query(q.y1)-T.query(q.y-1));
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
    return 0;
}