#!/bin/sh

r=0
while read a b
do
    ((r++))
    t=$r
    if [ $r -lt 10 ]
    then
        t="0"$t
    fi
    if [ $b -eq 0 ]
    then
        ./gen.cpp.bin <<< $a | ./tras.py > $t.in
    else
        ./pila.py <<< $a > tmp; ./tras.py < tmp > $t.in
        rm tmp
    fi
    ./sol.cpp.bin < $t.in > $t.out
done
