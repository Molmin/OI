Alice and Bob play the following game. First, they collect $N$ small stones and put them together in one pile. After that, they throw a coin one by one. Alice starts first. If a player throws heads then he takes exactly one stone from the pile. In case of tails he don't do anything. The one who takes the last stone wins. For each player, his skill of throwing a coin is known (to everyone, including himself and his opponent). More precisely, if Alice wants to throw some specific side of the coin, she always succeeds with probability $P$. The same probability for Bob is $Q$.

You are to find probability that Alice will win the game if both guys play optimally.

## Input

Input starts with a line containing one integer $T$ - a number of test cases ($1\leq T\leq 50$). Then $T$ test cases follow. Each of them is one line with three numbers $N$, $P$, and $Q$ separated with a space ($1\leq N\leq 99999999$, $0.5\leq P,\ Q\leq 0.99999999$). $P$ and $Q$ have not more than $8$ digits after decimal point.

## Output

For each test case output one line with a probability that Alice will win the game. Your answer must be precise up to $10^{-6}$.

## Example

```input1
1
1 0.5 0.5
```

```output1
0.666666667
```