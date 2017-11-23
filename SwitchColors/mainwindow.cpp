#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Switch colors");
    ui->switchChannelsBtn->setEnabled(false);
    ui->saveImageBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectImageBtn_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Please select an image.");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        poza = imread(fileName.toLatin1().data());

        if (poza.data)
            ui->switchChannelsBtn->setEnabled(true);
            ui->saveImageBtn->setEnabled(true);

        cvtColor(poza, poza, CV_BGR2RGB);
        QImage img = QImage ((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap ::fromImage(img));

        if (poza.rows > ui->label->width() && poza.cols > ui->label->height()) {
            ui->label->setScaledContents( true );
            ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_switchChannelsBtn_triggered()
{
    cvtColor(poza, poza, CV_RGB2BGR);
    QImage img = QImage ((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap ::fromImage(img));
}

void MainWindow::on_saveImageBtn_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Your file was not saved.");

    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        cvtColor(poza, poza, CV_RGB2BGR);
        imwrite(fileName.toLatin1().data(), poza);
    }
}

