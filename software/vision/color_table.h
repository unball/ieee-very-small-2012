#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

#include "opencv2/opencv.hpp"

using namespace cv;

#define N_COLORS 9

enum Color {field = 0, red = 1, orange = 2, yellow = 3, green = 4, cyan = 5, blue = 6, violet = 7, other = 8};

#define LUT_DIM 16

#define LUT_MODE_COLOR 0
#define LUT_MODE_BGR 2
#define LUT_MODE_HSV 3

class ColorTable
{
public:
    ColorTable();
    ~ColorTable();

    void AddColorData(Mat& data, Color color);
    void LUTTransform(Mat& src, Mat& dst, int mode = LUT_MODE_COLOR);

    Vec3b GetColorBGR(Color color);
    Vec3b GetColorHSV(Color color);
    const char* GetColorName(Color color);

    //void LoadColorTable(const char* filename);

protected:
private:
    unsigned char* LUT;
};

#endif // COLOR_TABLE_H
