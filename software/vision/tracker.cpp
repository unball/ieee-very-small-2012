/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 2012-09-28
*/

#include "tracker.h"

#include "utils.h"

using namespace cv;

TrackedObject::TrackedObject()
{
    _id = none;

    _type = none;

    _orientation = 0.0;
}

TrackedObject::~TrackedObject()
{

}

void TrackedObject::Init(Rect& tracking_window, Mat& src, Mat& mask)
{
    const int channels[] = {0,1}; //hsv

    const int h_size = 16;
    const int s_size = 16;
    const int hist_size[] = {h_size,s_size};

    const float h_ranges[] = {0,180};
    const float s_ranges[] = {0,256};
    const float* ranges[] = {h_ranges,s_ranges};

    this->_tracking_window = tracking_window;

    _src_roi = src(tracking_window);
    _mask_roi = mask(tracking_window);

    calcHist(&_src_roi,1,channels,_mask_roi,_histogram,2,hist_size,ranges);
    normalize(_histogram,_histogram,0,255,CV_MINMAX);
}

void TrackedObject::Track(Mat& src, Mat& mask)
{
    const int channels[] = {0,1};

    const float h_ranges[] = {0,180};
    const float s_ranges[] = {0,256};
    const float* ranges[] = {h_ranges,s_ranges};

    calcBackProject(&src,1,channels,_histogram,_backprojection,ranges);
    _backprojection &= mask;

    //imshow("back",backprojection);

    meanShift(_backprojection,_tracking_window,TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,10.0,1.0));
}

void TrackedObject::DrawMarkers(Mat& src)
{
    rectangle(src,_tracking_window.tl(),_tracking_window.br(),Scalar(255,255,255));
}

void TrackedObject::UpdateROI(Mat& src, Mat& mask)
{
    _src_roi = src(_tracking_window);
    _mask_roi = mask(_tracking_window);
}

bool TrackedObject::TestHistogram(double threshold)
{
    MatND test_histogram;

    const int channels[] = {0,1};

    const int h_size = 16;
    const int s_size = 16;
    const int hist_size[] = {h_size,s_size};

    const float h_ranges[] = {0,180};
    const float s_ranges[] = {0,256};
    const float* ranges[] = {h_ranges,s_ranges};

    calcHist(&_src_roi,1,channels,_mask_roi,test_histogram,2,hist_size,ranges);
    normalize(test_histogram,test_histogram,0,255,CV_MINMAX);

    double dist = compareHist(_histogram,test_histogram,CV_COMP_BHATTACHARYYA);

    if (dist > threshold) return false;
    else return true;
}

TeamRobot::TeamRobot()
{
    _orientation = 0.0;

    _type = team_robot;
}

TeamRobot::~TeamRobot()
{

}

void TeamRobot::DrawMarkers(Mat& src)
{
    rectangle(src,_tracking_window.tl(),_tracking_window.br(),Scalar(255,0,0));

    Point center(_tracking_window.x+_tracking_window.width/2,_tracking_window.y+_tracking_window.height/2);

    Point arrow(center.x + _tracking_window.width / 2 * cos(_orientation), center.y + _tracking_window.width / 2 * sin(_orientation));

    circle(src,center,5,Scalar(255,0,0),CV_FILLED);

    line(src,center,arrow,Scalar(255,0,0));
}

void TeamRobot::CalcOrientation(Mat& src, Mat& mask)
{
    //UpdateROI(src,mask);

    Mat hue(_src_roi.size(),CV_8UC1);

    int from_to[] = {0,0};

    mixChannels(&_src_roi,1,&hue,1,from_to,1);

    hue &= _mask_roi;

    Mat team_color_mask;

    Mat robot_color_mask;

    //inRange(hue,Scalar(100),Scalar(120),team_color_mask);

    inRange(hue,Scalar(10),Scalar(20),team_color_mask);

    robot_color_mask = _mask_roi & (~team_color_mask);

    Moments m_team_color = moments(team_color_mask,true);

    Moments m_robot_color = moments(robot_color_mask,true);;

    if (m_robot_color.m00 == 0 || m_team_color.m00 == 0)
    {
        _orientation = 0;

        return;
    }

    double x = m_robot_color.m10/m_robot_color.m00 - m_team_color.m10/m_team_color.m00;

    double y = m_robot_color.m01/m_robot_color.m00 - m_team_color.m01/m_team_color.m00;

    _orientation = acos(x/sqrt(x*x+y*y));

    _orientation -= M_PI/4.0;
}

OpponentRobot::OpponentRobot()
{
    _orientation = 0.0;

    _type = opponent_robot;
}

OpponentRobot::~OpponentRobot()
{

}

void OpponentRobot::DrawMarkers(Mat& src)
{
    // Draw rectangle

    rectangle(src,_tracking_window.tl(),_tracking_window.br(),Scalar(0,255,255));

    Point center(_tracking_window.x+_tracking_window.width/2,_tracking_window.y+_tracking_window.height/2);

    Point arrow(center.x + _tracking_window.width / 2 * cos(_orientation), center.y + _tracking_window.width / 2 * sin(_orientation));

    // Draw circle

    circle(src,center,5,Scalar(0,255,255),CV_FILLED);

    // Draw line

    line(src,center,arrow,Scalar(0,255,255));
}

