#ifndef TRACKING_TARGET_H
#define TRACKING_TARGET_H

#include "opencv2/opencv.hpp"

#include <list>

using namespace cv;

enum TrackedObjectType {none = 0, team_robot = 1, opponent_robot = 2, ball = 3, soccer_field};

class TrackedObject
{
public:
    TrackedObject();
    ~TrackedObject();

    void Init(Rect& tracking_window, Mat& src, Mat& mask);

    void Track(Mat& src, Mat& mask);

    virtual void DrawMarkers(Mat& dst);

    virtual void CalcOrientation(Mat& src, Mat& mask) {}

    void UpdateROI(Mat& src, Mat& mask);

    bool TestHistogram(double threshold);

    void Find(Mat& src, Mat& mask);

    Rect _tracking_window;

    int _id;

    TrackedObjectType _type;

    double _orientation;

    double GetX()
    {
        return (_tracking_window.x+_tracking_window.width/2);
    }

    double GetY()
    {
        return (_tracking_window.y+_tracking_window.height/2);
    }

    double GetOrientation()
    {
        return _orientation;
    }

    TrackedObjectType GetType()
    {
        return _type;
    }

    int GetID()
    {
        return _id;
    }

protected:
    MatND _histogram;

    Mat _src_roi;
    Mat _mask_roi;
    Mat _backprojection;

private:
};

class TeamRobot : public TrackedObject
{
public:
    TeamRobot();

    ~TeamRobot();

    void DrawMarkers(Mat& dst);

    void CalcOrientation(Mat& src, Mat& mask);
};

class OpponentRobot : public TrackedObject
{
public:
    OpponentRobot();

    ~OpponentRobot();

    void DrawMarkers(Mat& dst);

    void CalcOrientation(Mat& src, Mat& mask);
};

class Ball : public TrackedObject
{
public:
    Ball();

    ~Ball();

    void DrawMarkers(Mat& dst);
};

class Tracker
{
public:
    Tracker();
    ~Tracker();

    void AddNewTrackedObject(Rect tracking_window, TrackedObjectType type, Mat& src, Mat& mask);
    void Track(Mat& src, Mat& mask);
    void DrawMarkers(Mat& src);
    void ClearAll();
    void ClearLast();

    vector<TrackedObject*> _tracked_objects;

    int _team_counter, _opponent_counter;
protected:
private:
};
class Field : public TrackedObject
{
public:
    Field();

    ~Field();

    void DrawMarkers(Mat &dst);

    void CalcOrientation(Mat &src, Mat &mask);
};

#endif // TRACKING_TARGET_H
