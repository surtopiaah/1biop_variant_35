/* var: 35
stop when count >= 5,
x == 2 * count and sum > 50
print the count, sum, min, max
*/ 

#include <stdio.h>

int main(void){
    int x, count, sum, min, max;

    scanf("%d", &x);
    count = 1;
    sum = x;
    min = x;
    max = x;

    while (count < 5) {
        scanf("%d", &x);
        count++;
        sum += x;
        if (x < min) min = x;
        if (x > max) max = x;
    }

    scanf("%d", &x);
    // repeat the body until it's false
    while(!(x == 2 * count && sum > 50)){
        count++;
        sum += x;
        if (x < min) min = x;
        if (x > max) max = x;
        scanf("%d", &x);
    }
    
    printf("count = %d\n", count);
    printf("sum = %d\n", sum);
    printf("min = %d\n", min);
    printf("max = %d\n", max);

    return 0;
}

