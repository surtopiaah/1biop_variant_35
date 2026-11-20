#!/usr/bin/bash

#compile & run all ten tests
set -eu 
#-e: Exit immediately if any command exits with a non-zero status (i.e., on error). 
# This ensures scripts fail fast when something goes wrong.

#-u: Treat unset variables as an error and exit immediately.
# This prevents unintended behavior from uninitialized variables.


# Work in the folder containing this script.
cd "$(dirname "$0")"

flags="-std=c11 -Wall -Wextra -Wpedantic"

gcc $flags variant_35_while.c -o variant_35_while 
gcc $flags variant_35_do_while.c -o variant_35_do_while 

passed=0
total=0

 


# run_test: number, input (including the stopping number), expected count sum min max
run_test() {
    local no="$1" input="$2"
    local expected actual_w actual_d
    expected=$(printf 'count = %s\nsum = %s\nmin = %s\nmax = %s' "$3" "$4" "$5" "$6")
 
    # The same input is piped into both programs, nothing is typed manually.
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


#        no  input                                        count sum min max
run_test  1 '10 10 10 10 15 10'                            5   55  10   15   
run_test  2 '20 20 20 20 8 10'                             5   88   8   20
run_test  3 '20 20 20 20 20 11 12'                         6  111  11   20
run_test  4 '1 1 1 1 1 10 12 14 16 18'                     9   57   1   16
run_test  5 '10 10 10 10 10 10 12'                         6   60  10   10
run_test  6 '11 10 10 10 10 10'                            5   51  10   11
run_test  7 '30 5 40 8 7 9 6 14'                           7  105   5   40
run_test  8 '6 6 6 6 6 6 6 6 6 18'                         9   54   6    6
run_test  9 '0 0 0 0 0 100 12'                             6  100   0  100
run_test 10 '3 9 4 8 5 7 6 7 6 5 20'                       10  60   3    9


echo "$passed of $total tests passed"
[ "$passed" -eq "$total" ] || { echo "SOME TESTS FAILED"; exit 1; }