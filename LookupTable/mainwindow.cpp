#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Lookup table");
    ui->applyLookupTableBtn->setEnabled(false);
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                                             "border: 0; padding: 15px;");
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
            ui->applyLookupTableBtn->setEnabled(true);
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

void MainWindow::on_applyLookupTableBtn_triggered()
{
    Mat lut(1, 256, CV_8U);

    for (int i = 0; i < 256; i++) {
        lut.at<uchar>(i) = 256 - i;
    }

    resultImg = applyLookUp(image, lut);

    QImage img = QImage ((uchar*) resultImg.data, resultImg.cols, resultImg.rows, resultImg.step, QImage::Format_Indexed8);
    ui->lookupImgLabel->setPixmap(QPixmap ::fromImage(img));

    if ( resultImg.rows > ui->lookupImgLabel->width() && resultImg.cols > ui->lookupImgLabel->height() ) {
       ui->lookupImgLabel->setScaledContents( true );
       ui->lookupImgLabel->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

Mat MainWindow::applyLookUp(const Mat& image, const Mat& lookup)
{
    Mat result;

    LUT(image, lookup, result);

    return result;
}
