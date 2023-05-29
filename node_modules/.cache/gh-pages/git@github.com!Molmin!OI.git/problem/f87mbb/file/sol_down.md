对于一个结点 $u$，若是叶子结点，为方便处理，令 $\text{down}_u=0$。

若是非叶子结点，则第一步必须向其儿子结点走，若向儿子结点 $v$ 走，那么此时贡献的路径长度期望为

$$
\text{down}_v+w_{u-v}.
$$

那么易知

$$
\text{down}_u = \frac {\sum_{(u, v)\in E}\text{down}_v + w_{u-v}} {\text{son}_u}.
$$