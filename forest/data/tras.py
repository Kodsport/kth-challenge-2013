#!/usr/bin/env python
import random
import sys

r = 1
q = complex(random.uniform(-.05, .05), random.uniform(-.05, .05))
n = 0
a = []
mx, my = [1e10, -1e10], [1e10, -1e10]
while True:
		s = sys.stdin.readline().split()
		if len(s) < 2:
				break
		u, v = float(s[0]), float(s[1])
		x = q * complex(u + random.uniform(-r, r), v + random.uniform(-r, r))
		mx[0], mx[1] = min(mx[0], x.real), max(mx[1], x.real)
		my[0], my[1] = min(my[0], x.imag), max(my[1], x.imag)
		a.append(x)

print len(a)
for i in a:
		print "%.4lf %.4lf" % (i.real, i.imag)

x, y = complex(random.uniform(mx[0], mx[1]), random.uniform(my[0], my[1])),\
		complex(random.uniform(mx[0], mx[1]), random.uniform(my[0], my[1]))
print "%.4lf %.4lf %.4lf %.4lf" % (x.real, x.imag, y.real, y.imag)
print "%.4lf" % random.uniform(0, min(mx[1] - mx[0], my[1] - my[0]) / 5)
