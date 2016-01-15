/*
    @file Simulation.h

	@author		Guilherme C. Anselmo
	@author		Matheus V. Portela
	@author		Cíntia P. Martins
	@author		Tiago P. M. da Silva
    @autor		William Batista Aguiar Motta		@email yosoyninja@gmail.com

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
#ifndef SIMULATION_H
#define SIMULATION_H

/**
 * @brief Bibliotecas utilizadas
 *
 * Inclui todas as bibliotecas que serao utilizadas pelo
 * simulador
 */
#include <quaternion.h>
#include <Dados.h>
#include <Temporizador.h>
extern Temporizador t_temp;

#define dSINGLE
#ifdef _WIN32
#define DRAWSTUFF_TEXTURE_PATH "C:/ode-0.12/drawstuff/textures"
#endif
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include <texturepath.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <ios>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @brief Constantes utilizadas durante a simulacao
 *
 * Agrupamento de todas as constantes que foram utilizadas
 * durante a simulacao.
 *
 */

// constantes dos robos e da bola
#define LEITURA    6		  // lê o arquivo de posições dos robôs a cada 6 iterações
#define LENGTH     0.075      // comprimento do chassi
#define WIDTH      0.055      // largura do chassi
#define HEIGHT     0.070/2    // altura do chassi
#define RADIUS     0.075/2    // raio da roda
#define wTHICK     0.01       // espessura da roda
#define STARTZ     0.05       // altura inicial do chassi
#define CMASS      0.35/3     // massa do chassi
#define WMASS      0.03       // massa da roda
#define ROBOTS     6          // quantidade de robos
#define GRAVITY    -9.8       // gravidade
#define TQ         0.3    // torque

// escala: 1 unidade = 100 cm (?)
#define SC         0.01

// constantes das paredes
#define THICK      SC*2.5     // espessura da parede
#define HEIGTH     SC*20      // altura da parede

// constantes do gol
#define GOAL_WIDTH    SC*10    // largura do gol
#define GOAL_LENGTH   SC*40    // comprimento do gol

// constantes do campo
#define CIRCLE_RADIUS    SC*20     // raio do circulo central
#define FIELD_WIDTH      SC*150    // largura do campo
#define FIELD_LENGTH     SC*130    // comprimento do campo
#define SIDE_LENGTH     (FIELD_LENGTH-GOAL_LENGTH)/2    // comprimento lateral

// beirada triangular do campo
#define TRIANGLE_SIZE    SC*7      // tamanho do triangulo
#define TRIANGLE_THICK   SC*0.1    // espessura do triangulo
#define TRIANGLE_LENGTH  TRIANGLE_SIZE*sqrt(2.)    // comprimento do triangulo

// posicoes dos elementos do campo
#define FRONT_Y          (FIELD_LENGTH+THICK)/2
#define SIDE_X           (FIELD_WIDTH+THICK)/2
#define SIDE_Y           (FIELD_LENGTH+GOAL_LENGTH)/4
#define GOAL_LENGTH_X    (SIDE_X+GOAL_WIDTH)
#define GOAL_WIDTH_X     (SIDE_X+((GOAL_WIDTH+THICK)/2))
#define GOAL_WIDTH_Y     (GOAL_LENGTH+THICK)/2
#define TRIANGLE_X       ((FIELD_WIDTH/2)-(SC*3.5))
#define TRIANGLE_Y       ((FIELD_LENGTH/2)-(SC*3.5))

// constantes de velocidade
#define FRENTE   1
#define TRAS     2
#define HORARIO  3
#define ANTIHORARIO 4
#define QUANT_VEL_LINEAR 40
#define QUANT_VEL_ANGULAR 40

/**
 * @brief Variaveis utilizadas
 *
 * Todas as variaveis globais utilizadas no simulador
 *
 */

// campo
extern dGeomID wall[6];        // paredes externas
extern dGeomID goalL[3];       // gol esquerdo
extern dGeomID goalR[3];       // gol direito
extern dGeomID circle;         // circulo central
extern dGeomID triangle[4];    // triangulo da borda
extern dGeomID chao;           // chao

// objetos para dinamica e colisoes (chassi, 3 rodas e ambiente)
extern dWorldID world;              // mundo
extern dSpaceID space;              // espaco de colisao
extern dJointGroupID contactgroup;  // geometria de colisao
extern dJointGroup coll_contacts;
extern dGeomID ground;              // geometria do chao

// things that the user controls
extern int tempo, cont;
extern int n_robot;
extern dReal posx[];
extern dReal posy[];
extern dReal rot[];

// pointers to drawstuff functions
extern dsFunctions fn;

// funções da simulacao
void start();
void simLoop (int pause);
void command (int cmd);
void nearCallback (void *data, dGeomID o1, dGeomID o2);
void initDrawStuff();

// funções de velocidade
void acelerar(int direcao, double intensidade);

// funções de construção
void construirMundo();
void construirRobos();

void construirBola();

void construirCampo();
void construirParedes();
void construirChao();
void construirCirculoCentral();
void construirGols();
void construirQuinas();

// funções de destruição
void destruirMundo();

// funções de desenho
void desenharMundo();
void desenharRobos();
void desenharCampo();

// funções de atualização
void avancarPasso(dReal dt);
void atualizarVelocidadeBola();
void atualizarVelocidades();
void atualizarVelocidadesAngulares();
void atualizarVelocidadesLineares();
void atualizarPosicoes();
double calcularAngulo(int i);

// funções de comunicação
void inicializarComunicacao();
void enviarPosicoes();
void receberVelocidades();
void receberComando();

#endif // SIMULATION_H

