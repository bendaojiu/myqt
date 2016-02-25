#include <QGridLayout>
#include <QPalette>
#include <QMessageBox>

#include "logindlg.h"

logindlg::logindlg(QWidget *parent) :
    QDialog(parent)
{
    islogin = false;//islogin在对话框初始化的时候值为false

    label0 = new QLabel;
    label0->setText(tr("用户名"));
    label1 = new QLabel;
    label1->setText(tr("密码"));
    label2 = new QLabel;
    label2->setText(tr("数据库名称"));
    label3 = new QLabel;
    label3->setText(tr("服务器IP"));
    lineEditUserID = new QLineEdit;
    lineEditPasswd = new QLineEdit;
    lineEditPasswd->setEchoMode(QLineEdit::Password);//设置为密码框
    lineEdtDBName = new QLineEdit;
    lineEditHostIP = new QLineEdit;
    loginBtn = new QPushButton;
    loginBtn->setText(tr("登录"));
    logoutBtn = new QPushButton;
    logoutBtn->setText(tr("取消"));

    QGridLayout *layout1 = new QGridLayout(this);//构造函数需要写this
    layout1->addWidget(label0, 0, 0);
    layout1->addWidget(lineEditUserID, 0, 1);
    layout1->addWidget(label1, 1, 0);
    layout1->addWidget(lineEditPasswd, 1, 1);
    layout1->addWidget(label2, 2, 0);
    layout1->addWidget(lineEdtDBName, 2, 1);
    layout1->addWidget(label3, 3, 0);
    layout1->addWidget(lineEditHostIP, 3, 1);
    layout1->addWidget(loginBtn, 4, 0);
    layout1->addWidget(logoutBtn, 4, 1);
    layout1->setColumnStretch(0, 1);//设置0列
    layout1->setColumnStretch(1, 1);//设置1列
    layout1->setMargin(15);//设置layout边距
    layout1->setSpacing(10);//设置layout当中控件与控件之间的间距
    setWindowTitle(tr("登录"));
    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("2.jpg")));
    setPalette(palette);

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginBtnOnclick()));
    connect(logoutBtn, SIGNAL(clicked()), this, SLOT(logoutBtnOnclick()));
}

void logindlg::loginBtnOnclick()
{
    userid = lineEditUserID->text();
    passwd = lineEditPasswd->text();
    dbname = lineEdtDBName->text();
    hostip = lineEditHostIP->text();
    islogin = true;//只有用户点击了确定按钮，islogin的值才是true（话说验证密码呢？？）
    close();
}

void logindlg::logoutBtnOnclick()
{
    close();
}
