#include"../CommonLib/CommonLib.h"
//#include<cctype>
using namespace std;
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
   //cout <<inputSize<<endl;
   for (int i =0 ; i < inputSize;i++)
   {
       int singleNumber = 0;
       int lineSize = atoi(fileContents[lineNumber++].c_str());
       vector<int> tokens;
       Tokenize(fileContents[lineNumber++],tokens);
       //cout<<lineSize<<"\n";
       //printVector(tokens);
       for (vector<int>::size_type j =0; j < tokens.size();j++) 
       {
         singleNumber = singleNumber ^ tokens[j];
       }
       cout<<"Case #"<<i+1<<": "<<singleNumber<<"\n";
       //copy(tokens.begin(), tokens.end(), ostream_iterator<string>(cout, ", "));
   //    StringToInt(fileContents[lineNumber++],lineSize);
   //    for (int j = 0 ;j < lineSize;j++) 
   //    {
   //        
   //    }
   } 
}
