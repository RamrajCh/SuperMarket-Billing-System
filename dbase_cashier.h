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


};

#endif // DBASE_CASHIER_H
