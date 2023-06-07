$N$ bins are lined up in a row, numbered $1$ to $N$ from left to right. Bin $i$ initially contains $A_i$ balls, and it is considered beautiful if it contains $B_i$ balls. In one move, you may pick a bin $i$ ($1 < i < N$) with at least $2$ balls, move one ball from bin $i$ to any bin on its left, and move another ball from bin $i$ to any bin on its right. After some sequence of moves, is it possible to make all of the bins beautiful? To ensure the integrity of your solution, there may be up to $T$ test cases.

## Constraints

$1\leq T\leq 10^6$

$3\leq N\leq 10^6$

$1\leq a_i,\ b_i\leq 10^9$

The sum of $N$ over all test cases does not exceed $10^6$.

## Input Specification

The first line contains a single integer $T$, the number of test cases. The next $3T$ lines describe the test cases.

The first line of each test case contains a single integer $N$.

The second line of each test case contains $N$ integers $A_1,\ A_2,\ \cdots,\ A_N$.

The third line of each test case contains $N$ integers $B_1,\ B_2,\ \cdots,\ B_N$.

## Output Specification

For each test case, output a single line containing `YES` if it is possible to make all of the bins beautiful or `NO` otherwise.

## Sample

```input1
2
5
2 4 4 2 1
4 3 1 3 2
5
1 1 2 4 2
4 3 4 1 3
```

```output1
YES
NO
```

## Explanation for Sample

For the first test case, one possible solution is as follows:

1. Move one ball from bin $3$ to bin $1$ and another from bin $3$ to bin $4$. The number of balls in each bin is now $[3,\ 4,\ 2,\ 3,\ 1]$.

2. Move one ball from bin $2$ to bin $1$ and another from bin $2$ to bin $3$. The number of balls in each bin is now $[4,\ 2,\ 3,\ 3,\ 1]$.

3. Move one ball from bin $3$ to bin $2$ and another from bin $3$ to bin $5$. The number of balls in each bin is now $[4,\ 3,\ 1,\ 3,\ 2]$.

For the second test case, it can be proven that it is impossible to make all of the bins beautiful.