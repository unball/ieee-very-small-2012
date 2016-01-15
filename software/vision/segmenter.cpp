/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 2012-10-02
*/

#include "segmenter.h"

using namespace cv;

Segmenter::Segmenter()
{
    SetParameters(25,25,3);
}

Segmenter::~Segmenter()
{

}

void Segmenter::Run(Mat& src)
{
    cvtColor(src,hsv,CV_BGR2HSV); //hsv mais rapido que hls
    inRange(hsv,Scalar(0,smin,vmin),Scalar(180,256,256),mask);

    //testar espaco Lab ou Luv

    morphologyEx(mask,mask,MORPH_OPEN,structuring_element,Point(-1,-1),2); //mais rapido fazer 2x do que 1x com um S.E. maior
}

void Segmenter::SetParameters(int smin_percent, int vmin_percent, int structuring_element_size)
{
    if (smin_percent > 0) smin = round(smin_percent*2.55);
    if (vmin_percent > 0) vmin = round(vmin_percent*2.55);

    if (structuring_element_size > 0)
    {
        structuring_element.release();
        structuring_element = getStructuringElement(MORPH_RECT,Size(structuring_element_size,structuring_element_size));
    }
}
