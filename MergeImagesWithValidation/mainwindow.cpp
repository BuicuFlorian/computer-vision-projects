#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Merge images");
    ui->mergeImagesBtn->setEnabled(false);
    ui->saveImageBtn->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->verticalSlider->setEnabled(false);
    imageFormatQt = false;
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

void MainWindow::on_selectImageBtn_clicked()
{
       QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

        if( fileName.isEmpty() ) {
           errorBox.exec();
        } else {
           image1 = imread(fileName.toLatin1().data());

            if ( image1.data && image2.data )
				ui->mergeImagesBtn->setEnabled(true);

            cvtColor(image1, image1, CV_BGR2RGB);
            imageFormatQt = true;

            QImage img = QImage ((uchar*) image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
            ui->firstImage->setPixmap(QPixmap ::fromImage(img));

            if ( image1.rows > ui->firstImage->width() && image1.cols > ui->firstImage->height() ) {
				ui->firstImage->setScaledContents( true );
                ui->firstImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            }
      }
}

void MainWindow::on_selectImageBtn2_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

    if( fileName.isEmpty() ) {
        errorBox.exec();
    } else {
        image2 = imread(fileName.toLatin1().data());

        if ( image2.data && image1.data )
            ui->mergeImagesBtn->setEnabled(true);
            ui->horizontalSlider->setEnabled(true);
            ui->verticalSlider->setEnabled(true);

        cvtColor(image2, image2, CV_BGR2RGB);
        imageFormatQt = true;

        QImage img = QImage ((uchar*) image2.data, image2.cols, image2.rows, image2.step, QImage::Format_RGB888);
        ui->secondImage->setPixmap(QPixmap ::fromImage(img));

        if ( image2.rows > ui->secondImage->width() && image2.cols > ui->secondImage->height() ) {
			ui->secondImage->setScaledContents( true );
            ui->secondImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    x = value;
    point1 = Point(x, y);
    point2 = Point(x + image1.cols, y + image1.rows);
    image2.copyTo(imageWithRect);
    rectangle(imageWithRect, point1, point2, CV_RGB(255, 0, 0), 2, 8, 0);

    QImage img = QImage ((uchar*) imageWithRect.data, imageWithRect.cols, imageWithRect.rows, imageWithRect.step, QImage::Format_RGB888);
    ui->secondImage->setPixmap(QPixmap ::fromImage(img));

    if ( imageWithRect.rows > ui->secondImage->width() && imageWithRect.cols > ui->secondImage->height() ) {
        ui->secondImage->setScaledContents( true );
        ui->secondImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    y = value;
    point1 = Point(x, y);
    point2 = Point(x + image1.cols, y + image1.rows);
    image2.copyTo(imageWithRect);
    rectangle(imageWithRect, point1, point2, CV_RGB(255, 0, 0), 2, 8, 0);

    QImage img = QImage ((uchar*) imageWithRect.data, imageWithRect.cols, imageWithRect.rows, imageWithRect.step, QImage::Format_RGB888);
    ui->secondImage->setPixmap(QPixmap ::fromImage(img));

    if ( imageWithRect.rows > ui->secondImage->width() && imageWithRect.cols > ui->secondImage->height() ) {
        ui->secondImage->setScaledContents( true );
        ui->secondImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void MainWindow::on_mergeImagesBtn_clicked()
{

    if( x + image1.cols <= image2.cols && y + image1.rows <= image2.rows )
	{
		ui->saveImageBtn->setEnabled(true);

        image2.copyTo(resultImage);
        imageROI = resultImage(Rect(x, y, image1.cols, image1.rows));
        addWeighted(imageROI, 1.0, image1, 0.3, 0., imageROI);

        QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_RGB888);
        ui->mergedImages->setPixmap(QPixmap ::fromImage(img));

        if ( ui->mergedImages->width() < resultImage.rows && ui->mergedImages->height() < resultImage.cols ) {
            ui->mergedImages->setScaledContents( true );
            ui->mergedImages->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    } else {
        warningBox.setText("First image can't fit in the second image!");
        warningBox.exec();
    }
}

void MainWindow::on_saveImageBtn_clicked()
{      
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if ( fileName.isEmpty() ) {
        warningBox.setText("Your file was not saved.");
        warningBox.exec();
    } else {
        if ( imageFormatQt ) {
            cvtColor(resultImage, resultImage, CV_RGB2BGR);
            imageFormatQt = false;
        }

        imwrite(fileName.toLatin1().data(), resultImage);
    }
}
