/*
    @file Dados.h

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
#ifndef DADOS_H
#define DADOS_H

class Dados_Simulador
{
public:
	Dados_Simulador ();
	double v_pos_robo[6][3];
	double v_pos_bola[2];
};
class Dados_Estrategia
{
public:
	Dados_Estrategia ();
	double f_vel_linear[6];
	double f_vel_angular[6];
	double f_vel_roda_dir[6];
	double f_vel_roda_esq[6];
};

#endif // !DADOS_H
