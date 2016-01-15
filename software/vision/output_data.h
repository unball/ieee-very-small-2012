#ifndef OUTPUT_DATA_H
#define OUTPUT_DATA_H

#include "opencv2/opencv.hpp"
using namespace cv;

#include "tracker.h"

class OutputData
{
public:
	OutputData();
	~OutputData();

	bool Update(Tracker& tracker, float scale = 4.0);

	Point2f team_pos[3];
    double team_orientation[3];

    Point2f opponent_pos[3];
    double opponent_orientation[3];

    Point2f ball_pos;
protected:
private:

};
/*
    O campo possui 170 cm de gol a gol por 130 cm de largura. A imagem tem 640x480.
    Para fazer a devida conversao de valores o campo deve cobrir toda a altura da
    imagem 480 pixels. Os valores devem ser normalizados sabendo-se que sob as condicoes
    acima 480 pixels equivalem a 130 cm. Logo o campo tera 554 pixels de comprimento.
*/

#endif // OUTPUT_DATA_H

