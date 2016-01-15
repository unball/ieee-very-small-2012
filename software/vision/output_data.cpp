/**
RSVS: Robot Soccer Vision System

Autor: André Luiz Siega Nepomuceno
Email: andrelsn@live.com
Data: 2012-10-19
*/

#include "output_data.h"

#define INVALID_DATA 1e+10

using namespace std;
OutputData::OutputData()
{
    for (int i = 0; i < 3; i++)
    {
        team_pos[i] = Point2f(INVALID_DATA,INVALID_DATA);
        team_orientation[i] = INVALID_DATA;

        opponent_pos[i] = Point2f(INVALID_DATA,INVALID_DATA);
        opponent_orientation[i] = INVALID_DATA;
    }

    ball_pos = Point2f(INVALID_DATA,INVALID_DATA);
}

OutputData::~OutputData()
{

}

bool OutputData::Update(Tracker& tracker, float scale)
{
    for (unsigned int i = 0; i < tracker._tracked_objects.size(); i++)
    {
        TrackedObject *to = tracker._tracked_objects[i];

        unsigned int id = to->GetID();

        if (id < 0 || id > 2)
        {
            cout << "ERRO CRITICO: ID INVALIDO! NAO E POSSIVEL ATUALIZAR DADOS DE SAIDA" << endl;

            return false;
        }

        // O valores sao passados em metros e radianos.

        switch(to->GetType())
        {
        case team_robot:

            team_pos[id] = Point2f((to->GetX() - 640. / 2.) * 1.30 / 480.,(to->GetY() - 480. / 2.) * -1. * 1.30 / 480.);

            team_orientation[id] = to->GetOrientation();

            break;

        case opponent_robot:

            opponent_pos[id] = Point2f((to->GetX() - 640. / 2.) * 1.30 / 480.,(to->GetY() - 480. / 2.) * -1. * 1.30 / 480.);

            team_orientation[id] = to->GetOrientation();

            break;

        case ball:

            ball_pos = Point2f((to->GetX() - 640. / 2.) * 1.30 / 480.,(to->GetY() - 480. / 2.) * -1. * 1.30 / 480.);

            break;

        default:

            break;

        }
    }

    std::cout << team_pos[0] << std::endl;
    std::cout << team_orientation[0] << std::endl;

    return true;
}
