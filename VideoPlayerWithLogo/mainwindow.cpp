#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->playVideoBtn->setEnabled(false);
    ui->stopVideoBtn->setEnabled(false);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateFrame()));
    timer->stop();
    msgBox.setText("Couldn't open the video file.");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadVideoBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open video"), ".");

    cap.open(fileName.toLatin1().data());

    if (! cap.isOpened() ) {
        msgBox.exec();
    }

    if ( cap.isOpened() && logo.data ) {
       ui->playVideoBtn->setEnabled(true);
    }

    double fps = cap.get(CV_CAP_PROP_FPS);
    qInfo() << "Frames per second: " << fps ;
}

void MainWindow::on_playVideoBtn_clicked()
{
    timer->start(30);

    ui->stopVideoBtn->setEnabled(true);
    ui->playVideoBtn->setEnabled(false);

    if (! cap.read(frame) ) {
        msgBox.exec();
    }

    cvtColor(frame, frame, CV_BGR2RGB);
    QImage img = QImage ((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap ::fromImage(img));

    if ( frame.rows > ui->label->width() && frame.cols > ui->label->height() ) {
        ui->label->setScaledContents( true );
        ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

void MainWindow::on_stopVideoBtn_clicked()
{
    ui->playVideoBtn->setEnabled(false);
    ui->stopVideoBtn->setEnabled(false);
    cap.release();
    timer->stop();
}

void MainWindow::updateFrame()
{
    if ( cap.read(frame) && ui->stopVideoBtn->isEnabled() == true ) {
        frameROI = frame(Rect(1, 1, logo.cols, logo.rows));
        addWeighted(frameROI, 1.0, logo, 0.3, 0., frameROI);

        cvtColor(frame, frame, CV_BGR2RGB);
        QImage img = QImage ((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap ::fromImage(img));

        if ( frame.rows > ui->label->width() && frame.cols > ui->label->height() ) {
            ui->label->setScaledContents( true );
            ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}

void MainWindow::on_chooseLogoBtn_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose logo"), ".");

    if( fileName.isEmpty() ) {
        msgBox.exec();
    } else {
        logo = imread(fileName.toLatin1().data());

        if ( logo.data && cap.isOpened() ) {
			ui->playVideoBtn->setEnabled(true);
        }
    }
}
