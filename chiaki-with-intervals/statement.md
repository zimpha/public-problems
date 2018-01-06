# Chiaki With Intervals

Chiaki has a set $A$ of $n$ intervals, the $i$-th of them is $[l_i, r_i]$. She would like to know the number of such interval sets $S \subset A$: for every interval $a \in A$ which is not in $S$, there exists at least one interval $b$ in $S$ which has non-empty intersection with $a$. As this number may be very large, Chiaki is only interested in its remainder modulo $(10^9+7)$.

Interval $a$ has intersection with interval $b$ if there exists a real number $x$ that $l_a \le x \le r_a$ and $l_b \le x \le r_b$.

## Input

There are multiple test cases. The first line of input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains an integer $n$ ($1 \le n \le 2 \times 10^5$) -- the number of intervals.

Each of the following $n$ lines contains two integers $l_i$ and $r_i$ ($1 \le l_i < r_i \le 10^9$) denoting the $i$-th interval.

It is guaranteed that for every $1 \le i < j \le n$, $l_i \ne l_j$ or $r_i \ne r_j$ and that the sum of $n$ in all test cases does not exceed $2 \times 10^5$.

## Output

For each test case, output an integer denoting the answer.
