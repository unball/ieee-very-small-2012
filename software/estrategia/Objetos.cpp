/*
    @file Objetos.cpp

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
#include <Objetos.h>
#include <iostream>
Objeto::Objeto () : _id (0)
{
	t = Temporizador (1);
	v_pos = Vetor3 ().nulo ();
	v_pos_anterior = Vetor3 ().nulo ();
	v_vel_linear = Vetor3 ().nulo ();
	v_vel_angular = Vetor3 ().nulo ();
	v_normal = v3_X ();
	v_normal_anterior = Vetor3().nulo();
	v_forca_res = Vetor3().nulo();
	f_raio = 0.010 / 2.;
	f_vel_linear = 0;
	f_vel_angular = 0;
	massa = 1;
	d_movimento = d_indo;
}
void Objeto::roda ()
{
	v_vel_linear = v_pos - v_pos_anterior;
	v_vel_angular = acosf (v_normal.escalar(v_normal_anterior)) * Vetor3().Z();
	v_pos_anterior = v_pos;
	v_normal_anterior = v_normal;
}
double distancia_ponto_reta (const Vetor3 & r1, const Vetor3 & r2, const Vetor3 & p)
{
	// Só fazendo o desenho para entender essa aqui.
	Vetor3 d, a, b, b_;
	double alfa;
	a = p - r1;
	b = r2 - r1;
	alfa = a.escalar (b) / b.modulo ();
	b_ = alfa * b.unitario ();
	d = a - b_;
	return d.modulo ();
}
bool intercepta (const Vetor3 & p1, const Vetor3 & p2, const Objeto & o)
{
	if (distancia_ponto_reta (p1, p2, o.v_pos) <= o.f_raio)
	{
		return true;
	}
	else
	{
		return false;
	}
}
