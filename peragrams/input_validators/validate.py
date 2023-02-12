#!/usr/bin/python
from sys import stdin
import re
import sys

string = re.compile("[a-z]+\n")

line = stdin.readline()
assert string.match(line)
assert len(line) <= 1000+1
assert len(stdin.readline()) == 0
sys.exit(42)
