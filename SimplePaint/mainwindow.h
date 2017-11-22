#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
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

    void Mouse_pressed();

    void on_chooseFileBtn_triggered();

    void on_arrowedLineRadioBtn_toggled(bool arg1);

    void on_lineRadioBtn_toggled(bool arg1);

    void on_rectRadioBtn_toggled(bool arg1);

    void on_circleRadioBtn_toggled(bool arg1);

    void drawShape();

    void on_saveFileBtn_triggered();


private:
    Ui::MainWindow *ui;
    Point point1, point2;
    int x1, y1, x2, y2;
    bool clicked = true;
    String drawOption;
    QMessageBox errorBox;
    Mat image;
};

#endif // MAINWINDOW_H
