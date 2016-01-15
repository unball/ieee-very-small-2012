/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 2012-09-27
*/

#include "ui.h"
#include "utils.h"
#include "rsvs.h"

using namespace cv;
using namespace std;

#define CheckFlag(code) ((flags & code) == code)

UI::UI(RSVS* rsvs_handler)
{
    this->rsvs_handler = rsvs_handler;

    window_name = "RSVS";

    namedWindow("mask");

    namedWindow(window_name);

    setMouseCallback(window_name,StaticMouseCallback,this);

    createTrackbar("SMIN","RSVS",&rsvs_handler->segmenter.smin,256);

    createTrackbar("VMIN","RSVS",&rsvs_handler->segmenter.vmin,256);

    moveWindow ("mask", 640, 50);

    pause = false;

    stop = false;

    mode = ui_deactivated;

    trainning_color = field;

    selection_state = 0;

    new_tracked_object = none;

    homography_done = false;
}

UI::~UI()
{
    destroyWindow(window_name);
}

void UI::StaticMouseCallback(int event, int x, int y, int flags, void* param)
{
    ((UI*) param)->MouseCallback(event,x,y,flags);
}

void UI::MouseCallback(int event, int x, int y, int flags)
{
    if (output.empty()) return;

    if (CheckFlag(CV_EVENT_LBUTTONDOWN))
    {
        switch(mode)
        {
        case color_trainning:

            selection_rect.width = x - selection_rect.x;

            selection_rect.height = y - selection_rect.y;

            break;

        case team_selection:

        case opponent_selection:

        case ball_selection:

        case field_selection:

            selection_radius = sqrt((x-selection_center.x)*(x-selection_center.x)+(y-selection_center.y)*(y-selection_center.y));

            break;

        case homography:

            selection_center = Point2f(x,y);

            break;

        default:

            break;
        }
    }

    switch(event)
    {
    case CV_EVENT_LBUTTONDOWN:
        switch(mode)
        {
        case color_trainning:

            selection_state = -1;

            selection_rect = Rect(x,y,0,0);

            break;

        case team_selection:

        case opponent_selection:

        case ball_selection:

        case field_selection:

            selection_state = -1;

            selection_center = Point(x,y);

            selection_radius = 0;

            break;

        case homography:

            selection_state = -1;

            selection_center = Point2f(x,y);

            selection_radius = 5;

            break;

        default:

            break;
        }
        break;

    case CV_EVENT_LBUTTONUP:
        switch(mode)
        {
        case color_trainning:

            selection_rect = Rect(min(x,selection_rect.x),min(y,selection_rect.y),abs(selection_rect.width),abs(selection_rect.height));

            if (CheckRectBoundaries(selection_rect,output) && selection_rect.width > 0 && selection_rect.height > 0)
                selection_state = 1;
            else
                selection_state = 0;

            break;

        case team_selection:

        case opponent_selection:

        case ball_selection:

        case field_selection:

            if (CheckCircleBoundaries(selection_center,selection_radius,output) && selection_radius > 0)
                selection_state = 1;
            else
                selection_state = 0;

            break;

        case homography:

            selection_points.push_back(Point2f(x,y));

            cout << x << " " << y << endl;

            if (selection_points.size() == 6)
                selection_state = 1;

            break;

        default:

            break;
        }
        break;

    default:
        break;
    }
}

#ifdef __unix__

#define WAIT_KEY(wait_time) waitKey(wait_time)%256
#define KEY_F1 0xbe
#define KEY_F2 0xbf
#define KEY_F3 0xc0
#define KEY_F4 0xc1
#define KEY_F5 0xc2
#define KEY_F6 0xc3

#else

#define WAIT_KEY(wait_time) waitKey(wait_time)
#define KEY_F1 0x700000
#define KEY_F2 0x710000
#define KEY_F3 0x720000
#define KEY_F4 0x730000
#define KEY_F5 0x740000
#define KEY_F6 0x750000

#endif

