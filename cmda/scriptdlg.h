#ifndef SCRIPTDLG_H
#define SCRIPTDLG_H

#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

class scriptdlg : public QDialog
{
    Q_OBJECT
public:
    explicit scriptdlg(QWidget *parent = 0);
    QString SQL;
    bool islogin;

signals:

public slots:

private:
    QLabel *label0;
    QTextEdit *textEditSQL;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

private slots:
    void okBtnOnclick();
    void cancelBtnOnclick();
};

#endif // SCRIPTDLG_H
