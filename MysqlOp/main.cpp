#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
int main()
{
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.5.104"); //设置mysql主机的IP地址
    db.setDatabaseName("mydb2"); //设置数据库名
    db.setUserName("root"); //设置用户名
    db.setPassword("mima"); //设置密码
    if(!db.open())
    {
        qDebug() << "数据库操作失败";
        return -1;
    }


    system("pause");
    return 0;
}
