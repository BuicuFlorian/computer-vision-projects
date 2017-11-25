#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Inner contours");
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
            cvtColor(image, image, CV_BGR2GRAY);
            threshold(image, image2, 128, 255, CV_THRESH_BINARY_INV);

            QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
            ui->initialImageLabel->setPixmap(QPixmap ::fromImage(img));

            if ( image.rows > ui->initialImageLabel->width() && image.cols > ui->initialImageLabel->height() ) {
                ui->initialImageLabel->setScaledContents( true );
                ui->initialImageLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            }

            this->getContours();
        }
    }
}

void MainWindow::getContours()

{
    findContours( image2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    resultImage = Mat::zeros( image2.size(), CV_8UC3 );

    for( size_t i = 0; i < contours.size(); i++ ) {
        Scalar color = Scalar( rand() % 256, rand() % 256, rand() % 256 );
        drawContours( resultImage, contours, i, color, 2, 8, hierarchy, 0, Point());
    }

    QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_RGB888);
    ui->resultLabel->setPixmap(QPixmap ::fromImage(img));

    if ( resultImage.rows > ui->resultLabel->width() && resultImage.cols > ui->resultLabel->height() ) {
        ui->resultLabel->setScaledContents( true );
        ui->resultLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}
