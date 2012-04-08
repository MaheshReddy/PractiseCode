#include<iostream>
#include<string>
#include <CommonLib.h>
#include<bst.h>
#include<ll.h>
#include<ll.cpp>
#include<assert.h>
#include<sort.h>
#include<hashtable.h>

using namespace std;

int test_hash(int argc,char **argv){
	int lineNumber=0;
	vector<string> fileContents = readInputFile(argv[2],READ_LINES);
	int inputSize = atoi(fileContents[lineNumber++].c_str());
	struct h_table table;
	h_init(&table,inputSize);
	int r;

	for(int i=0;i<inputSize;i++){
		int value = rand();
		printf("Inserting (%d,%d)\n",atoi(fileContents[i].c_str()),value);
	if((r=h_put(atoi(fileContents[i].c_str()),value,&table))<0)
		printf("Error:");
	}


	for(int i=0;i<inputSize;i++){
	unsigned int ret_value;
	if((r = h_get(atoi(fileContents[i].c_str()),&table,&ret_value) )<0)
		printf("Error:");
	//assert(ret_value == atoi(fileContents[i].c_str()));
	printf("Retrieved (%d,%d)\n",atoi(fileContents[i].c_str()),ret_value);
	}
	
}

int test_bst(int argc,char** argv){
	bst *head = NULL;
	int lineNumber=0;
	vector<string> fileContents = readInputFile(argv[2],READ_LINES);
	int inputSize = atoi(fileContents[lineNumber++].c_str());
	for(int i=0;i<inputSize;i++)
	{
		int num = atoi(fileContents[lineNumber++].c_str());
		//cout<<num<<endl;
		head = bstAvlInsert(head,num);
	}
	bstPreOrder(head,1);
	return 0;
}

int test_sort(int argc, char **argv){
	int lineNumber=0;
	vector<string> fileContents = readInputFile(argv[2],READ_LINES);
	int inputSize = atoi(fileContents[lineNumber++].c_str());
	//int *data = (int *)malloc(sizeof(int)*inputSize);
	int data[inputSize];

	for(int i=0;i<inputSize;i++){
		int num = atoi(fileContents[lineNumber++].c_str());
		data[i] = num;
		printf("%d ",data[i]);
	}
	printf("\n");
	quickSort(&data[0],0,inputSize-1);
	//int *tmp = merge_sort(&data[0],inputSize);
	
	for(int i=0;i<inputSize;i++)
		printf("%d ",data[i]);
	printf("\n");
}

int test_ll(int argc,char** argv){
	struct ll_node* node = NULL;
	int lineNumber=0;
	vector<string> fileContents = readInputFile(argv[2],READ_LINES);
	int inputSize = atoi(fileContents[lineNumber++].c_str());

	for(int i=0;i<inputSize;i++){
		int num = atoi(fileContents[lineNumber++].c_str());
		node = ll_insert(node,num);
	}

	ll_print(node);
	assert(ll_size(node) == inputSize);
	struct ll_node *tmp = node;
	node = ll_merge_sort(node,ll_size(node));
	ll_delete_list(tmp);
	ll_print(node);

	//Reversing list
	node = ll_reverse_recurse(node);
	ll_print(node);

	//reversing list using iter
	node = ll_reverse_iter(node);
	ll_print(node);

	// Testing delete
	lineNumber=0;
	for(int i=0;i<inputSize;i++){
		int num = atoi(fileContents[++lineNumber].c_str());
		node = ll_delete(node,num);
		ll_print(node);
	}
	assert(ll_size(node) == 0);
	//node->print();
	//node = merge_sort_lst(node,node->size);
}

int test_ll_cpp(int argc,char** argv){
	list<int>* node= NULL;
	int lineNumber=0;
	vector<string> fileContents = readInputFile(argv[2],READ_LINES);
	int inputSize = atoi(fileContents[lineNumber++].c_str());
	for(int i=0;i<inputSize;i++){
		int num = atoi(fileContents[lineNumber++].c_str());
		if( NULL == node )
			node = new list<int>(num);
		else
			node->addElement(num);
	}
	//node->print();
	cout<<"Size::"<<node->size<<endl;
	node = merge_sort_lst(node,node->size);
	node->print();
}

int main(int argc,char** argv)
{
	if(argc != 3)
	{
		cout<<"usage: ./a.out MODULE filename.in"<<endl;
		return -1;
	}
	string module(argv[1]);
	if(module == ("bst"))
		test_bst(argc,argv);
	else if(module == "ll")
		test_ll(argc,argv);
	else if(module == "sort")
		test_sort(argc,argv);
	else if(module == "hash")
		test_hash(argc,argv);
	char ch='a';
	while (ch !='e'){
		ch = getchar();
	}
}
