#!/usr/bin/bash

#compile & run all ten tests
set -eu 
#-e: Exit immediately if any command exits with a non-zero status (i.e., on error). 
# This ensures scripts fail fast when something goes wrong.

#-u: Treat unset variables as an error and exit immediately.
# This prevents unintended behavior from uninitialized variables.

flags="-std=c11 -Wall -Wextra -Wpedantic"

gcc $flags variant_35_while.c -o variant_35_while 
gcc $flags variant_35_do_while.c -o variant_35_do_while 

passed=0
total=0

run_test() {
    local no="$1" input="$2"
    local expected actual_w actual_d
    expected=$(printf 'count = %s\nsum = %s\nmin = %s\nmax = %s' "$3" "$4" "$5" "$6")
    actual_w=$(printf '%s\n' "$input" | ./variant_35_while)
    actual_d=$(printf '%s\n' "$input" | ./variant_35_do_while)
    total=$((total + 1))

    echo "=== Test $no ==="
    echo "Input:    $input"
    echo "Expected: $(echo "$expected" | tr '\n' ' ')"
    echo "while:    $(echo "$actual_w" | tr '\n' ' ')"
    echo "do-while: $(echo "$actual_d" | tr '\n' ' ')"

    if [ "$actual_w" = "$expected" ] && [ "$actual_d" = "$expected" ]; then
        echo "PASS"
        passed=$((passed + 1))
    else
        echo "FAIL"
    fi
    echo
}


####### will have to make a separate file and extra .csv file
#        no  input                                        count sum min max
run_test 1  '10 10 10 10 15 10'                            5   55  10 15   # earliest termination


echo "$passed of $total tests passed"
[ "$passed" -eq "$total" ] || { echo "SOME TESTS FAILED"; exit 1; }