#include "mythread.h"
#include <QDebug>

MyThread::MyThread()
{
    getstr = "";
    IsGetString = false;
}

void MyThread::run()
{
    int dicNum = 0;
    qDebug()<<"正在打开字典文件...";
    QFile file("dic_ntlm.dic");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开成功";
        while (!file.atEnd())
        {
            file.readLine();
            dicNum++;
        }
        file.close();
    }
    else
    {
        qDebug()<<"打开失败";
    }
    //等待从主线程获得要破解的密文
    while(!IsGetString)
    {
        qDebug()<<"wait...";
        msleep(500);
    }



    qDebug()<<"ready!";
    qDebug()<<getstr;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开成功";
        int i = 0;
        while (!file.atEnd())
        {
            i++;
            QString str = file.readLine();
            str.remove("\n");
            qDebug()<<str;

            QString temphex = str.toUtf8().toHex();
            qDebug()<<temphex;
            qDebug()<<temphex.length();
            QString tempunicode = "";
            for(int i=0;i<temphex.length();)
            {
                tempunicode += temphex[i];
                tempunicode += temphex[i+1];
                tempunicode += "00";
                i+=2;
            }
            qDebug()<<tempunicode;
            QByteArray bytes = tempunicode.toUtf8();
            qDebug()<<bytes;

            QString md4encrypto = QCryptographicHash::hash(QByteArray::fromHex(tempunicode.toUtf8()),QCryptographicHash::Md4).toHex();
            qDebug()<<md4encrypto;

            if(md4encrypto == getstr)
            {
                emit boomSuccess(str);
                qDebug()<<"爆破成功！";
                file.close();
                return;
            }
            else
            {
                qDebug()<<i*100/dicNum;
                emit sendProgress(i*100/dicNum);
//                msleep(50);
            }

        }
        file.close();
    }
    else
    {
        qDebug()<<"打开失败";
    }
}

void MyThread::receiveData(QString str)
{
    getstr = str;
    IsGetString = true;
}
