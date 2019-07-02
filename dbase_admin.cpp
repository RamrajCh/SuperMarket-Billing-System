#include "dbase_admin.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


    Dbase_admin::Dbase_admin(const QString &path)
    {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);
        if(!db.open())
        {
            qDebug() <<"Error:Connection with database";
        }
        else
        {
            qDebug() <<"Sucess:Connection with database";
        }
    }

    Dbase_admin::~Dbase_admin()
    {
        if(db.open())
        {
            db.close();
        }
    }

    bool Dbase_admin::isOpen() const
    {
        return db.isOpen();
    }

  void Dbase_admin::createCompanyTable()
  {

      QSqlQuery qry;
      qry.prepare("CREATE TABLE Company(Name TEXT,VAT TEXT,Phone TEXT,Address TEXT,Email TEXT,Website TEXT)");

      if (!qry.exec())
      {
          qDebug() <<"Couldn't create Table,one might already exist";

      }
      else
      {
          qDebug()<<"Create table";
      }

  }

  bool Dbase_admin::addCompanyDetails(const QString &name, const QString &vat, const QString &phone, const QString &address, const QString &email, const QString &website)
  {
      bool sucess=false;
      QSqlQuery qry;
      qry.prepare("INSERT INTO Company(Name TEXT,VAT TEXT,Phone TEXT,Address TEXT,Email TEXT,Website TEXT) VALUES (:name,:vat,:phone,:address,:email,:website)");

      qry.bindValue(0,name);
      qry.bindValue(1,vat);
      qry.bindValue(2,phone);
      qry.bindValue(3,address);
      qry.bindValue(4,email);
      qry.bindValue(5,website);

      if(!qry.exec())
      {
          qDebug()<<"Add Details Failed"<<qry.lastError();
          sucess=false;
      }
      else
      {
          qDebug()<<"Details added Sucessfully";
          sucess=true;
      }
      return sucess;
  }

  bool Dbase_admin::getCompanyDetails()
  {
      bool sucess=false;
      QSqlQuery qry;
      qry.prepare("SELECT * FROM Company");
      if(!qry.exec())
      {
          sucess=false;
      }
      else
      {
          sucess=true;
      }
      return sucess;
  }

  bool Dbase_admin::removeCompanyDetails()
  {
      bool  sucess=false;
      QSqlQuery qry;
      qry.prepare("DELETE FROM Company");
      if(qry.exec())
      {
          sucess=true;
      }
      else
      {
          sucess=false;
      }
      return sucess;
  }
