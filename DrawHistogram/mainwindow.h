#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMessageBox>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
    void on_loadImgBtn_clicked();

    void on_drawHistBtn_clicked();

    MatND getHistogram(const Mat &image);

    Mat getHistogramImage(const Mat &image);

private:
    Ui::MainWindow *ui;
    QMessageBox errorBox;
    Mat image;
    Mat histogram;
    int histSize[1];
    float hranges[2];
    const float* ranges[1];
    int channels[1];
};

#endif // MAINWINDOW_H
