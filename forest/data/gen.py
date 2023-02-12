#!/usr/bin/env python
import math
import sys
import random
import Image, ImageDraw

t = ((0, 1), (1, 0), (0, -1), (-1, 0))
s = int(math.sqrt(int(sys.stdin.readline())))
s = 2 * s + 1
a = [[1 for i in xrange(s)] for j in xrange(s)]

def dfs(x):
	a[x[0]][x[1]] = 0
	e = [i for i in range(4)]
	for i in xrange(4):
		q = random.randint(i, 3)
		e[i], e[q] = e[q], e[i]

	for k in xrange(4):
		y = map(lambda x, y: x + 2 * y, x, t[e[k]]) 
		if y[0] < 0 or y[0] >= s or y[1] < 0 or y[1] >= s:
			continue
		if a[y[0]][y[1]] == 0:
			continue

		q = map(lambda x, y: x + y, x, t[e[k]])
		a[q[0]][q[1]] = 2
		dfs(y)

g = {}
def vloz(x, y):
  if x not in g:
    g[x] = []
  if y not in g:
    g[y] = []
  g[x].append(y)
  g[y].append(x)

dl = 12
sys.setrecursionlimit(100000)
print sys.getrecursionlimit()
dfs((1, 1))
size = (s / 2) * dl
#im = Image.new("RGB", ((s / 2) * dl, (s / 2) * dl))
#draw = ImageDraw.Draw(im)
def kresli(f, y):
  k1, k2 = f[0][0] >= 0 and f[0][1] >= 0, f[3][0] < size and f[3][1] < size 
  if y:
    if k1:
#      draw.line(f[0] + f[1])
      vloz(f[0], f[1])
    if k2:
#      draw.line(f[2] + f[3])
      vloz(f[2], f[3])
  else:
    if k1:
#      draw.line(f[0] + f[2])
      vloz(f[0], f[2])
    if k2:
#      draw.line(f[1] + f[3])
      vloz(f[1], f[3])

for i in range(s):
  for j in range(s):
    if i % 2 == 0 and j % 2 == 0:
      continue
    if a[i][j] != 0:
      if i % 2 == 1:
        e = ((j / 2 - 1) * dl + 3 * dl / 4, (i / 2) * dl + dl / 4)
        f = [(e[0] + (k / 2) * dl / 2, e[1] + (k % 2) * dl / 2) for k in xrange(4)]
        kresli(f, a[i][j] == 1)
      else:
        e = ((j / 2) * dl + dl / 4, (i / 2 - 1) * dl + 3 * dl / 4)
        f = [(e[0] + (k / 2) * dl / 2, e[1] + (k % 2) * dl / 2) for k in xrange(4)]
        kresli(f, a[i][j] == 2)

zoz, zac = [], g.keys()[0]
zoz.append(zac)
zoz.append(g[zac][0])
while zoz[0] != zoz[-1]:
  for x in g[zoz[-1]]:
    if x != zoz[-2]:
      zoz.append(x)
      break

zoz.pop()
#im.save("tmp.png")
novy = []
for i in range(len(zoz)):
  a, c = zoz[i - 1], zoz[(i + 1) % len(zoz)]
  if a[0] == c[0] or a[1] == c[1]:
    continue
  novy.append(zoz[i])

#im2 = Image.new("RGB", im.size)
#draw2 = ImageDraw.Draw(im2)
#for i in range(len(novy)):
#  draw2.line(novy[i - 1] + novy[i]) 
#im2.save("tmp2.png")
