/**
 * @file      Ball.h
 * @author    Matheus V. Portela
 * @date      09/11/2011
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */

#ifndef BALL_H
#define BALL_H

#include <math.h>
#include <Simulation.h>
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include <texturepath.h>

#include <ProcessLogger.h>

using namespace std;

#define PARA_RAD M_PI/180;      // converter para radianos
#define PARA_GRAUS 180/M_PI;    // converter para graus

#define BOLA_RAIO  0.02135    // raio da roda B
#define BOLA_MASSA 0.03       // massa da bola

#define BOLA_VELOCIDADE 0.1 // velocidade linear
#define BOLA_VELOCIDADE_ANGULAR 0.087266463 // velocidade angular em rad/ciclo

// lista de acoes
#define BOLA_MOVIMENTAR_RETA 1
#define BOLA_MOVIMENTAR_CIRCULO 2

class Bola
{
  public:
    Bola();
    
    void info();
    
    // pega atributos da bola
    double pegarX();
    double pegarY();
    double pegarVelocidadeX();
    double pegarVelocidadeY();
    
    // altera atributos da bola
    void mudarX(double x);
    void mudarY(double y);
    void mudarVelocidade(double velocidadeX, double velocidadeY);
    
    // para ODE
    void construir(dWorldID world, dSpaceID space);
    void destruir();
    
    bool podeControlar(); // verifica permissao para controlar a bola
    void mudarPermissaoControle(bool permitir); // define permissao para controlar a bola
    void definirAcao(int acao); // define acao a ser executada
    
    void movimentarReta(double angulo);
    void movimentarCirculo();
    void executarAcao(); // executa acao definida
    
    void loop(); // funcao executada a cada loop
    void resetar(); // reseta atributos para iniciais
  
    dSpaceID espaco;   // espaco da bola
    dBodyID corpo;     // corpo da bola
    dGeomID geometria; // geometria da bola
    
  private:
    double x, y;        // posicao em X e Y
    double velocidadeX; // velocidade em X
    double velocidadeY; // velocidade em Y
    
    int acao; // acao a ser executada
    bool permitirControle; // informa se o módulo de controle da bola está ativo
};

#endif
