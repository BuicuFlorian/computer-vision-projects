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
        cvtColor(frame, binary, CV_BGR2GRAY);
        threshold(binary, binary, 120, 255, THRESH_BINARY);

        erode(binary, foreground, Mat(), Point(-1, -1), 6);

        dilate(binary, background, Mat(), Point(-1, -1), 6);
        threshold(background, background, 1, 128, THRESH_BINARY_INV);

        Mat markers(binary.size(), CV_8U, Scalar(0));
        markers = foreground + background;

        segment.setMarkers(markers);
        segment.process(frame);

        result = segment.getWatersheds();

        QImage img = QImage ((uchar*) result.data, result.cols, result.rows, result.step, QImage::Format_Indexed8);
        ui->label->setPixmap(QPixmap ::fromImage(img));

        if (result.rows > ui->label->width() && result.cols > ui->label->height()) {
            ui->label->setScaledContents( true );
            ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        }
    }
}
