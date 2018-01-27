# Just a Palindrome

A palindrome is a symmetrical string, that is, a string read identically from left to right as well as from right to left.

Chiaki has a string $s$ and she can perform the following operation at most once:

+ choose two integer $i$ and $j$ ($1 \le i, j \le |s|$).
+ swap $s_i$ and $s_j$.

Chiaki would like to know the longest palindromic substring of string after the operation.

## Input

There are multiple test cases. The first line of input contains an integer $T$, indicating the number of test cases. For each test case:

The first line contains a non-empty string $s$ ($1 \le |s| \le 10^6$) consisting of lowercase and uppercase letters.

It is guaranteed that the sum of all $|s|$ does not exceed $10^6$.

## Output

For each test case, output an integer denoting the answer.