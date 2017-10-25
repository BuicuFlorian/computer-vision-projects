#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMessageBox>
#include <QDirIterator>
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
    void on_loadImages1_clicked();

    void on_nextBtn1_clicked();

    void on_previousBtn1_clicked();

    void on_horizontalSlider1_valueChanged(int value);

    void on_loadImages2_clicked();

    void on_nextBtn2_clicked();

    void on_previousBtn2_clicked();

    void on_horizontalSlider2_valueChanged(int value);

    void on_processImageBtn_clicked();

    void on_saveBtn_clicked();

    void on_addNoiseBtn_clicked();

    void on_addNoiseBtn2_clicked();

private:
    Ui::MainWindow *ui;
    Mat image1;
    Mat image2;
    Mat resultImage;
    Mat imageROI;
    int weight1 = 1;
    int weight2 = 1;
    int fileFirstDir;
    int fileSecondDir;
    bool imageFormatQt;
    QMessageBox warningBox;
    QMessageBox errorBox;
};

#endif // MAINWINDOW_H
