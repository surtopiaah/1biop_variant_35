#!/usr/bin/bash

gcc -std=c11 -Wall -Wextra -Wpedantic variant_35_while.c -o variant_35_while || exit 1
gcc -std=c11 -Wall -Wextra -Wpedantic variant_35_do_while.c -o variant_35_do_while || exit 1

input='10 10 10 10 15 10'
expected=$(printf 'count = 5\nsum = 55\nmin = 10\nmax = 15')
actual=$(printf '%s\n' "$input" | ./variant_35_while)

if [ "$actual" = "$expected" ]; then
    echo 'PASS'
else
    echo 'FAIL'
fi