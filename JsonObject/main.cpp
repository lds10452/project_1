#pragma execution_character_set("utf-8")
#include<iostream>
#include<QFile>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QDebug>
void ParseJsonArray(const QJsonArray& arr,int order);
void ParseJsonObject(const QJsonObject& obj,int order);

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
        ParseJsonObject(doc.object(),0);
    }
    else if(doc.isArray()){
        ParseJsonArray(doc.array(),0);
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

void ParseJsonObject(const QJsonObject& obj,int order)
{
    QString tab="";
    for(int i=0;i<order;i++)
    {
        tab.append('\t');
    }
    qDebug().noquote()<<tab<<"{";
    for(QJsonObject::const_iterator it=obj.begin();it!=obj.end();it++)
    {
        QString key=it.key();
        QJsonValue value=obj[key];
        if(value.isDouble())
        {
            qDebug().noquote()<<tab<<key<<":"<<value.toInt()<<",";
        }
        else if (value.isString()) {
            qDebug().noquote()<<tab<<key<<":"<<value.toString()<<",";
        }
        else if (value.isBool()) {
            qDebug().noquote()<<tab<<key<<":"<<value.toBool()<<",";
        }
        else if (value.isObject()) {
            qDebug().noquote()<<tab<<key<<":";
            ParseJsonObject(value.toObject(),order+1);
        }
        else if (value.isArray()) {
            qDebug().noquote()<<tab<<key<<":";
            ParseJsonArray(value.toArray(),order+1);
        }
    }
    qDebug().noquote()<<tab<<"}";
}
void ParseJsonArray(const QJsonArray& arr,int order)
{
    QString tab="";
    for(int i=0;i<order;i++)
    {
        tab.append('\t');
    }
    qDebug().noquote()<<tab<<"[";
    for(int i=0;i<arr.size();i++)
    {
        QJsonValue value=arr[i];
        if(value.isDouble())
        {
            qDebug().noquote()<<tab<<value.toInt()<<",";
        }
        else if (value.isString()) {
            qDebug().noquote()<<tab<<value.toString()<<",";
        }
        else if (value.isBool()) {
            qDebug().noquote()<<tab<<value.toBool()<<",";
        }
        else if (value.isObject()) {
            ParseJsonObject(value.toObject(),order+1);
        }
        else if (value.isArray()) {
            ParseJsonArray(value.toArray(),order+1);
        }
    }
    qDebug().noquote()<<tab<<"]";
}
