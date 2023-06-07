下面使用数学归纳法证明这个结论。

当 $m=1$ 时，结论显然成立。

若 $m=t-1\geq 1$ 时结论成立，则矩阵为

$$
\begin{matrix}
C_{t-1}^0 & C_{t-1}^1 & C_{t-1}^2 & \cdots & C_{t-1}^{i-2} & C_{t-1}^{i-1} \\
C_{t-1}^1 & C_{t-1}^1\cdot C_{t-1}^1 & C_{t-1}^1\cdot C_{t-1}^2 & \cdots & C_{t-1}^1\cdot C_{t-1}^{i-2} & C_{t-1}^{i-2} \\
C_{t-1}^2 & C_{t-1}^2\cdot C_{t-1}^1 & C_{t-1}^2\cdot C_{t-1}^2 & \cdots & C_{t-1}^2\cdot C_{t-1}^{i-2} & C_{t-1}^{i-3} \\
\vdots & \vdots & \vdots & \ddots & \vdots & \vdots \\
C_{t-1}^{i-2} & C_{t-1}^{i-2}\cdot C_{t-1}^1 & C_{t-1}^{i-2}\cdot C_{t-1}^2 & \cdots & C_{t-1}^{i-2}\cdot C_{t-1}^{i-2} & C_{t-1}^1 \\
C_{t-1}^{i-1} & C_{t-1}^{i-2} & C_{t-1}^{i-3} & \cdots & C_{t-1}^1 & C_{t-1}^0
\end{matrix}
$$

设上面矩阵的行与列从 $1$ 开始编号，且第 $i$ 行第 $j$ 列的数为 $a_{i,\ j}$，那么有

$$
a_{i,\ j}=\binom{t-1}{i-1}\cdot \binom{t-1}{j-1}.
$$

则当 $m=t$ 时，设其矩阵的行与列从 $0$ 开始编号，且第 $i$ 行第 $j$ 列的数为 $b_{i,\ j}$，则易得

$$
\begin{aligned}
b_{i,\ j} & = a_{i,\ j}+a_{i+1,\ j}+a_{i,\ j+1}+a_{i+1,\ j+1} \\
& = \binom{t-1}{i-1}\cdot \binom{t-1}{j-1}+\binom{t-1}i\cdot \binom{t-1}{j-1}+\binom{t-1}{i-1}\cdot \binom{t-1}j+\binom{t-1}i\cdot \binom{t-1}j \\
& = \left[\binom{t-1}{i-1}+\binom{t-1}i\right]\cdot\left[\binom{t-1}{j-1}+\binom{t-1}j\right] \\
& = \binom ti\cdot\binom tj.
\end{aligned}
$$

结论成立，**证毕**。