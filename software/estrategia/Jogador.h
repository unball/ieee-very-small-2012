/*
    @file Jogador.h

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
#ifndef JOGADOR_H
#define JOGADOR_H

#include <Estados_jogador.h>
#include <Robo.h>
#include <Regioes.h>
#include <Vetor.h>

class Jogador;
class Equipe;
class Campo;

class Jogador : public Robo
{
public:
	Jogador ();
	~Jogador ();
	//-- Inicialização
	void Init (Equipe * e);
	//-- Execução da rotina.
	void roda ();

	//-- Acesso às variáveis.
	Regiao regiao_base ();
	Campo * campo ();
	Equipe * equipe ();
	enum_Estado estado_atual ();
	enum_Estado estado_anterior ();

	//-- Modificação das variáveis.
	void setRegiao_base (Regiao r);
	void setEquipe (Equipe * e);
	void troca_estado (enum_Estado);
	void troca_regiao_base (Regiao);

	// Perguntas do tipo o que.
	Vetor3 normal_parede_proxima ();

	// perguntas do tipo sim/não.
	bool dentro_campo_visao (Vetor3 alvo);
	bool estou_em (Vetor3 v);
	bool perto_demais_parede ();
	bool controla_bola ();
	bool pode_passar ();
	bool pode_chutar_gol ();

	// controle
	bool alinha (Vetor3 v);
	bool olhe_para (Vetor3 v);
	bool espera ();
	bool mover_ate (Vetor3 v);

	

private:
	bool seguir_caminho;
	Equipe * e_Equipe;
	Campo * c_campo;

	Regiao r_base;

	const static int num_estados = 10;
	Estado * e_estado[num_estados];
	enum_Estado _estado_atual;
	enum_Estado _estado_anterior;
};

#endif // !JOGADOR_H
