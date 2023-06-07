## 题目描述

给定 $n, m$ ，和一个数列 $a$，问你有多少种方案构造一个长度为 $n$ 的序列 $b$，满足下的条件：

1. $\forall i,b_i\in[1,m]$;
2. $\displaystyle \forall i,\gcd_{j=1}^i b_i=a_i$.

You are given two integers $n$ and $m$ and an array $a$ of $n$ integers. For each $1 \le i \le n$ it holds that $1 \le a_i \le m$ .

Your task is to count the number of different arrays $b$ of length $n$ such that:

- $1 \le b_i \le m$ for each $1 \le i \le n$ , and
- $\gcd(b_1,b_2,b_3,\cdots,b_i) = a_i$ for each $1 \le i \le n$ .

Here $\gcd(a_1,a_2,\cdots,a_i)$ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $a_1,a_2,\ldots,a_i$ .

Since this number can be too large, print it modulo $998\,244\,353$ .

## 输入格式

Each test consist of multiple test cases. The first line contains a single integer $t$ ($1 \le t \le 100$) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $n$ and $m$ ($1 \le n \le 2 \cdot 10^5$, $1 \le m \le 10^9$) — the length of the array $a$ and the maximum possible value of the element.

The second line of each test case contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le m$) — the elements of the array $a$ .

It is guaranteed that the sum of $n$ across all test cases doesn't exceed $2 \cdot 10^5$ .

## 输出格式

For each test case, print a single integer — the number of different arrays satisfying the conditions above. Since this number can be large, print it modulo $998\,244\,353$ .

## 样例输入输出

```input1
5
3 5
4 2 1
2 1
1 1
5 50
2 3 5 2 3
4 1000000000
60 30 1 1
2 1000000000
1000000000 2
```

```output1
3
1
0
595458194
200000000
```

## 提示

In the first test case, the possible arrays $b$ are:

- $[4,2,1]$;
- $[4,2,3]$;
- $[4,2,5]$.

In the second test case, the only array satisfying the demands is $[1,1]$ .

In the third test case, it can be proven no such array exists.