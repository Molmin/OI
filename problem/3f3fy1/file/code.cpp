// 2023.10.18

#include<bits/stdc++.h>
using namespace std;

struct Matrix{
    long long a[3][3];
    Matrix operator*(Matrix m)const{
        Matrix ret={{{0,0,0},{0,0,0},{0,0,0}}};
        for(int k=0;k<3;k++)
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++)
                    ret.a[i][j]+=a[i][k]*m.a[k][j];
        return ret;
    }
    Matrix operator+(Matrix m)const{
        Matrix ret;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                ret.a[i][j]=a[i][j]+m.a[i][j];
        return ret;
    }
    bool operator!=(Matrix m)const{
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(a[i][j]!=m.a[i][j])return true;
        return false;
    }
};

struct SegmentTree{
    struct Node{
        int l,r;
        Matrix val,tag;
    }node[12000001];
    const Matrix defaultTag={{{1,0,0},{0,1,0},{0,0,1}}};
    const Matrix defaultValue={{{0,0,0},{0,0,0},{0,0,1}}};

    void mul(int id,Matrix val){
        node[id].val=val*node[id].val;
        node[id].tag=val*node[id].tag;
    }
    void pushup(int id){
        node[id].val=node[id<<1].val+node[id<<1|1].val;
    }
    void pushdown(int id){
        if(node[id].tag!=defaultTag){
            mul(id<<1,node[id].tag);
            mul(id<<1|1,node[id].tag);
            node[id].tag=defaultTag;
        }
    }

    void build(int id,int l,int r){
        node[id].tag=defaultTag;
        node[id].l=l,node[id].r=r;
        if(l==r)node[id].val=defaultValue;
        else{
            int mid=l+r>>1;
            build(id<<1,l,mid);
            build(id<<1|1,mid+1,r);
            pushup(id);
        }
    }

    void updateMulti(int id,int l,int r,Matrix val){
        if(l<=node[id].l&&node[id].r<=r){mul(id,val);return;}
        int mid=node[id].l+node[id].r>>1;
        pushdown(id);
        if(l<=mid)updateMulti(id<<1,l,r,val);
        if(mid<r)updateMulti(id<<1|1,l,r,val);
        pushup(id);
    }
    
    Matrix query(int id,int l,int r){
        if(l<=node[id].l&&node[id].r<=r)return node[id].val;
        int mid=node[id].l+node[id].r>>1;
        Matrix ret={{{0,0,0},{0,0,0},{0,0,0}}};
        if(l<=mid)ret=ret+query(id<<1,l,r);
        if(mid<r)ret=ret+query(id<<1|1,l,r);
        return node[id].tag*ret;
    }
}_;

int n,q,a[3000001],l[3000001],r[3000001];
long long answer[3000001];

struct Query{
    int l,r,qid;
    bool operator<(Query q)const{
        return r<q.r;
    }
}Q[3000001];

set<pair<int,int> > S;

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    for(int i=n;i>=1;i--)l[a[i]]=i;
    for(int i=1;i<=n;i++)r[a[i]]=i;
    for(int i=1;i<=q;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        Q[i]={l,r,i};
    }
    sort(Q+1,Q+1+q);
    _.build(1,1,n);
    int now=0;
    for(int i=1;i<=n;i++){
        if(r[a[i]]==i){
            pair<int,int> tmp={l[a[i]],a[i]};
            Matrix setTo={{{0,0,a[i]},{0,1,0},{0,0,1}}};
            auto it=S.lower_bound(tmp);
            if(it==S.end()||a[i]>it->second){
                if(it==S.begin()){
                    S.insert(tmp);
                    _.updateMulti(1,1,tmp.first,setTo);
                }
                else{
                    it--;
                    while(it!=S.begin()&&a[i]>it->second)S.erase(it--);
                    if(a[i]>it->second){
                        S.erase(it);
                        _.updateMulti(1,1,tmp.first,setTo);
                    }
                    else _.updateMulti(1,it->first+1,tmp.first,setTo);
                    S.insert(tmp);
                }
            }
        }
        _.mul(1,{{{1,0,0},{1,1,0},{0,0,1}}});
        while(now<q&&Q[now+1].r==i){
            now++;
            answer[Q[now].qid]=_.query(1,Q[now].l,i).a[1][2];
        }
    }
    for(int i=1;i<=q;i++)printf("%lld\n",answer[i]);
    return 0;
}