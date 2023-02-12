# This is an example solution to the "Peragrams" problem from KTH Challenge 2013, held on April 21,
# 2013.
#
# The solution is provided as-is, is not documented, and may be generally difficult to read.
#
# This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
# Attribution-Share Alike 2.5 Sweden License
# (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
# you like as long as this license information is not removed.
#
# Solution by Oskar Werkelin Ahlin
import sys


def solve():
    line = sys.stdin.readline().strip()
    counts = [0]*26
    for x in line:
        counts[ord(x)-ord('a')] += 1
    ans = 0
    for x in counts:
        if x % 2 == 1: ans += 1

    print max(0,ans-1)

if __name__ == "__main__":
    solve();
