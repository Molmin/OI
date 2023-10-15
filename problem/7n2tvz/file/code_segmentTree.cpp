namespace SegmentTree{
    struct Node{
        int left,right,cnt; // 最左/右的颜色 / 不同颜色数量
        int tag;
    }a[1000001];
    void pushup(int id){
        int l=id<<1,r=(id<<1)+1;
        a[id].left=a[l].left,
        a[id].right=a[r].right;
        a[id].cnt=a[l].cnt+a[r].cnt;
        if(a[l].right==a[r].left)a[id].cnt--;
    }
    void pushdown(int id){
        int l=id<<1,r=(id<<1)+1;
        if(a[id].tag==0)return;
        a[l].left=a[l].right=a[l].tag=a[id].tag;
        a[r].left=a[r].right=a[r].tag=a[id].tag;
        a[l].cnt=a[r].cnt=1,a[id].tag=0;
    }

    void build(int id,int l,int r){
        if(l==r){
            a[id].left=a[id].right=x[l],a[id].cnt=1;
            return;
        }
        int mid=l+r>>1;
        build(id<<1,l,mid);
        build((id<<1)+1,mid+1,r);
        pushup(id);
    }
    Node query(int id,int l,int r,int L,int R){
        if(L<=l&&r<=R)return a[id];
        int mid=l+r>>1;
        pushdown(id);
        Node lNode={0,0,0,0},rNode={0,0,0,0};
        if(L<=mid)lNode=query(id<<1,l,mid,L,R);
        if(R>mid) rNode=query((id<<1)+1,mid+1,r,L,R);
        return {
            lNode.left==0?rNode.left:lNode.left,
            rNode.right==0?lNode.right:rNode.right,
            lNode.cnt+rNode.cnt-(lNode.right==rNode.left?1:0),
            0
        };
    }
    void update(int id,int l,int r,int L,int R,int color){
        if(L<=l&&r<=R){
            a[id].left=a[id].right=a[id].tag=color,a[id].cnt=1;
            return;
        }
        int mid=l+r>>1;
        pushdown(id);
        if(L<=mid)update(id<<1,l,mid,L,R,color);
        if(R>mid) update((id<<1)+1,mid+1,r,L,R,color);
        pushup(id);
    }
}