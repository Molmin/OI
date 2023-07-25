## 题目描述

上帝先创造了一个长为 $L$ 米的环形单车道赛道，并设定了一个起点。

上帝接着创造了 $n$ 辆赛车，它们从 $1\sim n$ 编号。$i$ 号赛车初始时被上帝放在距起点顺时针方向 $p$ 米的位置，它的速度被上帝设置为每时刻匀速前进 $|v_i|$ 米，当 $v > 0$ 时它的前进方向为顺时针方向，否则为逆时针方向。

最后，上帝为每辆赛车再设定了战斗力 $a$，并制定了游戏规则：当上帝宣布游戏开始后，所有赛车将会按照自己的速度与方向前进，当多辆赛车在同一时间点出现在赛道的同一位置时（即相撞或超车时），只有战斗力最高的那辆赛车能继续游戏，其他赛车将被淘汰并移出赛道。当赛道中只剩一辆赛车时游戏将会结束。

现在上帝要你计算，游戏从开始到结束共进行了多少个时刻。

## 输入格式

第一行两个整数 $n,\ L$，表示赛车数量与赛道长度。

第二行 $n$ 个互不相同的整数 $p_i$，表示赛车的初始位置（$0\leq p_i < L$）。

第三行 $n$ 个互不相同的整数 $t_i$，表示赛车的速度（$1\leq |v_i| < L$）。

第四行 $n$ 个互不相同的整数 $a_i$，表示赛车的战斗力（$0\leq a < L$）。

## 输出格式

仅一行，将答案以 `x/y` 的最简分数形式输出。

```input1
3 10
1 5 6
-7 3 7
7 9 8
```

```output1
9/4
```

```input2
7 20
8 4 0 14 1 13 2
19 -11 16 -16 -5 18 -13
15 18 11 14 13 10 5
```

```output2
8/15
```

## 样例 3

见下发文件 [game3.in](file://game3.in) 和 [game3.ans](file://game3.ans)。

## 数据范围

对于 $20\%$ 的数据，$n=2$；

对于 $40\%$ 的数据，$n\leq 3$；

对于 $70\%$ 的数据，$n\leq 2000$；

对于 $100\%$ 的数据，$2\leq n\leq 2\times 10^5$，$n\leq L \leq 10^9$。