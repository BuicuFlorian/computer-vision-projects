#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Corners detector");
    ui->chooseFileBtn->setEnabled(false);
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
            cvtColor(image, image, CV_BGR2GRAY);

            morf.setThreshold(40);
            result = morf.getCorners(image);
            morf.drawOnImage(result, image);

            QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_Indexed8);
            ui->imageLabel->setPixmap(QPixmap ::fromImage(img));
            ui->imageLabel->resize(ui->imageLabel->pixmap()->size());
        }
    }
}


void MainWindow::on_strcutElemDim_returnPressed()
{
    structElemDim = ui->strcutElemDim->text().toDouble();

    morf.setSquare(structElemDim);
    morf.setRhombus(structElemDim);
    morf.setCross(structElemDim);
    morf.setX(structElemDim);

    if (! ui->chooseFileBtn->isEnabled()) {
        ui->chooseFileBtn->setEnabled(true);
    }
}
