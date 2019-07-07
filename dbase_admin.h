#ifndef DBASE_ADMIN_H
#define DBASE_ADMIN_H

#include <QSqlDatabase>
#include<QList>
#include <QMessageBox>

class Dbase_admin
{
private:
    QSqlDatabase db;
public:
    Dbase_admin(const QString &path);

    ~Dbase_admin();

    bool isOpen() const; //check if the database is connected or not


    ////functions for handling company details
    void createCompanyTable(); //create Company table

    bool addCompanyDetails(const QString &name, const QString &vat, const QString &phone, const QString &address, const QString &email, const QString &website);//Save data to Company

    bool getCompanyDetails();//read data from Company and return true if it has some value

    QList<QString> getComDetails(); //read and retrive data from table

    bool removeCompanyDetails();//removes all data from Company


    ////functions to handle cashier
    void createCashierTable(); //create Cashier table

    bool addCashierDetails(const QString &name, const QString &uname, const QString &phone, const QString &email, const QString &password); //add data to table

    bool modifyCashierDetails(const QString &uname); //modify cashier details

    void removeCashier(const QString &uname,const QString &email);//removes a cashier

    bool removeCashierTable();//deletes Cashier Table

    bool validCashier(const QString &uname,const QString &email);

    bool cashier_unameExists(const QString &uname);

    bool cashier_emailExists(const QString &uname);

    ////fnction to handle privacy
    void deleteAdmin_Login();

    QList<QString> getAdmin_LoginDetails();

    bool uNameExists(const QString &uname);

    bool passwordValid(const QString& passwd);

    void changeAdminPassword(const QString& username,const QString& npasswd);

    void changeAdmin_LoginPassword(const QString& username,const QString& npasswd);

    ////function to handle product

    void createProductTable();

    bool addProduct(const QString &id, const QString &name, const QString &category, const QString &price);

    bool product_IdExists(const QString &id);

    bool product_NameExists(const QString &name);

};

#endif // DBASE_ADMIN_H
