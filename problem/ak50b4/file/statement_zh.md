## 题目描述

多次给定三个 $n\times n$ 的矩阵 $A,\ B,\ C$，你需要判断 $A\times B$ 在模 $998244353$ 意义下是否等于 $C$。其中 $\times$ 为矩阵乘法，$C_{i,\ j}=\sum\limits_{k=1}^nA_{i,\ k}B_{k,\ j}$。

本题读入量较大，建议使用快速读入。

## 输入格式

从文件 `matrix.in` 中读入数据。

第 $1$ 行输入一个正整数 $T$，表示数据组数。

接下来包含 $T$ 组数据，每组数据第一行为一个正整数 $n$，表示矩阵大小。

接下来 $n$ 行，每行 $n$ 个整数，表示矩阵 $A$。

接下来 $n$ 行，每行 $n$ 个整数，表示矩阵 $B$。

接下来 $n$ 行，每行 $n$ 个整数，表示矩阵 $C$。

## 输出格式

输出到文件 `matrix.out` 中。

输出 $T$ 行 `Yes` 或 `No`，表示 $A\times B$ 在模 $998244353$ 意义下是否等于 $C$。

## 样例 1 输入

```input1
3
1
2
3
6
2
1 2
3 4
5 6
7 8
19 22
43 51
2
1111111 2222222
3333333 4444444
5555555 6666666
7777777 8888888
39625305 256038638
772687616 944903942
```

```output1
Yes
No
Yes
```

## 数据范围

对于 $20\%$ 的数据，满足 $\sum n\leq 300$。

对于另外 $20\%$ 的数据，满足 $A_{i,\ j}\not=0$ 的位置不超过 $n$ 个。

对于 $100\%$ 的数据，满足 $1\leq T,\ n\leq 3000$，$\sum n\leq 3000$，$0\leq A_{i,\ j},\ B_{i,\ j},\ C_{i,\ j} < 998244353$。