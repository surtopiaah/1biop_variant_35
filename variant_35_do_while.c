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
#include <unistd.h> // 

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
        while ((c = getchar()) != '\n' && c != EOF){
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
    int stop; // 1 when the loop must end
    int prompt = isatty(0); // 1 if a person types, 0 if input it piped
  
    if (prompt){
        fprintf(stderr, "Enter integers (separated by spaces or in a new line) \n"); 
        fprintf(stderr, "The program stops by itself when the stop rule is met \n"); 
    }


    do {
        // read a candidate first
        ok = read_int(&x, prompt);

         // checks it: stop if the input ended or the stop rule is true
        stop = !ok || (count >= 5 && x == 2 * count && sum > 50);
 
        // only a number that did not stop the loop is processed

        // checks it
        if (!stop){
            if (count == 0 || x < min) min = x;
            if (count == 0 || x > max) max = x;
            count++;
            sum += x;
        }
    } while (!stop);

    printf("count = %d\n", count);
    printf("sum = %lld\n", sum); // changed from %d to %lld
    printf("min = %d\n", min);
    printf("max = %d\n", max);

    return 0;
}