#!/usr/bin/env python3
import random
from sys import stdin

s = stdin.readline().strip()
a = s.split()
if a[0] == "exactly":
    n, t = int(a[1]), int(a[2])
else:
    n = random.randint(int(a[1]), int(a[2]))
    t = random.randint(int(a[3]), int(a[4]))

print(n, t)
for j in range(n):
    money = random.randint(1, 100000)
    time = random.randint(0, t - 1)
    print(money, time)
