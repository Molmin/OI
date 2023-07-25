// 2023.07.22

#include<bits/stdc++.h>
using namespace std;

struct Frac{
    int x,y;
    bool operator<(Frac tmp)const{
        return 1ll*x*tmp.y<1ll*tmp.x*y;
    }
    bool operator==(Frac tmp)const{
        return 1ll*x*tmp.y==1ll*tmp.x*y;
    }
};
Frac makeFrac(int x,int y){
    return {x/__gcd(x,y),y/__gcd(x,y)};
}

int n,l;
struct Car{
    int p,v,a;
    bool operator<(Car tmp)const{
        return p<tmp.p;
    }
}a[200001];

struct BOMB{
    Frac time;
    int u,v;
    bool operator<(BOMB tmp)const{
        if(time==tmp.time)return u<tmp.u;
        else return time<tmp.time;
    }
};

set<BOMB> S;

namespace System{
    Frac calcTime(int x,int y){
        if(x>y)swap(x,y);
        if((a[x].v>0&&a[y].v>0)||(a[x].v<0&&a[y].v<0)){
            if(a[x].v>a[y].v)return makeFrac(a[y].p-a[x].p,a[x].v-a[y].v);
            else return makeFrac(l+a[x].p-a[y].p,a[y].v-a[x].v);
        }
        else{
            if(a[x].v>0)return makeFrac(a[y].p-a[x].p,a[x].v-a[y].v);
            else return makeFrac(l+a[x].p-a[y].p,a[y].v-a[x].v);
        }
    }
}

void updateRemove(int x,int y){
    if(x>y)swap(x,y);
    S.erase({System::calcTime(x,y),x,y});
}
void updateInsert(int x,int y){
    if(x>y)swap(x,y);
    S.insert({System::calcTime(x,y),x,y});
}

int nxt[200001],pre[200001];

int main(){
    scanf("%d%d",&n,&l);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].p);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].v);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].a);
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)
        nxt[i]=i+1,pre[i]=i-1;
    pre[1]=n,nxt[n]=1;
    for(int i=1;i<=n;i++)
        updateInsert(i,nxt[i]);
    for(int i=1;i<=n-2;i++){
        int u=(*S.begin()).u,v=(*S.begin()).v;
        int loser=a[u].a<a[v].a?u:v;
        updateRemove(loser,pre[loser]);
        updateRemove(loser,nxt[loser]);
        updateInsert(pre[loser],nxt[loser]);
        nxt[pre[loser]]=nxt[loser],
        pre[nxt[loser]]=pre[loser];
    }
    printf("%d/%d\n",(*S.begin()).time.x,(*S.begin()).time.y);
    return 0;
}