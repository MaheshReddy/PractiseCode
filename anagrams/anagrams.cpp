#include"../CommonLib/CommonLib.h"
using namespace std;
class binomialTree 
{
		private:
				char data;
				vector<binomialTree> childern;
				bool wordEndedHere;
		public:
				binomialTree(){}
				binomialTree(char ch)
				{
						this->data=ch;
						this->wordEndedHere=false;
				}
				void insertString(string str)
				{
						if (str.size()==0){
								this->wordEndedHere=true;
								return;
								}
						for(int i=0;i<childern.size();i++)
						{
								if(childern[i].data == str.at(0))
								{
										childern[i].insertString(str.substr(1,-1));
										return;
								}
						}
						binomialTree child(str.at(0));
						child.insertString(str.substr(1,-1));
						this->childern.push_back(child);
				}
				bool isWordInTree(string str)
				{
						if(str.size()==0)
						{	if(this->wordEndedHere)
								return true;
								else
										return false;
						}
						for(int i=0;i<childern.size();i++)
						{
								if(childern[i].data == str.at(0))
								{
										return childern[i].isWordInTree(str.substr(1,-1));
								}
						}
						return false;

				}
				void print()
				{
						cout<<this->data;
						for(int i=0;i<this->childern.size();i++)
						{
								this->childern[i].print();
						}
						cout<<endl;
				}
				bool isLeaf()
				{
						if (this->childern.size()==0)
								return true;
						else
								return false;
				}

};
void permute(char *a,char *b,int n,int k,int *selected,binomialTree tree,int* count){
		if(k==n){
				//printer(b);
				if (tree.isWordInTree(b))
					*count=*count+1;
				return ;
		}
		int i;
		for(i=0;i<n;i++){
				if(!selected[i]){
						b[k]=a[i]; //alternately, a[k]=f(i) , here f(i)=i+1.
						//essentially, the i'th value from a list.
						selected[i]=1;
						permute(a,b,n,k+1,selected,tree,count); //fill up from the next index
						selected[i]=0; //backtrack
				}
		}
}

int main(int argc , char **argv)
{
		if (argc !=2)
		{
				cout<<"Usage ./a.out input-file"<<endl;
				return 1;
		}
		char ch;
		binomialTree mainTree('+');
		int lineNumber=0;
		vector<string> fileContents=readInputFile(argv[1],READ_WORDS);
		for (int i =0 ; i < fileContents.size();i++)
		{
				cout<<fileContents[i]<<endl;	
				mainTree.insertString(fileContents[i]);
		} 
		mainTree.print();
		if(mainTree.isWordInTree("leader1"))
				cout<<"It runs fine"<<endl;
		int count=0;
		char a[10]={"leader"};
		char b[10]={""};
		int selected[10]={0};
		permute(a,b,6,0,selected,mainTree,&count);	   	
		cout<<count<<endl;
		return 0;
}
