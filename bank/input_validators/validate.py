#!/usr/bin/python
from sys import stdin
import re
import sys


integer = "(0|[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
n, T = list(map(int, line.split()))
assert 1 <= n <= 10000 and 1 <= T <= 47

for i in range(n):
    line = stdin.readline()
    assert twoint.match(line)
    c, t = list(map(int, line.split()))
    assert 1 <= c <= 10 ** 5 and 0 <= t < T

assert len(stdin.readline()) == 0
sys.exit(42)
