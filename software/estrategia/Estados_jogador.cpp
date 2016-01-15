/*
    @file Estados_jogador.cpp

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
#include <Estados_jogador.h>
#include <Jogador.h>
#include <Equipe.h>
#include <Funcoes_gerais.h>
#include <Campo.h>

Estado_jogador::Estado_jogador (Jogador * jogador) : c_campo (jogador->campo ()), e_Equipe (jogador->equipe ()), jogador (jogador) {}
Sobra::Sobra (Jogador * jogador) : Estado_jogador (jogador) {}
Suporte_ataque::Suporte_ataque (Jogador * jogador) : Estado_jogador (jogador) {}
Fazer_gol::Fazer_gol (Jogador * jogador) : Estado_jogador (jogador) {}
Interceptar_bola::Interceptar_bola (Jogador * jogador) : Estado_jogador (jogador) {}
Esperar::Esperar (Jogador * jogador) : Estado_jogador (jogador) {}
Fechar_gol::Fechar_gol (Jogador * jogador) : Estado_jogador (jogador) {}
Voltar_base::Voltar_base (Jogador * jogador) : Estado_jogador (jogador) {}
Passar::Passar (Jogador * jogador) : Estado_jogador (jogador) {}
Penalty::Penalty (Jogador * jogador) : Estado_jogador (jogador){}

void Esperar::entra () {}
void Esperar::roda ()
{
    jogador->espera ();
}
void Esperar::sai () {}

void Voltar_base::entra () {}
void Voltar_base::roda ()
{
    if (jogador->equipe ()->regiao_de (jogador) & jogador->regiao_base ())
    {
        jogador->espera ();
    }
    else
    {
        jogador->mover_ate (jogador->equipe ()->centro (jogador->regiao_base ()));
    }
}
void Voltar_base::sai () {}

void Interceptar_bola::entra ()
{
    b_alvo_frente_alcancado = false;
}
void Interceptar_bola::roda ()
{
    if (b_alvo_frente_alcancado)
    {
        jogador->mover_ate (c_campo->bola ()->v_pos);
    }
    else
    {
        Vetor3 p, v1_;
        v1_ = c_campo->bola ()->v_pos - jogador->equipe ()->g_Adversario ()->v_pos;
        v1_ = v1_.unitario ();
        p = c_campo->bola ()->v_pos + jogador->f_raio * v1_;
        if (jogador->estou_em (p))
        {
            jogador->mover_ate (c_campo->bola()->v_pos);
            this->b_alvo_frente_alcancado = true;
        }
    }
}

void Interceptar_bola::sai () {}

void Fechar_gol::entra ()
{
    y_max = e_Equipe->g_Amigo ()->v_pos (1) + e_Equipe->g_Amigo ()->comprimento () / 2. - jogador->f_raio;
    y_min = e_Equipe->g_Amigo ()->v_pos (1) - e_Equipe->g_Amigo ()->comprimento () / 2. + jogador->f_raio;
    x = e_Equipe->g_Amigo ()->poste_dir () (0) + jogador->f_raio * e_Equipe->g_Amigo ()->v_normal (0);
}
void Fechar_gol::roda ()
{
    Vetor3 p;
    double y;
    y = c_campo->bola ()->v_pos (1);
    p (0) = x;
    p (1) = aparar_valor (y_min, y_max, y);
    p (2) = 0;
    jogador->mover_ate (p);
    if (jogador->estou_em (p))
    {
        jogador->alinha (c_campo->bola ()->v_pos - jogador->v_pos);
    }
}
void Fechar_gol::sai () {}

void Fazer_gol::entra () {}
void Fazer_gol::roda ()
{
    jogador->mover_ate (jogador->equipe ()->melhor_alvo_gol ());
}
void Fazer_gol::sai () {}

void Sobra::entra () {}
void Sobra::roda ()
{
    jogador->mover_ate (jogador->equipe ()->melhor_ponto_sobra ());
}
void Sobra::sai () {}

void Suporte_ataque::entra () {}
void Suporte_ataque::roda ()
{
    jogador->mover_ate (jogador->equipe ()->melhor_ponto_sobra ());
}
void Suporte_ataque::sai () {}

void Passar::entra () {}
void Passar::roda () {}
void Passar::sai () {}

void Penalty::entra () 
{

x = c_campo->bola ()->v_pos (0);	
y = c_campo->bola ()->v_pos (1);

nChute = 0;

}
void Penalty::roda () 
{
// Geraremos 3 tipos de função de chute
switch (nChute) {




	case	0:		// Primeiro caso 
	
	
	p (0) = x/2;
	p (1) = y + 0.2;
	p (2) = 0;
		
	jogador->mover_ate (p);
	if (jogador->estou_em(p))
	nChute =+ 1;
	
	break;
	
	case 	1:
	p (0) = x + 0.02;
	p (1) = y;
	p (2) = 0;	
	
		jogador->mover_ate (p);
		
	
	break;
	
		
	case	2:		// Segundo caso
	
	p (0) = x;
	p (1) = y;
	p (2) = 0;	
	
		jogador->mover_ate (p);
		if (jogador->estou_em(p))
	nChute =+ 1;
	
	break;
	case 	3:
	
	p (0) = x;
	p (1) = y + 10;
	p (2) = 0;	
	
		jogador->olhe_para (p);
		
	break;
		
		
	case	4:		// Terceiro caso

	p (0) = x;
	p (1) = y + 0.01;
	p (2) = 0;	
	
		jogador->mover_ate (p);
		if (jogador->estou_em(p))
	nChute =+ 1;
	break;
	
	case	5:
	
	p (0) = x + 0.07;
	p (1) = y + 0.05;
	p (2) = 0;	
	
		jogador->mover_ate (p);
	break;
	
}
	
	

	
	}
void Penalty::sai () {}
