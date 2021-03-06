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
#include "characteristics.h"

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

    void on_strcutElemDim_returnPressed();

private:
    Ui::MainWindow *ui;
    QMessageBox errorBox;
    Mat image;
    Mat result;
    double structElemDim;
    Characteristics morf;
};

#endif // MAINWINDOW_H
