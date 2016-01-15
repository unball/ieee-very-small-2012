/*
    @file Estados_equipe.h

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
