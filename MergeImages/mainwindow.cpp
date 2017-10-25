#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Merge images");
    ui->nextBtn1->setEnabled(false);
    ui->previousBtn1->setEnabled(false);
    ui->horizontalSlider1->setEnabled(false);
    ui->addNoiseBtn->setEnabled(false);
    ui->nextBtn2->setEnabled(false);
    ui->previousBtn2->setEnabled(false);
    ui->horizontalSlider2->setEnabled(false);
    ui->addNoiseBtn2->setEnabled(false);
    ui->processImageBtn->setEnabled(false);
    ui->saveBtn->setEnabled(false);
    imageFormatQt = false;
    errorBox.setText("No files found!");
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                           "border: 0; padding: 15px;");
    errorBox.QDialog::setWindowTitle("Error");
    warningBox.setText("Your file was not saved.");
    warningBox.setStyleSheet("background-color: #ff7518; color: #ffffff; font-size: 21px; "
                             "border: 0; padding: 15px;");
    warningBox.QDialog::setWindowTitle("Warning");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadImages1_clicked()
{
    QDir directory("D:/Images1");
    QStringList images = directory.entryList(QStringList(), QDir::Files);

    if ( images.size() > 0 ) {
        fileFirstDir = 0;
        image1 = imread("D:/Images1/"  + images.at(fileFirstDir).toStdString());
    }

    if ( image1.data ) {
        if( images.size() > 1 ) {
            ui->nextBtn1->setEnabled(true);
        }

        if( image2.data ) {
            ui->processImageBtn->setEnabled(true);
        }

        ui->horizontalSlider1->setEnabled(true);
        ui->addNoiseBtn->setEnabled(true);

        cvtColor(image1, image1, CV_BGR2RGB);
        imageFormatQt = true;

        QImage img = QImage ((uchar*) image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
        ui->firsImage->setPixmap(QPixmap ::fromImage(img));

        if ( ui->firsImage->width() < image1.rows && ui->firsImage->height() < image1.cols ) {
            ui->firsImage->setScaledContents( true );
            ui->firsImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    } else {
        errorBox.exec();
    }
}


void MainWindow::on_nextBtn1_clicked()
{
    fileFirstDir++;
    QDir directory("D:/Images1");
    QStringList images = directory.entryList(QStringList(), QDir::Files);

    if( fileFirstDir > 0 ) {
        ui->previousBtn1->setEnabled(true);
    }

    if ( fileFirstDir < images.size() ) {
        image1 = imread("D:/Images1/" + images.at(fileFirstDir).toStdString());

        cvtColor(image1, image1, CV_BGR2RGB);
        imageFormatQt = true;

        QImage img = QImage ((uchar*) image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
        ui->firsImage->setPixmap(QPixmap ::fromImage(img));

        if ( ui->firsImage->width() < image1.rows && ui->firsImage->height() < image1.cols ) {
            ui->firsImage->setScaledContents( true );
            ui->firsImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }

        if ( fileFirstDir == images.size() - 1 ) {
            ui->nextBtn1->setEnabled(false);
        }
    }
}

void MainWindow::on_previousBtn1_clicked()
{
    fileFirstDir--;
    QDir directory("D:/Images1");
    QStringList images = directory.entryList(QStringList(), QDir::Files);


    if( fileFirstDir < images.size() - 1 ) {
        ui->nextBtn1->setEnabled(true);
    }

    if ( fileFirstDir < images.size() ) {
        image1 = imread("D:/Images1/" + images.at(fileFirstDir).toStdString());

        cvtColor(image1, image1, CV_BGR2RGB);
        imageFormatQt = true;

        QImage img = QImage ((uchar*) image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
        ui->firsImage->setPixmap(QPixmap ::fromImage(img));

        if ( ui->firsImage->width() < image1.rows && ui->firsImage->height() < image1.cols ) {
            ui->firsImage->setScaledContents( true );
            ui->firsImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }

        if ( fileFirstDir == 0 ) {
            ui->previousBtn1->setEnabled(false);
        }
    }
}

void MainWindow::on_horizontalSlider1_valueChanged(int value)
{
    weight1 = value;
}

void MainWindow::on_addNoiseBtn_clicked()
{
    int n = 5000;

    for (int k = 0; k < n; k++) {
        int i = rand()%image1.rows;
        int j = rand()%image1.cols;

        if ( image1.channels() == 1 ) {
            image1.at<uchar>(i, j) = 255;
        } else {
            if ( image1.channels() == 3 )
                image1.at<Vec3b>(i, j)[0] = 255;
                image1.at<Vec3b>(i, j)[1] = 255;
                image1.at<Vec3b>(i, j)[2] = 255;
        }
    }

    QImage img = QImage ((uchar*) image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
    ui->firsImage->setPixmap(QPixmap ::fromImage(img));

    if ( ui->firsImage->width() < image1.rows && ui->firsImage->height() < image1.cols ) {
        ui->firsImage->setScaledContents( true );
        ui->firsImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void MainWindow::on_loadImages2_clicked()
{
    QDir directory("D:/Images2");
    QStringList images = directory.entryList(QStringList(), QDir::Files);

    if ( images.size() > 0 ) {
        fileSecondDir = 0;
        image2 = imread("D:/Images2/"  + images.at(fileSecondDir).toStdString());
    }

    if ( image2.data ) {
        if( image1.data ) {
            ui->processImageBtn->setEnabled(true);
        }

        if( images.size() > 1 ) {
            ui->nextBtn2->setEnabled(true);
        }

        ui->horizontalSlider2->setEnabled(true);
        ui->addNoiseBtn2->setEnabled(true);

        cvtColor(image2, image2, CV_BGR2RGB);
        imageFormatQt = true;

        QImage img = QImage ((uchar*) image2.data, image2.cols, image2.rows, image2.step, QImage::Format_RGB888);
        ui->secondImage->setPixmap(QPixmap ::fromImage(img));

        if ( ui->secondImage->width() < image2.rows && ui->secondImage->height() < image2.cols ) {
            ui->secondImage->setScaledContents( true );
            ui->secondImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    } else {
        errorBox.exec();
    }

}

void MainWindow::on_nextBtn2_clicked()
{
    fileSecondDir++;
    QDir directory("D:/Images2");
    QStringList images = directory.entryList(QStringList(), QDir::Files);

    if( fileSecondDir > 0 ) {
        ui->previousBtn2->setEnabled(true);
    }

    if ( fileSecondDir < images.size() ) {
        image2 = imread("D:/Images2/" + images.at(fileSecondDir).toStdString());

        cvtColor(image2, image2, CV_BGR2RGB);
        imageFormatQt = true;

        QImage img = QImage ((uchar*) image2.data, image2.cols, image2.rows, image2.step, QImage::Format_RGB888);
        ui->secondImage->setPixmap(QPixmap ::fromImage(img));

        if ( ui->secondImage->width() < image2.rows && ui->secondImage->height() < image2.cols ) {
            ui->secondImage->setScaledContents( true );
            ui->secondImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }

        if ( fileSecondDir == images.size() - 1 ) {
            ui->nextBtn2->setEnabled(false);
        }
    }
}

void MainWindow::on_previousBtn2_clicked()
{
    fileSecondDir--;
    QDir directory("D:/Images2");
    QStringList images = directory.entryList(QStringList(), QDir::Files);

    if (fileSecondDir < images.size() - 1 ) {
        ui->nextBtn2->setEnabled(true);
    }

    if ( fileSecondDir < images.size() ) {
        image2 = imread("D:/Images2/" + images.at(fileSecondDir).toStdString());

        cvtColor(image2, image2, CV_BGR2RGB);
        imageFormatQt = true;

        QImage img = QImage ((uchar*) image2.data, image2.cols, image2.rows, image2.step, QImage::Format_RGB888);
        ui->secondImage->setPixmap(QPixmap ::fromImage(img));

        if ( ui->secondImage->width() < image2.rows && ui->secondImage->height() < image2.cols ) {
            ui->secondImage->setScaledContents( true );
            ui->secondImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }

        if ( fileSecondDir == 0 ) {
            ui->previousBtn2->setEnabled(false);
        }
    }
}

void MainWindow::on_horizontalSlider2_valueChanged(int value)
{
    weight2 = value;
}

void MainWindow::on_addNoiseBtn2_clicked()
{
    int n = 5000;

    for (int k = 0; k < n; k++) {
        int i = rand()%image2.rows;
        int j = rand()%image2.cols;

        if ( image2.channels() == 1 ) {
            image2.at<uchar>(i, j) = 255;
        } else {
            if (image2.channels() == 3)
                image2.at<Vec3b>(i, j)[0] = 255;
                image2.at<Vec3b>(i, j)[1] = 255;
                image2.at<Vec3b>(i, j)[2] = 255;
        }
    }

    QImage img = QImage ((uchar*) image2.data, image2.cols, image2.rows, image2.step, QImage::Format_RGB888);
    ui->secondImage->setPixmap(QPixmap ::fromImage(img));

    if ( ui->firsImage->width() < image2.rows && ui->firsImage->height() < image2.cols ) {
        ui->firsImage->setScaledContents( true );
        ui->firsImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void MainWindow::on_processImageBtn_clicked()
{
    ui->saveBtn->setEnabled(true);

    image1.copyTo(resultImage);
    imageROI = resultImage(Rect(resultImage.cols/2 - image2.cols/2, 0, image2.cols, image2.rows));
    addWeighted(imageROI, weight1, image2, weight2, 0., imageROI);

    QImage img = QImage ((uchar*) resultImage.data, resultImage.cols, resultImage.rows, resultImage.step, QImage::Format_RGB888);
    ui->mergedImages->setPixmap(QPixmap ::fromImage(img));

    if ( ui->mergedImages->width() < resultImage.rows && ui->mergedImages->height() < resultImage.cols ) {
        ui->mergedImages->setScaledContents( true );
        ui->mergedImages->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void MainWindow::on_saveBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if( fileName.isEmpty() ) {
        warningBox.exec();
    } else {
        if ( imageFormatQt ) {
            cvtColor(resultImage, resultImage, CV_RGB2BGR);
            imageFormatQt = false;
        }

        imwrite(fileName.toLatin1().data(), resultImage);
    }
}
