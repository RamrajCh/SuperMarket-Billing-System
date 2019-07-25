#ifndef dbase_H
#define dbase_H

#include <QSqlDatabase>
#include<QList>


class Dbase
{
public:
      Dbase(const QString& path);

      ~Dbase();

      bool isOpen() const;

      void createTable();

      bool addAdmin(const QString &fname, const QString &lname, const QString &username, const QString &mobileno, const QString &email, const QString &passwd);


      bool emailExists(const QString& email);
      bool unameExists(const QString &uname);
      bool userAuth(const QString& uname, const QString& pass) const;

      QList<QString> getAdminInfo(const QString& uname);


      bool getAdminInfo();

      ////functions for handling admin login

      void createAdmin_LoginTable();//create table for  admin that has log in

      void addAdmin_Login(QString &uname);//store data of admin that has log in

      void deleteAdmin_Login();

      ////functions for handling cashier login
      bool cashierAuth(const QString& uname, const QString& pass) const;

      void createCashier_LoginTable();

      QList<QString> getCashierInfo(const QString &uname);

      void addCashier_Login(QString &uname);

      void deleteCashier_Login();

  private:
      QSqlDatabase db;
  };


#endif // dbase_H