void OpponentRobot::CalcOrientation(Mat& src, Mat& mask)
{
    //UpdateROI(src,mask);

    Mat hue(_src_roi.size(),CV_8UC1);

    int from_to[] = {0,0};

    mixChannels(&_src_roi,1,&hue,1,from_to,1);

    hue &= _mask_roi;

    Mat team_color_mask;

    Mat robot_color_mask;

    //inRange(hue,Scalar(100),Scalar(120),team_color_mask);

    inRange(hue,Scalar(10),Scalar(20),team_color_mask);

    robot_color_mask = _mask_roi & (~team_color_mask);

    Moments m_team_color = moments(team_color_mask,true);

    Moments m_robot_color = moments(robot_color_mask,true);;

    if (m_robot_color.m00 == 0 || m_team_color.m00 == 0)
    {
        _orientation = 0;

        return;
    }

    double x = m_robot_color.m10/m_robot_color.m00 - m_team_color.m10/m_team_color.m00;

    double y = m_robot_color.m01/m_robot_color.m00 - m_team_color.m01/m_team_color.m00;

    _orientation = acos(x/sqrt(x*x+y*y));

    _orientation -= M_PI/4.0;
}

Ball::Ball()
{
    _orientation = 0.0;

    _type = ball;
}

Ball::~Ball()
{

}

void Ball::DrawMarkers(Mat& src)
{
    rectangle(src,_tracking_window.tl(),_tracking_window.br(),Scalar(0,127,255));
}

Tracker::Tracker()
{
    _team_counter = 0;

    _opponent_counter = 0;
}

Tracker::~Tracker()
{

}
Field::Field()
{
    _orientation = 0.0;

    _type = soccer_field;
}

Field::~Field() {}

void Field::DrawMarkers(Mat &src)
{
    // Draw rectangle

    rectangle(src,_tracking_window.tl(),_tracking_window.br(),Scalar(140, 4, 168));

    Point center(_tracking_window.x+_tracking_window.width/2,_tracking_window.y+_tracking_window.height/2);

    Point arrow(center.x + _tracking_window.width / 2 * cos(_orientation), center.y + _tracking_window.width / 2 * sin(_orientation));

    // Draw circle

    circle(src, center, 5, Scalar(140, 4, 168), CV_FILLED);

    // Draw line

    line(src,center,arrow,Scalar(140, 4, 168));
}

void Field::CalcOrientation(Mat &src, Mat &mask) {}

void Tracker::AddNewTrackedObject(Rect tracking_window, TrackedObjectType type, Mat& src, Mat& mask)
{
    //verifica se ja existe

    TrackedObject* new_to;

    switch(type)
    {
    case team_robot:

        new_to = new TeamRobot();

        new_to->_id = _team_counter;

        _team_counter++;

        break;

    case opponent_robot:

        new_to = new OpponentRobot();

        new_to->_id = _opponent_counter;

        _opponent_counter++;

        break;

    case ball:

        new_to = new Ball();

        new_to->_id = 0;

        break;

    case soccer_field:

        new_to = new Field();

        new_to->_id = 0;

        break;

    case none:

        break;
    }

    new_to->Init(tracking_window,src,mask);

    _tracked_objects.push_back(new_to);
}

void Tracker::Track(Mat& src, Mat& mask)
{
    for (unsigned int i = 0; i < _tracked_objects.size(); i++)
    {
        _tracked_objects[i]->Track(src,mask);

        _tracked_objects[i]->UpdateROI(src,mask);
        if(!_tracked_objects[i]->TestHistogram(0.5)) //verifica se perdeu o tracking
            _tracked_objects[i]->Find(src,mask);

        _tracked_objects[i]->CalcOrientation(src,mask);
    }
}

void Tracker::DrawMarkers(Mat& src)
{
    for (unsigned int i = 0; i < _tracked_objects.size(); i++)
    {
        _tracked_objects[i]->DrawMarkers(src);
        //cout << tracked_objects[i]->GetX() << " " << tracked_objects[i]->GetY() << endl;
    }
}

void Tracker::ClearAll()
{
    _tracked_objects.clear();

    _team_counter = 0;
    _opponent_counter = 0;
}

void Tracker::ClearLast()
{
    if (_tracked_objects.size() > 0)
    {
        TrackedObject* to;
        to = _tracked_objects.back();

        if (to->GetType() == team_robot)
            _team_counter--;
        else if (to->GetType() == opponent_robot)
            _opponent_counter--;

        _tracked_objects.pop_back();
    }
}

void TrackedObject::Find(Mat& src, Mat& mask)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat temp_mask;
    mask.copyTo(temp_mask);

    Mat structuring_ele = getStructuringElement(MORPH_RECT,Size(7,7));
    dilate(temp_mask,temp_mask,structuring_ele);

    findContours(temp_mask,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

    Mat contours_img = Mat::zeros(src.size(),CV_8UC1);

    double max_sum = 0;
    unsigned int max_i;
    Rect max_rect;

    for (unsigned int i = 0; i < contours.size(); i++)
    {
        Mat points(contours[i]);
        Rect rect = boundingRect(points);

        Mat roi(_backprojection,rect);

        Scalar roi_sum = sum(roi);

        if (roi_sum[0] > max_sum)
        {
            max_sum = roi_sum[0];
            max_i = i;
            max_rect = rect;
        }
    }

    max_rect.width = _tracking_window.width;
    max_rect.height = _tracking_window.height;

    if (max_rect.x + max_rect.width > src.cols)
        max_rect.x = src.cols - max_rect.width;

    if (max_rect.y + max_rect.height > src.rows)
        max_rect.y = src.rows - max_rect.height;

    _tracking_window.x = max_rect.x;
    _tracking_window.y = max_rect.y;
}
