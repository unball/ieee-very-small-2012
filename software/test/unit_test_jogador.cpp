/*
    @file unit_test_jogador.cpp

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
#include <Jogador.h>
#include <Regioes.h>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE (unit_test_estrategia)
BOOST_AUTO_TEST_CASE (unit_test_Jogador)
{
	Campo campo;
	Jogador * jogador[2], ** jog;
	jog = campo.jogador ();
	jogador[0] = jog[0];
	jogador[1] = jog[1];
	Equipe * eq1 = campo.e_verde ();
	Equipe * eq2 = campo.e_roxo ();
	//-- Funções base de acesso.
	Vetor v;
	jogador[0]->v_pos = v;
	jogador[1]->v_pos = v.unitario ();
	BOOST_CHECK (jogador[0]->v_pos == v);
	BOOST_CHECK (jogador[1]->v_pos == v.unitario ());
	jogador[0]->troca_regiao_base (r_campo);
	BOOST_CHECK (jogador[0]->regiao_base () == r_campo);
	BOOST_CHECK (jogador[0]->equipe () == eq1);
	BOOST_CHECK (jogador[0]->campo () == &campo);
	//-- Pertinentes à tomada de decisão.
	jogador[0]->v_pos = v3_Y ();
	jogador[0]->v_normal = v3_Y ();
	BOOST_CHECK (jogador[0]->normal_parede_proxima () == -1 * v3_Y ());
	campo.bola ()->v_pos = 0.8 * v3_Y ();
	BOOST_CHECK (jogador[0]->dentro_campo_visao (campo.bola ()->v_pos) == false);
	campo.bola ()->v_pos = 1.2 * v3_Y ();
	BOOST_CHECK (jogador[0]->dentro_campo_visao (campo.bola ()->v_pos) == true);
	BOOST_CHECK (jogador[0]->estou_em (jogador[0]->v_pos) == true);
	BOOST_CHECK (jogador[0]->estou_em (campo.bola ()->v_pos) == false);
	jogador[0]->v_pos = campo.parede ()[0].v_pos;
	jogador[0]->v_normal = -1 * campo.parede ()[0].v_normal;
	BOOST_CHECK (jogador[0]->perto_demais_parede () == true);
	jogador[0]->v_pos = Vetor3 ().nulo ();
	jogador[0]->v_normal = campo.parede ()[0].v_normal;
	BOOST_CHECK (jogador[0]->perto_demais_parede () == false);
	campo.bola ()->v_pos = Vetor3 ().nulo ();
	jogador[0]->v_pos = campo.bola ()->v_pos + 0.01 * v3_X ();
	jogador[0]->v_normal = (campo.bola ()->v_pos - jogador[0]->v_pos).unitario ();
	BOOST_CHECK (jogador[0]->controla_bola () == false);
	jogador[0]->v_pos = campo.bola ()->v_pos - 0.01 * v3_X ();
	jogador[0]->v_normal = (campo.bola ()->v_pos - jogador[0]->v_pos).unitario ();
	BOOST_CHECK (jogador[0]->controla_bola () == true);
	//-- Funções de controle
	jogador[0]->espera ();
	BOOST_CHECK (jogador[0]->f_vel_linear == 0 && jogador[0]->f_vel_angular == 0);
	/*
	void roda ();
	void troca_estado (enum_Estado);
	void troca_regiao_base (Regiao);

	Regiao regiao_base ();
	Campo * campo ();
	Equipe * equipe ();

	Vetor normal_parede_proxima ();

	// controle
	bool alinha (Vetor v);
	bool olhe_para (Vetor v);
	bool espera ();
	bool mover_ate (Vetor v);
	bool chutar_para (Vetor v);	// precisa refinar

	// perguntas
	bool dentro_campo_visao (Objeto * observador, Vetor alvo);
	bool estou_em (Vetor v);
	bool perto_demais_parede ();
	bool rota_colisao_parede ();
	bool controla_bola ();
	bool pode_passar ();
	bool pode_chutar_gol ();
	*/
}
BOOST_AUTO_TEST_SUITE_END ()