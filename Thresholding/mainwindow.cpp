#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
            cvtColor(image, image, CV_BGR2GRAY);

            QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
            ui->image1->setPixmap(QPixmap ::fromImage(img));

            if ( image.rows > ui->image1->width() && image.cols > ui->image1->height() ) {
                ui->image1->setScaledContents( true );
                ui->image1->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            }
        }
   }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    threshold1 = value;
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    threshold2 = value;
}


void MainWindow::on_threshBinaryCheckBox_toggled(bool checked)
{
    if (checked == true) {
        threshold(image, thresholdedBinary, threshold1, threshold2, THRESH_BINARY);

        QImage img = QImage ((uchar*) thresholdedBinary.data, thresholdedBinary.cols, thresholdedBinary.rows, thresholdedBinary.step, QImage::Format_Indexed8);
        ui->image2->setPixmap(QPixmap ::fromImage(img));

        if ( thresholdedBinary.rows > ui->image2->width() && thresholdedBinary.cols > ui->image2->height() ) {
            ui->image2->setScaledContents( true );
            ui->image2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_threshBinaryInvCheckBox_toggled(bool checked)
{
    if (checked == true) {
        threshold(image, thresholdedBinaryInv, threshold1, threshold2, THRESH_BINARY_INV);

        QImage img = QImage ((uchar*) thresholdedBinaryInv.data, thresholdedBinaryInv.cols, thresholdedBinaryInv.rows, thresholdedBinaryInv.step, QImage::Format_Indexed8);
        ui->image3->setPixmap(QPixmap ::fromImage(img));

        if ( thresholdedBinaryInv.rows > ui->image3->width() && thresholdedBinaryInv.cols > ui->image3->height() ) {
            ui->image3->setScaledContents( true );
            ui->image3->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_threshTruncCheckBox_toggled(bool checked)
{
    if (checked == true) {
        threshold(image, thresholdedTrunc, threshold1, threshold2, THRESH_TRUNC);

        QImage img = QImage ((uchar*) thresholdedTrunc.data, thresholdedTrunc.cols, thresholdedTrunc.rows, thresholdedTrunc.step, QImage::Format_Indexed8);
        ui->image4->setPixmap(QPixmap ::fromImage(img));

        if ( thresholdedTrunc.rows > ui->image2->width() && thresholdedTrunc.cols > ui->image4->height() ) {
            ui->image4->setScaledContents( true );
            ui->image4->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_treshTozeroRadioBox_toggled(bool checked)
{
    if (checked == true) {
        threshold(image, thresholdedTozero, threshold1, threshold2, THRESH_TOZERO);

        QImage img = QImage ((uchar*) thresholdedTozero.data, thresholdedTozero.cols, thresholdedTozero.rows, thresholdedTozero.step, QImage::Format_Indexed8);
        ui->image5->setPixmap(QPixmap ::fromImage(img));

        if ( thresholdedTozero.rows > ui->image5->width() && thresholdedTozero.cols > ui->image5->height() ) {
            ui->image5->setScaledContents( true );
            ui->image5->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_treshTozeroInvRadioBox_toggled(bool checked)
{
    if (checked == true) {
        threshold(image, thresholdedTozeroInv, threshold1, threshold2, THRESH_TOZERO_INV);

        QImage img = QImage ((uchar*) thresholdedTozeroInv.data, thresholdedTozeroInv.cols, thresholdedTozeroInv.rows, thresholdedTozeroInv.step, QImage::Format_Indexed8);
        ui->image6->setPixmap(QPixmap ::fromImage(img));

        if ( thresholdedTozeroInv.rows > ui->image2->width() && thresholdedTozeroInv.cols > ui->image6->height() ) {
            ui->image6->setScaledContents( true );
            ui->image6->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}
