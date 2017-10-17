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
    void on_selectImageBtn_clicked();

    void on_flipHorizontallyBtn_clicked();

    void on_flipVerticallyBtn_clicked();

    void on_flipHorizontallyVerticallyBtn_clicked();

    void on_saveImageBtn_clicked();

private:
    Ui::MainWindow *ui;
    Mat poza;
};

#endif // MAINWINDOW_H
