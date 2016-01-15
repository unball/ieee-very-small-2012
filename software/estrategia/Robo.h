/*
    @file Robo.h

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
#ifndef ROBO_H
#define ROBO_H

#include <Objetos.h>
#include <Funcoes_gerais.h>
const double MAX_W = 15;
const double MIN_W = 1;
const double MAX_V = 15;
const double MIN_V = 1;

class Robo : public Objeto {
public:
	Robo();
	~Robo() {}
	void aplica_forca (Vetor3 forca);
	void forca_para_vel_rodas();
	void vel_linear_angular_para_vel_rodas();
	void vel_rodas_para_vel_linear_angular();
	void zerar_forcas();
	double vel_roda_dir;
	double vel_roda_esq;
};
#endif
