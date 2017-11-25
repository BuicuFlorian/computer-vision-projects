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
#include "watershedsegmenter.h"

using namespace cv;

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

private:
    Ui::MainWindow *ui;
    VideoCapture cap;
    Mat frame;
    Mat binary;
    Mat foreground;
    Mat background;
    Mat structuralElement;
    Mat result;
    QTimer *timer;
    WatershedSegmenter segment;
};

#endif // MAINWINDOW_H
