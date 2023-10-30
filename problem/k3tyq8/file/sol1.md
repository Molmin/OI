首先记 $c_i=h-a_i$，则 $a_i$ 与 $b_j$ 能匹配等价于 $c_i \leq b_j$。考虑建图，$a_i$ 对应结点 $1\sim n$，$b_i$ 对应结点 $n+1\sim n+m$，若 $a_i$ 与 $b_j$ 能匹配就将它们连边。

考虑将 $b$ 和 $c$ 都从小到大排序，那么此时问题转化为考虑 $b_i$ 与 $c_j$ 的匹配。注意到 $b$ 和 $c$ 有序，所以 $b$ 连边的结点是 $c$ 的一个前缀。那么考虑转化这个问题：对于 $b_{i+1}$ 连向结点 $c_j$，若 $b_i$ 也连向 $c_j$，就忽略这条边，而是从 $b_{i+1}$ 向 $b_i$ 连一条边。容易发现此时整个图是一棵树。