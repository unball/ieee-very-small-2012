/*
    @file Estados_jogador.h

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
#ifndef ESTADOS_JOGADOR_H
#define ESTADOS_JOGADOR_H

#include <Maquina_de_estados.h>
#include <Vetor.h>

class Objeto;
class Jogador;
class Equipe;
class Campo;

enum enum_Estado
{
	e_Sobra, e_Suporte_ataque, e_Fazer_gol,
	e_Passar, e_Interceptar_bola, e_Esperar,
	e_Fechar_gol,
	e_Voltar_base, e_Penalty
};

class Estado_jogador : public Estado
{
public:
	~Estado_jogador () {}
	Estado_jogador (Jogador * jogador);
protected:
	Campo * c_campo;
	Equipe * e_Equipe;
	Jogador * jogador;
};
class Sobra : public Estado_jogador
{
public:
	Sobra (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();
};
class Suporte_ataque : public Estado_jogador
{
public:
	Suporte_ataque (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();

};
class Fazer_gol : public Estado_jogador
{
public:
	Fazer_gol (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();
};
class Passar : public Estado_jogador
{
public:
	Passar (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();
};
class Interceptar_bola : public Estado_jogador
{
public:
	Interceptar_bola (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();
private:
	bool b_alvo_frente_alcancado;
	Objeto * b_bola;
	Vetor3 v_alvo;
};

class Esperar : public Estado_jogador
{
public:
	Esperar (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();
};
class Fechar_gol : public Estado_jogador
{
public:
	Fechar_gol (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();
private:
	double x;
	double y_min, y_max;
};
class Voltar_base : public Estado_jogador
{
public:
	Voltar_base (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();
};
class Penalty : public Estado_jogador
{
public:
	Penalty (Jogador * jogador);
	void entra ();
	void roda ();
	void sai ();

private:
	int nChute; // Qual o tipo de chute será dado. Aux do Switch Case.
	Vetor3 p;	// Vetor para posição.
	double	x;  // Posição x.
	double y;	// posição y.
};
#endif // !ESTADOS_JOGADOR_H
