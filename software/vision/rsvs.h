/*
    @file rsvs.h

	@autor			André Luiz Siega Nepomuceno		@email andrelsn@live.com
    @contributor	William Batista Aguiar Motta	@email yosoyninja@gmail.com

    @attention Copyright (C) 2013
    @attention UnBall Robot Soccer Team

       Este programa é um software livre; você pode redistribui-lo e/ou
    modifica-lo dentro dos termos da Licença Pública Geral GNU como
    publicada pela Fundação do Software Livre (FSF); na versão 2 da
    Licença, ou (na sua opnião) qualquer versão.

    Este programa é distribuido na esperança que possa ser  util,
    mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUAÇÂO a qualquer
    MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
    Licença Pública Geral GNU para maiores detalhes.

    Você deve ter recebido uma cópia da Licença Pública Geral GNU
    junto com este programa, se não, escreva para a Fundação do Software
    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef RSVS_H
#define RSVS_H

#include "opencv2/opencv.hpp"

#include "ui.h"
#include "color_table.h"
#include "preprocessor.h"
#include "segmenter.h"
#include "tracker.h"
#include "homography.h"
#include "output_data.h"

#ifdef __unix__
#include "communication.h"
//#include "camera.h"
#endif // __unix__

using namespace cv;

class RSVS
{
    friend class UI;

public:
    RSVS();
    ~RSVS();

    bool Run();
    bool Initialized();

protected:

private:
//#ifdef __unix__
//    Camera capture;
//#else //__unix__
    VideoCapture capture;
//#endif //__unix__

    UI ui;

    bool initialized;

    void Init();

    Mat frame;

    ColorTable color_table;

    Preprocessor preprocessor;

    Segmenter segmenter;

    Tracker tracker;

    Homography homography;

    OutputData output_data;
    
    VideoWriter video;

#ifdef __unix__
    Communication communication;
#endif // __unix__
};

#endif // RSVS_H
