// 2023.05.06

#include<bits/stdc++.h>
using namespace std;

int n,q,ans[60001];

struct Node{
    int x1,y1,x2,y2,k,qid;
}Q[310001],QL[310001],QR[310001];
int Qcnt;

int t[1001][1001];
int lowbit(int x){
    return x&-x;
}
void addvalue(int x,int y,int val){
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=n;j+=lowbit(j))
            t[i][j]+=val;
}
int getprefixsum(int x,int y){
    int sum=0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            sum+=t[i][j];
    return sum;
}
int getsum(int x1,int y1,int x2,int y2){
    return getprefixsum(x2,y2)-getprefixsum(x1-1,y2)+getprefixsum(x1-1,y1-1)-getprefixsum(x2,y1-1);
}

void binarySearch(int Ql,int Qr,int l,int r){
    if(Qr-Ql<0)return;
    if(r-l==0){
        for(int i=Ql;i<=Qr;i++)
            if(Q[i].qid)ans[Q[i].qid]=l;
        return;
    }
    int mid=(l+r)>>1,QLcnt=0,QRcnt=0;
    for(int i=Ql;i<=Qr;i++){
        if(Q[i].qid){
            int sum=getsum(Q[i].x1,Q[i].y1,Q[i].x2,Q[i].y2);
            if(sum>=Q[i].k)  QL[++QLcnt]=Q[i];
            else Q[i].k-=sum,QR[++QRcnt]=Q[i];
        }
        else{
            if(Q[i].k>mid){
                QR[++QRcnt]=Q[i];
                continue;
            }
            addvalue(Q[i].x1,Q[i].y1,1);
            QL[++QLcnt]=Q[i];
        }
    }

    int Qid=Ql;
    for(int i=1;i<=QLcnt;i++)
        Q[Qid++]=QL[i];
    for(int i=1;i<=QRcnt;i++)
        Q[Qid++]=QR[i];
    for(int i=Ql;i<=Ql-1+QLcnt;i++)
        if(!Q[i].qid&&Q[i].k<=mid)
            addvalue(Q[i].x1,Q[i].y1,-1);
    binarySearch(Ql,Ql+QLcnt-1,l,mid);
    binarySearch(Ql+QLcnt,Qr,mid+1,r);
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            int x; scanf("%d",&x);
            Q[++Qcnt]={i,j,0,0,x,0};
        }
    for(int i=1;i<=q;i++){
        int x1,y1,x2,y2,k;
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);
        Q[++Qcnt]={x1,y1,x2,y2,k,i};
    }
    binarySearch(1,Qcnt,0,1e9);
    for(int i=1;i<=q;i++)
        printf("%d\n",ans[i]);
    return 0;
}