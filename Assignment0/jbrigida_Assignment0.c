/**
 * Joel Brigida
 * CDA-4321: Cryptographic Engineering
 * Assignment 0
 * Due 8/27/2023
 * This program searches for the Greatest Common Denominator between the 2 
 * integers entered bby the user.
*/

#include <stdio.h>

int main()
{
    int n1, n2, i, gcd;
    printf("Enter Two Integers: ");
    scanf("%d %d", &n1, &n2);
    for(i = 1; i <= n1 && i < n2; ++i)
    {
        if(n1 % i == 0 && n2 % i == 0)
        {
            gcd = i;
        }
    }
    printf("G.C.D. of %d and %d is %d\n", n1, n2, gcd);
    return 0;
}