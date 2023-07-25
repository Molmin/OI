## 题目描述

给出一个长度为 $n$ 的数列 $\{ a_i \}$ 和一个长度为 $m$ 的数列 $\{ b_i \}$，求 $\{ a_i \}$ 有多少个长度为 $m$ 的连续子数列能与 $\{ b_i \}$ 匹配。

两个数列可以匹配，当且仅当存在一种方案，使两个数列中的数可以两两配对，两个数可以配对当且仅当它们的和不小于 $h$。

## 输入格式

第一行三个数字 $n, m, h$。

第二行有 $m$ 个数字 $b_1, b_2, \ldots , b_m$。

第三行有 $n$ 个数字 $a_1, a_2, \ldots, a_n$。

## 输出格式

输出一个数字，$\{ a_i \}$ 有多少个长度为 $m$ 的连续子数列能与 $\{ b_i \}$ 匹配。

```input1
5 2 10
5 3
1 8 5 5 7
```

```output1
2
```

```input2
2 2 6
2 3
3 4
```

```output2
1
```

```input3
4 2 10
5 5
9 3 8 9
```

```output3
1
```

## 数据范围与提示

对于 $10\%$ 的数据，$1 \leq m \leq n \leq 10$；

对于 $40\%$ 的数据，$1 \leq m \leq n \leq 1000$；

对于 $100\%$ 的数据，$1 \leq m \leq n \leq 150000$；

对于 $100\%$ 的数据，$1 \leq a_i, b_i, h \leq 10 ^ 9$。