#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>
#include <QMdiArea>

#include "mymysql.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    void script_msg(const char *SQL);
    mymysql db;
    void showview();
    void showsub();
    void createMenus();
    void createActions();
    QMdiArea *mdiArea;
    QMenu *adminMenu;
    QMenu *dataMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QAction *loginAction;
    QAction *logoutAction;
    QAction *exitAction;

    QAction *scriptAction;

    QAction *cascadeAction;
    QAction *tileAction;

    QAction *helpAction;
    QAction *aboutAction;

private slots:
    void on_login();
    void on_logout();
    void on_exit();

    void on_script();

    void cascadeSubWindows();
    void tileSubWindows();

    void on_help();
    void on_about();
};

#endif // MAINWINDOW_H
