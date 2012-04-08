/**
  C implementation of Linked List.
  I hope it performs better. Exited to write it:)
  */

#include<stdio.h>
#include<ll.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define LL_APPEND(ll_head,ll_node) { \
	while(ll_head->ll_next != NULL )\
		ll_head = ll_head->ll_next;\
	ll_head->ll_next = ll_node;\
	ll_node->ll_next = NULL;\
}


struct ll_node* ll_insert(struct ll_node* ll_head, int new_data){
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
	struct ll_node* ll_sorted = NULL;
	while( left_size > 0 || right_size >0 ){
		struct ll_node* trav;
		if(ll_sorted == NULL)
		{
			ll_sorted = (struct ll_node*)calloc(1,sizeof(struct ll_node));
			trav = ll_sorted;
		}
		else{
			trav->ll_next = (struct ll_node*)calloc(1,sizeof(struct ll_node));
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
	return ll_sorted;
}


struct ll_node* ll_merge_sort(struct ll_node* ll_head, int size){
	if(0 == size)
		return NULL;
	else if( 1 == size)
		return ll_merge(ll_head,ll_head,1,0);
	int left_size = size/2;
	int right_size = size -left_size;
	///printf("->%d %d %d\n",left_size,right_size,size);
	struct ll_node* ll_sorted_left = ll_merge_sort(ll_head, left_size);
	struct ll_node* ll_sorted_right = ll_merge_sort(ll_traverse( ll_head, left_size), right_size);
	struct ll_node* ll_sorted_list = ll_merge(ll_sorted_left,ll_sorted_right,left_size,right_size);
	printf("%d %d %d\n",left_size,right_size,size);
	ll_delete_list(ll_sorted_right);
	ll_delete_list(ll_sorted_left);
	return ll_sorted_list;
}


struct ll_node* ll_reverse_recurse(struct ll_node* ll_head){
	if(ll_head == NULL)
		return NULL;
	else if(ll_head->ll_next == NULL)
		return ll_head;
	struct ll_node* ll_reversed = ll_reverse_recurse(ll_head->ll_next);
	ll_head->ll_next->ll_next = ll_head;
	ll_head->ll_next = NULL;
	//LL_APPEND(trav,ll_head);
	return ll_reversed;
}

void ll_delete_list(struct ll_node* ll_head){
	while(ll_head != NULL){
		printf("%d ",ll_head->ll_data);
		struct ll_node* tmp = ll_head->ll_next;
		free(ll_head);
		ll_head = tmp;
	}
	printf("\n");
}

struct ll_node* ll_reverse_iter(struct ll_node* ll_head){
	if (ll_head == NULL)
		return ll_head;
	struct ll_node *prev, *cur, *next;
	prev = NULL;
	cur = ll_head;
	next = ll_head->ll_next;

	while(next != NULL){
		cur->ll_next = prev;
		prev = cur;
		cur = next;
		next = next->ll_next;
	}
	cur->ll_next = prev;
	return cur;
}
