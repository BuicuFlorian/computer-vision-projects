#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->saveImageBtn->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Please select an image.");

    QString fileName = QFileDialog::getOpenFileName(this,tr("Open image"),"D:/jpg");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        ui->saveImageBtn->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);

        poza = imread(fileName.toLatin1().data());

        cvtColor(poza, poza, CV_BGR2RGB);
        QImage img = QImage ((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap ::fromImage(img));

        if (ui->label->width() < poza.rows && ui->label->height() < poza.cols) {
            ui->label->setScaledContents( true );
            ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        } else {
           ui->label->resize(ui->label->pixmap()->size());
        }
    }
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    rez.create(poza.rows, poza.cols, poza.type());

    int nl = poza.rows;
    int nc = poza.cols * poza.channels();

    if (position > 0) {
        for(int j = 0; j < nl; j ++) {
            uchar* data_in = poza.ptr<uchar>(j);
            uchar* data_out = rez.ptr<uchar>(j);

            for(int i = 0; i < nc; i++) {
                  data_out[i] = data_in[i] - data_in[i] % position + position/2;
             }
         }

         QImage img = QImage ((uchar*) rez.data, rez.cols, rez.rows, rez.step, QImage::Format_RGB888);
         ui->label->setPixmap(QPixmap ::fromImage(img));

         if (ui->label->width() < rez.rows && ui->label->height() < rez.cols) {
             ui->label->setScaledContents( true );
             ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
         } else {
            ui->label->resize(ui->label->pixmap()->size());
         }
    }
}

void MainWindow::on_saveImageBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Your file was not saved.");

    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        cvtColor(rez, rez, CV_BGR2RGB);
        imwrite(fileName.toLatin1().data(), rez);
    }
}
