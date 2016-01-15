/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 2012-10-18
*/

#include "homography.h"

using namespace cv;

#include <iostream>
using namespace std;

Homography::Homography(float scale)
{
    this->scale = scale;

    dst_points.clear();

    dst_points.push_back(scale*Point2f(0.0,45.0));
    dst_points.push_back(scale*Point2f(85.0,0.0));
    dst_points.push_back(scale*Point2f(170.0,45.0));

    dst_points.push_back(scale*Point2f(170.0,85.0));
    dst_points.push_back(scale*Point2f(85.0,130.0));
    dst_points.push_back(scale*Point2f(0.0,85.0));
}

Homography::~Homography()
{

}

void Homography::CalcHomographyMat(vector<Point2f> src_points)
{
    if (src_points.size() != 6)
    {
        cout << "Erro: sao necessarios 6 pontos para o calculo da homografia." << endl;
        return;
    }

    Mat srcp(src_points);
    Mat dstp(dst_points);

    homography_mat = findHomography(srcp,dstp);
}

void Homography::Transform(Mat& src)
{
    warpPerspective(src,output,homography_mat,Size(scale*170,scale*130));
}
