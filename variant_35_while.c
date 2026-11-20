/* var: 35
stop when count >= 5,
x == 2 * count and sum > 50
print the count, sum, min, max
*/


#include <stdio.h>

 
// reads one integer into *x
// returns 1 if it did, 0 if the input has ended or is not a number
// *last is set to 1 if x is the last number on its line
static int read_number(int *x, int *last)
{
    int c;
 
    if (scanf("%d", x) != 1) {
        return 0;
    }
    c = getchar();
    while (c == ' ' || c == '\t' || c == '\r') {
        c = getchar(); // skip the spaces after the number
    }
    *last = (c == '\n' || c == EOF);
    if (!*last) {
        ungetc(c, stdin); // c belongs to the next number, put it back
    }
    return 1;
}

int main(void)
{
    int x = 0;

    int count = 0;       // number of already processed values
    long long sum = 0;   // sum of already processed values
    int min = 0;
    int max = 0;
    int ok;              // 1 if a number was read
    int last = 0;        // 1 if x is the last number of its line
 
    fprintf(stderr, "Enter all integers on ONE line, separated by spaces, then press Enter.\n");
 
    // read the first candidate before the loop
    ok = read_number(&x, &last);


    // repeat while the stop condition is false
    while (ok && !(count >= 5 && x == 2 * count && sum > 50)) {
        if (count == 0 || x < min) min = x;
        if (count == 0 || x > max) max = x;
        count++;
        sum += x;
 
        if (last) {
            // the line ended before the stop rule was met: start again from zero
            fprintf(stderr, "That sequence does not meet the stop rule, please try again: ");
            count = 0;
            sum = 0;
            min = 0;
            max = 0;
        }
        ok = read_number(&x, &last);
    }
 
    if (!ok) {
        fprintf(stderr, "\nThe input ended (or is not a number) and no sequence met the stop rule.\n");
        return 1;
    }


    printf("count = %d\n", count);
    printf("sum = %lld\n", sum);
    printf("min = %d\n", min);
    printf("max = %d\n", max);

    return 0;
}

