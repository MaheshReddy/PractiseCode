#include<stdio.h>
#include<error.h>
#include<stdlib.h>

int main(int argc , char ** argv)
{
   if (argc != 2)
       error(1,0,"Usage ./a.out hexnumber");
   int a = 0x8000;
   int b = atoi(argv[1]);
   int count = 0;
   while (!(b & 0x1))
   { 
       count ++;
       b=b >> 1;
       char c[100];
       dec2bin(b,c);
       printf("%s\n",c);
   }
   printf("The least set bit is %d\n",count);
   return 0;
}

void dec2bin(long decimal, char *binary)
{
  int  k = 0, n = 0;
  int  neg_flag = 0;
  int  remain;
  int  old_decimal;  // for test
  char temp[80];
 
  // take care of negative input
  if (decimal < 0)
  {      
    decimal = -decimal;
    neg_flag = 1;
  }
  do 
  {
    old_decimal = decimal;   // for test
    remain    = decimal % 2;
    // whittle down the decimal number
    decimal   = decimal / 2;
    // this is a test to show the action
    printf("%d/2 = %d  remainder = %d\n", old_decimal, decimal, remain);
    // converts digit 0 or 1 to character '0' or '1'
    temp[k++] = remain + '0';
  } while (decimal > 0);
 
  if (neg_flag)
    temp[k++] = '-';       // add - sign
  else
    temp[k++] = ' ';       // space
 
  // reverse the spelling
  while (k >= 0)
    binary[n++] = temp[--k];
 
  binary[n-1] = 0;         // end with NULL
}
