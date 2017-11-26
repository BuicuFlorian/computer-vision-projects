#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
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
    void on_chooseFileBtn_triggered();

    void on_tightenImgBtn_triggered();

    void on_equalizeImgBtn_triggered();

    Mat tighten(const Mat& image, int minValue);

    MatND getHistogram(const Mat &image);

    Mat applyLookUp(const Mat& image, const Mat& lookup);

    void on_minValueSlider_valueChanged(int value);

    void displayResult(const Mat& image);

private:
    Ui::MainWindow *ui;
    QMessageBox errorBox;
    Mat image;
    Mat tightImg;
    Mat equalizedImg;
    int histSize[1];
    float hranges[2];
    const float* ranges[1];
    int channels[1];
};

#endif // MAINWINDOW_H
