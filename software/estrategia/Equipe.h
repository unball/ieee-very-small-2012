/*
    @file Equipe.h

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
#ifndef EQUIPE_H
#define EQUIPE_H
#include <list>
#include <Regioes.h>
#include <Vetor.h>
#include <Objetos.h>
#include <Funcoes_gerais.h>

class Objeto;
class Jogador;
class Equipe;
class Campo;
class Gol;
class Estado;

class Equipe
{
public:
	enum cor_Equipe {verde, roxo}; // verde esquerdo, roxo direito.
	const static int NUM_ALVOS_GOL = 10;

	Equipe ();
	//-- Inicialização
	void Init (Campo * c, Jogador * j[], cor_Equipe cor);
	//-- Acesso às variáveis.
	Campo * campo ();
	Gol * g_Adversario ();
	Gol * g_Amigo ();
	cor_Equipe cor ();
	//-- Modificação das variáveis.
	void setcampo (Campo * c);
	void setG_Adversario (Gol * g);
	void setG_Amigo (Gol * g);
	void setCor (cor_Equipe c);
	//-- Perguntas do tipo quem.
	Jogador * aliado_mais_proximo_bola ();
	Jogador * aliado_com_controle_da_bola ();
	Jogador * aliado_candidato_goleiro ();
	Jogador * Adversario_com_controle_da_bola ();
	Jogador * receptor ();
	Jogador * suporte ();
	Jogador * principal ();
	Jogador * goleiro ();

	Vetor3 melhor_ponto_suporte ();
	Vetor3 melhor_ponto_sobra ();
	Vetor3 melhor_alvo_gol ();
	Vetor3 aparar_area_util (Vetor3 v);

	Direcao direcao_de (Objeto * o);

	Regioes regioes;
	Regiao regiao_de (Objeto * o);
	Regiao regiao_sobra_de (Objeto * o);
	Regiao regiao_defesa_de (Objeto * o);
	Regiao regiao_suporte_de (Objeto * o);
	Regiao regiao_inicio_de (Objeto * o);
	Vetor3 centro (Regiao r);

	void roda ();
	void troca_estado (Estado * e);

	// Perguntas do tipo sim/não.
	bool bola_perto_gol ();
	bool Equipe_adversario_controla_bola ();
	bool Equipe_controla_bola ();
	bool Equipe_posicoes_iniciais ();

private:
	Campo * c_campo;
	Gol * g_amigo;
	Gol * g_adversario;
	Jogador * j_jogador[3];
	cor_Equipe _cor;
	Estado * e_estado;

	Vetor3 v_alvo_gol[NUM_ALVOS_GOL];

	Jogador * j_receptor;
	Jogador * j_suporte;
	Jogador * j_principal;
	Jogador * j_goleiro;

};

#endif // !EQUIPE_H
