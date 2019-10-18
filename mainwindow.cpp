#include "mainwindow.h"
#include <QFile>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Windows NTLM爆破 by Boringboys");
    setMinimumSize(650,200);

    lab_input = new QLabel("密文:");
    lab_output = new QLabel("明文:");
    lab_progress = new QLabel("进度:");
    input_text = new QLineEdit;
    output_text = new QLineEdit;
    output_text->setFocusPolicy(Qt::NoFocus);
    progressbar = new QProgressBar;
    progressbar->setValue(0);
    btn_begin = new QPushButton("开始");

    mainlayout = new QGridLayout;
    mainlayout->addWidget(lab_input,0,0,1,1);
    mainlayout->addWidget(lab_output,1,0,1,1);
    mainlayout->addWidget(input_text,0,1,1,3);
    mainlayout->addWidget(output_text,1,1,1,3);
    mainlayout->addWidget(lab_progress,2,0,1,1);
    mainlayout->addWidget(progressbar,2,1,1,3);
    mainlayout->addWidget(btn_begin,3,3,1,1);

    widget = new QWidget;
    this->setCentralWidget(widget);
    widget->setLayout(mainlayout);

    mainlayout->setMargin(15);
    mainlayout->setSpacing(5);

    thread = new MyThread;

    connect(btn_begin,&QPushButton::clicked,this,&MainWindow::btn_begin_onclicked);
    connect(this,&MainWindow::sendData,thread,&MyThread::receiveData);
    connect(thread,&MyThread::boomSuccess,this,&MainWindow::get_success_str);
    connect(thread,&MyThread::sendProgress,this,&MainWindow::get_progress);
}

void MainWindow::btn_begin_onclicked()
{
    qDebug()<<"btn_begin_onclicked！";
    if(thread->isRunning())
    {
        qDebug()<<"thread is running!";
        thread->wait();
    }
    thread->start();

    while (true)
    {
        if(thread->isRunning())
        {
            qDebug()<<"thread started!";
            break;
        }
    }

    qDebug()<<"sendData!";
    emit sendData(input_text->text());
}

void MainWindow::get_progress(int num)
{
    progressbar->setValue(num);
}

void MainWindow::get_success_str(QString str)
{
    output_text->setText(str);
    while(progressbar->value()<100)
    {
        progressbar->setValue(progressbar->value()+1);
    }
}

MainWindow::~MainWindow()
{

}
