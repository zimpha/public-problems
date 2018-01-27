# The Sum of Unitary Divisors

A natural number $d$ is a unitary divisor of $n$ if $d$ is a divisor of $n$ and if $d$ and $\frac{n}{d}$ are coprime.

Let $\sigma^{*}(n)$ be the sum of the unitary divisors of $n$.

For example, $\sigma^{*}(1) = 1$, $\sigma^{*}(2) = 3$ and $\sigma^{*}(6) = 12$.

Let

$$S(n) = \sum_{i=1}^n \sigma^{*}(i).$$

Given $n$, find $S(n) \bmod 2^{64}$.

## Input

There are multiple test cases. The first line of input contains an integer $T$ ($1 \le T \le 50000$), indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 5 \times 10^{13}$).

## Output

For each test case, output a single line containing $S(n) \bmod 2^{64}$.
