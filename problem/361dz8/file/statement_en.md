Matt, a famous adventurer who once defeated a pack of dire wolves alone, found a lost court. Matt finds that there are $N$ fluorescent lights which seem to be the stars from the firmament. What’s more, there are $M$ switches that control these fluorescent lights. Each switch is connected to a group of lights. When Matt touches a switch, all the lights connected to it will change their states (turning the dark on, turning the bright off).

Initially, all the fluorescent lights are dark. For each switch, Matt will touch it with probability $1$.

As a curious gentleman, Matt wants to calculate $E(X^3)$, where X represents the number of bright lights at the end, $E(X^3)$ represents the expectation of cube of $X$.

## Input

The first line contains only one integer $T$, which indicates the number of test cases.

For each test case, the first line contains $N, M$ ($1 \leq N, M \leq 50$), denoting the number of fluorescent lights (numbered from $1$ to $N$) and the number of switches (numbered from $1$ to $M$).

$M$ lines follow. The $i$-th line begins with an integer $K_i$ ($1\leq K_i\leq N$). $K_i$ distinct integers $l_{i,j}$ ($1 \leq l_{i,j} \leq N$) follow, denoting the fluorescent lights that the $i$-th switch controls.
 
## Output

For each test case, output a single line `Case #x: y`, where $x$ is the case number (starting from $1$) and $y$ is the answer. To avoid rounding error, the answer you should output is:

$$
E(X^3)\cdot 2^M\text{ mod }(10^9+7).
$$

## Sample

```input1
2
2 2
1 1
2 1 2
3 1
3 1 2 3
```

```output1
Case #1: 10
Case #2: 27
```

## Hint

For the first sample, there’re $4$ possible situations:

All the switches is off, no light is bright, $X^3 = 0$.

Only the first switch is on, the first light is bright, $X^3 = 1$.

Only the second switch is on, all the lights are bright, $X^3 = 8$.

All the switches is on, the second lights are bright, $X^3 = 1$.

Therefore, the answer is $E(X^3) \cdot 2^2\text{ mod }(10^9 + 7) = 10$.

For the second sample, there’re $2$ possible situations:

The switches is off, no light is bright, $X^3 = 0$.

The switches is on, all the lights are bright, $X^3 = 27$.

Therefore, the answer is $E(X^3) \cdot 2^1\text{ mod }(10^9 + 7) = 27$.