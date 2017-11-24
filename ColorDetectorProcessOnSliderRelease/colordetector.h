#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/core/core.hpp>

using namespace cv;

class ColorDetector
{
    private:

        int minDist;
        Vec3b target;
        Mat result;

        int getDistance(Vec3b& color)
        {
            // Manhattan
            return abs(color[0] - target[0] +
                   abs(color[1] - target[1]) +
                   abs(color[2] - target[2]));
        }

    public:
        ColorDetector()
        {
            minDist = 100;
            target[0] = target[1] = target[2] = 0;
        }

        void setColorDistanceThreshold(int distance)
        {
            if (distance < 0) {
                distance = 0;
            }

            minDist = distance;
        }

        int getColorDistanceThreshold()
        {
            return minDist;
        }

        void setTargetColor(uchar red, uchar green, uchar blue)
        {
            target[0] = blue;
            target[1] = green;
            target[2] = red;

        }

        void setTargetColor(Vec3b color)
        {
            target = color;
        }

        Vec3b getTargetColor()
        {
            return target;
        }

        Mat process(Mat &image)
        {
            result.create(image.rows, image.cols, CV_8U);

            Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
            Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
            Mat_<uchar>::iterator itout = result.begin<uchar>();

            for ( ; it != itend; ++it, ++itout){
                if (getDistance(*it) < minDist){
                    *itout = 255; // white
                } else {
                    *itout = 0; // black
                }
            }

            return result;
        }
};

#endif // COLORDETECTOR_H
