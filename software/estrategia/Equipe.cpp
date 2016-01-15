/*
    @file Equipe.cpp

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
#include <Equipe.h>
#include <Jogador.h>
#include <Campo.h>
#include <Estados_equipe.h>

Equipe::Equipe ()
{
	c_campo = 0;
	g_amigo = 0;
	g_adversario = 0;
	j_jogador[0] = 0;
	j_jogador[1] = 0;
	j_jogador[2] = 0;
	_cor = Equipe::verde;
	e_estado = 0;
	j_receptor = 0;
	j_suporte = 0;
	j_principal = 0;
	j_goleiro = 0;
}
void Equipe::Init (Campo * campo, Jogador * jogadores[], cor_Equipe cor)
{
	c_campo = campo;
	_cor = cor;
	e_estado = 0;
	// inicialização dos gols.
	if (cor == verde)
	{
		g_adversario = campo->g_roxo ();
		g_amigo = campo->g_verde ();
	}
	else
	{
		g_adversario = campo->g_verde ();
		g_amigo = campo->g_roxo ();
	}
	// inicialização dos alvos.
	double k;
	Vetor3 v_d;
	v_d = g_Adversario ()->poste_dir () - g_Adversario ()->poste_esq ();
	k = v_d.modulo () / (NUM_ALVOS_GOL + 1);
	for (int i = 1; i < NUM_ALVOS_GOL + 1; i++)
	{
		v_alvo_gol[i - 1] = g_Adversario ()->poste_esq () + i * k * v_d;
	}
	// inicialização dos jogadores.
	j_jogador[0] = jogadores[cor * 3 + 0];
	j_jogador[1] = jogadores[cor * 3 + 1];
	j_jogador[2] = jogadores[cor * 3 + 2];
	j_jogador[0]->setEquipe (this);
	j_jogador[1]->setEquipe (this);
	j_jogador[2]->setEquipe (this);
	j_jogador[0]->_id = 0;
	j_jogador[1]->_id = 1;
	j_jogador[2]->_id = 2;
	j_principal = j_jogador[0];
	j_suporte = j_jogador[1];
	j_goleiro = j_jogador[2];
	j_receptor = 0;
	// inicialização do estado.
	troca_estado (new Defendendo (this));
}

void Equipe::roda ()
{
	std::list<Jogador *> j_disponiveis;
	j_disponiveis.push_back (j_jogador[0]);
	j_disponiveis.push_back (j_jogador[1]);
	j_disponiveis.push_back (j_jogador[2]);
	j_principal = this->aliado_mais_proximo_bola ();
	j_disponiveis.remove (j_principal);
	j_goleiro = this->aliado_candidato_goleiro ();
	j_disponiveis.remove (j_goleiro);
	j_suporte = j_disponiveis.front ();
	e_estado->roda ();
	j_jogador[0]->roda ();
	j_jogador[1]->roda ();
	j_jogador[2]->roda ();
}
void Equipe::troca_estado (Estado * e)
{
	if (e)
	{
		if (e_estado)
		{
			e_estado->sai ();
			delete e_estado;
		}
		e_estado = e;
		e_estado->entra ();
	}
}

Campo * Equipe::campo ()
{
	return c_campo;
}
Jogador * Equipe::receptor ()
{
	return j_receptor;
}
Jogador * Equipe::suporte ()
{
	return j_suporte;
}
Jogador * Equipe::principal ()
{
	return j_principal;
}
Jogador * Equipe::goleiro ()
{
	return j_goleiro;
}
Direcao Equipe::direcao_de (Objeto * o)
{
	if (g_Adversario ()->v_normal.escalar (o->v_vel_linear.unitario ()) < 0)
	{
		return d_indo;
	}
	else
	{
		return d_vindo;
	}
}
Jogador * Equipe::aliado_mais_proximo_bola ()
{
	double f_dist[3];
	double f_menor_dist;
	int n;
	f_dist[0] = (campo ()->bola ()->v_pos - j_jogador[0]->v_pos).modulo ();
	f_dist[1] = (campo ()->bola ()->v_pos - j_jogador[1]->v_pos).modulo ();
	f_dist[2] = (campo ()->bola ()->v_pos - j_jogador[2]->v_pos).modulo ();
	n = 0;
	f_menor_dist = f_dist[n];
	for (int i = 0; i < 3; i++)
	{
		if (f_dist[i] < f_menor_dist)
		{
			n = i;
			f_menor_dist = f_dist[i];
		}
	}
	return j_jogador[n];
}
Jogador * Equipe::aliado_candidato_goleiro ()
{
	list<Jogador *> j_candidatos;
	j_candidatos.push_back (j_jogador[0]);
	j_candidatos.push_back (j_jogador[1]);
	j_candidatos.push_back (j_jogador[2]);
	j_candidatos.remove (this->principal ());
	double f_menor_dist_gol, f_dist_gol;
	Jogador * escolhido = j_candidatos.front ();
	f_menor_dist_gol = (escolhido->v_pos - g_Amigo ()->v_pos).modulo ();
	for (list<Jogador *>::iterator it = j_candidatos.begin (); it != j_candidatos.end (); it++)
	{
		f_dist_gol = ((*it)->v_pos - g_Amigo ()->v_pos).modulo ();
		if (f_dist_gol < f_menor_dist_gol)
		{
			escolhido = *it;
			f_menor_dist_gol = f_dist_gol;
		}
	}
	return escolhido;
}
// A fazer
Vetor3 Equipe::melhor_ponto_suporte ()
{
	return centro (r_suporte_dir);
}
// A fazer
Vetor3 Equipe::melhor_ponto_sobra ()
{
	return centro (r_sobra_dir);
}
// A fazer
Vetor3 Equipe::melhor_alvo_gol ()
{
	/*
	para cada alvo faça
		custo (alvo) <- proximidade_obstaculos;
		insere (heap_max, alvo);
	fim para
	retorne primeiro (heap_max);
	*/
	return v_alvo_gol[4];
}


