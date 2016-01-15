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

#include <iostream>

#include "ProcessLogger.h"
#include "communication.h"

Communication::Communication()
{
    LOG(LEVEL_INFO) << "\n\nUnBall Robot Soccer Team"
                    << "\nVision Module\n";

    Init();
}

Communication::~Communication()
{

}

void Communication::Init()
{
    // Setup read/write channels

    LOG(LEVEL_DEBUG) << "Setup read/write channels";

    _com_write = new Comunicador ("Visao");

    LOG(LEVEL_DEBUG) << "Creating com_write variables";

    _com_write->criar_var<Dados_Simulador>("Dados_Simulador");

    LOG(LEVEL_DEBUG) << "Communication variables created";
}

void Communication::Send(OutputData& data)
{
    LOG(LEVEL_DEBUG) << "Enviando posições";

    Dados_Simulador dados;

    for (unsigned int i = 0; i < 3; i++)
    {
        //team

        dados.v_pos_robo[i][0] = data.team_pos[i].x - 85.;

        dados.v_pos_robo[i][1] = data.team_pos[i].y - 65.;

        dados.v_pos_robo[i][3] = data.team_orientation[i];

        dados.v_pos_robo[i + 3][0] = data.opponent_pos[i].x - 85.;

        dados.v_pos_robo[i + 3][1] = data.opponent_pos[i].y - 65.;

        dados.v_pos_robo[i + 3][3] = data.opponent_orientation[i];

    }

    //ball

    dados.v_pos_bola[0] = data.ball_pos.x - 85.;

    dados.v_pos_bola[1] = data.ball_pos.y - 65.;

    _com_write->escrever_var<Dados_Simulador>("Dados_Simulador", dados);

}
