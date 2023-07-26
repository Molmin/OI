// 2023.07.26

#include<bits/stdc++.h>
using namespace std;

struct Frac{
    long long x,y;
    Frac(long long a=0,long long b=1):x(a),y(b){
        long long gcd=__gcd(abs(x),abs(y));
        if(y<0)gcd=-gcd; x/=gcd,y/=gcd;
    }
    Frac operator+(Frac tmp)const{
        return Frac(x*tmp.y+y*tmp.x,y*tmp.y);
    }
    Frac operator-(Frac tmp)const{
        return Frac(x*tmp.y-y*tmp.x,y*tmp.y);
    }
    Frac operator*(Frac tmp)const{
        return Frac(x*tmp.x,y*tmp.y);
    }
    Frac operator/(Frac tmp)const{
        return Frac(x*tmp.y,y*tmp.x);
    }
    bool operator<(Frac tmp)const{
        return x*tmp.y<y*tmp.x;
    }
    bool operator<=(Frac tmp)const{
        return x*tmp.y<=y*tmp.x;
    }
    bool operator>=(Frac tmp)const{
        return x*tmp.y>=y*tmp.x;
    }
    bool operator==(Frac tmp)const{
        return x*tmp.y==y*tmp.x;
    }
    bool operator!=(Frac tmp)const{
        return x*tmp.y!=y*tmp.x;
    }
};

int n,m; Frac answer=Frac(1e14);

struct Edge{
    int to,nxt;
}edge[500001];
int cntEdge,head[200001];
void addEdge(int u,int v){
    edge[++cntEdge]={v,head[u]},head[u]=cntEdge;
}

int fa[200001],siz[200001],dep[200001],heavy[200001];
void init(int id){
    siz[id]=1;
    for(int i=head[id];i;i=edge[i].nxt){
        if(edge[i].to==fa[id])continue;
        fa[edge[i].to]=id;
        dep[edge[i].to]=dep[id]+1;
        init(edge[i].to);
        if(siz[edge[i].to]>siz[heavy[id]])
            heavy[id]=edge[i].to;
        siz[id]+=siz[edge[i].to];
    }
}

int cntdfn,dfn[200001],rnk[200001];
int top[200001];
void decomposition(int id,int x){
    // x 为当前链顶端
    top[id]=x,dfn[id]=++cntdfn,rnk[cntdfn]=id;
    if(!heavy[id])return;
    decomposition(heavy[id],x);
    for(int i=head[id];i;i=edge[i].nxt)
        if(edge[i].to!=heavy[id]&&edge[i].to!=fa[id])
            decomposition(edge[i].to,edge[i].to);
}

int getlca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}

Frac now;

struct LineSegment{
    Frac k,b,l,r; // 线段 y = kx + b，左右端点横坐标为 l 和 r
    bool operator<(LineSegment tmp)const{
        if(k*now+b!=tmp.k*now+tmp.b)
            return k*now+b<tmp.k*now+tmp.b;
        if(l!=tmp.l)return l<tmp.l;
        if(r!=tmp.r)return r<tmp.r;
        return k<tmp.k;
    }
};
bool operator<(pair<LineSegment,int> x,pair<LineSegment,int> y){
    Frac xt=x.second?x.first.l:x.first.r,
         yt=y.second?y.first.l:y.first.r;
    if(xt==yt)return x.second>y.second;
    else return xt<yt;
}
vector<LineSegment> lines[200001];

Frac calc(LineSegment x,LineSegment y){
    if(x.k==y.k&&x.b==y.b)return max(x.l,y.l);
    if(x.k==y.k)return Frac(1e14);
    Frac res=(x.b-y.b)/(y.k-x.k);
    if(max(x.l,y.l)<=res&&res<=min(x.r,y.r))return res;
    else return Frac(1e14);
}

void solve(vector<LineSegment> r){
    multiset<LineSegment> S;
    vector<pair<LineSegment,int> > Q;
    for(LineSegment i :r)
        Q.push_back({i,1}),Q.push_back({i,0});
    sort(Q.begin(),Q.end());
    for(pair<LineSegment,int> i :Q){
        now=i.second?i.first.l:i.first.r;
        if(now>=answer)break;
        if(i.second){
            auto tmp=S.insert(i.first),tmp1=tmp,tmp2=tmp;
            if(tmp1!=S.begin())answer=min(answer,calc(*--tmp1,*tmp));
            if(++tmp2!=S.end())answer=min(answer,calc(*tmp,*tmp2));
        }
        else{
            auto tmp=S.lower_bound(i.first),tmp1=tmp,tmp2=tmp;
            if(tmp1!=S.begin()&&++tmp2!=S.end())
                answer=min(answer,calc(*--tmp1,*tmp2));
            S.erase(tmp);
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    init(1); decomposition(1,1);

    for(int i=1;i<=m;i++){
        int x,y; Frac v,s,e;
        scanf("%lld%lld%d%d",&s.x,&v.x,&x,&y);
        e=Frac(dep[x]+dep[y]-dep[getlca(x,y)]*2)/v+s;
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]]){
                int from=y,to=fa[top[y]];
                lines[top[y]].push_back({v,Frac(dep[from])-v*e,
                    e-Frac(dep[from]-dep[to])/v,e});
                e=e-Frac(dep[from]-dep[to])/v;
                y=fa[top[y]];
            }
            else{
                int from=x,to=fa[top[x]];
                lines[top[x]].push_back({Frac(0)-v,Frac(dep[from])+v*s,
                    s,s+Frac(dep[from]-dep[to])/v});
                s=s+Frac(dep[from]-dep[to])/v;
                x=fa[top[x]];
            }
        }
        if(dep[x]>dep[y])lines[top[x]].push_back({Frac(0)-v,Frac(dep[x])+v*s,s,e});
        else lines[top[x]].push_back({v,Frac(dep[y])-v*e,s,e});
    }
    for(int i=1;i<=n;i++)solve(lines[i]);
    if(answer==Frac(1e14))return printf("-1\n"),0;
    printf("%.10Lf\n",(long double)answer.x/answer.y);
    return 0;
}