bool Equipe::Equipe_controla_bola ()
{
	for (int i = 0; i < 3; i++)
	{
		double f_dist;
		f_dist = (campo ()->bola ()->v_pos - j_jogador[i]->v_pos).modulo ();
		if (f_dist < 3 * (j_jogador[0]->f_raio))
		{
			return true;
		}
	}
	return false;
}
Jogador * Equipe::Adversario_com_controle_da_bola ()
{
	Equipe * e_adv;
	if (cor () == verde)
	{
		e_adv = campo ()->e_roxo ();
	}
	else
	{
		e_adv = campo ()->e_verde ();
	}
	for (int i = 0; i < 3; i++)
	{
		if (e_adv->j_jogador[i]->controla_bola ())
		{
			return e_adv->j_jogador[i];
		}
	}
	return 0;
}
Gol * Equipe::g_Adversario ()
{
	return g_adversario;
}
Gol * Equipe::g_Amigo ()
{
	return g_amigo;
}
Equipe::cor_Equipe Equipe::cor ()
{
	return _cor;
}
Vetor3 Equipe::centro (Regiao r)
{
	if (cor () == verde)
	{
		return regioes.centro (r);
	}
	else
	{
		return -1 * regioes.centro (r);
	}
}
/*
	se time verde passe o vetor
	se time roxo passe o Vetor3 com (x,y) invertido.
*/

Regiao Equipe::regiao_de (Objeto * o)
{
	if (cor () == verde)
	{
		return regioes.regiao_de (o->v_pos);
	}
	else
	{
		return regioes.regiao_de (-1 * o->v_pos);
	}
}
Regiao Equipe::regiao_sobra_de (Objeto * o)
{
	if (cor () == verde)
	{
		return regioes.regiao_sobra_de (o->v_pos);
	}
	else
	{
		return regioes.regiao_sobra_de (-1 * o->v_pos);
	}
}
Regiao Equipe::regiao_defesa_de (Objeto * o)
{
	if (cor () == verde)
	{
		return regioes.regiao_defesa_de (o->v_pos);
	}
	else
	{
		return regioes.regiao_defesa_de (-1 * o->v_pos);
	}
}
Regiao Equipe::regiao_suporte_de (Objeto * o)
{
	if (cor () == verde)
	{
		return regioes.regiao_suporte_de (o->v_pos);
	}
	else
	{
		return regioes.regiao_suporte_de (-1 * o->v_pos);
	}
}
Regiao Equipe::regiao_inicio_de (Objeto * o)
{
	if (cor () == verde)
	{
		return regioes.regiao_inicio_de (o->v_pos);
	}
	else
	{
		return regioes.regiao_inicio_de (-1 * o->v_pos);
	}
}
Vetor3 Equipe::aparar_area_util (Vetor3 v)
{
	Vetor3 r;
	Vetor3 v1, v2, _v;
	_v (0) = v (0);
	_v (1) = v (1);
	_v (2) = v (2);
	v1 (0) = - campo ()->comprimento () / 2.;
	v2 (0) = campo ()->comprimento () / 2.;
	v1 (1) = campo ()->largura () / 2.;
	v2 (1) = - campo ()->largura () / 2.;
	r = aparar_Vetor3 (v1, v2, _v);
	return r;
}