## Description

Alice is going to take all her savings out of the ATM (Automatic Teller Machine). Alice forget how many deposit she has, and this strange ATM doesn't support query deposit. The only information Alice knows about her deposit is the upper bound is $K$ RMB(that means Alice's deposit $x$ is a random integer between $0$ and $K4 (inclusively)).

Every time Alice can try to take some money $y$ out of the ATM. if her deposit is not small than $y$, ATM will give Alice $y$ RMB immediately. But if her deposit is small than $y$, Alice will receive a warning from the ATM.

If Alice has been warning more then $W$ times, she will be taken away by the police as a thief.

Alice hopes to operate as few times as possible.

As Alice is clever enough, she always take the best strategy.

Please calculate the expectation times that Alice takes all her savings out of the ATM and goes home, and not be taken away by the police.

## Input

The input contains multiple test cases. Each test case contains two numbers $K$ and $W$.

$1\leq K,W\leq 2000$

## Output

For each test case output the answer, rounded to $6$ decimal places.

## Sample

```input1
1 1
4 2
20 3
```

```output1
1.000000
2.400000
4.523810
```