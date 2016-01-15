/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 2012-10-02
*/

#include "preprocessor.h"

using namespace cv;

Preprocessor::Preprocessor()
{

}

Preprocessor::~Preprocessor()
{

}

void Preprocessor::Run(Mat& src)
{
    medianBlur(src,output,5); //mais lento, menor stddev
}
