考虑离线处理这些询问。

将 $R$ 指针扫描 $1$ 到 $n$，对每个 $L$ 维护区间 $[L,R]$ 的权值。

考虑 $R$ 指针从 $x-1$ 移动到 $x$ 产生的影响。

记 $l_i$ 和 $r_i$ 分别表示 $i$ 在数列中第一次出现的位置和最后一次出现的位置，容易发现它只影响了满足 $r_i=R$ 的 $i$ 对权值的贡献。即所有区间 $[L,R=x]$ 都需要与 $i$ 取 $\max$。

注意到区间总是单调不升的，所以操作转化为区间修改操作。

而所有子区间和可以转化为历史版本和，使用线段树维护 $3\times 3$ 矩阵做。