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

    void on_threshBinaryCheckBox_toggled(bool checked);

    void on_threshBinaryInvCheckBox_toggled(bool checked);

    void on_threshTruncCheckBox_toggled(bool checked);

    void on_treshTozeroRadioBox_toggled(bool checked);

    void on_treshTozeroInvRadioBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    Mat image;
    Mat thresholdedBinary;
    Mat thresholdedBinaryInv;
    Mat thresholdedTrunc;
    Mat thresholdedTozero;
    Mat thresholdedTozeroInv;
    QMessageBox errorBox;
    int threshold1;
    int threshold2;
};

#endif // MAINWINDOW_H
