#include<stdio.h>

#define a 100
#define b 200

//typedef enum {
//a,b,c,g
//} mahesh;


int main ()
{
  printf("%d\n",a);
  printf("%d\n",b);
  enum mahesh {A,B};
  printf("%d\n",mahesh(0));
  printf("%d\n",B);
}

