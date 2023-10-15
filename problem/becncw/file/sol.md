注意到数据范围 $\sum m\leq n$，所以 $\geq\sqrt n$ 的 $m$ 一定不超过 $\sqrt n$ 个。

对于 $m\geq\sqrt n$，直接枚举所有区间，这部分总复杂度为 $\Theta(n\sqrt n)$。

如果 $m<\sqrt n$，考虑枚举区间包含的 $x$ 的左右端点。例如，如何求出正好包含 $x_i,\ x_{i+1},\ \cdots,\ x_j$ 的区间数量？考虑扫描线，先对每个区间 $[l,r]$ 都将坐标 $(l,r)$ 插入，再查询横坐标在 $(x_{i-1},x_i]$ 范围内且纵坐标在 $[x_j,x_{j+1})$ 范围内的区间即可。而我们只需考虑 $j-i+1$ 是偶数的情况。这部分时间复杂度为 $\Theta((n+\sum m^2)\log n)$，注意到 $m\leq\sqrt n$，所以 $\sum m^2\leq n\sqrt n$。

时间复杂度 $\Theta(n\sqrt n\log n)$。