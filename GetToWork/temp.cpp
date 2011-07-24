#include<iostream>
#include<string>
#include<sstream>
using namespace std;
int main()
{
  string str1("abc");
  string str2("def");
  ostringstream str;
  str<<"abc";
  str<<1;
  cout << str1 + "def"<<"\n";
  cout<<str.str()<<endl;
  str.str("");
  str<<2<<32;
  cout<<str.str()<<endl;
}
