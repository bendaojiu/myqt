#include <string.h>
#include <QMessageBox>

#include "mymysql.h"

//所有有关mysql API函数调用，都是在这个类里面实现的，以实现封装
mymysql::mymysql()
{
    mysql_init(&mysql);
    connection = NULL;
    memset(buf, 0, sizeof(buf));
}

const char *mymysql::geterror()
{
    return buf;
}

int mymysql::sql_connect(const char *Hostname, const char *User, const char *Passwd, const char *DBName)
{
    connection = mysql_real_connect(&mysql, Hostname, User, Passwd, DBName, 0, 0, 0);
    if (connection == NULL)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }
    else
    {
        mysql_query(connection, "set names utf8");
        return 0;
    }
}

void mymysql::sql_disconnect()
{
    if (connection)
    {
        mysql_close(connection);
        connection = NULL;
    }
}

int mymysql::sql_exec(const char *SQL)
{
    if (mysql_query(connection, SQL) != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }
    return 0;
}

int mymysql::sql_open(const char *SQL, QStandardItemModel **p)
{
    if (mysql_query(connection, SQL) != 0)
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL)//没有查询结果
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        return -1;
    }

    int rowcount = mysql_affected_rows(connection);//这个函数返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//这个函数返回SQL语句执行后有多少列

    //根据SQL语句反悔的行列总数，动态的建一个modul出来
    *p = new QStandardItemModel(rowcount, fieldcount);
    MYSQL_FIELD *field;

    int i = 0;
    int j = 0;
    for (i=0; i<fieldcount; i++)
    {
        field = mysql_fetch_field(result);
        (*p)->setHeaderData(i, Qt::Horizontal, field->name);
    }

    for (i=0; i<rowcount; i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        for (j=0; j<fieldcount; j++)//循环遍历一行当中的所有列
        {
            (*p)->setData((*p)->index(i, j, QModelIndex()), row[j]);
        }
    }

    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}
