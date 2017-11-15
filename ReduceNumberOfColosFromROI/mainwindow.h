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

    void on_horizontalSlider_valueChanged(int value);

    void on_verticalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_verticalSlider_2_valueChanged(int value);

    void on_reduceColorsSlider_valueChanged(int value);

    void drawRect();

private:
    Ui::MainWindow *ui;
    Mat image1;
    Mat imageWithRect;
    Mat imageROI;
    Mat reducedROI;
    QMessageBox errorBox;
    Point point1, point2;
    int x1, x2, y1, y2;
};

#endif // MAINWINDOW_H
