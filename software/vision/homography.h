#ifndef HOMOGRAPHY_H
#define HOMOGRAPHY_H

#include "opencv2/opencv.hpp"
using namespace cv;

class Homography
{
public:
    Homography(float scale = 4.0);
    ~Homography();

    void CalcHomographyMat(vector<Point2f> src_points);
    void Transform(Mat& src);

    Mat output;

    float GetScale()
    {
        return scale;
    }

protected:
private:
    Mat homography_mat;
    float scale;
    vector<Point2f> dst_points;
};

#endif // HOMOGRAPHY_H

