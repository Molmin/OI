考虑动态规划：记 $f(l,r)$ 表示该块内从 $l$ 走到 $r$ 的最短路径长度。

实现函数

```cpp
void solve(int xl,int xr,int yl,int yr,bool sortX);
```

完成 $x$ 坐标在 $[xl,xr]$ 范围内且 $y$ 坐标在 $[yl,yr]$ 范围内的最短路计算。

时间复杂度 $\Theta(n^4)$，但是严重跑不满，可过。