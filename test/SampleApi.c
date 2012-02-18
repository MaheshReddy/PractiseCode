#include <stdio.h>

struct greet_api
{
     int (*say_hello) (char *name);
     int (*say_goodbye) (void);
};

int sayHello(char * name)
{
  printf("Hi %s\n",name);
  return 0;
}
int sayGoodBye(void)
{
  printf("bye");
  return 0;
}

int i=1;
struct greet_api mahesh = {.say_hello = sayHello ,.say_goodbye = sayGoodBye};

int main(int argc,char **argv)
{
if (argc == 2)
    mahesh.say_hello(argv[1]);
printf("%p, %p, %p , %p\n", mahesh.say_hello, sayHello, &sayHello,mahesh.say_hello);
printf("%d",i);
 return 0;
}
