#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Characteristics
{
public:
    Characteristics();

    void setThreshold(int value);
    void setSquare(int dim);
    void setRhombus(int dim);
    void setCross(int dim);
    void setX(int dim);
    Mat getSquare();
    Mat getRhombus();
    Mat getCross();
    Mat getX();
    void applyThreshold(Mat& result);
    Mat getEdges(Mat &image);
    Mat getCorners(const Mat &image);
    void drawOnImage(Mat& binary, Mat& image);

    int threshold = 0;
    Mat square;
    Mat rhombus;
    Mat cross;
    Mat x;
};

#endif // CHARACTERISTICS_H
