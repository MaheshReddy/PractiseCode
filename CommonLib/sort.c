#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int choose_pivot(int start,int end){
	return end;
}

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
/**
  end and start are inclusive.
  **/

//2596 21422 1475 24600 23311
void quickSort(int *arr, int start , int end){
	if ((end - start) < 2)
		return ;
	int pivot = choose_pivot(start,end);
	//swap(arr+pivot,arr+end);
	int trav1,trav2;
	trav1 = trav2 = start;
	while(trav2 < end){
		if (arr[trav2] < arr[end]){
			if(trav2 != trav1)
				swap(arr+trav2,arr+trav1);
				trav1++;
			}
		trav2++;
	}
	swap(arr+trav1,arr+end);
	quickSort(arr,start,trav1-1);
	quickSort(arr,trav1+1,end);
}

int* merge (int *left, int* right,int l_size,int r_size) {
	//printf("%d %d\n",l_size,r_size);
	if ( l_size == 0 && r_size == 0 )
		return NULL;
	int *sorted_array = (int *)malloc(sizeof(int) * (l_size + r_size));
	int l, r,k;
	l = r=k=0;
	while ( l <  l_size || r < r_size ){
		if (l <  l_size && r < r_size  ){
			if (left[l] < right[r])
				sorted_array[k++] = left[l++];
			else
				sorted_array[k++] = right[r++];
		}
		else if ( !(l < l_size) )
			sorted_array[k++] = right[r++];
		else if ( !(r < r_size) )
			sorted_array[k++] = left[l++];
	}
	return sorted_array;
}
/**
  start and end inclusive
  */

int *merge_sort(int *arr, int size){
	if (size == 0){
		return NULL;
	}
	if(size == 1){
		return merge(arr,arr,size,0);
	}
	int half = size / 2;
	int *sorted_left =  merge_sort(arr,half);
	int *sorted_right = merge_sort(arr+half,size - half);
	int *sorted_array = merge(sorted_left,sorted_right,half,size-half);
	if(sorted_left)
		free(sorted_left);
	if(sorted_right)
		free(sorted_right);
	return sorted_array;
}
