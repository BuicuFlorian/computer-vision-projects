#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Flip image");
    ui->flipHorizontallyBtn->setEnabled(false);
    ui->flipVerticallyBtn->setEnabled(false);
    ui->flipHorizontallyVerticallyBtn->setEnabled(false);
    ui->saveImageBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chooseFileBtn_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Please select an image.");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        image = imread(fileName.toLatin1().data());

        if ( image.data )
            ui->flipHorizontallyBtn->setEnabled(true);
            ui->flipVerticallyBtn->setEnabled(true);
            ui->flipHorizontallyVerticallyBtn->setEnabled(true);
            ui->saveImageBtn->setEnabled(true);

         cvtColor(image, image, CV_BGR2RGB);
         QImage img= QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
         ui->label->setPixmap(QPixmap ::fromImage(img));

        if (ui->label->width() < image.rows && ui->label->height() < image.cols) {
            ui->label->setScaledContents( true );
            ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        } else {
            ui->label->resize(ui->label->pixmap()->size());
        }
    }
}

void MainWindow::on_flipHorizontallyBtn_triggered()
{
    flip(image, image, 1);
    QImage img= QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap ::fromImage(img));
}

void MainWindow::on_flipVerticallyBtn_triggered()
{
    flip(image, image, 0);
    QImage img= QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap ::fromImage(img));
}

void MainWindow::on_flipHorizontallyVerticallyBtn_triggered()
{
    flip(image, image, -1);
    QImage img= QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap ::fromImage(img));
}

void MainWindow::on_saveImageBtn_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Your file it's not saved.");

    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        cvtColor(image, image, CV_RGB2BGR);
        imwrite(fileName.toLatin1().data(), image);
    }
}
