记 $u$ 的父亲结点为 $v$，则第一步必须向其父亲结点走，故贡献长度 $w_{u-v}$。

接着会向 $v$ 的相邻结点走。各个情况的期望和（注意不能走回结点 $u$）为

$$
\text{up}_v \times \text{fa}_v + \text{down}_v \times \text{son}_v-(w_{u-v} + \text{down}_u).
$$

那么易得

$$
\text{up}_u=w_{u-v}+\frac{\text{up}_v\times\text{fa}_v+\text{down}_v\times\text{son}_v-(w_{u-v}+\text{down}_u)}{\text{fa}_v+\text{son}_v-1}.
$$

容易发现 $\text{up}_u$ 的值依赖于其父亲结点的有关信息，那么只需从上到下依次处理即可。

特别地，根结点的 $\text{up}$ 值为 $0$（显然）。