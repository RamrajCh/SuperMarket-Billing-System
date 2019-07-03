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
      qry.prepare("INSERT INTO Company(Name,VAT,Phone,Address,Email,Website) VALUES (:name,:vat,:phone,:address,:email,:website)");

      qry.bindValue(":name",name);
      qry.bindValue(":vat",vat);
      qry.bindValue(":phone",phone);
      qry.bindValue(":address",address);
      qry.bindValue(":email",email);
      qry.bindValue(":website",website);

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

  QList<QString> Dbase_admin::getComDetails()
  {
      QList<QString> companydetails;
      QSqlQuery qry;
      qry.prepare(QString("SELECT * FROM Company"));
      if(!qry.exec())
      {
          qDebug()<<"Error in retriving data"<<qry.lastError();
      }
      else
      {
         if(qry.next())
         {
             QString name=qry.value(0).toString();
             QString vat=qry.value(1).toString();
             QString phone=qry.value(2).toString();
             QString address=qry.value(3).toString();
             QString email=qry.value(4).toString();
             QString website=qry.value(5).toString();

             companydetails.push_front(name);
             companydetails.push_front(vat);
             companydetails.push_front(phone);
             companydetails.push_front(address);
             companydetails.push_front(email);
             companydetails.push_front(website);
         }
         else
         {
             qDebug()<<"not executing qyery";
         }

      }
        return companydetails;
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
