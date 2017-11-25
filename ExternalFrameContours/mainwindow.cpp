#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Video Player");
    ui->playVideoBtn->setEnabled(false);
    ui->stopVideoBtn->setEnabled(false);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateFrame()));
    timer->stop();
    srand (time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadVideoBtn_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open video"), ".");

    cap.open(fileName.toLatin1().data());

    if (! cap.isOpened() )
    {
        qDebug() << "Couldn't open the video file.";
    }

    ui->playVideoBtn->setEnabled(true);

    double fps = cap.get(CV_CAP_PROP_FPS);
    qDebug() << "Frames per second: " << fps ;
}

void MainWindow::on_playVideoBtn_triggered()
{
    ui->stopVideoBtn->setEnabled(true);
    ui->playVideoBtn->setEnabled(false);

    if (! cap.read(frame) )
    {
        qDebug() << "Can't read the video file.";
    }

    cvtColor(frame, frame, CV_BGR2GRAY);
    threshold(frame, frame2, 128, 255, CV_THRESH_BINARY_INV);

    this->getContours();

    timer->start(30);
}

void MainWindow::on_stopVideoBtn_triggered()
{
    ui->playVideoBtn->setEnabled(false);
    ui->stopVideoBtn->setEnabled(false);
    cap.release();
    timer->stop();
}

void MainWindow::updateFrame()
{
    if ( cap.read(frame) && ui->stopVideoBtn->isEnabled() == true)
    {
        cvtColor(frame, frame, CV_BGR2GRAY);
        threshold(frame, frame2, 128, 255, CV_THRESH_BINARY_INV);

        this->getContours();
    }
}


void MainWindow::getContours()
{
    findContours( frame2, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    resultFrame = Mat::zeros( frame2.size(), CV_8UC3 );

    for( size_t i = 0; i < contours.size(); i++ ) {
        Scalar color = Scalar( rand() % 256, rand() % 256, rand() % 256 );
        drawContours( resultFrame, contours, i, color, 2, 8, hierarchy, 0, Point());
    }

    QImage img = QImage ((uchar*) resultFrame.data, resultFrame.cols, resultFrame.rows, resultFrame.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap ::fromImage(img));

    if (resultFrame.rows > ui->label->width() && resultFrame.cols > ui->label->height()) {
        ui->label->setScaledContents( true );
        ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}
