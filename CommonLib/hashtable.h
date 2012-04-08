#ifndef MY_HASHTABLE
#define MY_HASHTABLE


struct h_entry{
	unsigned int key;
	unsigned int value;
	struct h_entry* ll_next;
};

struct h_table{
	struct h_entry** h_buckets;
	int h_size;
	int (*h_func) (unsigned int key,int size);
};



void h_init(struct h_table* htable,int size);

int h_put(unsigned int key,unsigned int value, struct h_table* table);

int h_get(unsigned int key,struct h_table* table,unsigned int *value);

int h_delete(unsigned int key,struct h_table* table);
#endif
