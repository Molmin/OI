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