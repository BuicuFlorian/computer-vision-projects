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

    void on_chooseFileBtn_triggered();

    void on_saveImageBtn_triggered();

    void on_flipVerticallyBtn_triggered();

    void on_flipHorizontallyBtn_triggered();

    void on_flipHorizontallyVerticallyBtn_triggered();

private:
    Ui::MainWindow *ui;
    Mat image;
};

#endif // MAINWINDOW_H
