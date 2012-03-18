typedef struct Bst{
	int data;
	int height;
	struct Bst * left;
	struct Bst * right;
}bst;

bst * bstInsert(bst* head ,int inData);
int maxElement(bst *head);
int minElement(bst *head);

void bstInOrder(bst *head,int flag);
void bstPreOrder(bst *head,int flag);
void bstPostOrder(bst *head,int flag);

int bstSearch(bst *head,int data);
bst * bstDelete(bst *head,int data);
bst * bstAvlClckwiseRtn(bst *head);
bst * bstAvlCntrClckwiseRtn(bst *head);
bst * bstAvlInsert(bst * head,int data);
