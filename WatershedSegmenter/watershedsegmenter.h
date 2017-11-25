#ifndef WATERSHEDSEGMENTER_H
#define WATERSHEDSEGMENTER_H

#include <opencv2/core/core.hpp>

using namespace cv;

class WatershedSegmenter
{
    private:
        Mat markers;

    public:
        void setMarkers(Mat& markerImage)
        {
            markerImage.convertTo(markers, CV_32S);
        }

        Mat process(Mat &image)
        {
            watershed(image, markers);
            return markers;
        }

        Mat getSegmentation()
        {
            Mat result;
            markers.convertTo(result, CV_8U);
            return result;
        }

        Mat getWatersheds()
        {
            Mat result;
            markers.convertTo(result, CV_8U, 255, 255);
            return result;
        }
};

#endif // WATERSHEDSEGMENTER_H
