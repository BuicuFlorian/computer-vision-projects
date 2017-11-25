#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMessageBox>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateFrame();

private slots:

    void on_loadVideoBtn_triggered();

    void on_playVideoBtn_triggered();

    void on_stopVideoBtn_triggered();

    void getContours();

private:
    Ui::MainWindow *ui;
    VideoCapture cap;
    Mat frame;
    Mat frame2;
    Mat resultFrame;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    QTimer *timer;
};

#endif // MAINWINDOW_H
