#!/usr/bin/python3
from sys import stdin
import sys

lines = sys.stdin.readlines()
at = 0
def line():
    global at
    l = lines[at]
    at += 1
    return l

N, M = map(int, line().split());
S = ord('z')-ord('a')+1
three = [[[-1]*S for i in range(S)] for j in range(S)]
words = [""]*N
a = ord('a')
for i in range(N):
    one = [False]*S
    two = [[False]*S for x in range(S)]
    word = line().strip()
    left = [(i, j) for i in range(S) for j in range(S)]
    for j in range(len(word)):
        ch = ord(word[j]) - a
        for k in range(26):
            twoo = two[k]
            threee = three[ch][k]
            for l in range(26):
                if twoo[l] and threee[l] == -1:
                    threee[l] = i
        for k in range(S):
            two[k][ch] |= one[k]
        one[ch] = True
    words[i] = word

for i in range(M):
    plate = line()
    a = three[ord(plate[2])-ord('A')][ord(plate[0])-ord('A')][ord(plate[1])-ord('A')]
    if (a == -1):
        print("No valid word")
    else:
        print(words[a])
