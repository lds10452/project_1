#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

void CreateTable();
void InsertData();
void UpdateData();
void SelectData();
void DeleteData();
void DeleteTable();

int main()
{
    //建立数据库--加载数据库驱动
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("..\\SqliteOp\\mySqlite.db");
        //db.setDatabaseName("main");//有这个会报错
        //database.setUserName("");//可以省略
        //database.setPassword("");//可以省略
    }

    //打开数据库
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
        return -1;
    }

//    CreateTable();
//    InsertData();
//    UpdateData();
//    SelectData();
//    DeleteData();
    DeleteTable();

    //关闭数据库
    database.close();
    qDebug()<<"----------------finish!------------";
    system("pause");
    return 0;
}

void CreateTable()
{
    bool success=false;
    //#####################################################################
    //--新建一个表student作为测试表
    //#####################################################################
    //执行sql语句---新建一个表
    QSqlQuery sql_query;
    QString create_sql = "create table student (id int, name varchar(30), age int)";
    sql_query.prepare(create_sql);
    success = sql_query.exec();
    if(!success)
    {
        qDebug() << "Error: Fail to create table." << sql_query.lastError();
        return ;
    }
    else
    {
        qDebug() << "Table created!";
    }
}
void InsertData()
{
    bool success=false;
    QSqlQuery sql_query;
    //#####################################################################
    //--插入数据操作
    //#####################################################################
    //向student表中插入数据
    //第一种方法:
//    success = sql_query.exec("insert into student values(1, 'xiaowen', 10)");
//    if(!success)
//    {
//        qDebug() << "Error: Fail to create table." << sql_query.lastError();
//        return ;
//    }

    //第二种方方法:执行带有占位符的sql语句
    QString insert_sql = "insert into student values (?, ?, ?)";
//    sql_query.prepare(insert_sql);
//    sql_query.addBindValue(2);
//    sql_query.addBindValue("xiaohu");
//    sql_query.addBindValue(22);
    //以下方式也可以
//    sql_query.bindValue(0, 5);
//    sql_query.bindValue(1, "小马");
//    sql_query.bindValue(2, 30);
//    success = sql_query.exec();
//    if(!success)
//    {
//        qDebug() << sql_query.lastError();
//        return ;
//    }
//    else
//    {
//        qDebug() << "inserted success!";
//    }

    //批量插入
    insert_sql = "insert into student values(?,?,?)";
    sql_query.prepare(insert_sql);
    QVariantList GroupIDs;
    GroupIDs.append(0);
    GroupIDs.append(1);
    GroupIDs.append(2);
    QVariantList GroupNames;
    GroupNames.append("xiaoma");
    GroupNames.append("xiaowei");
    GroupNames.append("xiaolian");
    QVariantList GroupAddress;
    GroupAddress.append(10);
    GroupAddress.append(15);
    GroupAddress.append(18);
    sql_query.addBindValue(GroupIDs);
    sql_query.addBindValue(GroupNames);
    sql_query.addBindValue(GroupAddress);
    success = sql_query.execBatch();
    if(!success)
    {
        qDebug()<<sql_query.lastError();
        return ;
    }
    else
    {
        qDebug()<<"insert batch data succ";
    }
}
void UpdateData()
{
    bool success=false;
    QSqlQuery sql_query;
    //#####################################################################
    //--更新数据
    //#####################################################################
    //QString update_sql = "update student set name = :name where id = :id";
    QString update_sql = "update student set name = ? where id = ?";
    sql_query.prepare(update_sql);
    //sql_query.bindValue(":name", "Qt");
    //sql_query.bindValue(":id", 1);
    sql_query.bindValue(0, "Qt");
    sql_query.bindValue(1, 2);
    success = sql_query.exec();
    if(!success)
    {
        qDebug() << sql_query.lastError();
        return ;
    }
    else
    {
        qDebug() << "updated!";
    }
}
void SelectData()
{
    bool success=false;
    QSqlQuery sql_query;
    //#####################################################################
    //--查询数据
    //#####################################################################
    QString select_sql = "select id, name from student";
    success = sql_query.exec(select_sql);
    if(!success)
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString name = sql_query.value(1).toString();
            qDebug()<<QString("id:%1 name:%2").arg(id).arg(name);
        }
    }

    //查询最大的ID
    QString select_max_sql = "select max(id) from student";
    sql_query.prepare(select_max_sql);
    success = sql_query.exec();
    if(!success)
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int max_id = 0;
            max_id = sql_query.value(0).toInt();
            qDebug() << QString("max id:%1").arg(max_id);
        }
    }
}
void DeleteData()
{
    bool success=false;
    QSqlQuery sql_query;
    //#####################################################################
    //--删除数据
    //#####################################################################
    QString delete_sql = "delete from student where id = ?";
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(2);
    success = sql_query.exec();
    if(!success)
    {
        qDebug()<<sql_query.lastError();
        return ;
    }
    else
    {
        qDebug()<<"deleted!";
    }

    //清空表
    QString clear_sql = "delete from student";
    sql_query.prepare(clear_sql);
    success = sql_query.exec();
    if(!success)
    {
        qDebug() << sql_query.lastError();
        return ;
    }
    else
    {
        qDebug() << "table cleared";
    }
}
void DeleteTable()
{
    bool success=false;
    QSqlQuery sql_query;
    QString clear_sql = "drop table student";
    sql_query.prepare(clear_sql);
    success = sql_query.exec();
    if(!success)
    {
        qDebug() << sql_query.lastError();
        return ;
    }
    else
    {
        qDebug() << "table deleted";
    }
}
