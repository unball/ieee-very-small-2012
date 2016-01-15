/*
    @file main.cpp

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
#include <iostream>

#include <Config.h>
#include <Comunicador.h>
#include <Comunicador_robos.h>
#include <Campo.h>
#include <Equipe.h>
#include <Jogador.h>

#include <Vetor.h>
#include <Temporizador.h>
#include <Dados.h>

Campo campo;

Temporizador t (1);

using namespace std;

void receberPosicoes (Comunicador & c);
void enviarVelocidades (Comunicador & com_write);
//Comunicador_robos com_estrategia_robo("COM4");

int main ()
{
    //-- Limpeza em caso de finalização abrupta.
    //boost::interprocess::shared_memory_object::remove ("Simulacao_Estrategia");
    //boost::interprocess::shared_memory_object::remove ("Estrategia_Simulacao");
    //-- Config
    Config config ("constants.config");
    //-- Comunicador
    Comunicador com_estrategia ("Estrategia");

    com_estrategia.criar_var <Dados_Estrategia> ("Dados_Estrategia");
    com_estrategia.criar_var <Dados_Simulador> ("Dados_Simulador");
    Vetor3 v;
    v(0) = 0;
    v(1) = 1;
    while (true)
    {
        //if (com_simulador.ready ())
        //{
        receberPosicoes (com_estrategia);
        //	com_simulador.done ();
        //}
        //campo.e_roxo ()->roda ();
        //campo.e_verde ()->roda ();
        //campo.bola()->roda();
        //campo.e_verde()->principal()->troca_estado(e_Voltar_base);
        //campo.e_verde ()->principal ()->mover_ate (v);
        //campo.e_verde ()->principal ()->troca_regiao_base (r_sobra_dir);
        //campo.e_roxo ()->principal ()->roda ();
        //campo.e_verde()->principal()->troca_estado(e_Fazer_gol);
        //campo.e_verde()->principal()->roda();
        //campo.e_verde()->principal()->roda();
        //campo.e_roxo()->principal()->roda();
        campo.e_verde()->principal()->alinha(v);
        campo.e_verde()->suporte ()->alinha (v);
        campo.e_verde ()->goleiro ()->alinha (v);
        //campo.e_verde()->principal()->vel_linear_angular_para_vel_rodas();
        //campo.e_verde()->suporte()->alinha(v);
        //campo.e_verde()->goleiro()->alinha(v);
        //campo.e_roxo()->principal()->alinha(v);
        //campo.e_roxo()->suporte()->alinha(v);
        //campo.e_roxo()->goleiro()->alinha(v);
        //campo.e_verde()->goleiro()->olhe_para(v);
        //campo.e_verde()->principal()->olhe_para(v);
        //campo.e_verde()->suporte()->olhe_para(v);
        //campo.e_roxo()->goleiro()->olhe_para(v);
        //campo.e_roxo()->principal()->olhe_para(v);
        //campo.e_roxo()->suporte()->olhe_para(v);
        //campo.e_verde()->principal()->zerar_forcas();
        //campo.e_verde()->principal()->aplica_forca(v);
        //campo.e_verde()->principal()->forca_para_vel_rodas();
        //campo.e_verde()->suporte()->zerar_forcas();
        //campo.e_verde()->suporte()->aplica_forca(v);
        //campo.e_verde()->suporte()->forca_para_vel_rodas();
        //campo.e_verde()->goleiro()->zerar_forcas();
        //campo.e_verde()->goleiro()->aplica_forca(v);
        //campo.e_verde()->goleiro()->forca_para_vel_rodas();
        //if (com_estrategia.ready ())
        //{
        enviarVelocidades (com_estrategia);
        //	com_estrategia.done ();
        //	}
        std::cout << com_estrategia.n_processos () << std::endl;
    }
    return 0;
}

void receberPosicoes (Comunicador & com_read)
{
    std::cout << "recebendo posicoes" << std::endl;
    Jogador ** jogador;
    jogador = campo.jogador ();
    Objeto * bola = campo.bola ();
    Dados_Simulador dados;
    dados = com_read.ler_var <Dados_Simulador> ("Dados_Simulador");
    for (int num_team = 0; num_team < 2; num_team++)
    {
        for (int num_player = 0; num_player < 3; num_player++)
        {
            jogador[num_team * 3 + num_player]->v_pos (0) = dados.v_pos_robo[num_team * 3 + num_player][0];
            jogador[num_team * 3 + num_player]->v_pos (1) = dados.v_pos_robo[num_team * 3 + num_player][1];
            Vetor3 n;
            n (0) = cos (dados.v_pos_robo[num_team * 3 + num_player][2]);
            n (1) = sin (dados.v_pos_robo[num_team * 3 + num_player][2]);
            jogador[num_team * 3 + num_player]->v_normal = n;
        }
    }
    bola->v_pos (0) = dados.v_pos_bola[0];
    bola->v_pos (1) = dados.v_pos_bola[1];
}
void enviarVelocidades (Comunicador & com_write)
{
    std::cout << "enviando velocidades" << std::endl;
    Jogador ** jogador;
    jogador = campo.jogador ();
    Dados_Estrategia dados;
    for (int num_team = 0; num_team < 2; num_team++)
    {
        for (int num_player = 0; num_player < 3; num_player++)
        {
            dados.f_vel_linear[num_team * 3 + num_player] = jogador[num_team * 3 + num_player]->f_vel_linear;
            dados.f_vel_angular[num_team * 3 + num_player] = jogador[num_team * 3 + num_player]->f_vel_angular;
            dados.f_vel_roda_dir[num_team * 3 + num_player] = jogador[num_team * 3 + num_player]->vel_roda_dir;
            dados.f_vel_roda_esq[num_team * 3 + num_player] = jogador[num_team * 3 + num_player]->vel_roda_esq;
       }
    }
    //com_estrategia_robo.enviar_velocidades(dados);
    com_write.escrever_var <Dados_Estrategia> ("Dados_Estrategia", dados);
}
