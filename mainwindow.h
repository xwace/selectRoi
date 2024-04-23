#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


signals:
    void touch(void);

private slots:
    void readImg(void);
    void on_pB_PlayVideo_clicked();

private:
    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;

private:
        QPixmap pixImg,pixImg_d;
        QPoint rectStartPt,rectEndPt;
        bool inRect(const Ui::MainWindow* ui,QMouseEvent* event);
};

#endif // MAINWINDOW_H
