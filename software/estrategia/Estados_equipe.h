/*
    @file Estados_equipe.h

    @autor William Batista Aguiar Motta
    @email yosoyninja@gmail.com

    @attention Copyright (C) 2013
    @attention UnBall Robot Soccer Team

       Este programa � um software livre; voc� pode redistribui-lo e/ou
    modifica-lo dentro dos termos da Licen�a P�blica Geral GNU como
    publicada pela Funda��o do Software Livre (FSF); na vers�o 2 da
    Licen�a, ou (na sua opni�o) qualquer vers�o.

    Este programa � distribuido na esperan�a que possa ser  util,
    mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUA��O a qualquer
    MERCADO ou APLICA��O EM PARTICULAR. Veja a
    Licen�a P�blica Geral GNU para maiores detalhes.

    Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU
    junto com este programa, se n�o, escreva para a Funda��o do Software
    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/
#ifndef ESTADOS_EQUIPE_H
#define ESTADOS_EQUIPE_H

#include <Maquina_de_estados.h>

class Campo;
class Equipe;
class Jogador;


class Defendendo : public Estado
{
private:
	Campo * campo;
	Equipe * equipe;

	Jogador * j_gol;
	Jogador * j_dir;
	Jogador * j_esq;
public:
	Defendendo (Equipe *);
	~Defendendo () {}
	void roda ();
	void entra ();
	void sai ();
};
class Atacando : public Estado
{
private:
	Campo * campo;
	Equipe * equipe;
public:
	~Atacando () {}
	Atacando (Equipe *);
	void roda ();
	void entra ();
	void sai ();
};
class Preparando_para_iniciar_jogo : public Estado
{
private:
	Campo * campo;
	Equipe * equipe;
public:
	~Preparando_para_iniciar_jogo () {}
	Preparando_para_iniciar_jogo (Equipe *);
	void roda ();
	void entra ();
	void sai ();
};

class Preparando_para_Penalty : public Estado
{
private:
	Campo * campo;
	Equipe * equipe;
public:
	~Preparando_para_Penalty () {}
	Preparando_para_Penalty (Equipe *);
	void roda ();
	void entra ();
	void sai ();
};
#endif // ESTADOS_EQUIPE_H