void UI::KeyboardCallback(int wait_time)
{
    key = WAIT_KEY(wait_time);

    switch (key)
    {
    case ' ':
        pause = !pause;
        break;

    case 0x1b: //esc
        stop = true;
        break;

    case 0x8: //backspace
        rsvs_handler->tracker.ClearLast();
        break;

    case 'h':
        homography_done = false;
        break;

    case 'a':
        cout << "Homografia automatica a." << endl;
        selection_points.push_back(Point2f(56,165));
        selection_points.push_back(Point2f(328,12));
        selection_points.push_back(Point2f(599,157));
        selection_points.push_back(Point2f(598,288));
        selection_points.push_back(Point2f(333,434));
        selection_points.push_back(Point2f(61,296));
        rsvs_handler->homography.CalcHomographyMat(selection_points);
        selection_points.clear();
        homography_done = true;
        break;
        
     case 's':
        cout << "Homografia automatica s." << endl;
        selection_points.push_back(Point2f(598,288)); //4
        selection_points.push_back(Point2f(333,434)); //5
        
        selection_points.push_back(Point2f(61,296)); //6
        selection_points.push_back(Point2f(56,165)); //1
        selection_points.push_back(Point2f(328,12)); //2
        selection_points.push_back(Point2f(599,157)); //3
        rsvs_handler->homography.CalcHomographyMat(selection_points);
        selection_points.clear();
        homography_done = true;
        break;
    case 'f':

        SetMode(field_selection);

        break;

    case KEY_F1: //F1
        SetMode(color_trainning);
        break;

    case KEY_F2: //F2
        SetMode(team_selection);
        break;

    case KEY_F3: //F3
        SetMode(opponent_selection);
        break;

    case KEY_F4: //F4
        SetMode(ball_selection);
        break;

    case KEY_F5: //F5
        SetMode(ui_deactivated);
        break;

    case KEY_F6: //F6
        SetMode(homography);
        break;

    case '0':
        SetTrainningColor(field);
        break;

    case '1':
        SetTrainningColor(red);
        break;

    case '2':
        SetTrainningColor(orange);
        break;

    case '3':
        SetTrainningColor(yellow);
        break;

    case '4':
        SetTrainningColor(green);
        break;

    case '5':
        SetTrainningColor(cyan);
        break;

    case '6':
        SetTrainningColor(blue);
        break;

    case '7':
        SetTrainningColor(violet);
        break;

    case '8':
        SetTrainningColor(other);
        break;

    case 0xFFFFFFFF:
        break;

    default:
        cout << "key 0x" << hex << key << endl;
        break;
    }
}

void UI::Draw(Mat& src)
{
    src.copyTo(output);

    setTrackbarPos("SMIN","RSVS",rsvs_handler->segmenter.smin);
    setTrackbarPos("VMIN","RSVS",rsvs_handler->segmenter.vmin);

    rsvs_handler->tracker.DrawMarkers(output);

    rectangle(output, cv::Rect(43,0,554,480), Scalar(0,0,0));

    if (selection_state == -1)
    {
        switch(mode)
        {
        case color_trainning:

            rectangle(output,selection_rect.tl(),selection_rect.br(),Scalar(255,255,255));

            break;

        case team_selection:

            circle(output,selection_center,selection_radius,Scalar(255,0,0));

            break;

        case opponent_selection:

            circle(output,selection_center,selection_radius,Scalar(0,0,255));

            break;

        case ball_selection:

            circle(output,selection_center,selection_radius,Scalar(0,127,255));

            break;

        case field_selection:

            circle(output, selection_center, selection_radius, Scalar(0,255,255));

            break;

        case homography:

            for (unsigned int i = 0; i < selection_points.size(); i++)
            {
                circle(output,selection_points[i],selection_radius,Scalar(255,255,255));
            }

            break;

        case ui_deactivated:

            break;
        }
    }

    else if (selection_state == 1)
    {
        switch(mode)
        {
        case color_trainning:
        {
            Mat roi(output,selection_rect);
            roi = roi.clone();
            cvtColor(roi,roi,CV_BGR2HSV);
            Scalar mean, stddev;
            meanStdDev(roi,mean,stddev);
            cout << "H " << mean[0] << " " << stddev[0] << endl;
            cout << "S " << mean[1] << " " << stddev[1] << endl;
            cout << "V " << mean[2] << " " << stddev[2] << endl << endl;

            rsvs_handler->color_table.AddColorData(roi,trainning_color);
        }
        break;

        case team_selection:

            tracked_object_rect = CircleToRect(selection_center,selection_radius);

            new_tracked_object = team_robot;

            break;

        case opponent_selection:

            tracked_object_rect = CircleToRect(selection_center,selection_radius);

            new_tracked_object = opponent_robot;

            break;

        case ball_selection:

            tracked_object_rect = CircleToRect(selection_center,selection_radius);

            new_tracked_object = ball;

            break;

        case field_selection:

            tracked_object_rect = CircleToRect(selection_center, selection_radius);

            new_tracked_object = soccer_field;

            break;

        case homography:

            homography_done = true;

            rsvs_handler->homography.CalcHomographyMat(selection_points);

            selection_points.clear();

            break;

        default:

            break;
        }

        selection_state = 0;
    }
}

void UI::Show()
{
    imshow(window_name,output);
}

void UI::SetMode(Mode mode)
{
    this->mode = mode;

    switch(mode)
    {
    case ui_deactivated:
        cout << "UI desativada." << endl;
        break;

    case team_selection:
        cout << "Modo de selecao do time." << endl;
        break;

    case opponent_selection:
        cout << "Modo de selecao do oponente." << endl;
        break;

    case ball_selection:
        cout << "Modo de selecao da bola." << endl;
        break;

    case field_selection:

        cout << "Modo de selecao do campo." << endl;

        break;

    case color_trainning:
        cout << "Modo de treinamento de cor." << endl;
        break;

    case homography:
        cout << "Modo de homografia." << endl;
        break;
    }
}

void UI::SetTrainningColor(Color trainning_color)
{
    if (mode == color_trainning)
    {
        this->trainning_color = trainning_color;
        std::cout << "Cor selecionada: " << rsvs_handler->color_table.GetColorName(trainning_color) << std::endl;
    }
}
