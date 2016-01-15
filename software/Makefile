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

SUBDIRS = shared estrategia master simulation vision
CXX = g++
LIBBOOST = libboost-dev libboost-thread-dev libboost-system-dev libboost-filesystem-dev libboost-date-time-dev libboost-regex-dev libboost-program-options-dev
OTHERLIBS = libtool libsm-dev libglui-dev libcurses-ocaml-dev
LIBODE = libode-dev
LIBOPENCV = libopencv-dev
ODE = ode-0.12
OPENCV = opencv-2.4.6.1

TOOLS = build-essential synaptic pkg-config qtcreator $(CXX)
CAMERA = 
CLEANDIRS = $(SUBDIRS:%=clean-%)

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	@$(MAKE) -C $@

.PHONY: print
print:
	@echo Subdirs: $(SUBDIRS)
	@echo Cleandirs: $(CLEANDIRS)

.PHONY: subdirs $(CLEANDIRS)
clean: $(CLEANDIRS)
$(CLEANDIRS): 
	@$(MAKE) -C $(@:clean-%=%) clean

.PHONY: install
install:
	sudo apt-get install $(TOOLS) $(LIBBOOST) $(LIBODE) $(LIBOPENCV) $(OTHERLIBS)

.PHONY: install-ode
install-ode:
	tar -jxvf $(ODE).tar.bz2; \
	cd $(ODE)/; \
	./configure; \
	make; \
	make install;
.PHONY: remove-ode
remove-ode:
	-rm -r ./$(ODE)/;

.PHONY: install-opencv
install-opencv:
	sudo apt-get install libgtk2.0-dev pkg-config; \
	tar -zxvf $(OPENCV).tar.gz; \
	cd $(OPENCV)/; \
	mkdir debug; \
	cd debug/; \
	cmake ..; \
	make; \
	make install;

.PHONY: remove-opencv
remove-opencv:
	cd $(OPENCV)/debug/; \
	make uninstall;

