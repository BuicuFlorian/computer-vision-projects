#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Reduce colors");
        ui->verticalSlider->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);
        ui->verticalSlider_2->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        ui->reduceColorsSlider->setEnabled(false);
        errorBox.setText("Please select an image.");
        errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                                "border: 0; padding: 15px;");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadImgBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

    if ( fileName.isEmpty() ) {
        errorBox.exec();
    } else {
        image1 = imread(fileName.toLatin1().data());

        if ( image1.data )
            ui->verticalSlider->setEnabled(true);
            ui->horizontalSlider->setEnabled(true);
            ui->verticalSlider_2->setEnabled(true);
            ui->horizontalSlider_2->setEnabled(true);
            ui->reduceColorsSlider->setEnabled(true);

            cvtColor(image1, image1, CV_BGR2RGB);

            QImage img = QImage ((uchar*) image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
            ui->firstImage->setPixmap(QPixmap ::fromImage(img));

            if ( image1.rows > ui->firstImage->width() && image1.cols > ui->firstImage->height() ) {
                ui->firstImage->setScaledContents( true );
                ui->firstImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    x = value;
    this->drawRect();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    y = value;
    this->drawRect();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    cols = value;
    this->drawRect();
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    rows = value;
    this->drawRect();
}

void MainWindow::on_reduceColorsSlider_valueChanged(int position)
{
    image1.copyTo(reducedROI);
    imageROI = reducedROI(Rect(point1, point2));
    imageROI.create(imageROI.rows, imageROI.cols, imageROI.type());

    int nl = imageROI.rows;
    int nc = imageROI.cols * imageROI.channels();

    if (position > 0) {
        for(int j = 0; j < nl; j ++) {
            uchar* data_in = imageROI.ptr<uchar>(j);
            uchar* data_out = imageROI.ptr<uchar>(j);

            for(int i = 0; i < nc; i++) {
                data_out[i] = data_in[i] - data_in[i] % position + position/2;
            }
        }

        QImage img = QImage ((uchar*) reducedROI.data, reducedROI.cols, reducedROI.rows, reducedROI.step, QImage::Format_RGB888);
        ui->secondImage->setPixmap(QPixmap ::fromImage(img));

        if ( reducedROI.rows > ui->secondImage->width() && reducedROI.cols > ui->secondImage->height() ) {
            ui->secondImage->setScaledContents( true );
            ui->secondImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::drawRect()
{
    point1 = Point(x, y);
    point2 = Point(x + cols, y + rows);
    // point2 = Point(x + 100, y + 100);

    image1.copyTo(imageWithRect);
    rectangle(imageWithRect, point1, point2, CV_RGB(255, 0, 0), 2, 8, 0);

    QImage img = QImage ((uchar*) imageWithRect.data, imageWithRect.cols, imageWithRect.rows, imageWithRect.step, QImage::Format_RGB888);
    ui->firstImage->setPixmap(QPixmap ::fromImage(img));

    if ( imageWithRect.rows > ui->secondImage->width() && imageWithRect.cols > ui->secondImage->height() ) {
        ui->firstImage->setScaledContents( true );
        ui->firstImage->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}
