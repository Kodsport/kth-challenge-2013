#!/usr/bin/env python
import random
import sys

n = int(sys.stdin.readline())
a = [[0, 0] for i in range(n)]
u, v = 0, 1

for i in range(n / 2):
    w, z = random.uniform(3, 5), random.uniform(5, 1000)
    if i % 2 == 0:
        a[u][1] = -z
    else:
        a[v][1] = z
    if i < n / 2 - 1:
        a[u - 1][0] = a[u][0] + w
        a[v + 1][0] = a[u - 1][0]
    u -= 1
    v += 1

for i in range(n):
    print a[i][0], a[i][1]
