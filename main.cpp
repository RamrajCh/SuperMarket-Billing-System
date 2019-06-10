#include <iostream>
#include<cstdio>
#include <cstring>
#include "admin.h"
using namespace std;

int main()
{
  int flag;
  Admin A1;
  A1.register_admin();
  do
  {
    flag=A1.login(A1);
    if (flag==0)
    {
      cout<<"Incorrect Password\n try again";
    }
   }while (flag==0);
}
