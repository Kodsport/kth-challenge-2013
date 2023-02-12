# -*- coding: utf-8 -*-
# This is an example solution to the "Bank Queue" problem from KTH Challenge 2013, held on April
# 21, 2013.
#
# The solution is provided as-is, is not documented, and may be generally difficult to read.
#
# This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
# Attribution-Share Alike 2.5 Sweden License
# (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
# you like as long as this license information is not removed.
#
# Solution by lukasP (Lukáš Poláček)
from sys import stdin
import heapq


line = stdin.readline()
n, t = map(int, line.split())

people = [[] for x in range(t)]
for i in range(n):
    line = stdin.readline()
    c, s = map(int, line.split())
    people[s].append(c)

best = []
res = 0
for i in range(t - 1, -1, -1):
    for x in people[i]:
        heapq.heappush(best, -x)
    if len(best) > 0:
        res -= heapq.heappop(best)

print res
