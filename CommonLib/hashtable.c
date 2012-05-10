#include<stdio.h>
#include<hashtable.h>
#include<errno.h>
#include<stdlib.h>

#include<ll.h>


#define E_KEY_NOT_FOUND -1
#define E_INVAL_PARAM -2



int hash_function(unsigned int key, int size){
	return key % size;
}

void h_init(struct h_table* htable,int size){  
	htable->h_buckets = (struct h_entry **)calloc(size,sizeof(struct h_entry *)*size); 		
	(htable)->h_size = size; 
	(htable)->h_func = hash_function;	
}

int h_put(unsigned int key,unsigned int value, struct h_table* table){
	if (table == NULL || table->h_func == NULL)
		return E_INVAL_PARAM;
	int bucket_no = table->h_func(key,table->h_size);
	struct h_entry* entry = (struct h_entry*)calloc(1,sizeof(struct h_entry));
	entry->key = key;
	entry->value = value;
	if( table->h_buckets[bucket_no] == NULL){
		table->h_buckets[bucket_no] = entry;
	}
	else{
		struct h_entry* trav = table->h_buckets[bucket_no];
		while(trav->ll_next != NULL && trav->value != value)
			trav = trav->ll_next;
		trav->ll_next = entry;
	}
	return 0;
}

int h_get(unsigned int key,struct h_table* table,unsigned int *value){
	if (table == NULL || table->h_func == NULL)
		return E_INVAL_PARAM;
	int bucket_no = table->h_func(key,table->h_size);
	struct h_entry* list = table->h_buckets[bucket_no];
	while (list != NULL){
		if (list->key == key){
			*value = list->value;
			return 0;
		}
		list = list->ll_next;
	}
	return E_KEY_NOT_FOUND;
}

