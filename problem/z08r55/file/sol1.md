由于题目要求各个集合内的人最终位置相同，而不同集合的人最终位置不同，容易想到容斥。

记 $A,\ B,\ C$ 分别表示三个集合内的人，$f(S)$ 为集合 $S$ 内的人走 $m$ 步到同一个点的方案数，则易得答案为

$$
f(A)f(B)f(C)-\sum_{\text{cyc}}f(A\cup B)f(C)+2f(A\cup B\cup C).
$$