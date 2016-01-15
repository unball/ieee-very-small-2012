/**
 * @file      Robots.h
 * @author    Tiago Pimentel Martins da Silva
 * @author    Matheus V. Portela
 * @date      22/08/2011
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */

#ifndef ROBOTS_H
#define ROBOTS_H

/**
 * @brief Configuração de módulos de software UnBall 
 *
 * Robots é a classe responsável pelo funcionamento do robo e o acionamento de suas funcoes.
 *
 */
#include <Simulation.h>
#include <ode/ode.h>
#include <drawstuff/drawstuff.h>
#include <texturepath.h>

using namespace std;

#define QUANT_VEL_LINEAR 40
#define QUANT_VEL_ANGULAR 40

class Robots
{
    public:
		Robots();

        // Funcao a ser chamada automaticamente
		void act();

        // Pegar atributos
        int pegarId();
        int pegarTime();
		int pegarPosicaoTatica();
        
        double pegarX();
        double pegarY();
        double pegarTheta();
        
		double pegarVelocidadeLinear();
		double pegarVelocidadeAngular();
        double pegarAceleracaoLinear();
        double pegarAceleracaoAngular();
        
        int pegarAcao();
		
        // Mudar atributos do robo
        void mudarTime(int time);
        void mudarPosicaoTatica(int posicaoTatica);
        
        void mudarX(double x);
        void mudarY(double y);
        void mudarTheta(double th);
        
        void voltarPosicaoInicial();
        
		bool mudarVelocidadeLinear(int velocidadeLinear);
		bool mudarVelocidadeAngular(int velocidadeAngular);
        void mudarAceleracaoLinear(double aceleracaoLinear);
        void mudarAceleracaoAngular(double aceleracaoAngular);
        
		void mudarAcao (int acao);
		
		void construirChassi(dWorldID world);
		void construirRodas(dWorldID world);
		void conectarChassiRodas(dWorldID world);
		void criarEspacoRobo(dSpaceID space);
		void construirRobo(dWorldID world, dSpaceID space);

		// Atributos do ODE
        dBodyID body[2];      // corpo do chassi
        dBodyID wheel[2];     // corpo da roda
        dJointID joint[3];   // junta das rodas
        dSpaceID robot_space; // espaço do robô
        dGeomID box[2];      // geometria do chassi
        dGeomID cylinder[3]; // geometria das rodas

    private:
        static int numeroDeRobos;
    
        // Atributos de identificacao
        int id;
        int time;
        int posicaoTatica;
        
        // Atributos de localizacao
        double x, y, theta;
        double vetorX, vetorY;
        
        // Atributos de locomocao
        double velocidadeLinear;
        double velocidadeAngular;
        double aceleracaoLinear;
        double aceleracaoAngular;
        
        // Atributos de controle
        int acao;
};

//void actAll ();


#endif // ROBOTS_H

