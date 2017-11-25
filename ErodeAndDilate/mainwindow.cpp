#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->erodeImageBtn->setEnabled(false);
    ui->dilateImageBtn->setEnabled(false);
    ui->squareShape->setEnabled(false);
    ui->rhombusShape->setEnabled(false);
    ui->crossShape->setEnabled(false);
    ui->xShape->setEnabled(false);
    ui->strcutElemDim->setEnabled(false);
    this->setWindowTitle("Erode and dilate");
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

        if ( image.data )
            ui->strcutElemDim->setEnabled(true);
            cvtColor(image, image, CV_BGR2GRAY);
            threshold(image, image, 120, 255, THRESH_BINARY_INV);

            this->displayImage(image);
    }
}

void MainWindow::on_squareShape_triggered()
{
    square = Mat(structElemDim, structElemDim, CV_8U, Scalar(1));

    element = square;

    this->enableProcessingBtns();
}

void MainWindow::on_rhombusShape_triggered()
{
    rhombus = Mat(structElemDim, structElemDim, CV_8U, Scalar(1));

    rhombus.at<uchar>(0, 0) = 0;
    rhombus.at<uchar>(0, 1) = 0;
    rhombus.at<uchar>(1, 0) = 0;
    rhombus.at<uchar>(4, 4) = 0;
    rhombus.at<uchar>(3, 4) = 0;
    rhombus.at<uchar>(4, 3) = 0;
    rhombus.at<uchar>(4, 0) = 0;
    rhombus.at<uchar>(4, 1) = 0;
    rhombus.at<uchar>(3, 0) = 0;
    rhombus.at<uchar>(0, 4) = 0;
    rhombus.at<uchar>(0, 3) = 0;
    rhombus.at<uchar>(1, 4) = 0;

    element = rhombus;

    this->enableProcessingBtns();
}

void MainWindow::on_crossShape_triggered()
{
    cross = Mat(structElemDim, structElemDim, CV_8U, Scalar(1));

    for (int i = 0; i < structElemDim; i++)
    {
        cross.at<uchar>(((structElemDim - 1) / 2), i) = 1;
        cross.at<uchar>(i, ((structElemDim - 1) / 2)) = 1;
    }

    element = cross;

    this->enableProcessingBtns();
}

void MainWindow::on_xShape_triggered()
{
    x = Mat(structElemDim, structElemDim, CV_8U, Scalar(1));

    for (int i = 0; i < structElemDim; i++) {
        x.at<uchar>(i, i) = 1;
        x.at<uchar>((structElemDim - 1) - i, i) = 1;
    }

    element = x;

    this->enableProcessingBtns();
}

void MainWindow::on_strcutElemDim_textChanged(const QString &arg1)
{
    structElemDim = arg1.toDouble();

    ui->squareShape->setEnabled(true);
    ui->rhombusShape->setEnabled(true);
    ui->crossShape->setEnabled(true);
    ui->xShape->setEnabled(true);
}

void MainWindow::on_erodeImageBtn_triggered()
{
    erode(image, erodedImage, element);

    this->displayImage(erodedImage);
}

void MainWindow::on_dilateImageBtn_triggered()
{
    dilate(image, dilatedImage, element);

    this->displayImage(dilatedImage);
}

void MainWindow::displayImage(Mat image)
{
    QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
    ui->imageLabel->setPixmap(QPixmap ::fromImage(img));
    ui->imageLabel->resize(ui->imageLabel->pixmap()->size());
}

void MainWindow::enableProcessingBtns()
{
    if (! ui->erodeImageBtn->isEnabled() && ! ui->dilateImageBtn->isEnabled())
    {
        ui->erodeImageBtn->setEnabled(true);
        ui->dilateImageBtn->setEnabled(true);
    }
}
