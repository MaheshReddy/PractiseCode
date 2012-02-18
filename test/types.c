#include<stdio.h>
#include<stdint.h>

int main(void)
{
    char *c;
    int i=13;
    //c=i;
    i=(int)c;
    printf("%d\n",sizeof(i));
    printf("%d\n",sizeof(c));
    printf("%d\n",i);
    printf("%p\n",c);
    return 0;
}
