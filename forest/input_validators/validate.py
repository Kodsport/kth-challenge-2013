#!/usr/bin/python
from sys import stdin
import re
import sys
import math


integer = "(0|-0|-?[1-9]\d*)"
floating = integer + "?(\.\d{1,4})?"
onefloat = re.compile(floating + "\n")
twofloat = re.compile(floating + " " + floating + "\n")
fourfloat = re.compile("(" + floating + " ){3}" + floating + "\n")
oneint = re.compile(integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 3 <= n <= 250000

for i in range(n):
    line = stdin.readline()
    assert twofloat.match(line)
    for x in line.split():
        assert math.fabs(float(x)) <= 10 ** 5

line = stdin.readline()
assert fourfloat.match(line)
for x in line.split():
    assert math.fabs(float(x)) <= 10 ** 5

line = stdin.readline()
assert onefloat.match(line)
assert math.fabs(float(line[:-1])) <= 10 ** 5

assert len(stdin.readline()) == 0
sys.exit(42)
