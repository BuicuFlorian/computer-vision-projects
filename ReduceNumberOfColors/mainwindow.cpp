#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Reduce colors");
    ui->saveImageBtn->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_chooseFileBtn_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Please select an image.");

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open image"),".");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        ui->saveImageBtn->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);

        image = imread(fileName.toLatin1().data());

        cvtColor(image, image, CV_BGR2RGB);
        QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap ::fromImage(img));

        if (ui->label->width() < image.rows && ui->label->height() < image.cols) {
            ui->label->setScaledContents( true );
            ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        } else {
           ui->label->resize(ui->label->pixmap()->size());
        }
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    result.create(image.rows, image.cols, image.type());

    int nl = image.rows;
    int nc = image.cols * image.channels();

    if (position > 0) {
        for(int j = 0; j < nl; j ++) {
            uchar* data_in = image.ptr<uchar>(j);
            uchar* data_out = result.ptr<uchar>(j);

            for(int i = 0; i < nc; i++) {
                  data_out[i] = data_in[i] - data_in[i] % position + position/2;
             }
         }

         QImage img = QImage ((uchar*) result.data, result.cols, result.rows, result.step, QImage::Format_RGB888);
         ui->label->setPixmap(QPixmap ::fromImage(img));

         if (ui->label->width() < result.rows && ui->label->height() < result.cols) {
             ui->label->setScaledContents( true );
             ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
         } else {
            ui->label->resize(ui->label->pixmap()->size());
         }
    }
}


void MainWindow::on_saveImageBtn_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Your file was not saved.");

    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        cvtColor(result, result, CV_BGR2RGB);
        imwrite(fileName.toLatin1().data(), result);
    }
}
