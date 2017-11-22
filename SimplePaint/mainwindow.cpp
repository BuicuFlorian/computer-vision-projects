#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_qlabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple paint");
    connect(ui->lblDrawArea, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_pressed()));
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
                cvtColor(image, image, CV_BGR2RGB);

                QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
                ui->lblDrawArea->setPixmap(QPixmap ::fromImage(img));
                ui->lblDrawArea->resize(ui->lblDrawArea->pixmap()->size());
        }
}

void MainWindow::Mouse_pressed()
{
    if (clicked == true) {
        x1 = ui->lblDrawArea->x;
        y1 = ui->lblDrawArea->y;

        clicked = false;
    } else {
        clicked = true;
        x2 = ui->lblDrawArea->x;
        y2 = ui->lblDrawArea->y;

        point1 = Point(x1, y1);
        point2 = Point(x2, y2);

       this->drawShape();

       QImage img = QImage ((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
        ui->lblDrawArea->setPixmap(QPixmap ::fromImage(img));
        ui->lblDrawArea->resize(ui->lblDrawArea->pixmap()->size());
    }

}

void MainWindow::on_arrowedLineRadioBtn_toggled(bool arg1)
{
    drawOption = "arrowedLine";
}

void MainWindow::on_lineRadioBtn_toggled(bool arg1)
{
    drawOption = "line";
}

void MainWindow::on_rectRadioBtn_toggled(bool arg1)
{
	drawOption = "rectangle";

}

void MainWindow::on_circleRadioBtn_toggled(bool arg1)
{

    drawOption = "circle";
}

void MainWindow::drawShape()
{
    if (drawOption == "rectangle") {
        rectangle(image, point1, point2, CV_RGB(0, 51, 204), 2, 2, 0);
    } else if (drawOption == "circle") {
        circle(image,point1, abs(y2 - y1), CV_RGB(0, 51, 204), 2);
    } else if (drawOption == "line") {
        line(image, point1, point2, CV_RGB(0, 51, 204), 2);
    } else if (drawOption == "arrowedLine") {
        arrowedLine(image, point1, point2, CV_RGB(0, 51, 204), 2);
    } else {
        putText(image, "OpenCV Paint", Point2f(10,50), FONT_HERSHEY_COMPLEX_SMALL, 2,  Scalar(0,0,255,255));
    }
}

void MainWindow::on_saveFileBtn_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save file", "");

    if (fileName.isEmpty()) {
        errorBox.setText("Your file was not saved.");
        errorBox.exec();
    } else {
        cvtColor(image, image, CV_RGB2BGR);
        imwrite(fileName.toLatin1().data(), image);
    }
}
