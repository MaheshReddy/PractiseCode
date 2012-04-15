#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<hashtable.h>

#define LOWER_LIMIT 0
#define UPPER_LIMIT 11

int *non_surprised[UPPER_LIMIT];
void build_matrix_non_surp(int num){
	int i,j;
	int *arr = (int *)malloc;
	for (i= (num-1 < 0?0:num-1) ; i < ((num+2) > UPPER_LIMIT?UPPER_LIMIT: num+2 );i++ )
	{
		for (j= (num-1 < 0?0:num-1) ; i < ((num+2) > UPPER_LIMIT?UPPER_LIMIT: num+2 );i++ ){
		}
	}
}
int main(){
	int no_tc = 0;
	for (i=0;i<UPPER_LIMIT;i++)
		build_matrix_non_surp(i);
	scanf("%d",&no_tc);
}

