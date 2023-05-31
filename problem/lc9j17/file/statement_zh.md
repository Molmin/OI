## 题目描述

给定整数 $n$ 和质数 $M$。  
对于一个 $1\sim 3n$ 的排列 $p$，你可以进行下列操作：

- 将 $p$ 的前 $2n$ 个元素从小到大排序。
- 将 $p$ 的后 $2n$ 个元素从小到大排序。

可以证明任意 $1\sim 3n$ 的排列都能通过若干次上述操作从小到大排序。  
记 $f(p)$ 表示将 $p$ 从小到大排序所需的最小总操作次数。  
你需要求出对于所有 $1\sim 3n$ 的排列 $p$，其 $f(p)$ 总和对 $M$ 取模后的值。

## 输入格式

输入一行两个整数 $n,M$（$1\leq n\leq 10^6$，$10^8\leq M\leq 10^9$），保证 $M$ 是质数。  

## 输出格式

输出一行一个整数表示 $f(p)$ 的总和对 $M$ 取模后的值。

```input1
1 100009067
```

```output1
9
```

```input2
2 100000357
```

```output2
1689
```

```input3
69 999900997
```

```output3
193862705
```

## 提示

In the first test case, all the permutations are:

- $[1, 2, 3]$, which requires $0$ operations;
- $[1, 3, 2]$, which requires $1$ operation;
- $[2, 1, 3]$, which requires $1$ operation;
- $[2, 3, 1]$, which requires $2$ operations;
- $[3, 1, 2]$, which requires $2$ operations;
- $[3, 2, 1]$, which requires $3$ operations.

Therefore, the answer is $0+1+1+2+2+3=9$.