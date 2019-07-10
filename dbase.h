#ifndef dbase_H
#define dbase_H

#include <QSqlDatabase>
#include<QList>


class Dbase
{
public:
       /**
       * @brief Constructor
       *
       * Constructor sets up connection with db and opens it
       * @param path - absolute path to db file
       */
      Dbase(const QString& path);

      /**
       * @brief Destructor
       *
       * Close the db connection
       */
      ~Dbase();

      bool isOpen() const;

      /**
       * @brief Creates a new 'user' table if it doesn't already exist
       * @return true - 'user' table created successfully, false - table not created
       */
      void createTable();

      /**
       * @brief Add user data to db
       * @param email - email of user to add. email is unique
       * @param password - password of user to add
       * @param fname
       * @param lname
       * @param addr
       * @param phn
       * @return true - person added successfully, false - person not added
       */
      bool addAdmin(const QString &fname, const QString &lname, const QString &username, const QString &mobileno, const QString &email, const QString &passwd);

      /**
       * @brief Remove users data from db
       * @param email - email of user to remove.
       * @return true - user removed successfully, false - user not removed
       */
      bool removeUser(const QString& name);



      /**
       *@brief Check if the email is already taken
       */
      bool emailExists(const QString& email);
      bool unameExists(const QString &uname);
      bool passwordValid(const QString& passwd);


      void printAllUsers() const;

      /**
       * @brief Remove all users email from db
       * @return true - all users removed successfully, false - not removed
       */
      bool removeAllUsers();


      /**
       * @brief Authenticate the users via user email and password
       * @return db_primary_key - , 0 - log in failed
       */
      bool userAuth(const QString& uname, const QString& pass) const;

      /**
       * @brief Get all the user data from the dbase
       * @return Returns list of strings
       */
      QList<QString> getAdminInfo(const QString& uname);


      bool getAdminInfo();

      /**
       * @brief Get all the email/id of the registerd users from Dbase
       * @return Returns list of strings
       */
      QList<QString> getAllUsers();
      /**
        *change AdminPassword
        */
      void changeAdminPassword(const QString& username,const QString& npasswd);

      ////functions for handling admin login

      void createAdmin_LoginTable();//create table for  admin that has log in

      void addAdmin_Login(QString &uname);//store data of admin that has log in

      void deleteAdmin_Login();//delete Admin_Login table

      ////functions for handling cashier login
      bool cashierAuth(const QString& uname, const QString& pass) const;

      void createCashier_LoginTable();

      QList<QString> getCashierInfo(const QString& uname);

      void addCashier_Login(QString &uname);

      void deleteCashier_Login();

  private:
      QSqlDatabase db;
  };


#endif // dbase_H
