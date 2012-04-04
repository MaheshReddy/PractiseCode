#ifndef LL_NODE
#define LL_NODE


struct ll_node {
	int ll_data;
	struct ll_node* ll_next;
};

struct ll_node* ll_insert(struct ll_node* ll_head,int new_data);

struct ll_node* ll_delete(struct ll_node* ll_head, int new_data);

void ll_print(struct ll_node* ll_head);

int ll_size(struct ll_node* ll_head);

struct ll_node* ll_merge(struct ll_node* ll_left,struct ll_node* ll_right, int left_size,int right_size);

struct ll_node* ll_merge_sort(struct ll_node* ll_head, int size);

#endif
