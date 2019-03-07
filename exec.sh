#!/bin/bash
c=0
r=0
for i in {1..100}; do
./generator --big-superposition | ./lem-in > test.txt
printf "%-9s: " "expected"
e=`cat test.txt | grep -m 1 "required:" | grep -o "[0-9][0-9]*"`
echo $e
printf "%-9s: " "got"
g=`cat test.txt | grep -m 1 "move:" | grep -o "[0-9][0-9]*"`
echo $g
if ((g > e + 2)); then
let c++
fi
if ((g > e + 10)); then
let r++
fi
sleep 1
echo
done
echo "nbr of too high : $c/100"
echo "nbr of way too high : $r/100"
