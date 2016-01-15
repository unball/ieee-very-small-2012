/*
    @file Funcoes_gerais.h

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

#ifndef FUNCOES_GERAIS_H
#define FUNCOES_GERAIS_H
#include <Vetor.h>
// Funções de apoio.
Vetor3 aparar_Vetor3 (const Vetor3 & quina_superior_esquerda, const Vetor3 & quina_inferior_direita, const Vetor3 & v);
double aparar_valor (double inicio, double fim, double valor);
double restringe_0_2PI (double);
double para_graus (double);
double para_rad (double);

/*
//	Perguntas
bool Equipe_esta_nas_posicoes_iniciais (Equipe * t);
bool Equipe_tem_controle_bola (Equipe * t);

bool jogador_tem_bola_dentro_raio_chute (Jogador *j);
bool jogador_tem_bola_dentro_raio_recebimento (Jogador *j);
bool jogador_tem_bola_dentro_raio_controle (Jogador *j);
bool jogador_tem_bola_dentro_raio_interceptação (Jogador *j);
bool jogador_tem_controle_bola (Jogador *j);
bool jogador_e_o_mais_perto_bola (Jogador *j);
bool jogador_pronto_para_chute (Jogador *j);
bool jogador_pronto_para_próximo_chute (Jogador *j);
bool jogador_esta_ameaçado (Jogador *j);
bool jogador_esta_na_posicao_inicial (Jogador *j);
bool jogador_esta_a_frente_do_atacante (Jogador *j);
bool jogador_esta_no_alvo_destino (Jogador *j);
bool jogador_esta_dentro_cone_bola (Jogador *j);
bool objeto_esta_dentro_cone_jogador (Objeto * o, Jogador *j);
bool goleiro_tem_posse_bola (Jogador * j);
bool goleiro_esta_longe_gol (Jogador * j);

	// pertence ao Equipe.
bool passe_totalmente_seguro ();
*/
#endif // FUNCOES_GERAIS_H
