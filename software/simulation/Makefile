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
CPPFLAGS = -Wall -g

SOURCES = Simulation.cpp Ball.cpp RobotsSimulation.cpp
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
HEADERS = $(patsubst %.cpp, %.h, $(SOURCES))
EXECUTABLE = Simulation

SHARED_OBJ = $(wildcard ../shared/*.o)
BOOST_LIBS = -lboost_thread -lboost_system -lboost_filesystem -lboost_regex
ODE = ode-0.12
ODE_LIBS = ../$(ODE)/drawstuff/src/libdrawstuff.la ../$(ODE)/ode/src/libode.la
LIBS = -lSM -lICE -lGLU -lGL -lm -lpthread -lrt

ODE_FILES = $(wildcard ode*)

INC = -I. -I../$(ODE)/ode/demo -I../$(ODE)/ode/src  -I../$(ODE)/include -I../shared/
DEF = -DHAVE_CONFIG_H -DDRAWSTUFF_TEXTURE_PATH="\"../$(ODE)/drawstuff/textures\"" -DdTRIMESH_ENABLED -DdSINGLE

.PHONY: all
all: $(ODE_LIBS) $(SOURCES) $(EXECUTABLE)

# Create object files
%.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) $(INC) $(DEF) -c $< -MT $@ -MD -MP -MF .deps/$*.Tpo

# Create executable file
$(EXECUTABLE): $(OBJECTS)
	/bin/bash libtool --tag=CXX --mode=link $(CXX) -g -O2 -o $@ \
	$^ $(ODE_LIBS) $(SHARED_OBJ) $(BOOST_LIBS) $(LIBS)

.PHONY: print
print:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Headers: $(HEADERS)
	@echo Executable: $(EXECUTABLE)

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) *.o
