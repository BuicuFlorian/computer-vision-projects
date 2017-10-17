#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->flipHorizontallyBtn->setEnabled(false);
    ui->flipVerticallyBtn->setEnabled(false);
    ui->flipHorizontallyVerticallyBtn->setEnabled(false);
    ui->saveImageBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectImageBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Please select an image.");

    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Open image"),".",
                       tr("Image Files (*.jpg, *.jpeg, *.png, *.bmp)"));

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        poza = imread(fileName.toLatin1().data());

        if ( poza.data )
            ui->flipHorizontallyBtn->setEnabled(true);
            ui->flipVerticallyBtn->setEnabled(true);
            ui->flipHorizontallyVerticallyBtn->setEnabled(true);
            ui->saveImageBtn->setEnabled(true);

         cvtColor(poza, poza, CV_BGR2RGB);
         QImage img= QImage ((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
         ui->label->setPixmap(QPixmap ::fromImage(img));
         ui->label->resize(ui->label->pixmap()->size());
    }
}

void MainWindow::on_flipHorizontallyBtn_clicked()
{
    flip(poza, poza, 1);
           QImage img= QImage ((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
           ui->label->setPixmap(QPixmap ::fromImage(img));
}

void MainWindow::on_flipVerticallyBtn_clicked()
{
    flip(poza, poza, 0);
           QImage img= QImage ((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
           ui->label->setPixmap(QPixmap ::fromImage(img));
}

void MainWindow::on_flipHorizontallyVerticallyBtn_clicked()
{
    flip(poza, poza, -1);
           QImage img= QImage ((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
           ui->label->setPixmap(QPixmap ::fromImage(img));
}

void MainWindow::on_saveImageBtn_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Your file it's not saved.");

    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        cvtColor(poza, poza, CV_RGB2BGR);
        imwrite(fileName.toLatin1().data(), poza);
    }
}
