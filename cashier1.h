#ifndef CASHIER_H_INCLUDED
#define CASHIER_H_INCLUDED
#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
class cashier{
private:
    char username[50];
    char cashier_id[50];
    char password[50];
public:
     void register_cashier();

}
void cashier::register_cashier()
{
    cout<<"enter your full name"<<endl;
    cin>>username;
    cout<<"enter cashier_id"<<endl;
    cin>>cashier_id;
    cout<<"enter your password"<<endl;
    cin>>password;
}
};
class login
{
    protected:
    char fullname[50];
    char password[50];
    char email_id[50];
    int customer_no[50];

    public:
        void login_id(){};
        int setX(){};
        int getX(){};

}
void login::login_id()
{
    int i;
    cout<<"enter the fullname "<<endl;
    cin>>fullname;
    cout<<"enter your password"<<endl;
    cin>>password;
    cout<<"enter the email_id"<<endl;
    cin>>email_id;

}


};
#endif // CASHIER_H_INCLUDED
