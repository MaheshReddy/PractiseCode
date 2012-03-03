#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define debug 1
typedef struct Bst{
	int data;
	int height;
	struct Bst * left;
	struct Bst * right;
}bst;


inline int maxHeight(bst* left,bst* right){
	if(left == NULL && right == NULL)
		return -1;
	else if (NULL == left)
		return right->height;
	else if (NULL == right)
		return left->height;
	else
		return left->height > right->height ? left->height: right->height;
}

inline int getDiff(bst* head){
	if(head == NULL)
		return -1;
	else
		return head->height;
}

bst * bstInsert(bst* head ,int inData)
{
	if (NULL == head)
	{
		head = (bst*)malloc(sizeof(bst));
		head->left=NULL;
		head->right=NULL;
		head->data = inData;
		head->height = 0;
		return head;
	}
	else if(inData > head->data)
		head->right=bstInsert(head->right,inData);
	else
		head->left=bstInsert(head->left,inData);
	head->height = 1 + maxHeight(head->left,head->right);
	return head;
}

int maxElement(bst *head)
{
	if(head->right == NULL)
		return head->data;
	else 
		return maxElement(head->right);
}

int minElement(bst *head)
{
	if(head->left == NULL)
		return head->data;
	else
		return minElement(head->left);
}

void bstInOrder(bst *head)
{
	if(head==NULL)
		return;
	bstInOrder(head->left);
	printf("(%d,%d)",head->data,head->height);
	bstInOrder(head->right);
}

void bstPreOrder(bst *head)
{
	if(head==NULL)
		return;
	printf("(%d,%d)",head->data,head->height);
	bstPreOrder(head->left);
	bstPreOrder(head->right);
}


void bstPostOrder(bst *head)
{
	if(head==NULL)
		return;
	bstPostOrder(head->left);
	bstPostOrder(head->right);
	printf("(%d,%d)",head->data,head->height);
}

int bstSearch(bst *head,int data){
	if(NULL == head)
		return 0;
	if(head->data == data)
		return 1;
	if(data > head->data)
		return bstSearch(head->right,data);
	else 
		return bstSearch(head->left,data);
}

bst * bstDelete(bst *head,int data){
	if(NULL == head)
		return NULL;
	if(data > head->data)
		head->right = bstDelete(head->right,data);
	else if (data < head->data)
		head->left = bstDelete(head->left,data);
	else{
		// Found it
		if(head->left ==NULL && head->right == NULL){
			free(head);
			return NULL;
		}
		else if (head->left != NULL){
			int leftMax = maxElement(head->left);
			if(debug)
				printf("deleting leftMax:%d\n",leftMax);
			head->data  = leftMax;
			head->left  = bstDelete(head->left,leftMax);
		}
		else if (head->right != NULL){
			int rightMin = minElement(head->right);
			if(debug)
				printf("deleting rightMin:%d\n",rightMin);
			head->data = rightMin;
			head->right = bstDelete(head->right,rightMin);
		}
	}
	head->height = maxHeight(head->left,head->right) + 1;
	return head;
}

bst * bstAvlInsert(bst * head,int data)
{
	if(NULL == head)
	{
		head = (bst *)malloc(sizeof(bst));
		head->left = head->right = NULL;
		head->data = data;
		head->height = maxHeight(head->left,head->right)+1;
	}
	else if (data < head->data){
		head->left = bstAvlInsert(head->left,data);
		if ( height(head->left) - height(head->right))
	}

	else 
		head->right = bstAvlInsert(head->right,data);
}

int main(int argc,char **argv)
{
	bst  *head=NULL;
	head=bstInsert(head,1);
	head=bstInsert(head,4);
	head=bstInsert(head,2);
	head=bstInsert(head,7);
	head=bstInsert(head,9);
	head=bstInsert(head,6);
	head=bstInsert(head,5);
	head=bstInsert(head,8);
	printf("Done Inserting\n");
	if(bstSearch(head,7))
		printf("true\n");
	if(!bstSearch(head,100))
		printf("false\n");
	int maxElem = maxElement(head);
	int minElem = minElement(head->right);
	printf("max:%d and min:%d\n",maxElem,minElem);
	bstPreOrder(head);
	printf("\n");
	bstPostOrder(head);
	printf("\n");
	bstInOrder(head);
	printf("\n");
	head = bstDelete(head,7);
	bstInOrder(head);
	printf("\n");
	head = bstDelete(head,1);
	bstInOrder(head);
	printf("\n");
	head = bstDelete(head,9);
	bstInOrder(head);
	printf("\n");
	head = bstDelete(head,2);
	bstInOrder(head);
	printf("\n");
	return 1;
}
