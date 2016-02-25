#include <QMessageBox>
#include <QMdiSubWindow>
#include <QIcon>
#include <QStandardItemModel>
#include <QTableView>

#include "mainwindow.h"
#include "logindlg.h"
#include "scriptdlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("CDMA无线基站管理系统"));
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
    mdiArea->setBackground(Qt::NoBrush);
    //设置背景为1.jpg，子窗口大小可调整
    mdiArea->setStyleSheet("background-image: url(1.jpg);");
    //当子窗口的范围超过父窗口的显示范围时，父窗口自动添加横向滚动条
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //当子窗口的范围超过父窗口的显示范围时，父窗口自动添加纵向滚动条
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setWindowIcon(QIcon("main.png"));//设置窗口光标
    createActions();
    createMenus();

}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //通过question函数的返回值来判断用户到底点击的是yes还是no
    QMessageBox::StandardButton button = QMessageBox::question(this, "提示",
                                                               "是否退出程序",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes)
    {
        event->accept();//如果点击yes，接受退出
    }
    else
    {
        event->ignore();//否则，不接受退出
    }
}

void MainWindow::script_msg(const char *SQL)
{
    int res = 0;
    if ((strncmp(SQL, "SELECT", 6))==0 || (strncmp(SQL, "select", 6))==0)
    {
        QStandardItemModel *model = NULL;
        res = db.sql_open(SQL, &model);//如果是SELECT，那么执行sql_open

        QTableView *view1 = new QTableView;
        view1->setAttribute(Qt::WA_DeleteOnClose);//view在close的时候会自动delete
        mdiArea->addSubWindow(view1);
        view1->setStyleSheet("border-image: url(3.jpg);");//设置背景

        //view1继承自widget，如果没有modul，那么view不会显示任何数据
        view1->setModel(model);
        view1->show();
        mdiArea->activeSubWindow()->resize(width()-100, height()-100);
    }
    else
    {
        res = db.sql_exec(SQL);//如果用户执行的是非SELECT,那么执行sql_exec函数
    }

    if (res == -1)
    {
        QMessageBox::information(this, tr("执行失败"), db.geterror());
    }
    else
    {
        QMessageBox::information(this, tr("提示"), tr("执行成功"));
    }
}

/*************************************************/
/*这里仅仅是一个例子，如果需要，要根据mysql库中的表示来替换*/
/*************************************************/
void MainWindow::showview()
{
    QStandardItemModel *model = new QStandardItemModel(2, 3);//要建立一个2行3列的

    //设置modul的列头名称
    model->setHeaderData(0, Qt::Horizontal, "姓名");
    model->setHeaderData(1, Qt::Horizontal, "性别");
    model->setHeaderData(2, Qt::Horizontal, "年龄");
    //设置modul的每一个单元格的内容
    model->setData(model->index(0, 0, QModelIndex()), "张三");
    model->setData(model->index(0, 1, QModelIndex()), "男");
    model->setData(model->index(0, 2, QModelIndex()), "30");
    model->setData(model->index(1, 0, QModelIndex()), "李四");
    model->setData(model->index(1, 1, QModelIndex()), "女");
    model->setData(model->index(1, 2, QModelIndex()), "27");

    QTableView *view1 = new QTableView;
    view1->setAttribute(Qt::WA_DeleteOnClose);//view在close的时候自动会close
    mdiArea->addSubWindow(view1);
    view1->setStyleSheet("border-image: url(3.jpt);");//设置widget的背景图片

    //view1继承自widget，如果没有modul，那么view不会显示任何数据
    view1->setModel(model);
    view1->show();
    mdiArea->activeSubWindow()->resize(width()-100, height()-100);
}

void MainWindow::showsub()
{
    QWidget *w1 = new QWidget;
    w1->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete
    mdiArea->addSubWindow(w1);
    w1->setWindowTitle("数据");
    w1->setStyleSheet("border-image: url(3.jpg);");//设置widget背景图片
    w1->show();
    mdiArea->activeSubWindow()->resize(width()-100, height()-100);//设置widget窗口大小
}

