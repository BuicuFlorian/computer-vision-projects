#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Edge detection");
    ui->saveImageBtn->setEnabled(false);
    errorBox.setText("Please select an image.");
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                            "border: 0; padding: 15px;");
    errorBox.QDialog::setWindowTitle("Error");
    warningBox.setStyleSheet("background-color: #ff7518; color: #ffffff; font-size: 21px; "
                              "border: 0; padding: 15px;");
    warningBox.QDialog::setWindowTitle("Warning");
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    treshold1 = value;

    if ( treshold1 < treshold2 ) {
        Canny(image, resultImage, treshold1, treshold2, 3);

        QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_Indexed8);
        ui->cannyImage->setPixmap(QPixmap ::fromImage(img, Qt::AutoColor));

        if ( resultImage.rows > ui->cannyImage->width() && resultImage.cols > ui->cannyImage->height() ) {
            ui->cannyImage->setScaledContents( true );
            ui->cannyImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    treshold2 = value;

    if ( treshold1 < treshold2 ) {
        Canny(image, resultImage, treshold1, treshold2, 3);

        QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_Indexed8);
        ui->cannyImage->setPixmap(QPixmap ::fromImage(img, Qt::AutoColor));

        if ( resultImage.rows > ui->cannyImage->width() && resultImage.cols > ui->cannyImage->height() ) {
            ui->cannyImage->setScaledContents( true );
            ui->cannyImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
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
        if ( treshold1 < treshold2 ) {
            imwrite(fileName.toLatin1().data(), resultImage);
        } else {
            warningBox.setText("Treshold 1 should be lower than trehsold 2.");
            warningBox.exec();
        }
    }
}
