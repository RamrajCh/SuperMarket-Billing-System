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
	flag=A1.login();
}
