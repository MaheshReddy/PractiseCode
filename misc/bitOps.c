#include<stdio.h>
#include<stdlib.h>
int* global ;
int addBitWise(int a,int b){
	
	while(b){
		int c = a & b; // My carry bit that I will add later
		a = a ^ b; // My sum without carry bit
		b = c << 1;
	}
	return a;
}

inline int testMsb(int a){
	int bitsToShift = sizeof(a) * 8;
	return a >> 31;
}

int minWithoutCmpr(int a,int b){
	if(testMsb(a-b))
		return a;
	else
		return b;
}
/**
  First we set the first byte if its zero we skip the entire byte.
*/ 
int no_set_bits(int n){
	char *ch;
	ch = (char *)&n;
	int i=0,count=0,j=0;
	for(i=0;i<sizeof(int);i++){
		if( ! *ch )
			continue;
		int tester = 1;
		for(j=0;j<8;j++){
			tester = tester << 1;
			if ((*ch) & tester)
				count++;
		}
		ch++;
		printf("\n");
	}
	return count;
}
int no_set_bits_1(int n){
	int count=0;
	while(n){
		count++;
		n = n & n-1;
	}
	return count;
}



int main(int argc, char** argv){
	global = (int *)malloc(sizeof(int));
	volatile char* mahesh;
	if(argc<3){
		printf("usage ./a.out arg1 arg2\n");
		return -1;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("Sum of %d %d:%d\n",a,b,addBitWise(a,b));
	printf("Min of %d %d is:%d\n",a,b,minWithoutCmpr(a,b));
	printf("No of setsbits of %d is %d\n",a,no_set_bits(a));
	printf("No of setsbits of %d is %d\n",a,no_set_bits_1(a));
	return 0;
}
