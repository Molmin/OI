Kaguya 是一个喜欢秩序的女孩子，她常常收到很多序列作为礼物，有时她希望对某些序列进行排序。

今天，Ayu 又送了 Kaguya 一个排列 $a_{1\ldots n}$。Kaguya 希望按照如下伪代码对其进行排序：

```py
function sort(a[1...len(a)]):
  if len(a) <= 1 then return a
  let pivot = a[ceil(len(a) / 2)]
  let al, ag = empty sequence
  for i in 1...len(a) do
    let cmpcnt = cmpcnt + 1
    if a[i] < pivot then append a[i] to al
    if a[1] > pivot then append a[i] to ag
  return sort(al) + [pivot] + sort(ag)
```

Kaguya 比较关心排序需要的比较次数，所以希望你求出：用该函数对 $a_{1\ldots n}$ 进行一次排序后，`cmpcnt` 会增加多少。

## 输入格式

输入的第一行包含一个整数 $n$，表示要排序的排列长度。输入的第二行包含 $n$ 个整数 $a$，表示要排序的排列。

## 输出格式

输出一行包含一个整数，表示一次排序后 `cmpcnt` 的变化量。

```input1
5
4 3 5 1 2
```

```output1
11
```

## 样例 1 解释

作为函数参数的非空序列共 $[4,3,5,1,2]$、$[4,3,1,2]、$[4]$、$[1,2]$、$[2]$ 五个。

## 样例 2

见选手目录下的 [`sort/sort2.in`](file://sort2.in) 和 [`sort/sort2.ans`](file://sort2.ans)。

## 样例 3

见选手目录下的 [`sort/sort3.in`](file://sort3.in) 和 [`sort/sort3.ans`](file://sort3.ans)。

## 样例 4

见选手目录下的 [`sort/sort4.in`](file://sort4.in) 和 [`sort/sort4.ans`](file://sort4.ans)。

## 样例 5

见选手目录下的 [`sort/sort5.in`](file://sort5.in) 和 [`sort/sort5.ans`](file://sort5.ans)。

对于所有测试数据保证：$1\leq n\leq 7\times 10^5$，$1\leq a_i\leq n$，$\forall i\not=j$，$a_i\not=a_j$。

每个测试点的具体限制见下表：

| 测试点 | $n\leq$ | 特殊性质 |
| :---: | :-----: | :-----: |
| $1$ | $3\times 10^3$ | 无 |
| $2$ | $2\times 10^5$ | $a_{1\ldots n}$ 随机生成 |
| $3$ | $2\times 10^5$ | $a_i=i$ |
| $4$ | $2\times 10^5$ | $\sum_i[a_i\not=i]\leq 10$ |
| $5$ | $2\times 10^5$ | $\lvert a_i-i\rvert\leq 10$ |
| $6\sim 8$ | $10^5$ | 无 |
| $9\sim 10$ | $7\times 10^5$ | 无 |