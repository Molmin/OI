易知 $\text{LCA}(i,\ z)$ 一定在根节点到 $z$ 的路径上，而它的深度等价于它到根节点路径上的结点个数。

只需将结点 $i$ 到根结点的路径上的结点都 $+1$，然后结点 $z$ 到根结点的路径上数值总和就是最近公共祖先的深度。

这样，我们就只需要将 $l,\ l+1,\ \cdots,\ r$ 这些点到根结点的路径上结点全部 $+1$，再统计 $z$ 到根结点路径上结点的数值总和即可。

考虑优化。首先有个显然的优化，$[l,\ r]$ 的问题可以转化为 $[1,\ r]$ 和 $[1,\ l-1]$ 的问题。此时问题转化为求若干个左端点为 $1$ 的问题。

不妨将这些问题的右端点排序，依次将 $1,\ 2,\ \cdots$ 到根结点路径上的点 $+1$，若遇到询问就查询答案即可。

时间复杂度 $\Theta(n\log^2n)$。