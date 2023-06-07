对于基环树的情况，容易发现 $\text{down}$ 值的处理是类似的。而 $\text{up}$ 值的边界处理略有不同。

考虑环上结点的 $\text{up}$ 值求法。这里环上结点数量 $\leq 20$，故考虑枚举环上的结点 $u$ 分别求出 $\text{up}$ 值。

那么第一步必须向环上 $u$ 的相邻结点走。

首先按一定方向从结点 $u$ 开始遍历一遍环。设 $\text{mul}$ 表示走到当前这个点的概率。那么由结点 $u$ 走到第一个遇到的结点，概率为 $\dfrac 12$，故初始化 $\text{mul}\gets\dfrac 12$。

遇到一个新点 $v$ 时，设前一个点为 $t$。首先要加上之间连接的这条边的贡献即 $w_{v-t}$，然后由于有 $\dfrac{\text{son}_v}{\text{son}_v+1}$ 的概率进入这棵子树，故应更新值：

$$
\text{up}_u\gets\text{up}_u+\left(\frac{\text{son}_v}{\text{son}_v+1}\cdot\text{down}_v+w_{v-t}\right)\times\text{mul}.
$$

因为有 $\dfrac{\text{son}_v}{\text{son}_v+1}$ 的概率进入以 $v$ 为根的这棵树，故应更新 $\text{mul}$ 的值：

$$
\text{mul}\gets\frac{\text{mul}}{\text{son}_v+1}.
$$

考虑一种特殊情况：绕完一圈后到了 $u$ 的前一格，只能进入所在树内，故此时应更新：

$$
\text{up}_u\gets\text{up}_u+(\text{down}_v+w_{u-v})\times\text{mul}.
$$

最后，易知答案为

$$
\sum_{u=1}^n\frac{\text{up}_u\cdot\text{fa}_u+\text{down}_u\cdot\text{son}_u}{\text{fa}_u+\text{son}_u}.
$$