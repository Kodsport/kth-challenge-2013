#!/usr/bin/python
from sys import stdin
import re
import sys

line = stdin.readline()
number_pat = "(0|[1-9]\d*)"
nz_number_pat = "[1-9]\d*"
numbers_re = re.compile("{0} {0}\n".format(number_pat))
three_numbers_re = re.compile("{0} {0} {0}\n".format(number_pat))

# First line, three integers.
assert numbers_re.match(line)
N, S = map(int, line.split())
assert 2 <= N <= 50000 and 1 <= S <= 10**4

# UF for checking for no cycles
e = [-1] * N


def find(x):
    if e[x] < 0:
        return x
    e[x] = find(e[x])
    return e[x]


def join(a, b):
    a, b = find(a), find(b)
    if a == b:
        return
    if e[a] > e[b]:
        a, b = b, a
    e[a] += e[b]
    e[b] = a

edge_set = set()
# Check N-1 lines, three integers.
for i in xrange(N-1):
    line = stdin.readline()
    assert three_numbers_re.match(line)
    A, B, D = map(int, line.split())
    assert 1 <= A <= N and 1 <= B <= N and 1 <= D <= 100
    assert find(A-1) != find(B-1)
    join(A - 1, B - 1)
    if B < A:
        A, B = B, A
    assert (A, B) not in edge_set
    edge_set.add((A, B))

# OK, no cycles. must be connected.

line = stdin.readline()
assert re.match(number_pat + "\n", line)
L = int(line)
assert 0 <= L <= N

# Check for L numbers at the end.
end_re = re.compile("(|({0} )*{0})\n".format(nz_number_pat))
endline = stdin.readline()
assert end_re.match(endline)

# Check lamp nodes
lamps = map(int, endline.split())
assert len(lamps) == L
for x in lamps:
    assert 1 <= x <= N

lamps.sort()
assert not any(i for i in range(0, L - 1) if lamps[i] == lamps[i + 1])

# EOF
assert len(stdin.readline()) == 0
sys.exit(42)
