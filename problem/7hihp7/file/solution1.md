考虑求出取 $l\leq i\leq r$，对于任意的 $l\leq k\leq r$，都满足 $s_i\mid s_k$ 的 $i$ 的个数，再用 $r-l+1$ 减去求出的数量即可。

根据条件，$s_i\mid s_l,\ s_i\mid s_{l+1},\ \cdots,\ s_i\mid s_r$，则 $s_i\mid\gcd_{k=l}^rs_k$，又因为 $s_i$ 也在 $\{s_l,\ s_{l+1},\ \cdots,\ s_r\}$ 中，则 $s_i=\gcd_{k=l}^rs_k=\min_{k=l}^rs_k$。