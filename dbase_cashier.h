#ifndef DBASE_CASHIER_H
#define DBASE_CASHIER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QList>
#include <QMessageBox>


class Dbase_Cashier
{
private:
    QSqlDatabase db;

public:
    Dbase_Cashier(const QString &path);

    ~Dbase_Cashier();

    bool isOpen() const;

    bool cashierAuth(const QString& uname, const QString& pass) const;

    ////fnction to handle logout
    void deleteCashier_Login();

    QList<QString> getCashier_loginDetails();

    QList<QString> getComDetails();

    bool validProduct(QString &id);

    bool validCashier(QString &username,QString &oldpassword);

    void updateCashier(QString &Username,QString &newpassword);

    ////functions for invoice
    void createBillTable();

    QList<QString> getProductDetails(const QString &id);

    bool addProduct(const QString &id,const QString &name,const int &quantity,const double &rate,const double &amount);

    bool product_IdExists(const QString &id);

    void deleteBillTable();
};

#endif // DBASE_CASHIER_H
