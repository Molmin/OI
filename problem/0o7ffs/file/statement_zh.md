$n$ 朵花，按顺序排成一排。从 $m$ 种颜色中选出 $k$ 种颜色，给这 $n$ 朵花染色，要求相邻的花颜色不同。问共有多少种染色方案？答案对 $10^9 + 7$ 取模。

$1\leq n,m\leq 10^9$，$1\leq k\leq 10^6$，$k\leq n,m$。

## Description

Recently, Mr. Big recieved $n$ flowers from his fans. He wants to recolor those flowers with $m$ colors. The flowers are put in a line. It is not allowed to color any adjacent flowers with the same color. Flowers $i$ and $i + 1$ are said to be adjacent for every $i$, $1\leq i < n$. Mr. Big also wants the total number of different colors of the $n$ flowers being exactly $k$.

Two ways are considered different if and only if there is at least one flower being colored
with different colors.

## Input

The first line of the input gives the number of test cases, $T$. $T$ test cases follow. $T$ is about $300$ and in most cases $k$ is relatively small.

For each test case, there will be one line, which contains three integers $n, m, k$ ($1 \leq n, m \leq 10^9$, $1 \leq k \leq 10^6$, $k \leq n, m$).

## Output

For each test case, output one line containing `Case #x: y`, where $x$ is the test case number (starting from $1$) and $y$ is the number of ways of different coloring methods modulo $10^9 + 7$.

```input1
2
3 2 2
3 2 1
```

```output1
Case #1: 2
Case #2: 0
```