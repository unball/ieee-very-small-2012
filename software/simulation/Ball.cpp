/**
 * @file      Ball.cpp
 * @author    Matheus V. Portela
 * @date      09/11/2011
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */

#include <Ball.h>
#include <Simulation.h>

Bola::Bola()
{
    this->x = 0;
    this->y = 0;
    this->velocidadeX = 0;
    this->velocidadeY = 0;
    this->permitirControle = false;
    this->acao = 0;
}

void Bola::info()
{
    LOG(LEVEL_INFO) << "Bola"
                    << " X: " << this->pegarX()
                    << " Y: " << this->pegarY()
                    << " Vel X: " << this->pegarVelocidadeX()
                    << " Vel Y: " << this->pegarVelocidadeY();
}

double Bola::pegarX()
{
    return this->x;
}

double Bola::pegarY()
{
    return this->y;
}

double Bola::pegarVelocidadeX()
{
    return this->velocidadeX;
}

double Bola::pegarVelocidadeY()
{
    return this->velocidadeY;
}

void Bola::mudarX(double x)
{
    this->x = x;
}

void Bola::mudarY(double y)
{
    this->y = y;
}

void Bola::mudarVelocidade(double velocidadeX, double velocidadeY)
{
    if (!this->permitirControle)
    {
        LOG(LEVEL_WARN) << "Bola: Tentando mudar velocidade sem permissao. Aperte \'i\'";
    }
    
    else
    {
        this->velocidadeX = velocidadeX;
        this->velocidadeY = velocidadeY;
    }
}

void Bola::construir(dWorldID world, dSpaceID space)
{
    // Cria objeto e geometria
	this->corpo = dBodyCreate(world);
	this->geometria = dCreateSphere(0,BOLA_RAIO);
	
	// Define a posição do objeto
	dBodySetPosition(this->corpo, this->pegarX(), this->pegarY(), STARTZ);
	
	// Define a massa do objeto
	dMass m;
	dMassSetSphere(&m,1,BOLA_RAIO);
	dMassAdjust(&m,BOLA_MASSA);
	dBodySetMass(this->corpo,&m);
	
	// Associa o objeto à geometria
	dGeomSetBody(this->geometria,this->corpo);
	
	// Cria um espaço para a bola e a adiciona
	this->espaco = dSimpleSpaceCreate(space);
	dSpaceSetCleanup(this->espaco,0);
	
	dSpaceAdd(this->espaco,this->geometria);
}

void Bola::destruir()
{
    dGeomDestroy(this->geometria); //destruir geometria
    this->permitirControle = false;
}

bool Bola::podeControlar()
{
    return this->permitirControle;
}

void Bola::mudarPermissaoControle(bool permitir)
{
    LOG(LEVEL_INFO) << "Bola: Alterar permissão de controle = " << permitir;
    this->permitirControle = permitir;
}

void Bola::definirAcao(int acao)
{
    if (!this->podeControlar())
    {
        LOG(LEVEL_WARN) << "Bola: Tentando controlar sem permissao. Aperte \'i\'";
        this->acao = 0;
    }
    
    else
    {
        // imprimir acao escolhida
        switch(acao)
        {
            case(BOLA_MOVIMENTAR_RETA):
                LOG(LEVEL_INFO) << "Bola: Movimentar em reta";
                break;
            case(BOLA_MOVIMENTAR_CIRCULO):
                LOG(LEVEL_INFO) << "Bola: Movimentar em circulo";
                break;
        }
        
        this->acao = acao;
    }
}

void Bola::movimentarReta(double angulo = 0) // angulo em graus
{
    angulo = angulo * PARA_RAD; // converter para radianos
    
    double novaVelocidadeX = BOLA_VELOCIDADE * cos(angulo);
    double novaVelocidadeY = BOLA_VELOCIDADE * sin(angulo);
    
    this->mudarVelocidade(novaVelocidadeX, novaVelocidadeY);
}

void Bola::movimentarCirculo()
{
    double anguloAtual = atan2(this->pegarVelocidadeY(), this->pegarVelocidadeX());
    
    double novaVelocidadeX = BOLA_VELOCIDADE * cos(anguloAtual + BOLA_VELOCIDADE_ANGULAR);
    double novaVelocidadeY = BOLA_VELOCIDADE * sin(anguloAtual + BOLA_VELOCIDADE_ANGULAR);
    
    this->mudarVelocidade(novaVelocidadeX, novaVelocidadeY);
}

void Bola::executarAcao()
{
    switch(this->acao)
    {
        case(BOLA_MOVIMENTAR_RETA):
            this->movimentarReta();
            break;
        case(BOLA_MOVIMENTAR_CIRCULO):
            this->movimentarCirculo();
            break;
    }
}

void Bola::loop()
{
    //this->info();
    this->executarAcao();
}

void Bola::resetar()
{
    this->x = 0;
    this->y = 0;
    this->velocidadeX = 0;
    this->velocidadeY = 0;
    this->permitirControle = false;
    this->acao = 0;
}
