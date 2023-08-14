//
// Tomás Oliveira e Silva, AED, October 2021
//
// example of function overloading (same function name, different argument numbers and/or data types)
//

#include <iostream>

using std::cout; // make this symbol from the std namespace directly visible

void show(const int i)
{
  cout << "int: "
       << i
       << std::endl;
}

void show(const double d)
{
  cout << "double: "
       << d
       << std::endl;
}

void show(const char *s,const char *h = "string: ") // second argument with default value
{
  cout << h
       << s
       << std::endl;
}

void show(const char a)
{
    cout << "char:" << a << std::endl;
}

void show(const int *a , const int n = 3){
    cout << "Array: [";
    for(int i = 0; i<n-1;i++){
        cout << a[i]<<",";
    }
    cout << a[n-1]<< "]";
}


int main(void)
{
  show(1.0);
  show("hello");
  show(-3);
  show("John","name: ");
  show('a');
  int a[3] = {1,2,3};
  show(a);
  return 0;
}