#ifndef DBASE_ADMIN_H
#define DBASE_ADMIN_H

#include <QSqlDatabase>
#include<QList>

class Dbase_admin
{
private:
    QSqlDatabase db;
public:
    Dbase_admin(const QString &path);

    ~Dbase_admin();

    bool isOpen() const; //check if the database is connected or not


    //functions for handling company details
    void createCompanyTable(); //create Company table

    bool addCompanyDetails(const QString &name, const QString &vat, const QString &phone, const QString &address, const QString &email, const QString &website);//Save data to Company

    bool getCompanyDetails();//read data from Company and return true if it has some value

    QList<QString> getComDetails();

    bool removeCompanyDetails();//removes all data from Company
};

#endif // DBASE_ADMIN_H
