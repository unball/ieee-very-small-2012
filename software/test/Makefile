#
#    @file Makefile
#
#    @autor William Batista Aguiar Motta
#    @email yosoyninja@gmail.com
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
CPPFLAGS = -Wall -g -std=c++11

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
EXECUTABLE = unit_test

SHARED_OBJ = $(wildcard ../shared/*.o) $(wildcard ../estrategia/*.o)
BOOST_LIBS = -lboost_thread -lboost_system -lboost_filesystem -lboost_regex
LIBS = -lSM -lICE -lGLU -lGL -lm -lpthread -lrt

INC = -I. -I../shared/ -I../estrategia/
DEF =

.PHONY: all
all: $(EXECUTABLE)

# Create object files
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(INC) $(DEF) -c $<

# Create executable file
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CPPFLAGS) $(INC) $(DEF) $(SOURCES) $(ODE_LIBS) $(SHARED_OBJ) $(LIBS) $(BOOST_LIBS) -o $(EXECUTABLE)
	
.PHONY: print
print:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Executable: $(EXECUTABLE)

.PHONY: clean
clean:
	-rm -f $(EXECUTABLE) *.o
