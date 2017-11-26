#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BGR Histograms");
    ui->drawHistBtn->setEnabled(false);
    errorBox.setText("Please select an image.");
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                            "border: 0; padding: 15px;");
    errorBox.QDialog::setWindowTitle("Error");
    range[0] = 0;
    range[1] = 256;
    histRange = range;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadImgBtn_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

    if( fileName.isEmpty() ) {
        errorBox.exec();
    } else {
        image = imread(fileName.toLatin1().data());

        if ( image.data ) {
            split( image, bgr_planes );
            ui->drawHistBtn->setEnabled(true);
            cvtColor(image, image, CV_BGR2RGB);

            QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
            ui->image->setPixmap(QPixmap ::fromImage(img));

            if ( image.rows > ui->image->width() && image.cols > ui->image->height() ) {
                ui->image->setScaledContents( true );
                ui->image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            }
        }
    }
}

void MainWindow::on_drawHistBtn_triggered()
{
    histograms = this->getHistograms(image);

    // Display histograms
    QImage img = QImage ((uchar*) histograms.data, histograms.cols, histograms.rows, histograms.step, QImage::Format_RGB888);
    ui->histogram->setPixmap(QPixmap ::fromImage(img));

    if ( histograms.rows > ui->histogram->width() && histograms.cols > ui->histogram->height() ) {
        ui->histogram->setScaledContents( true );
        ui->histogram->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    }
}

Mat MainWindow::getHistograms(const Mat &image)
{
    // Compute the histograms
    calcHist( &bgr_planes[0], 1, 0, Mat(), blueHist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), greenHist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), redHist, 1, &histSize, &histRange, uniform, accumulate );

    // Draw the histograms for B, G and R
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    // Normalize the result to [ 0, histImage.rows ]
    normalize(blueHist, blueHist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(greenHist, greenHist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(redHist, redHist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    // Draw for each channel
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(blueHist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(blueHist.at<float>(i)) ),
                         Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(greenHist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(greenHist.at<float>(i)) ),
                         Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(redHist.at<float>(i-1)) ) ,
                         Point( bin_w*(i), hist_h - cvRound(redHist.at<float>(i)) ),
                         Scalar( 0, 0, 255), 2, 8, 0  );
    }

    return histImage;
}
