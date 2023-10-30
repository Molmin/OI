为了在下一次天下第一舞斗会中一雪前耻，小 E 正在练习一段高难度舞蹈。

一段舞蹈可以视为为一个长度为 $n\geq 3$ 的动作序列 $a$，第 $i$ 个动作的难度为整数 $a_i$，且有 $1\leq a_i\leq n$。小 E 会用 $n−2$ 天练习这段舞蹈，第 $i$ 天练习动作 $i\sim i+2$ 之间的衔接。

小 E 定义第 $i$ 天的 **疲劳度** 为 $w_{\max(a_i,a_{i+1},a_{i+2})}$，其中 $w$ 为一个给定的序列。整支舞蹈的 **练习代价** 为每天疲劳度的乘积。由于最终的舞蹈动作还未确定，无聊的小 E 想先算出，对于所有本质不同的序列 $a$ 对应的舞蹈 **练习代价** 的和对 $998244353$ 取模的值。

## 输入格式

第一行输入一个整数 $n$。

第二行输入 $n$ 个整数 $w_i$。

## 输出格式

一行，一个数，表示答案对 $998244353$ 取模的结果。

```input1
3
1 2 3
```

```output1
72
```

## 样例 1 解释

有 $1$ 个序列满足 $\max(a_1,a_2,a_3)=1$，$7$ 个序列满足 $\max(a_1,a_2,a_3)=2$，$19$ 个序列满足 $\max(a_1,a_2,a_3)=3$，答案为 $w_1+7w_2+19w_3=72$。

```input2
6
1 2 3 4 5 6
```

```output2
6971872
```

## 样例 3

见选手目录下的 [`sequence/sequence3.in`](file://sequence3.in) 和 [`sequence/sequence3.ans`](file://sequence3.ans)。

该样例数据范围满足测试点 $5$。

## 数据范围

本题共 $10$ 个测试点，全部测试点满足 $3\leq n\leq 4\times 10^3$，$0\leq a_i < 998244353$。

| 测试点 | $n\leq$ | 特殊性质 |
| :---: | :-----: | :-----: |
| $1\sim 2$ | $6$ | 无 |
| $3\sim 4$ | $18$ | 无 |
| $5$ | $100$ | 无 |
| $6$ | $500$ | 无 |
| $7$ | $4\times 10^3$ | $w_i=1$ |
| $8$ | $4\times 10^3$ | $\sum[w_i>0]\leq 40$ |
| $9$ | $2\times 10^3$ | 无 |
| $10$ | $4\times 10^3$ | 无 |