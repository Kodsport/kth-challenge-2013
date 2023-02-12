#!/usr/bin/python
from sys import stdin
import re, sys

line = stdin.readline()
assert re.match("[1-9]\d* [1-9]\d*\n", line)
N, M = map(int, line.split())
assert 1 <= N <= 5000 and 1 <= M <= 10000

for i in range(N):
    line = stdin.readline()
    assert re.match("[a-z]{1,100}\n", line)
for i in range(M):
    line = stdin.readline()
    assert re.match("[A-Z]{3}\n", line)

assert len(stdin.readline()) == 0
sys.exit(42)
