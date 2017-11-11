#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->drawHistBtn->setEnabled(false);
    histSize[0] = 256;
    hranges[0] = 0.0;
    hranges[1] = 255.0;
    ranges[0] = hranges;
    channels[0] = 0;
    errorBox.setText("Please select an image.");
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                            "border: 0; padding: 15px;");
    errorBox.QDialog::setWindowTitle("Error");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadImgBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), "D:\Images1");

     if( fileName.isEmpty() ) {
        errorBox.exec();
     } else {
        image = imread(fileName.toLatin1().data());

         if ( image.data ) {
             ui->drawHistBtn->setEnabled(true);
             cvtColor(image, image, CV_BGR2GRAY);

             QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
             ui->image->setPixmap(QPixmap ::fromImage(img));

             if ( image.rows > ui->image->width() && image.cols > ui->image->height() ) {
                 ui->image->setScaledContents( true );
                 ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
             }
         }
   }
}

void MainWindow::on_drawHistBtn_clicked()
{
    histogram = getHistogramImage(image);

    QImage img = QImage ((uchar*) histogram.data, histogram.cols, histogram.rows, histogram.step, QImage::Format_Indexed8);
    ui->histogram->setPixmap(QPixmap ::fromImage(img));

    if ( histogram.rows > ui->histogram->width() && histogram.cols > ui->histogram->height() ) {
        ui->histogram->setScaledContents( true );
        ui->histogram->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

Mat MainWindow::getHistogramImage(const Mat &image)
{
    MatND histo = getHistogram(image);

    double maxVal = 0;
    double minVal = 0;
    minMaxLoc(histo, &minVal, &maxVal, 0, 0);

    Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));
    int hpt = static_cast<int>(0.9*histSize[0]);

    for (int h = 0; h < histSize[0]; h++) {
        float binVal = histo.at<float>(h);
        int intensity = static_cast<int>(binVal*hpt/maxVal);
        line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
    }

    return histImg;
}

MatND MainWindow::getHistogram(const Mat &image)
{
    MatND hist;

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);

    return hist;
}
