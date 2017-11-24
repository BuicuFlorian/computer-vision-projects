#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->setColorDistanceSlider->setEnabled(false);
    ui->chooseColorBtn->setEnabled(false);
    ui->processImageBtn->setEnabled(false);
    ui->saveImageBtn->setEnabled(false);
    this->setWindowTitle("Color detector");
    errorBox.setStyleSheet("background-color: #ff0039; color: #ffffff; font-size: 21px; "
                                     "border: 0; padding: 15px;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chooseFileBtn_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open image"), ".");

            if ( fileName.isEmpty() ) {
                errorBox.setText("Please select an image.");
                errorBox.exec();
            } else {
                image = imread(fileName.toLatin1().data());

                if ( image.data )
                    ui->chooseColorBtn->setEnabled(true);
                    ui->setColorDistanceSlider->setEnabled(true);
                    cvtColor(image, image, CV_BGR2RGB);

                    QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
                    ui->firstImage->setPixmap(QPixmap ::fromImage(img));
                    ui->firstImage->resize(ui->firstImage->pixmap()->size());
            }
}

void MainWindow::on_chooseColorBtn_triggered()
{
    QColor color = QColorDialog::getColor(Qt::blue, this);

    if (color.isValid()) {
        cDetect.setTargetColor(color.red(), color.green(), color.blue());
    }
}

void MainWindow::on_processImageBtn_triggered()
{
    result = cDetect.process(image);

    QImage img = QImage ((uchar*) result.data, result.cols, result.rows, result.step, QImage::Format_Indexed8);
    ui->firstImage->setPixmap(QPixmap ::fromImage(img));
    ui->firstImage->resize(ui->firstImage->pixmap()->size());

    if (! ui->saveImageBtn->isEnabled()){
        ui->saveImageBtn->setEnabled(true);
    }
}

void MainWindow::on_saveImageBtn_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

        if (fileName.isEmpty()) {
            errorBox.setText("Your file was not saved.");
            errorBox.exec();
        } else {
            imwrite(fileName.toLatin1().data(), result);
        }
}

void MainWindow::on_manhattanRadioBtn_toggled(bool checked)
{

}

void MainWindow::on_euclideanRadioBtn_toggled(bool checked)
{

}

void MainWindow::on_chebyshevRadioBtn_toggled(bool checked)
{

}

void MainWindow::on_minkowskiRadioBtn_toggled(bool checked)
{

}

void MainWindow::on_setColorDistanceSlider_valueChanged(int value)
{
    if (! ui->processImageBtn->isEnabled()) {
         ui->processImageBtn->setEnabled(true);
    }

    cDetect.setColorDistanceThreshold(value);
}
