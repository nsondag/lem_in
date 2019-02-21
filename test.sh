#!/bin/bash
make
for i in {1..100};do
echo $i
time ./generator --big-superposition | ./lem-in > f$i
done
for i in {1..100};do
if ((`cat f$i|grep ici|wc -l` != 2));then
open f$i
fi
done
