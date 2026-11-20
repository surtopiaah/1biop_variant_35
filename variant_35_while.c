/* var: 35
stop when count >= 5,
x == 2 * count and sum > 50
print the count, sum, min, max
*/

/* adding the  part that makes sense to me, eventhough it is not asked to:
(had to figure it out with an extra library):
-- added an interactive version to know whether i am inputing correct type:
--  */

#include <stdio.h>
#include <unistd.h> // for isatty

// return 1 or 0, depending if the input has ended
// if the input is not an integer, the rest of that line is thrown away and the program asks again

static int read_int(int *x, int prompt)
{
    int r;
    int c;

    while ((r = scanf("%d", x)) != 1){
        if (r == EOF) {
            return 0;
        }
        if(prompt) {
            fprintf(stderr, "That is not an integer, please try again: ");
        }
        while ((c = getchar()) != '\n' && c != EOF){ // "\n" - makes it a string, '\n' - makes it a 1 character
            // SKIP THE WRONG TEXT
        }
        if (c == EOF){
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int x = 0;
    int count = 0;
    long long sum = 0; // changed from int to long long
    int min = 0;
    int max = 0;
    int ok; // 1 if the number was read successfully
    int prompt = isatty(0); // 1 if a person types, 0 if input it piped
  
    if (prompt){
        fprintf(stderr, "Enter all integers on ONE line, separated by spaces, then press Enter \n");
        fprintf(stderr, "The program stops by itself when the stop rule is met \n");
    }

    // read the first input before the loop
    ok = read_int(&x, prompt);

    
    // The loop repeats while the stop condition is false
    while(ok && !(count >= 5 && x == 2 * count && sum > 50)){
        if (count == 0 || x < min) min = x;
        if (count == 0 || x > max) max = x;
        count++;
        sum += x;
        ok = read_int(&x, prompt);
    }
    
    printf("count = %d\n", count);
    printf("sum = %lld\n", sum); // changed from %d to %lld
    printf("min = %d\n", min);
    printf("max = %d\n", max);

    return 0;
}

