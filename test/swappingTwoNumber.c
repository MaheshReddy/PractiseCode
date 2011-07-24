#include<stdio.h>
#include<error.h>
#include<stdlib.h>
int main(int argc , char **argv)
{
    if (argc !=3)
        error(1,0,"Usage ./a.out 2 3");
   
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    
    printf("original numbers are %d\t%d\n",a,b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("Swapped numbers are %d\t%d\n",a,b);
    return 0; 
}
