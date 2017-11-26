#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tightenImgBtn->setEnabled(false);
    ui->equalizeImgBtn->setEnabled(false);
    ui->minValueSlider->setVisible(false);
    ui->label->setVisible(false);
    this->setWindowTitle("Contrast enhancement");
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                                             "border: 0; padding: 15px;");
    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chooseFileBtn_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

    if ( fileName.isEmpty() ) {
        errorBox.setText("Please select an image.");
        errorBox.exec();
    } else {
        image = imread(fileName.toLatin1().data());

        if ( image.data ){
            ui->tightenImgBtn->setEnabled(true);
            ui->equalizeImgBtn->setEnabled(true);
            cvtColor(image, image, CV_BGR2GRAY);

            QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
            ui->imageLabel->setPixmap(QPixmap ::fromImage(img));

            if ( image.rows > ui->imageLabel->width() && image.cols > ui->imageLabel->height() ) {
               ui->imageLabel->setScaledContents( true );
               ui->imageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            }
        }
    }
}

void MainWindow::on_tightenImgBtn_triggered()
{
    int minValue = ui->minValueSlider->value();

    tightImg = tighten(image, minValue);

    this->displayResult(tightImg);

    ui->minValueSlider->setVisible(true);
    ui->label->setVisible(true);
}


void MainWindow::on_equalizeImgBtn_triggered()
{
    equalizeHist(image, equalizedImg);

    this->displayResult(equalizedImg);

    ui->minValueSlider->setVisible(false);
    ui->label->setVisible(false);
}

Mat MainWindow::tighten(const Mat& image, int minValue = 0)
{
    MatND hist = getHistogram(image);
    int imin = 0;

    while (imin < histSize[0] && hist.at<float>(imin) < minValue) {
        imin++;
    }

    int imax = histSize[0] - 1;

    while (imax >= 0 && hist.at<float>(imax) <= minValue) {
        imax--;
    }

    Mat lookup(1, 256, CV_8U);

    for (int i = 0; i < 256; i++) {
        if (i < imin) {
            lookup.at<uchar>(i) = 0;
        } else {
            if (i > imax) {
                lookup.at<uchar>(i) = 255;
            } else {
                lookup.at<uchar>(i) = static_cast<uchar>(255.0 * (i - imin) / (imax - imin) + 0.5);
            }
        }
    }

    Mat result;
    result = applyLookUp(image, lookup);

    return result;
}

MatND MainWindow::getHistogram(const Mat &image)
{
    MatND hist;

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);

    return hist;
}

Mat MainWindow::applyLookUp(const Mat& image, const Mat& lookup)
{
    Mat result;

    LUT(image, lookup, result);

    return result;
}

void MainWindow::on_minValueSlider_valueChanged(int value)
{
    tightImg = tighten(image, value);

    this->displayResult(tightImg);
}

void MainWindow::displayResult(const Mat& image)
{
    QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
    ui->resultImgLabel->setPixmap(QPixmap ::fromImage(img));

    if ( image.rows > ui->resultImgLabel->width() && image.cols > ui->resultImgLabel->height() ) {
       ui->resultImgLabel->setScaledContents( true );
       ui->resultImgLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}
