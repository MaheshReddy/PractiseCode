#include<stdio.h>
#include<iostream>
using namespace std;
void printer(char* a){
		int i;
		printf("%s\n",a);
}
/*recursive permute function
Semantics:
a - array which holds the present permutation of size n

k - present slot in the array a. we have a permutation when k==n
if k < n , we are still building our permutation.

We can think of the permutation result as
a row of n slots, holding a number between 1 and n 

(if we want permutations from another array b, we can think of
it as holding b[1] to b[n] ..the logic is the same)

if we don't want them to repeat, we need to maintain
state of our computations in the array called 'selected'.

 */
void permute(char *a,char *b,int n,int k,int *selected){
		if(k==n){
				printer(b);
				return;
		}
		int i;
		for(i=0;i<n;i++){
				if(!selected[i]){
						b[k]=a[i]; //alternately, a[k]=f(i) , here f(i)=i+1.
						//essentially, the i'th value from a list.
						selected[i]=1;
						permute(a,b,n,k+1,selected); //fill up from the next index
						selected[i]=0; //backtrack
				}
		}
}
int main(void){
		char a[10]={"mahesh"};
		char b[10]={""};
		//int i;
		int selected[10]={0};
		permute(a,b,6,0,selected);
		return 0;
}
