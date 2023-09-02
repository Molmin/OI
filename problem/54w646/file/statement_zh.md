在一个游戏中，有 $n$ 个角色，每个角色有三个属性 $a_i,b_i,c_i$。

对于每一个角色 $i$，你可以将 $a_i,b_i,c_i$ 变为 $(a'_i,b'_i,c'_i)$。你要将角色的差距最小化。

差距定义为 $\max(\max\limits_{i=1}^na_i-\min\limits_{i=1}^na_i,\max\limits_{i=1}^nb_i-\min\limits_{i=1}^nb_i,\max\limits_{i=1}^nc_i-\min\limits_{i=1}^nc_i)$。

## Problem Description

Little Q is playing an RPG online game. In this game, there are $n$ characters labeled by $1,\ 2,\ \cdots,\ n$. The $i$-th character has three types of quotas:

- $a_i$ - The maximum points of damage he can achieve in $15$ seconds.
- $b_i$ - The maximum points of damage he can achieve in $40$ seconds.
- $c_i$ - The maximum points of damage he can achieve in $120$ seconds.

You are the team leader working for the new balance between these $n$ characters, aiming at bringing hope to the weak characters. For each character, your teammates have made a plan to strengthen some skills such that the three quotas may be increased as a result. Note that it is not allowed to weaken characters, because it will make their owners upset.

To make a perfect balance, you need to accept some plans and deny others such that the gap between all the $n$ characters is minimized. Note that a plan can only be entirely accepted or entirely denied. Here, the gap is defined as

$$
\max(\max_{1\leq i\leq n}a_i-\min_{1\leq i\leq n}a_i, \max_{1\leq i\leq n}b_i-\min_{1\leq i\leq n}b_i, \max_{1\leq i\leq n}c_i-\min_{1\leq i\leq n}c_i).
$$

## Input

The first line contains a single integer $T$ ($1 \leq T \leq 100$), the number of test cases. For each test case:

The first line contains a single integer $n$ ($1 \leq n \leq 100\,000$), denoting the number of characters.

In the next $n$ lines, the $i$-th line contains six integers $a_i$, $b_i$, $c_i$, $a_i'$, $b_i'$ and $c_i'$ ($1\leq a_i\leq a_i'\leq 10^9$, $1\leq b_i\leq b_i'\leq 10^9$, $1\leq c_i\leq c_i'\leq 10^9$), describing the quotas of the $i$-th character now and in plan.

It is guaranteed that the sum of all $n$ is at most $500\,000$.

## Output

For each test case, output a single line containing an integer, denoting the optimal gap.

```input1
1
2
1 1 1 2 3 5
2 4 3 7 5 8
```

```output1
2
```