#include<math.h>
#include<stdio.h>
#include<stdlib.h>

inline long no_digits(long n){
	long count = 0;
	while(n){
		count++;
		n = n /10;
	}
	return count;
}

long digit_list(long n,long **list){
	long size = no_digits(n);
	(*list) = (long *)malloc(sizeof(long)*size);
	long i=0;
	for(i=0;i<size;i++){
		(*list)[i] = n % 10;
		n = n / 10;
	}
	return size;
}

long list_to_num(long *list,long size){
	long num = 0,i;
	for(i=0;i<size;i++){
		num = num + list[i]*pow((double)10,i);
	}
	return num;
}

int main(long argc , char **argv)
{
   char ch;
   long lineNumber=0;
   long inputSize=0,i;
   scanf("%lu",&inputSize);
   long *input = (long *)malloc(sizeof(long)*inputSize);
   for(i=0;i<inputSize;i++)
	   scanf("%lu",&(input[i]));

   for (i =0 ; i < inputSize;i++)
   {
	   long num=0,*list,size,j=0;
	   num = input[i];
	   size = digit_list(num,&list);
	   for(j=0;j<size/2;j++){
		   list[j] = list[(size-1) - j];
	   }

	   long palin_num = list_to_num(list,size);
	   if (palin_num <= num){
		   if (!(size % 2)){
		   	list[size/2]++;
			list[size/2 -1]++;
		   }
		   else
			   list[size/2]++;
	   }
	   for (j=0;j<size;j++){
		   printf("%lu",list[j]);
	   }
	   printf("\n");
   }
   return 0;
}
