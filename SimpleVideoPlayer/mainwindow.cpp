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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chooseFileBtn_triggered()
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
    timer->start(30);

    ui->stopVideoBtn->setEnabled(true);
    ui->playVideoBtn->setEnabled(false);

    if (! cap.read(frame) )
    {
        qDebug() << "Can't read the video file.";
    }

    cvtColor(frame, frame, CV_BGR2RGB);
    QImage img = QImage ((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap ::fromImage(img));

    if (frame.rows > ui->label->width() && frame.cols > ui->label->height()) {
        ui->label->setScaledContents( true );
        ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
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
        cvtColor(frame, frame, CV_BGR2RGB);
        QImage img = QImage ((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap ::fromImage(img));

        if (frame.rows > ui->label->width() && frame.cols > ui->label->height()) {
            ui->label->setScaledContents( true );
            ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}
