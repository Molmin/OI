从数据范围容易猜到本题应该用状压 dp。

记 $dp_{i,j}$ 表示已经到了第 $i$ 次抛出宝物，已经吃过的宝物的集合为 $j$。易知

$$
dp_{i,j}=\frac 1n\cdot\sum_{k=1}^n\begin{cases} 
\max\{dp[i + 1][j],dp[i + 1][j|1<<(k-1)]+p_k\},  & \text{if can get item }k \\
dp[i + 1][j], & \text{if cannot get item }k 
\end{cases}.
$$