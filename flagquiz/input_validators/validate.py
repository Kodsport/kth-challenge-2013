#!/usr/bin/python
from sys import stdin
import re
import sys

token = "(\w+)"
string = re.compile("((" + token + " )*" + token + "|)")

titleline = stdin.readline()
assert len(titleline) >= 2
casesline = stdin.readline()
assert re.match("[1-9]\d*\n", casesline)
N = int(casesline.strip())
assert 1 <= N <= 100

length = -1
for i in range(N):
    line = stdin.readline()
    assert line[-1] == '\n'
    elements = line[:-1].split(", ")

    if i == 0:
        length = len(elements)
    else:
        assert len(elements) == length

    for e in elements:
        assert string.match(e)
        assert len(e) <= 50

assert len(stdin.readline()) == 0
assert length >= 1
assert length * N <= 10000
sys.exit(42)
