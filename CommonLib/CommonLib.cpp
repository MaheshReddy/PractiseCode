#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <sstream> 
#include <cctype>
#include <stdlib.h>
#include "CommonLib.h"
using namespace std;

vector<string> readInputFile(char *filename,int flag)
{
    string line;
    vector<string> content;
    ifstream fileStream(filename);
    if (fileStream.is_open())
    {
		if(flag & READ_LINES)
		{
        while(!fileStream.eof())
        {
        getline(fileStream,line);
        content.push_back(line);
        }
		}
		else if (flag & READ_WORDS)
   		{
			while(fileStream >> line)
			{
				content.push_back(line);
			}
		} 

    }
    else 
        cout<<"File not found\t"<<"\t"<<endl;
    return content;
}
//void Tokenize(const string& str,
//                      vector<int>& tokens,
//                      const string& delimiters = " ")
//{
//    // Skip delimiters at beginning.
//    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
//    // Find first "non-delimiter".
//    string::size_type pos     = str.find_first_of(delimiters, lastPos);
//
//    while (string::npos != pos || string::npos != lastPos)
//    {
//        // Found a token, add it to the vector.
//        tokens.push_back(atoi(str.substr(lastPos, pos - lastPos).c_str()));
//        // Skip delimiters.  Note the "not_of"
//        lastPos = str.find_first_not_of(delimiters, pos);
//        // Find next "non-delimiter"
//        pos = str.find_first_of(delimiters, lastPos);
//    }
//}
void printVector(vector<string> tokens)
{
    for(vector<string>::size_type i=0; i < tokens.size();i++)
    {
        cout << tokens[i]<<" ";
    }
}
void insertInOrder(int* &array,int a , int len)
{
   for(int i=0;i<len;i++)
   {
     if (array[i]<=a)
     {
         for(int j=len-1;j>i;j--)
           array[j]=array[j-1];
         array[i]=a;
         break ;
     }
   }
}
