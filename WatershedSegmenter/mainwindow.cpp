#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Watershed Segmenter");
    ui->processImageBtn->setEnabled(false);
    ui->chooseFileBtn->setEnabled(false);
    ui->strcutElemDim->setEnabled(false);
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
            ui->strcutElemDim->setEnabled(true);
            ui->processImageBtn->setEnabled(true);
            cvtColor(image, binary, CV_BGR2GRAY);
            threshold(binary, binary, 120, 255, thresholdType);

            QImage img = QImage ((uchar*) binary.data, binary.cols, binary.rows, binary.step, QImage::Format_Indexed8);
            ui->imageLabel->setPixmap(QPixmap ::fromImage(img));
            ui->imageLabel->resize(ui->imageLabel->pixmap()->size());
        }
    }
}

void MainWindow::on_strcutElemDim_textChanged(const QString &arg1)
{
    structElemDim = arg1.toDouble();

    structuralElement = Mat(structElemDim, structElemDim, CV_8U, Scalar(0));
}

void MainWindow::on_threshBinaryBtn_triggered()
{
    thresholdType = THRESH_BINARY;

    if (! ui->chooseFileBtn->isEnabled()) {
        ui->chooseFileBtn->setEnabled(true);
    }
}

void MainWindow::on_threshBinaryInvBtn_triggered()
{
    thresholdType = THRESH_BINARY_INV;

    if (! ui->chooseFileBtn->isEnabled()) {
        ui->chooseFileBtn->setEnabled(true);
    }
}

void MainWindow::on_processImageBtn_triggered()
{
    erode(binary, foreground, structuralElement, Point(-1, -1), 6);

    dilate(binary, background, structuralElement, Point(-1, -1), 6);
    threshold(background, background, 1, 128, THRESH_BINARY_INV);

    Mat markers(binary.size(), CV_8U, Scalar(0));
    markers = foreground + background;

    segment.setMarkers(markers);
    segment.process(image);

    result = segment.getWatersheds();

    QImage img = QImage ((uchar*) result.data, result.cols, result.rows, result.step, QImage::Format_Indexed8);
    ui->imageLabel->setPixmap(QPixmap ::fromImage(img));
    ui->imageLabel->resize(ui->imageLabel->pixmap()->size());
}
