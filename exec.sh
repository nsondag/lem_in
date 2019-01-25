#!/bin/sh
time ./generator --big-superposition | ./lem-in > test.txt ;
printf "%-9s: " "expected";
cat test.txt | grep "required:" | grep -o "[0-9][0-9]*" ;
printf "%-9s: " "got";
cat test.txt | grep "move :" | grep -o "[0-9][0-9]*" ;
