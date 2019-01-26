#!/bin/sh
time ./generator --big-superposition | ./lem-in > test.txt ;
printf "%-9s: " "expected";
cat test.txt | grep -m 1 "required:" | grep -o "[0-9][0-9]*" ;
printf "%-9s: " "got";
cat test.txt | grep -m 1 "move :" | grep -o "[0-9][0-9]*" ;
