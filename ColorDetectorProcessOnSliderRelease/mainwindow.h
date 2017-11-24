#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMessageBox>
#include <QColorDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "colordetector.h"

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

    void on_chooseColorBtn_triggered();

    void on_setColorDistanceSlider_valueChanged(int value);

    void on_setColorDistanceSlider_sliderReleased();

    void on_manhattanRadioBtn_toggled(bool checked);

    void on_saveImageBtn_triggered();

    void on_euclideanRadioBtn_toggled(bool checked);

    void on_chebyshevRadioBtn_toggled(bool checked);

    void on_minkowskiRadioBtn_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QMessageBox errorBox;
    Mat image;
    Mat result;
    ColorDetector cDetect;
    int colorDistanceThreshold;
};

#endif // MAINWINDOW_H
