**请注意本题特殊的时间限制。**

给定 $n$ 个 $\{1,\ 2,\ \cdots,\ m\}$ 的子集 $S_1,\ S_2,\ \cdots,\ S_n$。有一个初始为空的集合 $T$。

进行 $Q$ 次操作，每次给定 $z$，把 $T$ 更新为 $T\oplus S_z$，其中 $\oplus$ 是对称差，也可以理解为异或，即仅保留恰好在一个集合的元素。

每次操作之后输出 $|T|$。

因为这个问题太过困难，所以允许一定误差：我们会计算你的输出与标准答案的相对误差，再把所有相对误差求几何平均值，当你的平均相对误差不超过 $1.2$ 时可以获得满分。

## 输入格式

第一行三个正整数 $n,\ m,\ Q$。

接下来 $n$ 行，每行描述一个集合 $S_i$。每一行首先是一个正整数 $k$，然后是 $k$ 个整数 $x_1,\ x_2,\ \cdots,\ x_k$（保证 $x_j < i$），表示 $S_i=S_{x_1}\oplus S_{x_2}\oplus\cdots\oplus S_{x_k}$。特别地，设 $S_{−1},S_{-2},\cdots,S_{−m}$ 分别只包含 $1,\ 2,\ \cdots,\ m$。

接下来 $Q$ 行，每行一个正整数 $z$。

## 输出格式

对每次操作输出一行一个正整数，表示答案。

```input1
5 10 10
2 -1 -10
1 -2
2 -3 -6
2 -4 -8
3 -5 -7 -9
1
5
2
4
3
3
2
3
3
2
```

```output1
2
5
6
8
10
8
7
9
7
8
```

## 样例 2

见选手目录下的 [`approx/approx2.in`](file://approx2.in) 和 [`approx/approx2.ans`](file://approx2.ans)。

## 样例 3

见选手目录下的 [`approx/approx3.in`](file://approx3.in) 和 [`approx/approx3.ans`](file://approx3.ans)。

保证样例的输出均为标准答案。

## 数据范围与评测方式

测试数据中有 $30$ 分保证 $m,\ Q\leq 2 \times 10^5$，$\sum k_i \leq 6 \times 10^5$。

对于所有测试数据，保证 $n\leq 10^5$，$m,\ Q\leq 10^6$，$\sum k_i\leq 10^6$，描述集合时非负的 $x_i$ 一共不超过 $2m$ 个。

保证答案基本在对数坐标上均匀分布，保证 $T$ 不会太多次成为某个特定集合。

定义两个数 $x,\ y$ 的相对误差为 $\dfrac{\max(x,\ y)}{\min(x,\ y)}$。特别地，两个数均为 $0$ 时的相对误差为 $1$，而恰有一个数为 $0$ 时的相对误差为 $\infty$。

设你的平均相对误差为 $w$。如果 $w=\infty$，你将获得零分；否则你的分数是

$$
\max(0.3,\ \min(1,\ \dfrac{1}{5(w-1)}))\times 100\%.
$$