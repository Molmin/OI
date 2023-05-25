考虑计算每条边对答案的贡献。

但如果直接建网格图，是没法直接 dp 的，难以解决，所以考虑转化为树上问题。

因为只有横边和竖边两种，并且统计方式类似，所以考虑将他们分开计数。

对于竖边，每一行的连续块对竖直距离的贡献是一样的，所以可以所成一点，大小为其包含的个数。

类似的建图后，我们发现形成了一棵树，至于为什么，可以考虑按行分割，行之间的点是没有连边的，并且有竖直的边当且仅当这一列两行间是连通的，若存在环一定会有白色被包围的现象。

接下来直接树形 dp，记录子树大小，对于每条边计算贡献即可。

复杂度为 $\Theta(n)$。