#!/usr/bin/env python3
# -*- coding: utf-8 -*-
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
# Solution by Emma Enström
# Naive solution - checks every pair of vectors twice, and all vectors with themselves.
import sys

def readInput():
	q = sys.stdin.readline()
	N = int(sys.stdin.readline().strip())
	options = []
	for i in range(N):
		option = sys.stdin.readline().rstrip('\n').split(', ')
		options.append(option)
	return options, N

def compare(o1, o2):
	dist = 0
	for i in range(len(o1)):
		if o1[i] != o2[i]:
			dist+=1
	return dist

def hamming(options):
	mindist = []
	globalmin = len(options[0])
	for option in options:
		localmax = 0
		for other in options:
			dist = compare(option, other)
			if dist > localmax:
				localmax = dist
		if localmax < globalmin:
			globalmin = localmax
			mindist = [option]
		elif localmax == globalmin:
			mindist.append(option)
	return globalmin, mindist

def printSolution(best):
	for e in best:
		print(', '.join(e))

options, N = readInput()
minmax, best = hamming(options)
printSolution(best)
