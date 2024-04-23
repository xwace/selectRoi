#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDateTime"
#include <qthread.h>
#include <iostream>
#include <QTime>
#include <QTimer>
#include <QtGui>
#include <qwaitcondition.h>
#include <qdesktopwidget.h>
#include <qmessagebox.h>
#include <qfilesystemmodel.h>
#include <memory>
#include <opencv2/opencv.hpp>
QTimer* my_timer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(touch(void)),this,SLOT(readImg(void)));

    my_timer = new QTimer(this);//多线程，一个执行功能的类
    connect(my_timer,&QTimer::timeout,this,[=]{
        QThread::msleep(1000);
        QDateTime date_t= QDateTime::currentDateTime();
        ui->lcdNumber->display(date_t.toString("yyyy:MM:dd:HH:mm:ss"));
     });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pB_PlayVideo_clicked(){
    emit touch();
    my_timer->start(500);
}

void MainWindow::readImg(){
    int x, y, w, h;

    pixImg.load("1.png");
    ui->showImg->geometry().getRect(&x,&y,&w,&h);
    pixImg_d = pixImg.scaled(w,h);
    ui->showImg->setPixmap(pixImg_d);
    ui->showImg->show();
}

bool MainWindow::inRect(const Ui::MainWindow* ui,QMouseEvent* event){
    int x,y,w,h;
    ui->showImg->geometry().getRect(&x,&y,&w,&h);

    QRect rect{x,y,w,h};

    return rect.contains(event->x(),event->y());
}


void MainWindow::mousePressEvent(QMouseEvent* event){
    if(!inRect(ui,event)) return;

    rectStartPt.setX(event->x());
    rectStartPt.setY(event->y());
}

void MainWindow::mouseMoveEvent(QMouseEvent* event){
    if(!inRect(ui,event)) return;

    QPainter painter;
    QPixmap pixImg_;

    int x,y,w,h;
    int xmin = std::min(event->x(), rectStartPt.x());
    int ymin = std::min(event->y(), rectStartPt.y());
    int dx = std::abs(event->x() - rectStartPt.x());
    int dy = std::abs(event->y() - rectStartPt.y());

    ui->showImg->geometry().getRect(&x,&y,&w,&h);

    xmin = xmin - x;
    ymin = ymin - y - 13;//13为看图画的经验值
    pixImg_d = pixImg.scaled(w,h);
    pixImg_ = pixImg_d.copy();
    painter.begin(&pixImg_);
    painter.drawRect(xmin,ymin,dx,dy);
    painter.end();

    ui->showImg->setPixmap(pixImg_);
    ui->showImg->show();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event){

}
