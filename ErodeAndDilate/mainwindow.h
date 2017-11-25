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

    void on_squareShape_triggered();

    void on_rhombusShape_triggered();

    void on_crossShape_triggered();

    void on_xShape_triggered();

    void on_strcutElemDim_textChanged(const QString &arg1);

    void on_erodeImageBtn_triggered();

    void on_dilateImageBtn_triggered();

    void displayImage(Mat image);

    void enableProcessingBtns();

private:
    Ui::MainWindow *ui;
    QMessageBox errorBox;
    Mat image;
    Mat erodedImage;
    Mat dilatedImage;
    Mat element;
    Mat square;
    Mat rhombus;
    Mat cross;
    Mat x;
    double structElemDim;
};

#endif // MAINWINDOW_H
