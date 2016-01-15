/*
    @file communication.h

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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "tracker.h"
//#include "Communicator.h"
#include <Comunicador.h>
#include <Dados.h>
#include "output_data.h"

class Communication
{
public:
    Communication();
    ~Communication();

    void Send(OutputData& data);
protected:
private:
    void Init();
    //Communicator* com_write;
    Comunicador* _com_write;
};

#endif // COMMUNICATION_H
