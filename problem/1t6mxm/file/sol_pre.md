容易想到记 $f(i,j,k)$ 表示 $a[i-1]=k$ 且 $a[i-2]=j$ 时的方案总数。

转移时间复杂度 $\Theta(n)$，总时间复杂度 $\Theta(n^4)$。

前缀和优化后可以做到 $\Theta(n^3)$。