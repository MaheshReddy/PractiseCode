#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

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


/**
   Heap Sort
  **/

#define HEAP_PARENT(i) i%2?i/2:i/2-1

#define HEAP_INIT(heap,size){\
	(heap)->heap_size = size;\
	(heap)->heap_cursize=0;\
	(heap)->heap_arr=NULL;\
}

#define HEAP_LEFT(i) 2i+1
#define HEAP_RIGHT(i) 2i+2

struct heap{
	int heap_size;
	int heap_cursize;
	int *heap_arr;
};

void heap_build(struct heap* heap, int *arr,int size){
	if (heap == NULL || arr == NULL)
		return;
	if (heap->heap_arr == NULL)
		heap->heap_arr = (int *)malloc(sizeof(int)*(heap->heap_size));
	if (heap->heap_size < size)
		return;
	memcpy((void*)heap->heap_arr,(void*)arr,size*sizeof(int));
	heap->heap_cursize = size;
	int i=0;
	for (i=size-1;i>0;i--){
		if (heap->heap_arr[i] < heap->heap_arr[HEAP_PARENT(i)]){
			swap(&heap->heap_arr[i],&heap->heap_arr[HEAP_PARENT(i)]);
		}
	}
}


void heap_push_up(struct heap* heap,int pos){
	if (heap == NULL)
		return;
	if (pos > heap->heap_cursize)
		return;
	while (pos){
		if (heap->heap_arr[pos] < heap->heap_arr[HEAP_PARENT(pos)]){
			swap(&(heap->heap_arr[pos]),&(heap->heap_arr[HEAP_PARENT(pos)]));
			pos = HEAP_PARENT(pos);
		}
		else
			break;
	}
}

void heap_insert(struct heap* heap,int num){
	if (heap == NULL)
		return;
	if (heap->heap_size <= heap->heap_cursize)
		return;
	heap->heap_arr[heap->heap_cursize++] = num;
	heap_push_up(heap,heap->heap_cursize-1);
}
/*
void heap_push_down(struct heap* heap,int pos){
	if (head == NULL)
		return;
	int left_pos = HEAP_LEFT(pos), right_pos = HEAP_RIGHT(pos), size = heap->heap_cursize;
	while ((right_pos < size) && pos < size){
		if ( heap->heap_arr[left_pos] < heap->heap_arr[pos])
	}
}
*/

void heap_delete(struct heap* heap,int pos){
	heap->heap_arr[pos]=heap->heap_arr[heap->heap_cursize--];
	heap_push_down(heap,pos);
}

int heap_min_elem(struct heap* heap,int *min){
	if (heap == NULL)
		return -1;
	*min = heap->heap_arr[0];	 
	heap_delete(heap,0);
}


int main(){
	int a[10] = {5,6,1,2,3,8,7,11,10,20},i=0;
	struct heap heap;
	HEAP_INIT(&heap,12);
	heap_build(&heap,a,10);
	heap_insert(&heap,4);
	heap_insert(&heap,0);
	for(i=0;i<12;i++){
		printf("%d ",heap.heap_arr[i]);
	}
}
