#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
int main()
{
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.5.104"); //����mysql������IP��ַ
    db.setDatabaseName("mydb2"); //�������ݿ���
    db.setUserName("root"); //�����û���
    db.setPassword("mima"); //��������
    if(!db.open())
    {
        qDebug() << "���ݿ����ʧ��";
        return -1;
    }


    system("pause");
    return 0;
}
