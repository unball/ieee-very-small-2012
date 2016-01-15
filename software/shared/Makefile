#
#    @file Makefile
#
#    @contributor	William Batista Aguiar Motta	@email yosoyninja@gmail.com
#
#    @attention Copyright (C) 2013
#    @attention UnBall Robot Soccer Team
#
#       Este programa é um software livre; você pode redistribui-lo e/ou
#    modifica-lo dentro dos termos da Licença Pública Geral GNU como
#    publicada pela Fundação do Software Livre (FSF); na versão 2 da
#    Licença, ou (na sua opnião) qualquer versão.
#
#    Este programa é distribuido na esperança que possa ser  util,
#    mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUAÇÂO a qualquer
#    MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
#    Licença Pública Geral GNU para maiores detalhes.
#
#    Você deve ter recebido uma cópia da Licença Pública Geral GNU
#    junto com este programa, se não, escreva para a Fundação do Software
#    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
#
CXX = g++
CPPFLAGS = -Wall -g -std=c++0x

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
HEADERS = $(patsubst %.cpp, %.h, $(SOURCES))

.PHONY: all
all: $(OBJECTS) 

.cpp.o: $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $< -I.

.PHONY: print
print:
	@echo Objects: $(OBJECTS)
	@echo Headers: $(HEADERS)

.PHONY: clean
clean:
	-rm -f *.o
