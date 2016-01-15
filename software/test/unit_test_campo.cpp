/*
    @file unit_test_campo.cpp

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
#include <Config.h>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE (unit_test_estrategia)
BOOST_AUTO_TEST_CASE (unit_test_Campo)
{
	ProcessLogger::setPrintLevel (LEVEL_ERROR);
	Config config ("constants.config");
	//-- Checando inicialização do gol.
	Gol gol (v3_X (), -1 * v3_X ());
	BOOST_CHECK (gol.poste_dir () == v3_X ());
	BOOST_CHECK (gol.poste_esq () == -1 * v3_X ());
	BOOST_CHECK (gol.v_normal == v3_Y ());
	//-- Checando inicialização do campo.
	Campo campo;
	BOOST_CHECK_CLOSE (campo.largura (), atof (config.get ("FIELD_WIDTH").c_str ()), 0.000001);
	BOOST_CHECK_CLOSE (campo.comprimento (), atof (config.get ("FIELD_LENGTH").c_str ()), 0.000001);
	BOOST_CHECK (campo.bola () != 0);
	BOOST_CHECK (campo.e_roxo () != 0);
	BOOST_CHECK (campo.e_verde () != 0);
	BOOST_CHECK (campo.g_verde () != 0);
	BOOST_CHECK (campo.g_roxo () != 0);
	// Checar demais propriedades com auxilio do autocad.
	/*
	Objeto parede[4];
	*/
}
BOOST_AUTO_TEST_SUITE_END ()