#include<stdio.h>

int main(void)
{
  float a = 0.45;
  float b = 8.0;
  
  double ad = 0.45;
  double bd  = 8.0;
 
  printf("float : %10.9f\n",a);
  printf("float+float, 6dp    : %f\n", a+b);
  printf("double+double, 6dp  : %f\n", ad+bd);
  //printf("float+float, 20dp   : %10.20f\n", a+b);
  printf("float+float, 20dp   : %10.1f\n", a+b);
  printf("dobule+double, 20dp : %10.20f\n", ad+bd);
  return 0; 
}
