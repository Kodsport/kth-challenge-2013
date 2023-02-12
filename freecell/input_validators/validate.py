#!/usr/bin/python
from sys import stdin
import re
import sys

integer = "(0|[1-9]\d*)"
threeint = re.compile("(" + integer + " ){2}" + integer + "\n")

line = stdin.readline()
assert threeint.match(line)
n, m, k = list(map(int, line.split()))
assert 0 <= n <= 5 and 0 <= m <= 5 and 0 <= k <= 100

assert len(stdin.readline()) == 0
sys.exit(42)
