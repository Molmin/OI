下面考虑旋转和对称怎么做。

容易想到只需考虑将询问反向旋转即可。用 $flipped$ 表示是否翻转过，$rotated$ 表示旋转的个数。只需对于输入的每个位置都反向转换即可。

时间复杂度 $\Theta((N+Q)\log N)$。