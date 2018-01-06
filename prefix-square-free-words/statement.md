# Prefix Square Free Words

A string is called a square string if it can be obtained by concatenating two copies of the same string (i.e. $s=uu$ for some word $u$). For example, "abab", "aa" are square strings, while "aaa", "abba" are not. A string is called prefix-square free if none of its prefixes is a square.

Chiaki would like to know the number of nonempty prefix-square free strings whose length is less than or equal to $n$. The size of the alphabet Chiaki uses is $m$. As this number may be very large, Chiaki is only interested in its remainder modulo $2^{32}$.

## Input

There are multiple test cases. The first line of input contains an integer $T$ ($1 \le T \le 100$), indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n \le 100, 1 \le m \le 10^9$) -- the length of the string and the size of the alphabet.

## Output

For each case, Output an integer denoting the answer.
