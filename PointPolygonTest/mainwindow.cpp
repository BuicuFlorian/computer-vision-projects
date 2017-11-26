#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Point Polygon Test");
        errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                                                 "border: 0; padding: 15px;");
    srand (time(NULL));
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

        if ( image.data ) {
            Mat image_copy;
            image.copyTo(image_copy);
            cvtColor(image, image, CV_BGR2RGB);

            QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
            ui->initialImageLabel->setPixmap(QPixmap ::fromImage(img));
            ui->initialImageLabel->resize(ui->initialImageLabel->pixmap()->size());

            vtColor(image_copy, image_copy, CV_BGR2GRAY);
            threshold(image_copy, image2, 128, 255, CV_THRESH_BINARY_INV);

            this->getContours();
        }
    }
}

void MainWindow::getContours()
{
    // Get the contours
    findContours(image2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    // Calculate the distances to the contour
    Mat raw_dist( image2.size(), CV_32FC1 );

    for ( int j = 0; j < image2.rows; j++ ) {
        for ( int i = 0; i < image2.cols; i++ ) {
            raw_dist.at<float>(j,i) = (float)pointPolygonTest( contours[0], Point2f((float)i,(float)j), true );
        }
    }

    double minVal;
    double maxVal;
    minMaxLoc( raw_dist, &minVal, &maxVal, 0, 0, Mat() );
    minVal = abs(minVal); maxVal = abs(maxVal);

    // Depicting the  distances graphically
    drawing = Mat::zeros(image2.size(), CV_8UC3);

    for( int j = 0; j < image2.rows; j++ ) {
        for( int i = 0; i < image2.cols; i++ ) {
            if ( raw_dist.at<float>(j,i) < 0 ) {
                drawing.at<Vec3b>(j,i)[0] = (uchar)(255 - abs(raw_dist.at<float>(j,i)) * 255 / minVal);
            } else if ( raw_dist.at<float>(j,i) > 0 ) {
                drawing.at<Vec3b>(j,i)[2] = (uchar)(255 - raw_dist.at<float>(j,i) * 255 / maxVal);
            } else {
                drawing.at<Vec3b>(j,i)[0] = 255;
                drawing.at<Vec3b>(j,i)[1] = 255;
                drawing.at<Vec3b>(j,i)[2] = 255;
            }
        }
    }

    // Display the result
    QImage img = QImage ((uchar*) drawing.data, drawing.cols, drawing.rows, drawing.step, QImage::Format_RGB888);
    ui->resultImageLabel->setPixmap(QPixmap ::fromImage(img));
    ui->resultImageLabel->resize(ui->resultImageLabel->pixmap()->size());
}
