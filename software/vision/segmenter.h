#ifndef SEGMENTER_H
#define SEGMENTER_H

#include "opencv2/opencv.hpp"

using namespace cv;

class Segmenter
{
public:
    Segmenter();
    ~Segmenter();

    void Run(Mat& src);
    void SetParameters(int smin_percent, int vmin_percent, int structuring_element_size);

    //output
    Mat hsv;
    Mat mask;

    int smin;
    int vmin;
protected:
private:

    Mat structuring_element;
};

#endif // SEGMENTER_H

