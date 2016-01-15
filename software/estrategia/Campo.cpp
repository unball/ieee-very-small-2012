/*
    @file Campo.cpp

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
#include <Campo.h>
#include <Vetor.h>
#include <Regioes.h>
#include <Equipe.h>
#include <Jogador.h>
#include <Config.h>

Gol::Gol ()
{
	v_dir = Vetor3 ().nulo ();
	v_esq = Vetor3 ().nulo ();
	v_meio = Vetor3 ().nulo ();
}
Gol::Gol (Vetor3 v_dir, Vetor3 v_esq) : v_dir (v_dir), v_esq (v_esq)
{
	Config config ("constants.config");
	Vetor3 v_temp;
	v_meio = 1. / 2. * (v_dir + v_esq);
	v_pos = v_meio;
	v_temp = (v_esq - v_dir).vetorial (v3_Z ());
	v_normal = v_temp.unitario ();
	_comprimento = (v_dir - v_esq).modulo ();
	_largura = atof (config.get ("GOAL_WIDTH").c_str ());
}
double Gol::largura ()
{
	return _largura;
}
double Gol::comprimento ()
{
	return _comprimento;
}
Vetor3 Gol::poste_dir ()
{
	return v_dir;
}
Vetor3 Gol::poste_esq ()
{
	return v_esq;
}
Campo::Campo ()
{
	Config config ("constants.config");
	//-- Variáveis do campo.
	double f_gol_comprimento = atof (config.get ("GOAL_LENGTH").c_str ());
	f_largura = atof (config.get ("FIELD_WIDTH").c_str ());
	f_comprimento = atof (config.get ("FIELD_LENGTH").c_str ());
	//-- Gols
	Vetor3 v_dir, v_esq;
	v_dir (0) = f_comprimento / 2.;
	v_esq (0) = f_comprimento / 2.;
	v_dir (1) = - f_gol_comprimento / 2.;
	v_esq (1) = f_gol_comprimento / 2.;
	g_Roxo = Gol (v_dir, v_esq);
	v_dir (0) = -f_comprimento / 2.;
	v_esq (0) = -f_comprimento / 2.;
	v_dir (1) = f_gol_comprimento / 2.;
	v_esq (1) = - f_gol_comprimento / 2.;
	g_Verde = Gol (v_dir, v_esq);
	//-- Paredes
	Vetor3 pos;
	pos (0) = 0;
	pos (1) = f_largura / 2.;
	o_parede[0].v_pos = pos;
	o_parede[0].v_normal = -1 * v3_Y ();
	pos (0) = -f_comprimento / 2.;
	pos (1) = 0;
	o_parede[1].v_pos = pos;
	o_parede[1].v_normal = v3_X ();
	pos (0) = 0;
	pos (1) = -f_largura / 2.;
	o_parede[2].v_pos = pos;
	o_parede[2].v_normal = v3_Y ();
	pos (0) = f_comprimento / 2.;
	pos (1) = 0;
	o_parede[3].v_pos = pos;
	o_parede[3].v_normal = -1 * v3_X ();
	//-- Criação dos elementos presentes no campo.
	o_Bola = new Objeto;
	e_Roxo = new Equipe;
	e_Verde = new Equipe;
	for (int i = 0; i < 6; i++)
	{
		j_jogador[i] = new Jogador[6];
	}
	//-- Inicialização das equipes e jogadores.
	e_Roxo->Init (this, j_jogador, Equipe::roxo);
	e_Verde->Init (this, j_jogador, Equipe::verde);
}
Campo::~Campo ()
{
	delete o_Bola;
	delete e_Roxo;
	delete e_Verde;
	for (int i = 0; i < 6; i++)
	{
		delete j_jogador[i];
	}
}
double Campo::largura ()
{
	return f_largura;
}
double Campo::comprimento ()
{
	return f_comprimento;
}
Objeto * Campo::bola ()
{
	return o_Bola;
}
Gol * Campo::g_roxo ()
{
	return &g_Roxo;
}
Gol * Campo::g_verde ()
{
	return &g_Verde;
}
Equipe * Campo::e_roxo ()
{
	return e_Roxo;
}
Equipe * Campo::e_verde ()
{
	return e_Verde;
}
Jogador ** Campo::jogador ()
{
	return j_jogador;
}
Objeto * Campo::parede ()
{
	return &o_parede[0];
}