#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<cctype>
#include<cstring>
#include<sstream>
#define READ_WORDS 0x1
#define READ_LINES 0x2
using namespace std;
vector<string> readInputFile(char *filename,int flag);
void Tokenize(const string& str,
                      vector<int>& tokens,
                      const string& delimiters = " ");
//void printVector(vector<string> tokens);
void insertInOrder(int* &array,int a , int order);
