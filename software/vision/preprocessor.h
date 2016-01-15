#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "opencv2/opencv.hpp"

using namespace cv;

class Preprocessor
{
public:
    Preprocessor();
    ~Preprocessor();

    void Run(Mat& src);

    Mat output;
protected:
private:
};

#endif // PREPROCESSOR_H

