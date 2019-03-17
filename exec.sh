#!/bin/bash
c=0
r=0
h=0
for ((i=1; i <= $1; i++)); do
./generator --big > b$i
cat b$i | ./lem-in > f$i
if ((`echo $?` != 0)); then
exit
fi
printf "%-9s: " "expected"
e=`cat f$i | grep -m 1 "required:" | grep -o "[0-9][0-9]*"`
echo $e
printf "%-9s: " "got"
g=`cat f$i | grep "^L" | wc -l`
echo $g
if ((g > e)); then
let h++
fi
if ((g > e + 2)); then
let c++
fi
if ((g > e + 10)); then
let r++
fi
echo $i
sleep 1
done
echo "nbr of high : $h/$1"
echo "nbr of too high : $c/$1"
echo "nbr of way too high : $r/$1"