void MainWindow::createMenus()
{
    adminMenu = menuBar()->addMenu(tr("管理"));//添加管理菜单
    adminMenu->addAction(loginAction);
    adminMenu->addAction(logoutAction);
    adminMenu->addSeparator();//加入分隔符
    adminMenu->addAction(exitAction);

    dataMenu = menuBar()->addMenu(tr("数据"));
    dataMenu->addAction(scriptAction);

    windowMenu = menuBar()->addMenu(tr("窗口"));
    windowMenu->addAction(cascadeAction);
    windowMenu->addAction(tileAction);

    helpMenu = menuBar()->addMenu(tr("帮助"));
    helpMenu->addAction(helpAction);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{
    loginAction = new QAction(tr("登录"), this);
    loginAction->setShortcut(tr("Ctul + u"));
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_login()));

    logoutAction = new QAction(tr("注销"), this);
    logoutAction->setShortcut(tr("Ctrl + b"));
    connect(logoutAction, SIGNAL(triggered()), this, SLOT(on_logout()));

    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("Ctrl + w"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(on_exit()));

    scriptAction = new QAction(tr("执行脚本"), this);
    scriptAction->setShortcut(tr("Ctrl + p"));
    scriptAction->setEnabled(false);//设置执行脚本这个行为不可用，需要登录后使用
    connect(scriptAction, SIGNAL(triggered()), this, SLOT(on_script()));

    cascadeAction = new QAction(tr("层叠"), this);
    cascadeAction->setShortcut(tr("Ctrl +　q"));
    connect(cascadeAction, SIGNAL(triggered()), this, SLOT(cascadeSubWindows()));

    tileAction = new QAction(tr("并列"), this);
    tileAction->setShortcut(tr("Ctrl +　r"));
    connect(tileAction, SIGNAL(triggered()), this, SLOT(tileSubWindows()));

    helpAction = new QAction(tr("帮助"), this);
    helpAction->setShortcut(tr("Ctrl+s"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(on_help()));

    aboutAction = new QAction(tr("关于"), this);
    aboutAction->setShortcut(tr("Ctrl+t"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(on_about()));
}

void MainWindow::on_login()
{
    logindlg dlg;//将对话框实例化
    dlg.exec();//调用exec产生一个模式对话框，程序在exec函数这个地方阻塞了

    if (dlg.islogin)//代表用户点击了dlg对话框的登录按钮
    {
        int res = db.sql_connect(dlg.hostip.toStdString().data(),
                                 dlg.userid.toStdString().data(),
                                 dlg.passwd.toStdString().data(),
                                 dlg.dbname.toStdString().data());
        if (res == -1)
        {
            QMessageBox::information(this, tr("登录失败"), db.geterror());
        }
        else//此处可能产生漏洞。。。。
        {
            QMessageBox::information(this, "", tr("登录成功"));
            scriptAction->setEnabled(true);
        }
    }
}

void MainWindow::on_logout()
{
    QMessageBox::StandardButton button = QMessageBox::question(this, tr("提示"), tr("是否注销"),
                                                               QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::Yes)
    {
        db.sql_disconnect();
        scriptAction->setEnabled(false);
    }
}

void MainWindow::on_exit()
{
    close();
}

void MainWindow::on_script()
{
    scriptdlg dlg;//申请scriptdlg类的实例
    dlg.exec();//模式对话框，阻塞

    if (dlg.islogin)//如果用户点击了执行按钮才执行下面的代码
    {
        script_msg(dlg.SQL.toStdString().data());
    }
}

void MainWindow::cascadeSubWindows()
{
    mdiArea->cascadeSubWindows();
}

void MainWindow::tileSubWindows()
{
    mdiArea->tileSubWindows();
}

void MainWindow::on_help()
{
    QMessageBox::information(this, tr("帮助"), tr("自学方可成才！！！"));
}

void MainWindow::on_about()
{
    QMessageBox::information(this, tr("关于"), tr("这个简单不好意思要版权啊！！！/(ㄒoㄒ)/~~"));
}
