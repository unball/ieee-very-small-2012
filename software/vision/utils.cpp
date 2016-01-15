#include "utils.h"

using namespace cv;

Scalar hls2bgr (float h, float l, float s)
{
    float b, g, r;

    h*=2.0f;
    l*=0.00392156862745098f;
    s*=0.00392156862745098f;

    if( s == 0 )
        b = g = r = l;
    else
    {
        static const int sector_data[][3]=
        {{1,3,0}, {1,0,2}, {3,0,1}, {0,2,1}, {0,1,3}, {2,1,0}};
        float tab[4];
        int sector;

        float p2 = l <= 0.5f ? l*(1 + s) : l + s - l*s;
        float p1 = 2*l - p2;

        h *= 0.016666666666666666f; // h /= 60;
        if( h < 0 )
            do h += 6;
            while( h < 0 );
        else if( h >= 6 )
            do h -= 6;
            while( h >= 6 );

        assert( 0 <= h && h < 6 );
        sector = cvFloor(h);
        h -= sector;

        tab[0] = p2;
        tab[1] = p1;
        tab[2] = p1 + (p2 - p1)*(1-h);
        tab[3] = p1 + (p2 - p1)*h;

        b = tab[sector_data[sector][0]];
        g = tab[sector_data[sector][1]];
        r = tab[sector_data[sector][2]];
    }

    b=round(255*b);
    g=round(255*g);
    r=round(255*r);

    return Scalar(b,g,r);
}

Rect CircleToRect(Point center, int radius)
{
    return Rect(center.x - radius, center.y - radius, 2*radius, 2*radius);
}

bool CheckRectBoundaries(Rect& rect, Mat& src)
{
    if ((rect.x + rect.width < src.cols) && (rect.x >= 0) && (rect.y + rect.height < src.rows) && (rect.y >= 0))
        return true;
    else
        return false;
}

bool CheckCircleBoundaries(Point& center, int radius, Mat& src)
{
    if ((center.x + radius < src.cols) && (center.x - radius >= 0) &&
            (center.y + radius < src.rows) && (center.y - radius >= 0))
        return true;
    else
        return false;
}

Scalar hsv2bgr (float h, float s, float v)
{
    float b, g, r;

    h /= 30.0;
    s /= 255.0;
    v /= 255.0;

    if( s == 0 )
        b = g = r = v;
    else
    {
        static const int sector_data[][3]=
        {{1,3,0}, {1,0,2}, {3,0,1}, {0,2,1}, {0,1,3}, {2,1,0}};
        float tab[4];
        int sector;
        //h /= 60.0;
        if( h < 0 )
            do h += 6;
            while( h < 0 );
        else if( h >= 6 )
            do h -= 6;
            while( h >= 6 );
        sector = cvFloor(h);
        h -= sector;

        tab[0] = v;
        tab[1] = v*(1.f - s);
        tab[2] = v*(1.f - s*h);
        tab[3] = v*(1.f - s*(1.f - h));

        b = tab[sector_data[sector][0]];
        g = tab[sector_data[sector][1]];
        r = tab[sector_data[sector][2]];
    }

    b=round(255*b);
    g=round(255*g);
    r=round(255*r);

    return Scalar(b,g,r);
}
