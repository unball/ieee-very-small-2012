#ifndef UTILS_H
#define UTILS_H

#include "opencv2/opencv.hpp"

using namespace cv;

Scalar hls2bgr (float h, float l, float s);
Rect CircleToRect(Point center, int radius);
bool CheckRectBoundaries(Rect& rect, Mat& src);
bool CheckCircleBoundaries(Point& center, int radius, Mat& src);
Scalar hsv2bgr (float h, float s, float v);

#endif // UTILS_H
