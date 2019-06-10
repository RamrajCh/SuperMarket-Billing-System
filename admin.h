#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <fstream>
#include<cstdio>
#include <cstring>
#include "conio.h"
#include "product.h"
using namespace std;
class Admin
{
  private:
    char name[25];
    char admin_id[12];
    char passwd[16];
    char rec_passwd[16];
  public:
    Admin(){}
    Admin (Admin &A)
    {
      strcpy(name,A.name);
      strcpy(admin_id,A.admin_id);
      strcpy(passwd,A.passwd);
      strcpy(rec_passwd,A.rec_passwd);
    }
    char VAT[10];
    void register_admin();
    int login( Admin);
    friend void Admin_home_page(Admin);
    friend Admin Change_Password(Admin);
};
void Admin_home_page(Admin);
Admin Change_Password(Admin);

void Admin :: register_admin()
{
  cout<<"\nGive your full name:\t";
    cin>>name;
  cout<<"\nGive your mobile no.:\t";
    cin>>admin_id;
  cout<<"\nPassword:\t";
    cin>>passwd;
  cout<<"\nGive unique password remember phrase:\t";
    cin>>rec_passwd;
  cout<<"\nData Saved\nYour user name is "<<admin_id;
}

int Admin :: login(Admin A)
{
  Admin T;
  re:
  cout<<"\nGive your username:\t";
    cin>>T.admin_id;
  //int i;
  if ((strcmp(T.admin_id,A.admin_id)==0))
  {
    cout<<"\nGive your password:\t";
      cin>>T.passwd;
    /*int len=strlen(passwd);
    for (i=0;i<len+1;i++)
    {
      password[i]=getch();
      cout<<"*";
    }
    password[i]='\0';*/
    if ((strcmp(T.admin_id,A.admin_id)==0)&&(strcmp(T.passwd,A.passwd)==0))
      Admin_home_page(T);
    else
      return 0;
    }
  else
  {
    cout<<"Incorrect Username!";
    goto re;
  }
  }
void Admin_home_page(Admin A)
{
  Admin T=A;
  int control;
  cout<<"Press"<<endl;
  re:
  cout<<"1\tCashier Management"<<endl
      <<"2\tProduct Management"<<endl
      <<"3\tChange Password"<<endl
      <<"4\tGo Back to LoginPage"<<endl;
    cin>>control;
    switch (control) {
      case 1:
        //Cashier Management
        break;
       case 2:
       Product_Management();
        break;
       case 3:
        A=Change_Password(T);
        break;
      case 4:
       T.login(T);
       break;
      default:
        cout<<"YOU HAVE TO CHOOSE FOUR OPTION"<<endl;
        goto re;
    }
}

Admin Change_Password(Admin A)
{
  int i;
  Admin T=A;
  for (i=0;i<strlen(T.passwd);i++)
    T.passwd[i]=0;
  cout<<"Your password is"<<T.passwd;
  return T;
}
#endif
