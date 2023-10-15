考虑先离散化，再使用二维莫队。

### 奇偶排序优化

莫队中奇偶排序是一种常用的优化方法。

指针经常在移动到边界之后，又因为另一个指针的移动要移动很长的距离，所以可以使用奇偶排序的方法。

```cpp
struct Question{
    int x1,y1,x2,y2,k,qid;
    bool operator<(Question tmp)const{
        if(blockId[x1]!=blockId[tmp.x1])return blockId[x1]<blockId[tmp.x1];
        if(blockId[y1]!=blockId[tmp.y1])return blockId[x1]&1?y1<tmp.y1:y1>tmp.y1;
        if(blockId[y2]!=blockId[tmp.y2])return blockId[y1]&1?y2<tmp.y2:y2>tmp.y2;
        else return blockId[y2]&1?x2<tmp.x2:x2>tmp.x2;
    }
};
```