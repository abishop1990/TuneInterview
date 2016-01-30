/*
 * factorial.c
 *
 * Program to compute the factorial of a number
 *
 * Written by Alan Bishop 1/28/2016
 */

#include <stdio.h>
#include <stdlib.h>

/* Simple recursive version with negative error handling
 * Because of C's type limitations, we can only get up to about 64! here
 * No point in optimizing further since this is so fast, and we can't get big x values anyway
 */
unsigned long long factorial(int x) 
{
    if(x <= 1) return 1;
    unsigned long long result = x * factorial(x-1);
    return result;
}


//Mainline test program
int main(int argc, char * argv []) 
{
    int x;

    //This isn't super error checked, but it is a toy problem...
    if(argc < 2) {
        printf("Enter x value:");
        scanf("%d", &x);
    }
    else  x = atoi(argv[1]); 

    //This breaks about here due to number size, so let's error out there
    if(x > 64) printf("x value %d is too high for this program, sorry :(\n");

    printf("%d! = %llu\n", x, factorial(x));

    return 0;
}
