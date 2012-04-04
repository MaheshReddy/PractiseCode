/**
  C implementation of Linked List.
  I hope it performs better. Exited to write it:)
  */

#include<stdio.h>
#include<ll.h>
#include<stdlib.h>
#include<math.h>

struct ll_node* ll_insert(struct ll_node* ll_head,int new_data){
	if(NULL == ll_head){
		ll_head = (struct ll_node*) malloc(sizeof(struct ll_node));
		ll_head->ll_data = new_data;
		ll_head->ll_next = NULL;
	}
	else
		ll_head->ll_next = ll_insert(ll_head->ll_next,new_data);
	return ll_head;
}

struct ll_node* ll_delete(struct ll_node* ll_head, int new_data){
	if(NULL == ll_head)
		return NULL;
	if(ll_head->ll_data == new_data){
		struct ll_node* ll_next = ll_head->ll_next;
		free(ll_head);
		return ll_next;
	}
	else
		ll_head->ll_next = ll_delete(ll_head->ll_next,new_data);
	return ll_head;
}

void ll_print(struct ll_node* ll_head){
	while(NULL != ll_head){
		printf("%d->",ll_head->ll_data);
		ll_head = ll_head->ll_next;
	}
	printf("NULL\n");
}

int ll_size(struct ll_node* ll_head){
	int size=0;
	while( NULL != ll_head){
		size++;
		ll_head = ll_head->ll_next;
	}
	return size;
}

inline struct ll_node* ll_traverse(struct ll_node* ll_head,int size){
	while(ll_head != NULL && size-- > 0)
		ll_head = ll_head->ll_next;
	return ll_head;
}

struct ll_node* ll_merge(struct ll_node* ll_left,struct ll_node* ll_right, int left_size,int right_size){
	if(left_size == 0)
		return ll_right;
	else if(right_size == 0)
		return ll_right;
	struct ll_node* ll_sorted = NULL;
	while( left_size > 0 || right_size >0 ){
		struct ll_node* trav;
		if(ll_sorted == NULL)
		{
			ll_sorted = (struct ll_node*)malloc(sizeof(struct ll_node));
			trav = ll_sorted;
		}
		else{
			trav->ll_next = (struct ll_node*)malloc(sizeof(struct ll_node));
			trav = trav->ll_next;
		}
		if(left_size > 0 && right_size >0){
			if( ll_left->ll_data < ll_right->ll_data)
				goto assign_left;
			else
				goto assign_right;
		}
		if(left_size == 0)
			goto assign_right;
		else if(right_size == 0 )
			goto assign_left;
assign_left:
		trav->ll_data = ll_left->ll_data;
		ll_left = ll_left->ll_next;
		left_size--;
		continue;
assign_right:
		trav->ll_data = ll_right->ll_data;
		ll_right = ll_right->ll_next;
		right_size--;
		continue;
	}
	//TODO need to free ll_left && ll_right , care fully
	return ll_sorted;
}


struct ll_node* ll_merge_sort(struct ll_node* ll_head, int size){
	if(0 == size)
		return NULL;
	else if( 1 == size)
		return ll_head;
	int left_size = floor((float)size/2.0);
	int right_size = ceil((float)size/2.0);
	struct ll_node* ll_sorted_left = ll_merge_sort(ll_head, left_size);
	struct ll_node* ll_sorted_right = ll_merge_sort(ll_traverse( ll_head, left_size), right_size);
	struct ll_node* ll_sorted_list = ll_merge(ll_sorted_left,ll_sorted_right,left_size,right_size);
	return ll_sorted_list;
}

