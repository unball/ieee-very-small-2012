/*
    @file Estados_equipe.cpp

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
#include <Estados_equipe.h>
#include <Equipe.h>
#include <Jogador.h>
#include <Regioes.h>
#include <Campo.h>

Defendendo::Defendendo (Equipe * e) : campo (e->campo ()), equipe (e) {}
void Defendendo::entra ()
{
    if (equipe->regiao_de (equipe->principal ()) & r_defesa_dir)
    {
        j_dir = equipe->principal ();
        j_esq = equipe->suporte ();
    }
    else
    {
        j_dir = equipe->suporte ();
        j_esq = equipe->principal ();
    }
    j_gol = equipe->goleiro ();
    j_dir->troca_regiao_base (r_defesa_centro);
    j_esq->troca_regiao_base (r_defesa_centro);
    j_gol->troca_estado (e_Fechar_gol);
}
void Defendendo::roda ()
{
    if (equipe->regiao_de (campo->bola ()) & r_ataque)
    {
        equipe->troca_estado (new Atacando (equipe));
        return;
    }
    if (j_gol != equipe->goleiro ())
    {
        this->entra ();
    }
    if (equipe->regiao_defesa_de (campo->bola ()) == r_defesa_dir)
    {
        if (j_dir->controla_bola ())
        {
            j_dir->troca_estado (e_Fazer_gol);
        }
        else
        {
            j_dir->troca_estado (e_Interceptar_bola);
        }
        j_esq->troca_estado (e_Voltar_base);
        return;
    }
    if (equipe->regiao_defesa_de (campo->bola ()) == r_defesa_esq)
    {
        if (j_esq->controla_bola ())
        {
            j_esq->troca_estado (e_Fazer_gol);
        }
        else
        {
            j_esq->troca_estado (e_Interceptar_bola);
        }
        j_dir->troca_estado (e_Voltar_base);
        return;
    }
}
void Defendendo::sai () {}

Atacando::Atacando (Equipe * e) : campo (e->campo ()), equipe (e) {}
void Atacando::entra ()
{
    equipe->principal ()->troca_estado (e_Fazer_gol);
    equipe->suporte ()->troca_estado (e_Sobra);
    equipe->goleiro ()->troca_estado (e_Fechar_gol);
}
void Atacando::roda ()
{
    if (equipe->regiao_de (campo->bola ()) & r_defesa)
    {
        equipe->troca_estado (new Defendendo (equipe));
        return;
    }
    if (equipe->principal ()->pode_chutar_gol ())
    {
        if (equipe->principal ()->controla_bola ())
        {
            equipe->principal ()->troca_estado (e_Fazer_gol);
        }
        else
        {
            equipe->principal ()->troca_estado (e_Interceptar_bola);
        }
        equipe->suporte ()->troca_estado (e_Sobra);
    }
    else
    {
        equipe->principal ()->troca_estado (e_Passar);
        equipe->suporte ()->troca_estado (e_Suporte_ataque);
    }
    equipe->goleiro ()->troca_estado (e_Fechar_gol);
}
void Atacando::sai () {}

Preparando_para_iniciar_jogo::Preparando_para_iniciar_jogo (Equipe * e) : campo (e->campo ()), equipe (e) {}
void Preparando_para_iniciar_jogo::entra ()
{
    equipe->principal ()->troca_regiao_base (r_inicio_dir);
    equipe->suporte ()->troca_regiao_base (r_inicio_esq);
    equipe->goleiro ()->troca_regiao_base (r_inicio_gol);
    equipe->principal ()->troca_estado (e_Voltar_base);
    equipe->suporte ()->troca_estado (e_Voltar_base);
    equipe->goleiro ()->troca_estado (e_Voltar_base);
}
void Preparando_para_iniciar_jogo::roda ()
{
    // espere entrada do usuário.
    equipe->troca_estado (new Atacando (equipe));
}
void Preparando_para_iniciar_jogo::sai () {}


//PENALTY - /Em caso de Penalty a equipe se reune para rebote e jogador principal se posiciona para chute.
Preparando_para_Penalty::Preparando_para_Penalty (Equipe * e) : campo (e->campo ()), equipe (e) {}
void Preparando_para_Penalty::entra ()
{
	equipe->principal ()->troca_regiao_base (r_campo);
	equipe->suporte ()->troca_regiao_base (r_inicio_esq);
	equipe->goleiro ()->troca_regiao_base (r_inicio_gol);
	equipe->principal ()->troca_estado (e_Voltar_base);
	equipe->suporte ()->troca_estado (e_Voltar_base);
	equipe->goleiro ()->troca_estado (e_Voltar_base);
	equipe->principal ()->troca_estado (e_Penalty);
	
	
	}
void Preparando_para_Penalty::roda ()
{
	// espere entrada do usuário.
	
	
	equipe->troca_estado(new Preparando_para_iniciar_jogo (equipe));
}
void Preparando_para_Penalty::sai () 
{
		
}

