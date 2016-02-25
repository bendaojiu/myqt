#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class logindlg : public QDialog
{
    Q_OBJECT
public:
    explicit logindlg(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *label0, *label1, *label2, *label3;
    QLineEdit *lineEditUserID, *lineEditPasswd, *lineEdtDBName, *lineEditHostIP;
    QPushButton *loginBtn, *logoutBtn;

private slots:
    void loginBtnOnclick();
    void logoutBtnOnclick();

public:
    QString userid;
    QString passwd;
    QString dbname;
    QString hostip;
    bool islogin;

};

#endif // LOGINDLG_H
