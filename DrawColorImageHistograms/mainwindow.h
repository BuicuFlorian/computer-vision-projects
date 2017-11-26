#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMessageBox>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
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

private slots:
    void on_loadImgBtn_triggered();

    void on_drawHistBtn_triggered();

    Mat getHistograms(const Mat &image);

private:
    Ui::MainWindow *ui;
    QMessageBox errorBox;
    Mat image;
    Mat histograms;
    Mat blueHist, greenHist, redHist;
    int channels[3];
    bool uniform = true;
    bool accumulate = false;
    vector<Mat> bgr_planes;
    int histSize = 256;
    float range[2];
    const float* histRange;
};

#endif // MAINWINDOW_H
