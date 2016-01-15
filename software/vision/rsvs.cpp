/*
    @file communication.cpp

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

#include "rsvs.h"

#ifdef __unix__
#include <boost/progress.hpp>
#else
#include "timer.h"
#endif //__unix__


#include <ctime>
#include <string>

string get_date(void)
{
   time_t now;

   const  struct tm * timeinfo;

   char the_date[30];

   the_date[0] = '\0';

   now = time(&now);

   timeinfo = localtime(&now);

   if (now != -1)
   {
      strftime(the_date, 30, "%d-%m-%Y(%X).avi", timeinfo);
   }

   return string(the_date);
}

using namespace cv;

RSVS::RSVS() : ui(this)
{
    initialized = false;

    Init();
}

RSVS::~RSVS()
{
    capture.release();
}

void RSVS::Init()
{
    capture.open(0);

    if (!capture.isOpened())
    {
        std::cout << "Erro fatal: nao foi possivel iniciar captura!" << std::endl;
        return;
    }

    video.open(get_date(), CV_FOURCC('M','J','P','G'), 15.0, Size(640,480));

    initialized = true;

}

bool RSVS::Initialized()
{
    return initialized;
}

bool RSVS::Run()
{
    //acquisition
    if (ui.stop) return false;

    if (!ui.pause)
    {
        if (!capture.grab())
            return false;

        capture.retrieve(frame,0);

        video << frame;

        //frame = imread("data/field.png");
    }

    //input
    if (ui.new_tracked_object)
    {
        tracker.AddNewTrackedObject(ui.tracked_object_rect,ui.new_tracked_object,segmenter.hsv,segmenter.mask);

        ui.new_tracked_object = none;
    }

    if (ui.homography_done)
    {
        homography.Transform(frame);

        frame = homography.output;
    }

    preprocessor.Run(frame);

    segmenter.Run(preprocessor.output);

    imshow("mask",segmenter.mask);

    tracker.Track(segmenter.hsv,segmenter.mask);

    //communication
    if (output_data.Update(tracker))
    {
      communication.Send(output_data);
    }

    //user interface
    ui.KeyboardCallback(1);

    ui.Draw(preprocessor.output);

    ui.Show();

    return true;
}
