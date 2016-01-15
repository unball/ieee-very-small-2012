/*
    @file Temporizador.cpp

    @autor William Batista Aguiar Motta
    @email yosoyninja@gmail.com

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
#include <Temporizador.h>

Temporizador::Temporizador (double dt)
{
	Dt = 1000 * dt;
	Hora_zero = boost::posix_time::microsec_clock::local_time ();
}
void Temporizador::reset ()
{
	Hora_zero = boost::posix_time::microsec_clock::local_time ();
}
bool Temporizador::zerou ()
{
	boost::posix_time::ptime Hora_atual;
	Hora_atual = boost::posix_time::microsec_clock::local_time ();
	if ((Hora_atual - Hora_zero).total_milliseconds () > Dt)
	{
		return true;
	}
	else
	{
		return false;
	}
}
