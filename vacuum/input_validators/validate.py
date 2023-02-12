#!/usr/bin/python
from sys import stdin
import re, sys

line = stdin.readline()
assert re.match("[1-9]\d* [1-9]\d* [1-9]\d*\n", line)
L1, L2, N = map(int, line.split())
assert 1 <= L1 <= 10000 and 1 <= L2 <= 10000 and 4 <= N <= 2000

for i in range(N):
    line = stdin.readline()
    assert re.match("[1-9]\d*\n", line)
    l = int(line)
    assert 1 <= l <= 10000

assert len(stdin.readline()) == 0
sys.exit(42)
