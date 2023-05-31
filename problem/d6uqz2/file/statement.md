给定 $2n$ 个点的树，要求两两匹配。两个点能匹配当且仅当两点之间没有连边，问有多少种匹配方案。

$n\leq 2000$

AAA gets a complete graph of $2n$ vertices, where every pair of distinct vertices is connected by a unique edge, as a birthday present. However, AAA thinks the complete graph is not that beautiful and he decides to delete $2n-1$ edges that form a tree.

Now he wonders the number of different perfect matchings in the remaining graph. Note that a perfect matching is a set of $n$ edges where no two edges share a common vertex. Since the answer may be very large, you only need to output the answer modulo $998\,244\,353$.

## Input

The first line contains a single integer $n$ $(2\le n\le 2\,000)$.

Each of the next $2n-1$ lines contains two integers $u$ and $v$ $(1\le u,v\le 2n)$, representing an edge deleted from the complete graph. It is guaranteed that the given edges form a tree of $2n$ vertices.

## Output

Output a line containing a single integer, representing the answer modulo $998\,244\,353$.

## Examples

```input1
2
1 2
1 3
3 4
```

```output1
1
```

```input2
3
1 2
2 3
3 4
4 5
5 6
```

```output2
5
```