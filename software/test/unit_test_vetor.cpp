/*
    @file unit_test_vetor.cpp

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
#include <Vetor.h>
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE (unit_test_compartilhado)
BOOST_AUTO_TEST_CASE (unit_test_Vetor)
{
	Vetor v1 (2, 2), v2 (2, 2), v3 (2, 2);
	Vetor v4 (3), v5 (3), v6 (3);
	double k1 = 10., k2 = 1.5, k3 = 3.0;
	//-- Espaço Vetorial.
	// Axiomas.
	//	A1
	BOOST_CHECK (v1 + v2 == v2 + v1);
	//	A2
	BOOST_CHECK ( (v1 + v2) + v3 == v1 + (v2 + v3));
	//	A3
	BOOST_CHECK ( v1 + v1.nulo () == v1);
	//	A4
	BOOST_CHECK ( v1 + (-1 * v1) == v1.nulo ());
	//	A5
	BOOST_CHECK (k1 * (v1 + v2) == k1 * v1 + k1 * v2);
	//	A6
	BOOST_CHECK ((k1 + k2) * v1 == k1 * v1 + k2 * v1);
	//	A7
	BOOST_CHECK ((k1 * k2) * v1 == k1 * (k2 * v1));
	//	A8
	BOOST_CHECK (v1.identidade () * v1 == v1);
	//-- Testando operações especiais.
	//-- Produto escalar.
	// Axiomas.
	// A1
	BOOST_CHECK (v4.escalar (v5) > 0);
	BOOST_CHECK (v4.nulo ().escalar (v5) == 0);
	// A2
	BOOST_CHECK (v4.escalar (v5) == v5.escalar (v4));
	// A3
	BOOST_CHECK_CLOSE (((k1 * v4) + (k2 * v5)).escalar (v6), k1 * v4.escalar (v6) + k2 * v5.escalar (v6), 0.000001);
	// Excessões esperadas.
	BOOST_CHECK_THROW (v1.vetorial (v2), const char *);
	// Teste de mesa.
	BOOST_CHECK (v2_X ().escalar (v2_X ()) == 1);
	BOOST_CHECK (v2_X ().escalar (v2_Y ()) == 0);
	//-- Produto vetorial.
	// Excessões esperadas.
	BOOST_CHECK_THROW (v2_X ().vetorial (v2_X ()), const char *);
	// Teste de mesa.
	BOOST_CHECK (v3_X ().vetorial (v3_X ()) == v3_X ().nulo ());
	BOOST_CHECK (v3_X ().vetorial (v3_Y ()) == -1 * v3_Z ());
	// Axiomas
	// A1
	BOOST_CHECK (v4.vetorial (v5) == -1 * v5.vetorial (v4));
	// A2
	BOOST_CHECK (v4.vetorial (v5 + v6) == v4.vetorial (v5) + v4.vetorial (v6));
	// A3
	BOOST_CHECK ((k1 * v4).vetorial (v5) == v4.vetorial (k1 * v5));
	BOOST_CHECK ((k1 * v4).vetorial (v5) == k1 * v4.vetorial (v5));
	// A4
	BOOST_CHECK (v4.vetorial (v5.vetorial (v6)) + v5.vetorial (v6.vetorial (v4)) + v6.vetorial (v4.vetorial (v5)) == v4.nulo ());
	//-- Norma ou Módulo (R2 e R3).
	// Teste de mesa.
	BOOST_CHECK (v3_X ().modulo () == 1);
	BOOST_CHECK (v2_X ().modulo () == 1);
	// Axiomas
	// A1
	BOOST_CHECK (v4.modulo () > 0);
	// A2
	BOOST_CHECK ((k1 * v4).modulo () == abs (k1) * v4.modulo ());
	// A3
	BOOST_CHECK ((v4 + v5).modulo () <= v4.modulo () + v5.modulo ());
	// Vetor unitario
	BOOST_CHECK_CLOSE (v4.unitario ().modulo (), 1, 0.00001);
}
BOOST_AUTO_TEST_SUITE_END ()