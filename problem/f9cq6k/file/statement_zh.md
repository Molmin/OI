## 题目描述

上帝正在筹备 UOI2038，这项赛事共有 $n$ 位选手参加，选手用 $1\sim n$ 编号。上帝测试了所有选手的水平，对每位选手各给定了 $m$ 个可能的成绩，即这些选手的成绩将只能是这 $m$ 个之一。

UOI2038 的奖牌由选手的成绩从大到小排名后决定，若选手成绩相同则编号更大的选手排名更靠前。更具体地，排名前 $a$ 位的选手获得金牌，排名后 $c$ 位的选手获得铜牌，剩余的 $b=n-a-c$ 位选手获得银牌。

现在上帝要你计算 $q$ 次下列问题：给定一组 $a,\ b,\ c$，求有多少种不同的奖牌获得情况，两种奖牌获得情况不同当且仅当存在至少一位选手获得的奖牌在两种情况中不同。你只需要给出结果模 $10^9+7$ 后的值。

## 输入格式

第一行三个整数 $n,\ m,\ q$ 表示选手数量、可能的成绩个数与询问次数。

接下来 $n$ 行每行 $m$ 个正整数 $a_{i,j}$，第 $i$ 行的数字表示 $i$ 号选手可能的成绩（$1\leq a_{i,j}\leq 10^4$。接下来 $q$ 行每行三个正整数 $a,\ b,\ c$，表示一组询问。保证 $a+b+c=n$。

## 输出格式

输出 $q$ 行，每行一个整数表示对应询问的答案。

```input1
3 2 1
1 2
3 1
1 2
1 1 1
```

```output1
5
```

## 样例 1 解释

共有 $8$ 种可能的成绩情况，下面用 $(u,\ v,\ w)$ 依次表示三人成绩，对应的奖牌分配如下：

- $(1,\ 3,\ 1)$：铜、金、银；
- $(1,\ 3,\ 2)$：铜、金、银（重复）；
- $(1,\ 1,\ 1)$：铜、银、金；
- $(1,\ 1,\ 2)$：铜、银、金（重复）；
- $(2,\ 3,\ 1)$：银、金、铜；
- $(2,\ 3,\ 2)$：铜、金、银（重复）；
- $(2,\ 1,\ 1)$：金、铜、银；
- $(2,\ 1,\ 2)$：银、铜、金；

```input2
4 3 2
2 1 4
4 4 3
1 3 3
1 3 2
1 1 2
2 1 1
```

```output2
9
10
```

## 样例 3

见下发文件 [medal3.in](file://medal3.in) 和 [medal3.ans](file://medal3.ans)。

## 数据范围

对于 $20\%$ 的数据，$n=3$，$m\leq 5$；

对于 $40\%$ 的数据，$n,\ m\leq 7$；

对于 $60\%$ 的数据，$n,\ m\leq 20$；

对于 $80\%$ 的数据，$n,\ m\leq 50$；

对于全部的数据，$3\leq n\leq 80$，$1\leq m\leq 1000$，$1\leq q\leq 10$。