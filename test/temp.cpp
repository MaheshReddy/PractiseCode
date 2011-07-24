#include <sstream> 
#include <string>  
#include <iostream>

using namespace std;

bool StringToInt(const string &s, int &i);

int main(void)
{
  string s1 = "12";
  int result;
  
  if (StringToInt(s1, result))
  {
    cout<<result<<endl;
    cout << "The string value is " << s1
         << " and the int value is " << result << endl;
  }
  else
  {
    cout << "Number conversion failed" <<endl;
  }
  return(0);
}

bool StringToInt(const string &s, int &i)
{
  istringstream myStream(s);
  cout<<i<<endl;
  
  if (myStream>>i)
    return true;
  else
    return false;
}
