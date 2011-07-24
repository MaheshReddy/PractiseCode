#include"CommonLib.h"
#include<stdlib.h>
#include<stdio.h>
template <class myType>
void  divideAndConquer(myType* array, // array to be sorted
        bool(*sortFunction)(myType,myType),//sorting function
        myType* (*mergerFunction)(myType*,myType*),//merging function
        int n)
{
	if (n==1)
		return ;
        else { 
                int r=n/2;// Splitting the array
                int i,j,k;
		myType *leftSortedArray,*rightSortedArray;
		leftSortedArray=(myType *)malloc(sizeof(myType)*(r));
		rightSortedArray=(myType *)malloc(sizeof(myType)*(n-r));
		memcpy((void *)leftSortedArray,(const void *)(array),sizeof(myType)*r);// copying the arrya in two halves 
		memcpy((void *)rightSortedArray,(const void *)(array+r),sizeof(myType)*(n-r));
		mergeSort(leftSortedArray,sortFunction,r);//sorting individual halfs
                mergeSort(rightSortedArray,sortFunction,n-r);
		for (i=0,j=0,k=0;i<r && j <n-r;)//merging two halfs
                {
  			if(sortFunction(leftSortedArray[i],rightSortedArray[j]))
			{
				array[k]=leftSortedArray[i];
				i++;
			}
			else
			{
				array[k]=rightSortedArray[j];
                        	j++;
			}
				k++;
                }
		if (i==r)
			memcpy((void *)(array+k),(const void *)(rightSortedArray+j),sizeof(myType)*(n-r-j));
		else
			memcpy((void *)(array+k),(const void *)(leftSortedArray+i),sizeof(myType)*(r-i));

		free((void *)rightSortedArray);
		free((void *)leftSortedArray);
	}
            
}
bool increasingOrder(int a,int b)
{	
	if (a > b)
		return true;
	else
		return false;
}
bool increasingOrder(char a,char b)
{
	if (a>b)
		return true;
	else 
		return false;
}
int main()
{
	//int a[30]={1,2,24};
	int a[30];
	for (int i=0;i<30;i++){
		a[i]=random()%1000+i;
                printf("%d\t",a[i]);}
        mergeSort<int>(a,&increasingOrder,30);
        printf("\n");
        printf("\n");
	for (int i=0;i<30;i++){
                printf("%d\t",a[i]);}
        printf("\n");
        char c[5]={'a','g','d','b','m'};
	mergeSort <char>(c,&increasingOrder,5);
	for (int i=0;i<5;i++){
                printf("%c\t",c[i]);}
}
