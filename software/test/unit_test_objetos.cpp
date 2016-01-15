/*
    @file unit_test_objetos.cpp

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
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE (unit_test_estrategia)
BOOST_AUTO_TEST_CASE (unit_test_Objetos)
{
	Objeto obj;
	Vetor v1 (2), v2 (2);
	obj.f_raio = 1.5;
	obj.v_pos = v3_Y ();
	v1 = -1 * v3_X ();
	v2 = v3_X ();
	BOOST_CHECK_CLOSE (distancia_ponto_reta (v1, v2, obj.v_pos), 1., 0.00001);
	BOOST_CHECK (intercepta (v1, v2, obj) == true);
}
BOOST_AUTO_TEST_SUITE_END ()
