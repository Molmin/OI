小 D 正在学习图论，你需要帮她完成课后习题。

小 D 今天学习了导出子图的定义：一个点集 $V'$ 的导出子图 $G'=(V',E')$，其中 $E'$ 为 $E$ 中所有两端点都在 $V'$ 中的边。

给定一张包含 $n$ 个点，$m$ 条边的简单无向图 $G=(V,E)$，以及一个指数 $k$。

你需要求出所有 $2^n$ 个集合的导出子图的边数的 $k$ 次方和对 $10^9+7$ 取模的值。

## 输入格式

第一行三个正整数 $n,m,k$。

接下来 $m$ 行，每行两个正整数 $u_i,v_i$，表示一条边。

## 输出格式

一个正整数，表示答案对 $10^9+7$ 取模的值。

```input1
4 5 2
1 2
2 3
3 4
4 1
2 4
```

```output1
56
```

## 样例 1 解释

有 $5$ 张导出子图的边数为 $1$。有 $2$ 张导出子图的边数为 $2$。有 $2$ 张导出子图的边数为 $3$。有 $1$ 张导出子图的边数为 $5$。

故答案为 $5\times 1^2+2\times 2^2+2\times 3^2+1\times 5^2=56$。

## 样例 2

见选手目录下的 [`splitham/graph2.in`](file://graph2.in) 和 [`splitham/graph2.ans`](file://graph2.ans)。

该样例数据范围满足测试点 $4$。

## 样例 3

见选手目录下的 [`splitham/graph3.in`](file://graph3.in) 和 [`splitham/graph3.ans`](file://graph3.ans)。

该样例数据范围满足测试点 $7$。

## 数据范围

本题共 $10$ 个测试点，全部测试点满足 $1\leq n,m\leq 10^5$，$1\leq k\leq 3$，$1\leq u_i,v_i\leq n$，$u_i\not=v_i$。

| 测试点 | $n\leq$ | $m\leq$ | $k=$ | 特殊性质 |
| :---: | :-----: | :-----: | :--: | :-----: |
| $1$ | $10^5$ | $10^5$ | $1$ | 无 |
| $2$ | $10^5$ | $n-1$ | $2$ | A |
| $3$ | $10^5$ | $n-1$ | $2$ | B |
| $4$ | $10^5$ | $10^5$ | $2$ | 无 |
| $5$ | $12$ | $50$ | $3$ | 无 |
| $6$ | $100$ | $10^3$ | $3$ | 无 |
| $7$ | $2048$ | $10^5$ | $3$ | 无 |
| $8$ | $10^5$ | $n-1$ | $3$ | A |
| $9$ | $10^5$ | $n-1$ | $3$ | B |
| $10$ | $10^5$ | $10^5$ | $3$ | 无 |

特殊性质 A：$u_i=i$，$v_i=i+1$。

特殊性质 B：$u_i=1$，$v_i=i+1$。