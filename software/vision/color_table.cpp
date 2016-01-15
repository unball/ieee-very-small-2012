/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 2012-09-28
*/

#include <iostream>

#include "color_table.h"
#include "utils.h"

using namespace std;
using namespace cv;

ColorTable::ColorTable()
{
    LUT = new unsigned char[LUT_DIM*LUT_DIM*LUT_DIM];
    //memset(LUT,0,LUT_DIM*LUT_DIM*LUT_DIM);
}

ColorTable::~ColorTable()
{
    delete LUT;
}

void ColorTable::AddColorData(Mat& data, Color color)
{
    for (int i = 0; i < data.rows; i++)
        for (int j = 0; j < data.cols; j++)
        {
            Vec3b pixel = data.at<Vec3b>(i,j);

            pixel[0] = round((LUT_DIM-1)*pixel[0]/255.0);
            pixel[1] = round((LUT_DIM-1)*pixel[1]/255.0);
            pixel[2] = round((LUT_DIM-1)*pixel[2]/255.0);

            LUT[LUT_DIM*LUT_DIM*pixel[0]
                + LUT_DIM*pixel[1]
                + pixel[2]] = (unsigned char)color;
        }
}

void ColorTable::LUTTransform(Mat& src, Mat& dst, int mode)
{
    if (dst.empty()) dst = Mat::zeros(src.size(),CV_8UC3);

    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            Vec3b pixel = src.at<Vec3b>(i,j);

            pixel[0] = round((LUT_DIM-1)*pixel[0]/255.0);
            pixel[1] = round((LUT_DIM-1)*pixel[1]/255.0);
            pixel[2] = round((LUT_DIM-1)*pixel[2]/255.0);

            switch(mode)
            {
            case LUT_MODE_COLOR:
                dst.at<Vec3b>(i,j) = LUT[LUT_DIM*LUT_DIM*pixel[0]
                                         + LUT_DIM*pixel[1]
                                         + pixel[2]];
                break;

            case LUT_MODE_BGR:
                dst.at<Vec3b>(i,j) = GetColorBGR((Color)LUT[LUT_DIM*LUT_DIM*pixel[0]
                                                 + LUT_DIM*pixel[1]
                                                 + pixel[2]]);
                break;

            case LUT_MODE_HSV:
                dst.at<Vec3b>(i,j) = GetColorHSV((Color)LUT[LUT_DIM*LUT_DIM*pixel[0]
                                                 + LUT_DIM*pixel[1]
                                                 + pixel[2]]);
                break;

            default:
                cout << "LUT: Modo invalido." << endl;
                return;
            }
        }
}

Vec3b ColorTable::GetColorBGR(Color color)
{
    switch(color)
    {
    case field:
        return Vec3b(0,0,0);
        break;

    case red:
        return Vec3b(0,0,255);
        break;

    case orange:
        return Vec3b(0,127,255);
        break;

    case yellow:
        return Vec3b(0,255,255);
        break;

    case green:
        return Vec3b(0,255,0);
        break;

    case cyan:
        return Vec3b(255,255,0);
        break;

    case blue:
        return Vec3b(255,0,0);
        break;

    case violet:
        return Vec3b(255,0,143);
        break;

    case other:
        return Vec3b(255,255,255);
        break;
    }

    return Vec3b(0,0,0);
}

Vec3b ColorTable::GetColorHSV(Color color)
{
    switch(color)
    {
    case field:
        return Vec3b(0,0,0);
        break;

    case red:
        return Vec3b(0,255,255);
        break;

    case orange:
        return Vec3b(15,255,255);
        break;

    case yellow:
        return Vec3b(30,255,255);
        break;

    case green:
        return Vec3b(60,255,255);
        break;

    case cyan:
        return Vec3b(90,255,255);
        break;

    case blue:
        return Vec3b(120,255,255);
        break;

    case violet:
        return Vec3b(137,255,255);
        break;

    case other:
        return Vec3b(0,0,255);
        break;
    }

    return Vec3b(0,0,0);
}

const char* ColorTable::GetColorName(Color color)
{
    switch(color)
    {
    case field:
        return "field";
        break;

    case red:
        return "red";
        break;

    case orange:
        return "orange";
        break;

    case yellow:
        return "yellow";
        break;

    case green:
        return "green";
        break;

    case cyan:
        return "cyan";
        break;

    case blue:
        return "blue";
        break;

    case violet:
        return "violet";
        break;

    case other:
        return "other";
        break;
    }

    return "unknown";
}
