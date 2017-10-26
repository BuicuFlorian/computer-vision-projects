#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMessageBox>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

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

public slots:
    void updateFrame();

private slots:
    void on_loadVideoBtn_clicked();

    void on_playVideoBtn_clicked();

    void on_stopVideoBtn_clicked();

    void on_chooseLogoBtn_clicked();

private:
    Ui::MainWindow *ui;
    VideoCapture cap;
    Mat frame;
    Mat logo;
    Mat frameROI;
    QTimer *timer;
    QMessageBox msgBox;
};

#endif // MAINWINDOW_H
