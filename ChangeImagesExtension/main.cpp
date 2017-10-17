#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir directory("D:/images/jpg");

    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG",QDir::Files);

    foreach(QString filename, images) {
        Mat poza = imread("D:/images/jpg/" + filename.toStdString());
		
		QString cropedFileName = filename.section(".",0,0);

        imwrite("D:/images/bmp/" + cropedFileName.toStdString() + ".bmp", poza);
    }

    qInfo() << "All jpg images from D:/images/jpg where "
                "saved in D:/images/bmp/ with bmp extension.";

    return a.exec();
}
