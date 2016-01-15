/*
    @file unit_test_Config.cpp

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

#include <stdio.h>
#include <iostream>

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <Config.h>
BOOST_AUTO_TEST_SUITE (unit_test_shared)
BOOST_AUTO_TEST_CASE(unit_test_config)
{
    // To see errors in the program, change the equality to a false number
	Config teste("teste_unit.txt");

	BOOST_CHECK(teste.name() == "teste_unit.txt");
	
	BOOST_CHECK(teste.read("teste_unit2.txt") == false);
	BOOST_CHECK(teste.parseLine ("") == false);
	BOOST_CHECK(teste.parseLine("#teste") == false);
    // Line 19 will show errors to check what happens when there is a space before #
	BOOST_CHECK(teste.parseLine(" #teste") == false); 
	BOOST_CHECK(teste.parseLine("Dummy teste1 teste2 teste3") == true);
	BOOST_CHECK(teste.parseLine("Teste teste") == true);
	
	BOOST_CHECK(teste.getSize("Dummy") == 3);
	BOOST_CHECK(teste.get("Dummy") == "teste1");
	BOOST_CHECK(teste.get("Dummy",1) == "teste2");
	BOOST_CHECK(teste.get("Dummy",2) == "teste3");
	
	BOOST_CHECK(teste.getSize("Dummyzao") == 2);
	BOOST_CHECK(teste.get("Dummyzao") == "resp1");
	BOOST_CHECK(teste.get("Dummyzao",1) == "resp2");

	BOOST_CHECK(teste.getSize("line") == 2);
	BOOST_CHECK(teste.get("line") == "21");
	BOOST_CHECK(teste.get("line",1) == "t2e");

	BOOST_CHECK(teste.getSize("teeeest") == 3);
	BOOST_CHECK(teste.get("teeeest") == "r");
	BOOST_CHECK(teste.get("teeeest",1) == "read1");
	BOOST_CHECK(teste.get("teeeest",2) == "read2");

	BOOST_CHECK(teste.getSize("jumP") == 3);
	BOOST_CHECK(teste.get("jumP") == "1");
	BOOST_CHECK(teste.get("jumP",1) == "1");
}
BOOST_AUTO_TEST_SUITE_END ()