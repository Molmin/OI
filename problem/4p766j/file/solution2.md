由于四个顶点都是直角，而要求三角形全部是锐角三角形，故每个顶点至少添加 $1$ 条线段。

而对于非正方形顶点的点，有两种情况：

- 该点出现在一个三角形的边上（不含端点）或该点在正方形的边上。

  那么这个三角形占了该点 $180^\circ$ 的角，还剩下 $180^\circ$。若该点还出现在另一个三角形的边上（不含端点），那么虽然合法，但是由于该点不是任何一个三角形的顶点，故该点没有研究意义。
  
  故只需讨论剩下 $180^\circ$ 分配给若干锐角的情况。
  
  由于每个锐角都 $< 90^\circ$，故该点至少是 $3$ 个锐角三角形的顶点。
  
- 该点没有出现在一个三角形的边上（不含端点）且该点也不在正方形的边上。

  此时该点的 $360^\circ$ 将分配给若干锐角，即至少是 $5$ 个锐角三角形的顶点。
  
对于两种情况，记前者出现 $x$ 次，后者出现 $y$ 次。

考虑统计三角形的总顶点数，那么有 $5x+3y+8\leq 3k$。$5x$ 表示 $x$ 个点都至少为 $5$ 个三角形贡献顶点，$3y$ 表示 $y$ 个点至少为 $3$ 个三角形贡献顶点。而 $8=4\times 2$ 表示正方形的 $4$ 个至少各贡献了 $2$ 个顶点。而实际总贡献为 $3k$。

再考虑计算所有三角形的总内角和。首先由于有 $k$ 个三角形，故总内角和为 $180^\circ k$。又第一种情况的点每个点贡献 $360^\circ$，第二种情况的点每个点贡献 $180^\circ$，正方形的四个顶点各贡献 $90^\circ$，故总度数为 $360^\circ x+180^\circ y+360^\circ$。即 $360^\circ x+180^\circ y+360^\circ=180^\circ k$，化简得 $2x+y+2=k$。

代入 $5x+3y+8\leq 3k$ 并化简得 $x\geq 2$。即至少有两个第一类点。

而对于两个第一类点，每个点都有 $5$ 个三角形，共 $10$ 个。而至多有 $2$ 个三角形重复（如下图），故至少有 $8$ 个三角形，即 $k < 8$ 时无解。

![](file://pic2.png =200x200)