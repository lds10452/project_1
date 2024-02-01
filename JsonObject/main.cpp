#pragma execution_character_set("utf-8")
#include<iostream>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QDebug>
void ParseJsonArray(const QJsonArray& arr);
void ParseJsonObject(const QJsonObject& obj);

void ReadJsonFile()
{
    QFile file("../JsonObject/read.json");
    bool res = file.open(QIODevice::ReadOnly);
    if(!res)
    {
        qDebug()<<"open error";
        return;
    }
    QByteArray fileData=file.readAll();
    file.close();
    QJsonDocument doc=QJsonDocument::fromJson(fileData);
    if(doc.isObject())
    {
        ParseJsonObject(doc.object());
    }
    else if(doc.isArray()){
        ParseJsonArray(doc.array());
    }
}
void WriteJsonFile()
{
    QJsonArray arr;
    arr.append("father");
    arr.append(false);
    arr.append(10);
    arr.append("mother");
    QJsonObject subObj;
    subObj.insert("father",QString("小李"));
    subObj.insert("age",45);
    QJsonObject obj;
    obj.insert("family",arr);
    obj.insert("family1",subObj);
    obj.insert("name","小张");
    obj.insert("age",21);
    obj.insert("isMan",true);
    QJsonDocument doc(obj);
    QFile file("../JsonObject/write.json");
    bool res= file.open(QIODevice::WriteOnly|QIODevice::Text);
    if(!res)
    {
        qDebug()<<"open error!";
        return;
    }
    file.write(doc.toJson());
    file.close();
}
int main()
{
//    ReadJsonFile();
    WriteJsonFile();
    system("pause");
    return 0;
}

void ParseJsonObject(const QJsonObject& obj)
{
    qDebug()<<"{";
    QStringList keys=obj.keys();
    for(int i=0;i<keys.size();i++)
    {
        QJsonValue value=obj[keys[i]];
        if(value.isDouble())
        {
            qDebug()<<keys[i]<<":"<<value.toInt()<<",";
        }
        else if (value.isString()) {
            qDebug()<<keys[i]<<":"<<value.toString()<<",";
        }
        else if (value.isBool()) {
            qDebug()<<keys[i]<<":"<<value.toBool()<<",";
        }
        else if (value.isObject()) {
            qDebug()<<keys[i]<<":";
            ParseJsonObject(value.toObject());
        }
        else if (value.isArray()) {
            qDebug()<<keys[i]<<":";
            ParseJsonArray(value.toArray());
        }
    }
    qDebug()<<"}";
}
void ParseJsonArray(const QJsonArray& arr)
{
    qDebug()<<"[";
    for(int i=0;i<arr.size();i++)
    {
        QJsonValue value=arr[i];
        if(value.isDouble())
        {
            qDebug()<<value.toInt()<<",";
        }
        else if (value.isString()) {
            qDebug()<<value.toString()<<",";
        }
        else if (value.isBool()) {
            qDebug()<<value.toBool()<<",";
        }
        else if (value.isObject()) {
            ParseJsonObject(value.toObject());
        }
        else if (value.isArray()) {
            ParseJsonArray(value.toArray());
        }
    }
    qDebug()<<"]";
}
