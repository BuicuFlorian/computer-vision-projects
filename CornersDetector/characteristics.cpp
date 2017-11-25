#include "characteristics.h"

Characteristics::Characteristics()
{
}

void Characteristics::setThreshold(int value)
{
    threshold = value;
}

void Characteristics::setSquare(int dim)
{
    square = Mat(dim, dim, CV_8U, Scalar(0));
}

void Characteristics::setRhombus(int dim)
{
    rhombus = Mat(dim, dim, CV_8U, Scalar(0));

    rhombus.at<uchar>(0, 0) = 0;
    rhombus.at<uchar>(0, 1) = 0;
    rhombus.at<uchar>(1, 0) = 0;
    rhombus.at<uchar>(4, 4) = 0;
    rhombus.at<uchar>(3, 4) = 0;
    rhombus.at<uchar>(4, 3) = 0;
    rhombus.at<uchar>(4, 0) = 0;
    rhombus.at<uchar>(4, 1) = 0;
    rhombus.at<uchar>(3, 0) = 0;
    rhombus.at<uchar>(0, 4) = 0;
    rhombus.at<uchar>(0, 3) = 0;
    rhombus.at<uchar>(1, 4) = 0;
}

void Characteristics::setCross(int dim)
{
    cross = Mat(dim, dim, CV_8U, Scalar(0));

    for (int i = 0; i < dim; i++)
    {
        cross.at<uchar>(((dim - 1) / 2), i) = 1;
        cross.at<uchar>(i, ((dim - 1) / 2)) = 1;
    }
}

void Characteristics::setX(int dim)
{
    x = Mat(dim, dim, CV_8U, Scalar(0));

    for (int i = 0; i < dim; i++) {
        x.at<uchar>(i, i) = 1;
        x.at<uchar>((dim - 1) - i, i) = 1;
    }
}

Mat Characteristics::getSquare()
{
    return square;
}

Mat Characteristics::getRhombus()
{
    return rhombus;
}

Mat Characteristics::getCross()
{
    return cross;
}

Mat Characteristics::getX()
{
    return x;
}

void Characteristics::applyThreshold(Mat &result)
{
    if (threshold > 0)
    {
        cv::threshold(result, result, threshold, 255, THRESH_BINARY_INV);
    }
}

Mat Characteristics::getEdges(Mat &image)
{
    Mat result;

    morphologyEx(image, result, MORPH_GRADIENT, Mat());

    this->applyThreshold(result);

    return result;
}

Mat Characteristics::getCorners(const Mat &image)
{
    Mat result;

    dilate(image, result, cross);

    erode(result, result, rhombus);

    Mat result2;

    dilate(image, result2, x);

    erode(result2, result2, square);

    absdiff(result2, result, result);

    this->applyThreshold(result);

    return result;
}

void Characteristics::drawOnImage(Mat& binary, Mat& image)
{
    Mat_<uchar>::const_iterator it = binary.begin<uchar>();
    Mat_<uchar>::const_iterator itend = binary.end<uchar>();

    for (int i = 0; it != itend; ++it, ++i)
    {
        // if current pixel is black
        if (*it == 0) {
            circle(image, Point(i%image.step, i/image.step), 5, Scalar(255, 0, 0));
        }
    }
}
