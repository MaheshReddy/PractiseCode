#include<iostream>
#include<math.h>
#include"ll.h"

using namespace std;


template <class myType>
class list{
	public:
	myType data;
	class list* child;
	int size;
	list(void)
	{
		size=0;
		child=NULL;		
	}
	list(myType data1)
	{
		size=1;
		data=data1;
		child=NULL;		
	}
	void addElement(myType data);
	void removeElement(myType data);
	void print(void);
};
template <class myType>
list<myType>* merge_sort_lst(list<myType>* head,int size);

template <class myType>
void list<myType>::addElement(myType data)
{
	list<myType> *traverser= (this);
	size++;
	while(traverser->child!=NULL )
		traverser=traverser->child;
	traverser->child = new list(data);
	traverser->child->child=NULL;
}

template <class myType>
void list<myType>::removeElement(myType data1)
{
	list<myType> *traverser= (this);
	list<myType> *backUpGuy;
	size--;
	if(data==data1)//removing the head .. so sad need to find another :(
	{	
		if(child!=NULL)//copy the child data into my data and sacrifice the firstborn 
		{
			data=child->data;
			backUpGuy=child->child;
			delete child;
			child=backUpGuy;
		}
		else // else return black hole
			data=NULL;
		return;
	}
	while( traverser->child != NULL && traverser->child->data != data1)// traverse the list till you find meaning of ur damm life
		traverser=traverser->child;
	if (traverser->child==NULL)
		return;
	if(traverser->child->data==data1)
	{
		backUpGuy=traverser->child->child;
		delete traverser->child;
		traverser->child=backUpGuy;
	}
}


template <class myType>
void list<myType>::print(void)
{
	list<myType> *traverser= (this);
	while(traverser!=NULL)
	{	
		cout<<traverser->data<<"\t";
		traverser=traverser->child;
	}
	cout<<endl;
}

template<class myType>
inline list<myType>* traverse(list<myType>* head,int size){
	while(NULL != head & size-- > 0)
		head = head->child;
	return head;
}

template<class myType>
list<myType>* merge_list(list<myType>* left,list<myType>* right,int l_size,int r_size){
	if(NULL == left && NULL == right)
		return NULL;
	if(l_size == 0 && r_size == 0)
		return NULL;
	else if (NULL == left || l_size==0 )
		return right;
	else if(NULL == right || r_size ==0 )
		return left;
	list<myType>* merge_list = NULL;

	//while(NULL != left || NULL != right){
	while(l_size > 0 || r_size > 0){
		list<myType>* trav = new list<myType>();
		if(NULL == merge_list)
			merge_list = trav;

		if(NULL != left && NULL != right){
			if(left->data < right->data){
				trav->data = left->data;
				left = left->child;
				l_size--;
			}
			else{
				trav->data = right->data;
				left = left->child;
				r_size--;
			}
			trav = trav->child;
		}
		//else if (NULL == left){
		else if (l_size == 0){
			trav->data = right->data;
			trav = trav->child;
			right = right->child;
			r_size--;
		}
		else if(r_size ==0){
			trav->data = left->data;
			trav = trav->child;
			left = left->child;
			l_size++;
		}
	}
	return merge_list;
}

template <class myType>
list<myType>* merge_sort_lst(list<myType>* head,int size){
	if(NULL == head || 0 == size)
		return NULL;
	else if(size == 1)
		return head;

	list<myType>* sorted_left = merge_sort_lst(head,floor(size/2));
	list<myType>* sorted_right = merge_sort_lst(traverse(head,floor((float)size/2.0)),ceil((float)size/2.0));
	cout<<"left:"<<floor((float)size/2.0)<<":";
	sorted_left->print();
	cout<<"right:"<<ceil((float)size/2.0)<<":";
	sorted_right->print();
	list<myType>* sorted_head = merge_list(sorted_left,sorted_right,floor(size/2),ceil((float)size/2.0));
	return sorted_head;
}
/*
int main()
{
	class list <char>sll('a');
	sll.addElement('a');
	//sll.addElement('b');
	sll.addElement('c');
	//sll.addElement('d');
	//sll.addElement('e');
	//sll.addElement('f');
	sll.addElement('g');
	sll.print();
	sll.removeElement('a');
	sll.print();
	sll.removeElement('a');
	sll.print();
	sll.removeElement('c');
	sll.print();
	sll.removeElement('z');
	sll.print();
	sll.removeElement('g');
	sll.print();
	sll.removeElement('g');
	sll.removeElement('g');
	sll.removeElement('g');
	sll.removeElement('g');
	sll.removeElement('g');
	sll.removeElement('g');
	sll.print();
	sll.print();
	sll.print();
	sll.print();
	sll.print();
	sll.print();
}*/
