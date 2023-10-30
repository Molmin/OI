## 题目描述

充满快乐的，Hyunuk 将要举办一个关于将来的一年有多伟大的大会！

大会有 $n$ 个讲座。Hyunuk 有两个可供选择的会场 A 和 B。对于 $n$ 个讲座中的每一个，演讲者选择了两个时间区间 $[sa_{i},ea_{i}]$（$sa_{i} \leq ea_{i}$）和 $[sb_{i},eb_{i}]$（$sb_{i} \leq eb_{i}$）。如果大会在 A 会场举办，那么讲座就会在 $sa_{i}$ 到 $ea_{i}$ 的时间举行；如果大会在 B 会场举行，那么该讲座就会在 $sb_{i}$ 到 $eb_{i}$ 的时间举行。Hyunuk 只能选定两个会场中的一个，然后所有讲座都要在那个会场举行。

两个讲座被称为冲突，当且仅当它们共用了同一个时间点。正式地，我们称一个在区间 $[x,y]$ 中举办的讲座和一个在 $[u,v]$ 区间举办的讲座冲突，当且仅当 $\max(x,u) \leq \min(y,v)$。

我们称一个听众可以参加所有讲座的一个子集 $s$，当且仅当这个子集中任何一对讲座都不冲突。注意：是否能参加这个子集 $s$ 的可能取决于 Hyunuk 选择的是 A 会场或是 B 会场来举办大会。

对于一个子集 $s$，若在一个会场，观众可以参加，而在另一个会场，观众却不可以参加，那么它被称为“会场敏感的”。

对于观众来说，是否存在一个会场敏感的子集 $s$ 是一个重要的问题，因为观众无法确定讲座时间是否会冲突。Hyunuk 会开心当且仅当不存在任意一个会场敏感的子集。请判断 Hyunuk 是否会开心。

## 输入格式

第一行包含一个整数 $n$，表示讲座的数目；

接下来的 $n$ 行，每行四个整数 $sa_{i},\ ea_{i},\ sb_{i},\ eb_{i}$（$1 \leq sa_{i},\ ea_{i},\ sb_{i},\ eb_{i} \leq 10^9$，$sa_{i} \leq ea_{i}$，$sb_{i} \leq eb_{i}$）。

## 输出格式

当 Hyunuk 开心时，输出 `YES`，否则输出 `NO`。

```input1
2
1 2 3 6
3 4 7 8
```

```output1
YES
```

```input2
3
1 3 2 4
4 5 6 7
3 4 5 5
```

```output2
NO
```

```input3
6
1 5 2 9
2 4 5 8
3 6 7 11
7 10 12 16
8 11 13 17
9 12 14 18
```

```output3
YES
```