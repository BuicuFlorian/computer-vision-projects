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

private slots:
    void on_loadImageBtn_clicked();

    void on_saveImageBtn_clicked();

    void on_contururiCheckBox_toggled(bool checked);

    void on_poligoaneCheckBox_toggled(bool checked);

    void on_cercuriCheckBox_toggled(bool checked);

    void on_loadImageBtn_2_clicked();

private:
    Ui::MainWindow *ui;
    Mat image;
    Mat image2;
    Mat resultImage;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    QMessageBox warningBox;
    QMessageBox errorBox;
};

#endif // MAINWINDOW_H
