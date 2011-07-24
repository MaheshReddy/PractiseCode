#include"../CommonLib/CommonLib.h"
using namespace std;
class EmployeeTownInfo
{
  public:
    int numberOfEmployees;
    int *buffer;
    EmployeeTownInfo(void); 
};
EmployeeTownInfo::EmployeeTownInfo(void)
{
  numberOfEmployees=0;
  buffer =  NULL;
}
int main(int argc , char **argv)
{
   if (argc !=2)
   {
       cout<<"Usage ./a.out input-file"<<endl;
       return 1;
   }
   char ch;
   int lineNumber=0;
   vector<string> fileContents=readInputFile(argv[1]);
   int inputSize=atoi(fileContents[lineNumber++].c_str());
   for (int i =0 ; i < inputSize;i++)
   {
       int N=0,T=0,E=0;
       vector<int> tokens;
       Tokenize(fileContents[lineNumber++],tokens);
       N=tokens[0]+1;
       T=tokens[1];
       E=atoi(fileContents[lineNumber++].c_str());
       EmployeeTownInfo distribution[N];
       ostringstream result;
       for (int j =0;j < E;j++)
       {
         tokens.clear();
         Tokenize(fileContents[lineNumber++],tokens);
         int town=-1,capacity=-1;
         town=tokens[0];
         capacity=tokens[1];
         if (town == T)
           continue;
         if (distribution[town].buffer == NULL)
         {
           //distribution[town].buffer = (int *)malloc((sizeof(int)*E));
           distribution[town].buffer = new int [E];
           for (int i=0;i<E;i++)
             distribution[town].buffer[i]=0;
         }
         distribution[town].numberOfEmployees++;
         insertInOrder(distribution[town].buffer,capacity,E);
       }
       //cout<<N<<"\t"<<T<<"\t"<<E<<"\n";
       cout<<"Case #"<<i+1<<":";
       for (int j=1;j<N;j++)
       {
         int currentCapacity=0;
         int k=0;
         for (k=0;k< E;k++)
         {
           if(currentCapacity >= distribution[j].numberOfEmployees)
             break;
           currentCapacity=currentCapacity + distribution[j].buffer[k];
         }
         if(currentCapacity < distribution[j].numberOfEmployees)
         {
           result.str("");
           result<<" IMPOSSIBLE";
           break;
         }
         else
           result<<" "<<k;
         if (distribution[j].buffer!=NULL)
               free(distribution[j].buffer); 
       }
       cout << result.str()<<"\n";
   } 
       return 0;
}
