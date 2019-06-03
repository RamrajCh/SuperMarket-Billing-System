#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include<cstdio>
#include <cstring>
using namespace std;
class Admin
{
	private:
		char name[25];
		char admin_id[12];
		char passwd[16];
		char rec_passwd[16];
	public:
		char VAT[10];
		void register_admin();
		int login();
};

void Admin :: register_admin()
{
	cout<<"\nGive your full name:\t";
	cin>>name;
	cout<<"\nGive your mobile no.:\t";
	cin>>admin_id;
	cout<<"\nPassword:\t";
	gets(passwd);
	cout<<"\nGive unique password remember phrase:\t";
	cin>>rec_passwd;
	cout<<"\nData Saved\nYour user name is "<<admin_id;
}

int login()
{
	char username[12],password[16];
	cout<<"\nGive your username:\t";
	cin>>username;
	if ((strcmp(username,admin_id)==0)
	{
		cout<<"\nGive your password:\t";
		int len=strlen	
		cin>>password;
	
#endif
