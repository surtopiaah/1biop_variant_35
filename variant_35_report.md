# 1BIOBP — Individual Assignment, Variant 35

**Task:** Read a sequence of integers. Stop when all three conditions hold for the current candidate `x`: at least 5 values have been processed, `x == 2 * count`, and `sum > 50`. The terminating `x` must **not** be counted, added to the sum, or used for the minimum and maximum. Print `count`, `sum`, `min` and `max` of the processed values. Both a `while` and a `do ... while` version are required and must print identical results.

## The state (short explanation)

1. `x` holds the current input candidate.
2. `count` stores the number of already processed values.
3. `sum` stores the sum of already processed values (`long long`, so large inputs do not overflow).
4. `min` and `max` store the smallest and largest already processed value; they are set from the first processed value (when `count == 0`).
5. `count`, `sum`, `min` and `max` start at zero because the processed prefix is initially empty.
6. The stop condition is `count >= 5 && x == 2 * count && sum > 50`. It is evaluated before `x` is processed, so `count` and `sum` do not include `x`.
7. `last` is 1 when `x` is the last number on its line. The helper `read_number` sets it: after reading a number it skips the spaces and looks at the next character; a newline (or the end of the input) means the line is over, anything else is put back with `ungetc`.
8. The `while` version reads the first candidate before entering the loop, so its condition is checked before the body.
9. The `do ... while` version first reads a candidate, computes `stop`, and processes the candidate only if `stop` is false.
10. Both programs deliberately exclude the terminating candidate and therefore print identical results.
11. Every line is a separate try. If the line ends before the stop condition is met, the program writes "That sequence does not meet the stop rule, please try again:" to stderr and sets `count`, `sum`, `min` and `max` back to zero, so numbers from different lines are never mixed.
12. As soon as one line meets the stop rule, the result is printed and the program ends; later lines are not read.
13. If the input ends, or something that is not a number is read, before any line met the stop rule, the program writes a message to stderr, prints nothing on stdout, and exits with status 1.

## Usage

The numbers are typed (or piped) as lines of integers separated by spaces; each line is one try:

```sh
./variant_35_while
10 10 10 10 15 10
```

To save the result in a separate file, use a redirect:

```sh
echo "10 10 10 10 15 10" | ./variant_35_while > result.txt
```

The messages for a person go to stderr, so they never appear in `result.txt`.

## Compilation

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic variant_35_while.c -o variant_35_while
gcc -std=c11 -Wall -Wextra -Wpedantic variant_35_do_while.c -o variant_35_do_while
```

## 10 tests (verified against both compiled programs)

| No. | Complete input | Expected | while actual | do ... while actual | OK? | What it checks |
|---:|---|---|---|---|---|---|
| 1 | `10 10 10 10 15 10` | `count = 5; sum = 55; min = 10; max = 15` | `count = 5; sum = 55; min = 10; max = 15` | `count = 5; sum = 55; min = 10; max = 15` | YES | Earliest possible stop: exactly 5 processed values and sum 55 > 50 |
| 2 | `20 20 20 20 8 10` | `count = 5; sum = 88; min = 8; max = 20` | `count = 5; sum = 88; min = 8; max = 20` | `count = 5; sum = 88; min = 8; max = 20` | YES | Near-miss: x == 2*count (8 at count 4) and sum > 50, but count < 5 |
| 3 | `20 20 20 20 20 11 12` | `count = 6; sum = 111; min = 11; max = 20` | `count = 6; sum = 111; min = 11; max = 20` | `count = 6; sum = 111; min = 11; max = 20` | YES | Near-miss: count >= 5 and sum > 50, but x = 11 != 2*count = 10 |
| 4 | `1 1 1 1 1 10 12 14 16 18` | `count = 9; sum = 57; min = 1; max = 16` | `count = 9; sum = 57; min = 1; max = 16` | `count = 9; sum = 57; min = 1; max = 16` | YES | Near-miss: count >= 5 and x == 2*count (10, 12, 14, 16), but sum <= 50 |
| 5 | `10 10 10 10 10 10 12` | `count = 6; sum = 60; min = 10; max = 10` | `count = 6; sum = 60; min = 10; max = 10` | `count = 6; sum = 60; min = 10; max = 10` | YES | Boundary: sum is exactly 50 (not > 50), then stops at x = 12 |
| 6 | `11 10 10 10 10 10` | `count = 5; sum = 51; min = 10; max = 11` | `count = 5; sum = 51; min = 10; max = 11` | `count = 5; sum = 51; min = 10; max = 11` | YES | Boundary: sum is exactly 51 (> 50), stops at the earliest moment |
| 7 | `30 5 40 8 7 9 6 14` | `count = 7; sum = 105; min = 5; max = 40` | `count = 7; sum = 105; min = 5; max = 40` | `count = 7; sum = 105; min = 5; max = 40` | YES | Min and max are in the middle of the sequence |
| 8 | `6 6 6 6 6 6 6 6 6 18` | `count = 9; sum = 54; min = 6; max = 6` | `count = 9; sum = 54; min = 6; max = 6` | `count = 9; sum = 54; min = 6; max = 6` | YES | Terminating x is larger than every processed value (not used for max) |
| 9 | `0 0 0 0 0 100 12` | `count = 6; sum = 100; min = 0; max = 100` | `count = 6; sum = 100; min = 0; max = 100` | `count = 6; sum = 100; min = 0; max = 100` | YES | Zeros are processed, so min = 0 must be handled |
| 10 | `3 9 4 8 5 7 6 7 6 5 20` | `count = 10; sum = 60; min = 3; max = 9` | `count = 10; sum = 60; min = 3; max = 9` | `count = 10; sum = 60; min = 3; max = 9` | YES | Longer run; x == 2*count at count 2 is ignored because count < 5 |

The stop condition has three parts, so the tests include near-misses where each part fails on its own (tests 2, 3 and 4) and exact boundary values for `sum > 50` (tests 5 and 6). Test 1 checks the earliest possible stop.

## Bash test runner

[`run_tests.sh`](run_tests.sh) uses the Bash shebang `#!/usr/bin/bash`, compiles both programs with GCC, runs the same ten tests listed above (the input is piped in, nothing is typed manually), and prints the input, expected output, actual outputs and `PASS`/`FAIL` for each test. It finishes with a summary and exits with a non-zero status if any test fails. The programs print their messages for a person to stderr; the script hides them with `2>/dev/null`, so only the results on stdout are compared.

Run it from a Linux terminal:

```bash
bash run_tests.sh
```

The file [`run_tests_output.txt`](run_tests_output.txt) contains an actual successful run, created with:

```bash
bash run_tests.sh > run_tests_output.txt
```