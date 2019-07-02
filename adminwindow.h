#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class AdminWindow;
}

class AdminWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit AdminWindow(QWidget *parent = 0);
  ~AdminWindow();

private slots:
    void on_companyButton_clicked();

    void on_cashierButton_clicked();

    void on_productButton_clicked();

    void on_privacyButton_clicked();

private:
  Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
