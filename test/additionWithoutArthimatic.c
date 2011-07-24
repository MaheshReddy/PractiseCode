#include<stdio.h>
#include<stdlib.h>

int additionWithoutOperators(int number)
{
    printf("%d\n",number);
    if((number%2)==0)
        number=number | 0x1;
    else{
        int complementNumber=~number;
        int counter=1;
        while( !(complementNumber & counter))
        {
                number= number ^ counter;
                counter=counter<<1;
        }
        number = number | counter;
    }
    printf("\n%d\n",number);

    return number;
}
