#ifndef UI_H
#define UI_H

#include "opencv2/opencv.hpp"

#include "color_table.h"
#include "tracker.h"

using namespace cv;

class RSVS;

class UI
{
public:
    enum Mode {ui_deactivated = 0, team_selection = 1, opponent_selection = 2, ball_selection = 3, color_trainning = 4, homography = 5, field_selection};

    UI(RSVS* rsvs_handler);
    ~UI();

    void MouseCallback(int event, int x, int y, int flags);
    void KeyboardCallback(int delay);

    void Draw(Mat& src);
    void Show();

    bool pause;
    bool stop;

    TrackedObjectType new_tracked_object;
    Rect tracked_object_rect;

    bool homography_done;

protected:
private:
    const char* window_name;

    int key;

    Mat output;

    void SetMode(Mode mode);

    void SetTrainningColor(Color color);

    Mode mode;

    Color trainning_color;

    int selection_state;
    Point selection_center;
    float selection_radius;
    Rect selection_rect;

    RSVS* rsvs_handler; //gambiarra (ou nao)

    static void StaticMouseCallback(int event, int x, int y, int flags, void* param);

    vector<Point2f> selection_points;
};

#endif // UI_H
