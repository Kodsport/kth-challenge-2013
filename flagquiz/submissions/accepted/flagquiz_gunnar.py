#!/usr/bin/env python3
# This is an example solution to the "Flag Quiz" problem from KTH Challenge 2013, held on April 21,
# 2013.
#
# The solution is provided as-is, is not documented, and may be generally difficult to read.
#
# This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
# Attribution-Share Alike 2.5 Sweden License
# (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
# you like as long as this license information is not removed.
#
# Solution by Gunnar Kreitz
import sys

sys.stdin.readline()
n = int(sys.stdin.readline().strip())
lines = [ sys.stdin.readline().strip('\n').split(', ') for i in range(n) ]
dist = [ max([sum([(0 if w1 == w2 else 1) for w1,w2 in zip(l1, l2)]) for l2 in lines]) for l1 in lines]
print('\n'.join([', '.join(l) for l, d in zip(lines, dist) if d == min(dist)]))
