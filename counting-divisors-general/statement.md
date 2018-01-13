# Counting Divisors (general)

Let $\sigma_0(n)$ be the number of positive divisors of $n$.

For example, $\sigma_0(1) = 1$, $\sigma_0(2) = 2$ and $\sigma_0(6) = 4$.

Let $$S_k(n) = \sum _{i=1}^n \sigma_0(i^k).$$

Given $n$ and $k$, find $S_k(n) \bmod 2^{64}$.

## Input

There are multiple test cases. The first line of input contains an integer $T$ ($1 \le T \le 10000$), indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $k$ ($1 \le n, k \le 10^{10}$).

## Output

For test case, output a single line containing $S_k(n) \bmod 2^{64}$.
