#include<iostream>
#include<string>
#include <CommonLib.h>
#include<bst.h>
#include<ll.cpp>
#include<ll.h>
#include<assert.h>

using namespace std;

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
	node = ll_merge_sort(node,ll_size(node));
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
		return test_bst(argc,argv);
	else if(module == "ll")
		return test_ll(argc,argv);
}
