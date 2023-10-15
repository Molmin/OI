## 题目描述

Alice 和 Bob 在玩一个游戏。

有 $n$ 个石子在这里，Alice 和 Bob 轮流投掷硬币，如果正面朝上，则从 $n$ 个石子中取出一个石子，否则不做任何事。取到最后一颗石子的人胜利。Alice 在投掷硬币时有 $p$ 的概率投掷出他想投的一面，Bob 有 $q$ 的概率投掷出他相投的一面。

现在 Alice 先手投掷硬币，假设他们都想赢得游戏，问你 Alice 胜利的概率为多少。

## 输入格式

Input starts with a line containing one integer $T$ - a number of test cases ($1\leq T\leq 50$). Then $T$ test cases follow. Each of them is one line with three numbers $N$, $P$, and $Q$ separated with a space ($1\leq N\leq 99999999$, $0.5\leq P,\ Q\leq 0.99999999$). $P$ and $Q$ have not more than $8$ digits after decimal point.

## 输出格式

For each test case output one line with a probability that Alice will win the game. Your answer must be precise up to $10^{-6}$.

## 样例输入输出

```input1
1
1 0.5 0.5
```

```output1
0.666666667
```