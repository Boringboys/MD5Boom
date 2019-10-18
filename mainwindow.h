#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QProgressBar>
#include <mythread.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void btn_begin_onclicked();
    void get_success_str(QString str);
    void get_progress(int num);

signals:
    void sendData(QString str);

private:
    QLabel *lab_input;
    QLabel *lab_output;
    QLabel *lab_progress;
    QLineEdit *input_text;
    QLineEdit *output_text;
    QPushButton *btn_begin;
    QProgressBar *progressbar;

    QGridLayout *mainlayout;

    QWidget *widget;

    MyThread *thread;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
