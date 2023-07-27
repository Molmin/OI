给定一棵有 $n$ 个节点的树, 有 $m$ 次询问, 每次询问两点间的最短路径上的最长连续严格递增子序列。

For a sequence $S_1,\ S_2,\ \cdots,\ S_N$, and a pair of integers $(i,\ j)$, if $1\leq i\leq j\leq N$ and $S_i < S_{i+1} < S_{i+2} < \cdots < S_{j-1} < Sj$, then the sequence $S_i,\ S_{i+1},\ \cdots,\ S_j$ is a **CIS** (Continuous Increasing Subsequence). The longest CIS of a sequence is called the **LCIS** (Longest Continuous Increasing Subsequence).

Now we consider a tree rooted at node $1$. Nodes have values. We have $Q$ queries, each with two nodes $u$ and $v$. You have to find the shortest path from $u$ to $v$. And write down each nodes' value on the path, from $u$ to $v$, inclusive. Then you will get a sequence, and please show us the length of its **LCIS**.

## Input

The first line has a number $T$ ($T \leq 10$), indicating the number of test cases.

For each test case, the first line is a number $N$ ($N \leq 10^5$), the number of nodes in the tree.

The second line comes with $N$ numbers $v_1,\ v_2,\ v_3,\ \cdots,\ v_N$, describing the value of node $1$ to node $N$. ($1\leq v_i \leq 10^9$)

The third line comes with $N - 1$ numbers $p_2,\ p_3,\ p_4,\ \cdots,\ p_N$, describing the father nodes of node $2$ to node $N$. Node $1$ is the root and will have no father.

Then comes a number $Q$, it is the number of queries. ($Q \leq 10^5$)

For next $Q$ lines, each with two numbers $u$ and $v$. As described above.

## Output

For test case $X$, output `Case #X:` at the first line.

Then output $Q$ lines, each with an answer to the query.

There should be a blank line **BETWEEN** each test case.

```input1
1
5
1 2 3 4 5
1 1 3 3
3
1 5
4 5
2 5
```

```output1
Case #1:
3
2
3
```