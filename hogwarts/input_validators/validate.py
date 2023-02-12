#!/usr/bin/python
from sys import stdin
import re
import sys

line = stdin.readline()
numbers = re.compile("(0|[1-9]\d*) (0|[1-9]\d*)\n")
assert numbers.match(line)
n, m = map(int, line.split())
assert 3 <= n <= 50 and 0 <= m <= n * (n - 1) / 2

for k in range(2):
    edges = set()
    for i in range(m):
        line = stdin.readline()
        assert numbers.match(line)
        a, b = map(int, line.split())
        assert 0 <= a < n and 0 <= b < n
        assert a != b

        if a > b:
            a, b = b, a
        assert (a, b) not in edges
        edges.add((a, b))

assert len(stdin.readline()) == 0
sys.exit(42)
