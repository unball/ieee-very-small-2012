/*
    @file unit_test_equipe.cpp

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
#include <Equipe.h>
#include <Campo.h>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE (unit_test_estrategia)
BOOST_AUTO_TEST_CASE (unit_test_equipe)
{
	Campo campo;
	Equipe * eq1, *eq2;
	eq1 = campo.e_verde ();
	eq2 = campo.e_roxo ();
	Vetor v;
	v (0) = 1.5 / 2.;
	v (1) = 0;
	v (2) = 0;
	Objeto alvo;
	alvo.v_pos = v;
	BOOST_CHECK (eq1->campo () == &campo);
	BOOST_CHECK_CLOSE (eq1->g_Amigo ()->v_pos (0), -v (0), 0.00001);
	BOOST_CHECK_CLOSE (eq1->g_Amigo ()->v_pos (1), -v (1), 0.00001);
	BOOST_CHECK_CLOSE (eq1->g_Amigo ()->v_pos (2), -v (2), 0.00001);
	BOOST_CHECK_CLOSE (eq1->g_Adversario ()->v_pos (0), v (0), 0.00001);
	BOOST_CHECK_CLOSE (eq1->g_Adversario ()->v_pos (1), v (1), 0.00001);
	BOOST_CHECK_CLOSE (eq1->g_Adversario ()->v_pos (2), v (2), 0.00001);
	BOOST_CHECK (eq1->cor () == Equipe::verde);
	BOOST_CHECK (eq1->regiao_de (&alvo) == r_ataque);
	BOOST_CHECK (eq1->regiao_sobra_de (&alvo) == r_campo);
	BOOST_CHECK (eq1->regiao_defesa_de (&alvo) == r_campo);
	BOOST_CHECK (eq1->regiao_suporte_de (&alvo) == r_campo);
	BOOST_CHECK (eq1->regiao_inicio_de (&alvo) == r_campo);
	/*Equipe (Campo * c, Jogador * j, cor_Equipe cor);

	Campo * campo ();

	Jogador * aliado_mais_proximo_bola ();
	Jogador * aliado_com_controle_da_bola ();
	Jogador * Adversario_com_controle_da_bola ();
	Jogador * receptor ();
	Jogador * suporte ();
	Jogador * principal ();
	Jogador * goleiro ();

	Gol * g_Adversario ();
	Gol * g_Amigo ();

	Vetor melhor_ponto_suporte ();
	Vetor melhor_ponto_sobra ();
	Vetor melhor_alvo_gol ();

	cor_Equipe cor();

	Direcao direcao_de (Objeto * o);

	Regiao regiao_de (Objeto * o);
	Regiao regiao_sobra_de (Objeto * o);
	Regiao regiao_defesa_de (Objeto * o);
	Regiao regiao_suporte_de (Objeto * o);
	Regiao regiao_inicio_de (Objeto * o);

	void roda();
	void troca_estado (Estado * e);

	// Perguntas
	bool bola_perto_gol ();
	bool Equipe_adversario_controla_bola ();
	bool Equipe_controla_bola ();
	bool Equipe_posicoes_iniciais ();
	*/
}
BOOST_AUTO_TEST_SUITE_END ()