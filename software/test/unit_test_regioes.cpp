/*
    @file unit_test_regioes.cpp

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
#include <Regioes.h>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE (unit_test_estrategia)
BOOST_AUTO_TEST_CASE (unit_test_Regioes)
{
	Regioes regioes;
	Vetor v1, v2, v3, v4;
	Vetor fora;
	Vetor centro_defesa, centro_defesa_dir, centro_defesa_esq;
	Vetor centro_inicio_dir, centro_inicio_esq, centro_inicio_gol;
	v1 (0) = 0.485;
	v2 (0) = 0.485;
	v3 (0) = -0.485;
	v4 (0) = -0.485;
	v1 (1) = 0.136;
	v2 (1) = -0.136;
	v3 (1) = 0.136;
	v4 (1) = -0.136;
	fora (0) = 10;
	fora (1) = 10;
	centro_defesa (0) = -0.600;
	centro_defesa (1) = 0.0;
	centro_defesa_dir (0) = -0.375;
	centro_defesa_dir (1) = -325;
	centro_defesa_esq (0) = -0.375;
	centro_defesa_esq (1) = 325;
	centro_inicio_dir (0) = -0.303;
	centro_inicio_dir (1) = -0.0475;
	centro_inicio_esq (0) = -0.336;
	centro_inicio_esq (1) = 0.0722;
	centro_inicio_gol (0) = -0.7125;
	centro_inicio_gol (1) = 0.0;
	BOOST_CHECK (r_ataque == regioes.regiao_de (v1));
	BOOST_CHECK (r_defesa == regioes.regiao_de (v3));
	BOOST_CHECK (r_sobra_dir == regioes.regiao_sobra_de (v2));
	BOOST_CHECK (r_sobra_esq == regioes.regiao_sobra_de (v1));
	BOOST_CHECK (r_defesa_esq == regioes.regiao_defesa_de (v3));
	BOOST_CHECK (r_defesa_dir == regioes.regiao_defesa_de (v4));
	BOOST_CHECK (r_defesa_centro == regioes.regiao_defesa_de (centro_defesa));
	BOOST_CHECK (r_suporte_esq == regioes.regiao_suporte_de (v1));
	BOOST_CHECK (r_suporte_dir == regioes.regiao_suporte_de (v2));
	BOOST_CHECK (r_inicio_dir == regioes.regiao_inicio_de (centro_inicio_dir));
	BOOST_CHECK (r_inicio_esq == regioes.regiao_inicio_de (centro_inicio_esq));
	BOOST_CHECK (r_inicio_gol == regioes.regiao_inicio_de (centro_inicio_gol));
	BOOST_CHECK (r_fora_campo == regioes.regiao_de (fora));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_ataque, v1));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_defesa, v3));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_sobra_dir, v2));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_sobra_esq, v1));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_defesa_dir, v4));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_defesa_esq, v3));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_defesa_centro, centro_defesa));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_suporte_esq, v1));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_suporte_dir, v2));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_inicio_dir, centro_inicio_dir));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_inicio_esq, centro_inicio_esq));
	BOOST_CHECK (true == regioes.vetor_pertence_regiao (r_inicio_gol, centro_inicio_gol));
	BOOST_CHECK (true != regioes.vetor_pertence_regiao (r_campo, fora));
	/*
	mais_proximo_de (Regiao r, Vetor v);
	centro (Regiao r);
	*/
}
BOOST_AUTO_TEST_SUITE_END ()