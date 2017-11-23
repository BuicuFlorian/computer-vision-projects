#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Reduce colors from ROI");
    connect(ui->firstImage, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
        ui->reduceColorsSlider->setEnabled(false);
        errorBox.setText("Please select an image.");
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
        errorBox.exec();
    } else {
        image1 = imread(fileName.toLatin1().data());

        if ( image1.data )
            ui->reduceColorsSlider->setEnabled(true);

            cvtColor(image1, image1, CV_BGR2RGB);

            QImage img = QImage ((uchar*) image1.data, image1.cols, image1.rows, image1.step, QImage::Format_RGB888);
            ui->firstImage->setPixmap(QPixmap ::fromImage(img));
            ui->firstImage->resize(ui->firstImage->pixmap()->size());
    }
}

void MainWindow::Mouse_pressed()
{
    if (clicked == true) {
        x1 = ui->firstImage->x;
        y1 = ui->firstImage->y;

        clicked = false;
    } else {
        clicked = true;
        x2 = ui->firstImage->x;
        y2 = ui->firstImage->y;

        this->drawRect();
    }
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
        ui->secondImage->resize(ui->secondImage->pixmap()->size());
    }
}

void MainWindow::drawRect()
{
    point1 = Point(x1, y1);
    point2 = Point(x2, y2);

    image1.copyTo(imageWithRect);
    rectangle(imageWithRect, point1, point2, CV_RGB(255, 0, 0), 2, 8, 0);

    QImage img = QImage ((uchar*) imageWithRect.data, imageWithRect.cols, imageWithRect.rows, imageWithRect.step, QImage::Format_RGB888);
    ui->firstImage->setPixmap(QPixmap ::fromImage(img));
    ui->firstImage->resize(ui->firstImage->pixmap()->size());
}

