#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMessageBox>
#include <QPainter>
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
    void on_selectImageBtn_clicked();

    void on_selectImageBtn2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_mergeImagesBtn_clicked();

    void on_saveImageBtn_clicked();

private:
    Ui::MainWindow *ui;
    Mat image1;
    Mat image2;
    Mat imageWithRect;
    Mat resultImage;
    Mat imageROI;
    bool imageFormatQt;
    QMessageBox warningBox;
    QMessageBox errorBox;
    int x = 1;
    int y = 1;
    Point point1, point2;
};

#endif // MAINWINDOW_H
