#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QFile>
#include <QByteArray>
#include <QCryptographicHash>

class MyThread : public QThread
{
    Q_OBJECT
public slots:
    void receiveData(QString str);

signals:
    void sendProgress(int num1);
    void boomSuccess(QString str);

public:
    MyThread();

protected:
    virtual void run();

private:
    QString getstr;
    volatile bool IsGetString;
};

#endif // MYTHREAD_H
