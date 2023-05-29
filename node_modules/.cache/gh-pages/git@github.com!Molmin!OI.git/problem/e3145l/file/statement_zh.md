## 题目描述

一家石油公司最近在一片区域开采石油，这片区域可以看作一个二维平面，其中 $x$ 轴平行于地面，$x$ 坐标表示地表的水平位置，而 $y$ 轴垂直于地面，$y$ 坐标表示深度。这片区域内还有 $n$ 个石油矿，每个石油矿都可以看作一条平行于 $x$ 轴的线段，其中石油的储量即为该线段的长度，如下图就对应着样例一的输入：

![](file://pic1.png =690x319)

现在这家石油公司想要挖一个石油井，石油井可以看作一条与 $x$ 轴相交的直线（如上图中蓝色虚线所示），通过挖石油井，这家石油公司能获取到所有与石油井有公共点的石油矿内的石油（端点处或者在线段内均算）。

你的任务就是替这家公司找到一个挖石油井的方案，使得其能获得最大储量的石油，为了方便，你只需要输出最大储量即可。

## 输入格式

Multiple test cases. Please process until EOF is reached. For each test case:

The first line of input contains a single integer $n$ ( $1 \leq n \leq 2\, 000$ ), which is the number of oil deposits. This is followed by $n$ lines, each describing a single deposit. These lines contain three integers $x_0$ , $x_1$ , and $y$ giving the deposit’s position as the line segment with endpoints $(x_0,y)$ and $(x_1,y)$ . These numbers satisfy $|x_0|, |x_1| \leq 10^6$ and $1 \le y \le 10^6$ . No two deposits will intersect, not even at a point.

## 输出格式

For each test case, display the maximum amount of oil that can be extracted by a single oil well.

## 样例输入输出

```input1
5
100 180 20
30 60 30
70 110 40
10 40 50
0 80 70
3
50 60 10
-42 -42 20
25 0 10
```

```output1
200
25
```