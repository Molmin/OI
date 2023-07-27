考虑树链剖分。两点之间的路径被分为 $\Theta(\log n)$ 条链的一段。每段链用线段树维护最大连续上升长度。为了合并两段区间，还需要维护左端或右端开始的最长上升长度。注意到区间可能需要翻转，所以还需要维护下降的长度。合并代码如下：

```cpp
Node pushup(Node &x,Node lson,Node rson){
    int lenl=lson.r-lson.l+1,lenr=rson.r-rson.l+1;
    x.lval=lson.lval,x.rval=rson.rval;
    x.up=max(lson.up,rson.up);
    if(lson.rval<rson.lval)x.up=max(x.up,lson.r_up+rson.l_up);
    x.l_up=lson.l_up;
    if(lson.l_up==lenl&&lson.rval<rson.lval)
        x.l_up+=rson.l_up;
    x.r_up=rson.r_up;
    if(rson.r_up==lenr&&lson.rval<rson.lval)
        x.r_up+=lson.r_up;
    x.down=max(lson.down,rson.down);
    if(lson.rval>rson.lval)
        x.down=max(x.down,lson.r_down+rson.l_down);
    x.l_down=lson.l_down;
    if(lson.l_down==lenl&&lson.rval>rson.lval)
        x.l_down+=rson.l_down;
    x.r_down=rson.r_down;
    if(rson.r_down==lenr&&lson.rval>rson.lval)
        x.r_down+=lson.r_down;
    return x;
}
```

实现细节：

1. 多组数据，数据开始时要清空。两组数据输出之间有一个空行。
2. 注意在什么时候区间需要翻转。翻转时左侧上升应该和右侧下降互换而不是右侧上升。
3. 更多细节见代码。