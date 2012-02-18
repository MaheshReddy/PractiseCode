#include<iostream>

using namespace std;
template <class myType>
class singleLinkedList{
	private:
	myType data;
	class singleLinkedList* child;
	public:
	singleLinkedList(void)
	{
		child=NULL;		
	}
	singleLinkedList(myType data1)
	{
		data=data1;
		child=NULL;		
	}
	void addElement(myType data);
	void removeElement(myType data);
	void print(void);
};

template <class myType>
void singleLinkedList<myType>::addElement(myType data)
{
	singleLinkedList<myType> *traverser= (this);
	while(traverser->child!=NULL )
		traverser=traverser->child;
	traverser->child = new singleLinkedList(data);
	traverser->child->child=NULL;
}

template <class myType>
void singleLinkedList<myType>::removeElement(myType data1)
{
	singleLinkedList<myType> *traverser= (this);
	singleLinkedList<myType> *backUpGuy;
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
void singleLinkedList<myType>::print(void)
{
	singleLinkedList<myType> *traverser= (this);
	while(traverser!=NULL)
	{	
		cout<<traverser->data<<"\t";
		traverser=traverser->child;
	}
	cout<<endl;
}

int main()
{
	class singleLinkedList <char>sll('a');
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
	
}
