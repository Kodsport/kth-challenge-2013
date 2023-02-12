from sys import stdin
import random

a = [line for line in stdin]

for i in range(20):
    ind = random.randint(i, len(a) - 1)
    a[i], a[ind] = a[ind], a[i]
    f = open("%02d.in" % (i + 1), "w")
    print(a[i], end='', file=f)
