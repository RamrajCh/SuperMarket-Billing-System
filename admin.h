#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <fstream>
#include<cstdio>
#include <cstring>
#include "conio.h"
#include "product.h"
using namespace std;
ofstream fout;
class Admin
{
  private:
    char name[25];
    char admin_id[12];
    char passwd[16];
    char rem_passwd[16];
  public:
    Admin(){}
    Admin (Admin &A)
    {
      strcpy(name,A.name);
      strcpy(admin_id,A.admin_id);
      strcpy(passwd,A.passwd);
      strcpy(rem_passwd,A.rem_passwd);
    }
    char VAT[10];
    void register_admin();
    int login(Admin);
    friend void Admin_home_page(Admin);
    friend Admin Change_Password(Admin);
};
void Admin_home_page(Admin);
Admin Change_Password(Admin);

void Admin :: register_admin()
{
  fout.open("/home/ramraj_ch/SBS/Admin.xls");
  cout<<"\nGive your full name:\t";
    cin>>name;
    fout<<name<<'\t';
  cout<<"\nGive your mobile no.:\t";
    cin>>admin_id;
     fout<<admin_id<<'\t';
  cout<<"\nPassword:\t";
    cin>>passwd;
     fout<<passwd<<'\t';
  cout<<"\nGive unique password remember phrase:\t";
    cin>>rem_passwd;
     fout<<rem_passwd<<endl;
  cout<<"\nData Saved\nYour user name is "<<admin_id;
  fout.close();
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
     if ((strcmp(T.admin_id,A.admin_id)==0)&&(strcmp(T.passwd,A.passwd)!=0))
        return 0;
    if ((strcmp(T.admin_id,A.admin_id)==0)&&(strcmp(T.passwd,A.passwd)==0))
      return 1;

    }
  else
  {
    cout<<"Incorrect Username!";
    goto re;
  }
  }
void Admin_home_page(Admin A)
{
  Admin T;
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
        T=Change_Password(A);
        T.login(T);
        break;
      case 4:
       T=A;
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
  Admin T;
  re:
  cout<<"Give old password\t";
  cin>>T.passwd;
 if ((strcmp(T.passwd,A.passwd)==0))
 {
  for (i=0;i<strlen(A.passwd);i++)
    {A.passwd[i]=0;}
  cout<<"Give new password\t";
  cin>>A.passwd;
  cout<<"\nGive unique password remember phrase:\t";
    cin>>A.rem_passwd;
  }
 else
 {
   cout<<"Incorrect Password!\n";
   goto re;
 }
 cout<<"Your username is"<<A.admin_id<<endl;
  return A;
}
#endif
