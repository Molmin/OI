// 2023.05.24

#include<bits/stdc++.h>
using namespace std;

int n,c,q,x[500001];

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

bool flipped; int rotated;
void convert(int &x){
    if(flipped)x=rotated+2-x;
    else x-=rotated;
    x=(x+n+n-1)%n+1;
}

int main(){
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
        scanf("%d",x+i);
    SegmentTree::build(1,1,n);
    scanf("%d",&q);
    while(q--){
        string op; cin>>op;
        if(op=="R"){
            // 顺时针旋转 k 位
            int k; scanf("%d",&k);
            rotated=(rotated+k)%n;
        }
        if(op=="F"){
            // 沿给定对称轴翻转
            flipped=!flipped,
            rotated=(n-rotated)%n;
        }
        if(op=="S"){
            // 交换两个珠子
            int i,j;
            scanf("%d%d",&i,&j);
            convert(i),convert(j);
            int color1=SegmentTree::query(1,1,n,i,i).left;
            int color2=SegmentTree::query(1,1,n,j,j).left;
            if(color1!=color2)
                SegmentTree::update(1,1,n,i,i,color2),
                SegmentTree::update(1,1,n,j,j,color1);
        }
        if(op=="P"){
            // 将 i 顺时针方向到 j 的一段染为 x
            int i,j,x;
            scanf("%d%d%d",&i,&j,&x);
            convert(i),convert(j);
            if(flipped)swap(i,j);
            if(i<=j)SegmentTree::update(1,1,n,i,j,x);
            else
                SegmentTree::update(1,1,n,i,n,x),
                SegmentTree::update(1,1,n,1,j,x);
        }
        if(op=="C"){
            // 查询当前项链有多少个部分组成
            printf("%d\n",max(SegmentTree::a[1].cnt-
                (SegmentTree::a[1].left==SegmentTree::a[1].right),1));
        }
        if(op=="CS"){
            // 查询从 i 顺时针方向到 j 有多少个部分组成
            int i,j;
            scanf("%d%d",&i,&j);
            convert(i),convert(j);
            if(flipped)swap(i,j);
            int res=0;
            if(i<=j)
                printf("%d\n",SegmentTree::query(1,1,n,i,j).cnt);
            else printf("%d\n",SegmentTree::query(1,1,n,i,n).cnt
                +SegmentTree::query(1,1,n,1,j).cnt
                -(SegmentTree::a[1].left==SegmentTree::a[1].right));
        }
    }
    return 0;
}