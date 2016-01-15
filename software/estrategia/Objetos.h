/*
    @file Objetos.h

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
#ifndef OBJETOS_H
#define OBJETOS_H

#include <Vetor.h>
#include <Temporizador.h>
enum Direcao
{
	d_indo, d_vindo
};

class Objeto
{
public:
	int _id;
	Objeto ();
	~Objeto () {}
	void roda ();

	Vetor3 v_forca_res;
	double massa;
	Vetor3 v_pos;
	Vetor3 v_pos_anterior;
	Vetor3 v_vel_linear;
	Vetor3 v_vel_angular;
	Vetor3 v_normal;
	Vetor3 v_normal_anterior;
	double f_raio;
	double f_vel_linear;
	double f_vel_angular;
	Direcao d_movimento;
	Temporizador t;
	//double Tempo_para_percorrer (double dist);
};

bool intercepta (const Vetor3 & p1, const Vetor3 & p2, const Objeto & o);
double distancia_ponto_reta (const Vetor3 & r1, const Vetor3 & r2, const Vetor3 & p);

#endif // OBJETOS_H
