#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    ui->saveImageBtn->setEnabled(false);
    errorBox.setText("Please select an image.");
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                            "border: 0; padding: 15px;");
    errorBox.QDialog::setWindowTitle("Error");
    warningBox.setStyleSheet("background-color: #ff7518; color: #ffffff; font-size: 21px; "
                              "border: 0; padding: 15px;");
    warningBox.QDialog::setWindowTitle("Warning");
    srand (time(NULL));
}

void MainWindow::on_loadImageBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

     if( fileName.isEmpty() ) {
        errorBox.exec();
     } else {
        image = imread(fileName.toLatin1().data());

         if ( image.data )
             ui->saveImageBtn->setEnabled(true);

         cvtColor(image, image, CV_BGR2RGB);

         QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
         ui->image->setPixmap(QPixmap ::fromImage(img));

         if ( image.rows > ui->image->width() && image.cols > ui->image->height() ) {
             ui->image->setScaledContents( true );
             ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
         }
   }
}

void MainWindow::on_loadImageBtn_2_clicked()
{
    Canny(image, image2, 100, 200, 3);

    resultImage = Mat::zeros( image2.size(), CV_8UC3 );

    QImage img = QImage ((uchar*) image2.data, image2.cols, image2.rows, image2.step, QImage::Format_Indexed8);
    ui->image2->setPixmap(QPixmap ::fromImage(img, Qt::AutoColor));

    if ( image2.rows > ui->image2->width() && image2.cols > ui->image2->height() ) {
        ui->image2->setScaledContents( true );
        ui->image2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void MainWindow::on_contururiCheckBox_toggled(bool checked)
{
    if (checked == true) {
        findContours( image2, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

        for( size_t i = 0; i < contours.size(); i++ ) {
            Scalar color = Scalar( rand() % 256, rand() % 256, rand() % 256 );
            drawContours( resultImage, contours, i, color, 2, 8, hierarchy, 0, Point());
        }

        QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_RGB888);
        ui->resultImg->setPixmap(QPixmap ::fromImage(img));
        if ( resultImage.rows > ui->resultImg->width() && resultImage.cols > ui->resultImg->height() ) {
            ui->resultImg->setScaledContents( true );
            ui->resultImg->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_poligoaneCheckBox_toggled(bool checked)
{
    if (checked == true) {
        vector<vector<Point> > contours_poly( contours.size() );

        for( size_t i = 0; i < contours.size(); i++ ) {
            approxPolyDP( Mat(contours[i]), contours_poly[i], 10, true );
        }

        for ( size_t i = 0; i < contours.size(); i++ ) {
            Scalar color = Scalar( rand() % 256, rand() % 256, rand() % 256 );
            drawContours( resultImage, contours_poly, i, color, 2, 8, hierarchy, 0, Point());
        }

        QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_RGB888);
        ui->resultImg->setPixmap(QPixmap ::fromImage(img));

        if ( resultImage.rows > ui->resultImg->width() && resultImage.cols > ui->resultImg->height() ) {
            ui->resultImg->setScaledContents( true );
            ui->resultImg->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_cercuriCheckBox_toggled(bool checked)
{
    if (checked == true) {
        vector<Point2f> center( contours.size() );
        vector<float> radius( contours.size() );

        for( size_t i = 0; i < contours.size(); i++ ) {
            minEnclosingCircle( Mat(contours[i]), center[i], radius[i] );
        }

        for ( size_t i = 0; i < contours.size(); i++ ) {
            Scalar color = Scalar( rand() % 256, rand() % 256, rand() % 256 );
            circle( resultImage, center[i], (int)radius[i], color, 2, 8, 0 );
        }

        QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_RGB888);
        ui->resultImg->setPixmap(QPixmap ::fromImage(img));

        if ( resultImage.rows > ui->resultImg->width() && resultImage.cols > ui->resultImg->height() ) {
            ui->resultImg->setScaledContents( true );
            ui->resultImg->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_saveImageBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if ( fileName.isEmpty() ) {
        warningBox.setText("Your file was not saved.");
        warningBox.exec();
    } else {
        imwrite(fileName.toLatin1().data(), image);
    }
}
