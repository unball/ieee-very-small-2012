/*
    @file Jogador.cpp

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
#include <Jogador.h>
#include <Equipe.h>
#include <Campo.h>
#include <Regioes.h>
#include <Estados_jogador.h>
#include <Objetos.h>

Jogador::Jogador () : Robo ()
{
    for (int i = 0; i < num_estados; i++)
    {
        this->e_estado[i] = 0;
    }
    this->f_raio = 0.075 / 2.;
}
void Jogador::Init (Equipe * e)
{
    for (int i = 0; i < num_estados; i++)
    {
        delete this->e_estado[i];
    }
    this->e_Equipe = e;
    this->c_campo = e->campo ();
    this->r_base = r_campo;
    this->_estado_atual = e_Esperar;
    this->_estado_anterior = e_Esperar;
    this->e_estado[e_Sobra] = new Sobra (this);
    this->e_estado[e_Suporte_ataque] = new Suporte_ataque (this);
    this->e_estado[e_Fazer_gol] = new Fazer_gol (this);
    this->e_estado[e_Passar] = new Passar (this);
    this->e_estado[e_Interceptar_bola] = new Interceptar_bola (this);
    this->e_estado[e_Esperar] = new Esperar (this);
    this->e_estado[e_Fechar_gol] = new Fechar_gol (this);
    this->e_estado[e_Voltar_base] = new Voltar_base (this);
}

Jogador::~Jogador ()
{
    for (int i = 0; i < num_estados; i++)
    {
        delete this->e_estado[i];
    }
}
void Jogador::setEquipe (Equipe * e)
{
    this->Init (e);
}
void Jogador::setRegiao_base (Regiao r)
{
    this->r_base = r;
}
void Jogador::roda ()
{
    Objeto::roda ();
    this->e_estado[_estado_atual]->roda ();
    this->zerar_forcas();
}
void Jogador::troca_estado (enum_Estado e_novo)
{
    if (e_novo != this->_estado_atual)
    {
        this->e_estado[_estado_atual]->sai ();
        this->_estado_anterior = this->_estado_atual;
        this->_estado_atual = e_novo;
        this->e_estado[_estado_atual]->entra ();
    }
}
enum_Estado Jogador::estado_atual ()
{
    return this->_estado_atual;
}
enum_Estado Jogador::estado_anterior ()
{
    return this->_estado_anterior;
}
void Jogador::troca_regiao_base (Regiao r)
{
    this->r_base = r;
}
bool Jogador::alinha (Vetor3 v)
{
    float sinal;
    sinal = v.unitario().escalar(this->v_normal) > 0 ? 1. : -1.;
    this->f_vel_angular = MAX_W * v.unitario().vetorial (sinal * this->v_normal) (2);
    if (abs (this->f_vel_angular) < MIN_W)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Jogador::olhe_para (Vetor3 v)
{
    this->alinha (v - this->v_pos);
    return this->dentro_campo_visao (v);
}
bool Jogador::espera ()
{
    this->f_vel_linear = 0;
    this->f_vel_angular = 0;
    return true;
}
bool Jogador::mover_ate (Vetor3 alvo)
{
    /*
    if (this->estou_em (alvo)) {
        return true;
    }
    Vetor3 forca;
    forca = alvo - this->v_pos;
    if (forca.modulo() > 15.)
    {
        forca = 15. * forca.unitario();
    }
    this->aplica_forca (forca);
    this->forca_para_vel_rodas();
    this->vel_rodas_para_vel_linear_angular();
    return false;
    */

    Vetor3 alvo_valido = equipe ()->aparar_area_util (alvo);
    Vetor3 _normal = this->v_normal;
    this->espera ();
    if (this->estou_em (alvo_valido))
    {
        return true;
    }
    if (this->olhe_para (alvo_valido))
    {
        if (this->perto_demais_parede () && this != this->equipe ()->goleiro ())
        {
            if (this->olhe_para (this->normal_parede_proxima ()))
            {
                this->f_vel_linear = MAX_V * 0.5 * _normal.escalar ((alvo_valido - v_pos).unitario ());
            }
        }
        else
        {
            this->f_vel_linear = MAX_V * _normal.escalar ((alvo_valido - v_pos).unitario ());
            alinha (alvo_valido - this->v_pos);
        }
    }
    return false;

    /*
    Vetor3 v_dist;
    double distance;
    double alfa, beta;
    double v = 20;
    double w;
    double kA = 75;
    double kB = -45;

    v_dist = alvo - v_pos;
    distance = v_dist.modulo ();

    if(distance == 0.0)
        distance = 0.6;
    alfa = acosf (v_dist.unitario ().escalar (this->v_normal));
    beta = acosf (v_dist.unitario ().escalar (Vetor3().X()));

    w = kA * alfa + kB * beta;

    f_vel_linear=  v;
    f_vel_angular = w;

    return false;
    */
}
bool Jogador::dentro_campo_visao (Vetor3 alvo)
{
    // O robô olha para frente e para trás.
    // ângulo de visão de 90 graus.
    double f_cos;
    f_cos = this->v_normal.escalar ((alvo - this->v_pos).unitario ());
    if (abs (f_cos) > 0.9)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Jogador::estou_em (Vetor3 alvo)
{
    Vetor3 alvo_valido = this->equipe ()->aparar_area_util (alvo);
    if ((this->v_pos - alvo_valido).modulo () < 1. * this->f_raio)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Jogador::perto_demais_parede ()
{
    double y_min, y_max, x_min, x_max;
    y_min = - this->campo ()->largura () / 2. + this->f_raio;
    y_max = this->campo ()->largura () / 2. - this->f_raio;
    x_min = - this->campo ()->comprimento () / 2. + this->f_raio;
    x_max = this->campo ()->comprimento () / 2. - this->f_raio;
    if (this->v_pos (0) < x_min || x_max < this->v_pos (0) || this->v_pos (1) < y_min || y_max < this->v_pos (1))
    {
        return true;
    }
    else
    {
        return false;
    }
}
Vetor3 Jogador::normal_parede_proxima ()
{
    double f_dist[4];
    f_dist[0] = abs (v_pos (0) - campo ()->parede ()[0].v_pos (0));
    f_dist[1] = abs (v_pos (0) - campo ()->parede ()[2].v_pos (0));
    f_dist[2] = abs (v_pos (1) - campo ()->parede ()[1].v_pos (1));
    f_dist[3] = abs (v_pos (1) - campo ()->parede ()[3].v_pos (1));
    int i_j;
    double f_menor;
    i_j = 0;
    f_menor = f_dist[0];
    for (int i = 0; i < 4; i++)
    {
        if (f_dist[i] < f_menor)
        {
            i_j = i;
            f_menor = f_dist[i];
        }
    }
    return this->campo ()->parede ()[i_j].v_normal;
}
bool Jogador::controla_bola ()
{
    Vetor3 v1_, v2_;
    v1_ = this->campo ()->bola ()->v_pos - v_pos;
    v2_ = this->campo ()->bola ()->v_pos - this->equipe ()->g_Adversario ()->v_pos;
    v2_ = v2_.unitario ();
    if (v1_.unitario ().escalar (v2_) < -0.7)
    {
        if (v1_.modulo () < 5 * this->f_raio)
        {
            return true;
        }
    }
    return false;
}
bool Jogador::pode_passar ()
{
    /*
    existe um Jogador à frente.
    existe caminho livre para um ponto alcançável pelo Jogador.
    */
    return true;
}
bool Jogador::pode_chutar_gol ()
{
    /*
    Existe um alvo no gol cujo caminho não esteja obstruído.
    */
    return true;
}
Regiao Jogador::regiao_base ()
{
    return this->r_base;
}
Equipe * Jogador::equipe ()
{
    return this->e_Equipe;
}
Campo * Jogador::campo ()
{
    return this->c_campo;
}
