/**
 * @file      Robots.cpp
 * @author    Tiago Pimentel Martins da Silva
 * @author    Matheus V. Portela
 * @date      22/08/2011
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */

#include <RobotsSimulation.h>
#include <Simulation.h>

int Robots::numeroDeRobos = 0;

Robots::Robots()
{	
    this->id = this->numeroDeRobos++;
    this->time = 0;
    this->posicaoTatica = 0;
    this->x = 0;
	this->y = 0;
	this->vetorX = 0;
	this->vetorY = 0;
    this->velocidadeLinear = 0;
    this->velocidadeAngular = 0;
    this->aceleracaoLinear = 0;
    this->aceleracaoAngular = 0;
    
    this->acao = 0;
    
    this->voltarPosicaoInicial();
}

void Robots::act()
{
	switch(this->acao)
	{
		case 0:
            break;
		case 1:
			//chutar(0.1);
            break;
		case 2:
			//defender();
            break;
	}
}

int Robots::pegarId()
{
    return this->id;
}

int Robots::pegarTime()
{
    return this->time;
}

int Robots::pegarPosicaoTatica()
{
	return this->posicaoTatica;
}

double Robots::pegarX()
{
    return this->x;
}

double Robots::pegarY()
{
    return this->y;
}

double Robots::pegarTheta()
{
    return this->theta;
}

double Robots::pegarVelocidadeLinear()
{
	return this->velocidadeLinear;
}

double Robots::pegarVelocidadeAngular()
{
	return this->velocidadeAngular;
}
double Robots::pegarAceleracaoLinear()
{
    return this->aceleracaoLinear;
}

double Robots::pegarAceleracaoAngular()
{
    return this->aceleracaoAngular;
}

int Robots::pegarAcao()
{
	return this->acao;
}

void Robots::mudarTime(int time)
{
    this->time = time;
}

void Robots::mudarPosicaoTatica(int posicaoTatica)
{
    this->posicaoTatica = posicaoTatica;
}

void Robots::mudarX(double x)
{
    this->x = x;
}

void Robots::mudarY(double y)
{
    this->y = y;
}

void Robots::mudarTheta(double theta)
{
    this->theta = theta;
}

void Robots::voltarPosicaoInicial()
{
	double posicaoInicialX[] = {-37.*SC, -37.*SC, -72.*SC, 71.*SC, 37.*SC, 39.*SC};
	double posicaoInicialY[] = {-40.*SC, 39.*SC, -1.*SC, -2.*SC, -39.*SC, 41.*SC};
	
	this->mudarX(posicaoInicialX[this->id]);
	this->mudarY(posicaoInicialY[this->id]);
	this->mudarTheta(0.0);
}

bool Robots::mudarVelocidadeLinear(int velocidadeLinear)
{
	if(abs(velocidadeLinear) <= QUANT_VEL_LINEAR)
	{
		this->velocidadeLinear = velocidadeLinear;
		return true;
	}
	else
		return false;
}

bool Robots::mudarVelocidadeAngular(int velocidadeAngular)
{
	if(abs(velocidadeAngular) <= QUANT_VEL_ANGULAR)
	{
		this->velocidadeAngular = velocidadeAngular;
		return true;
	}
	else
		return false;
}
        
void Robots::mudarAceleracaoLinear(double aceleracaoLinear)
{
    this->aceleracaoLinear = aceleracaoLinear;
}

void Robots::mudarAceleracaoAngular(double aceleracaoAngular)
{
    this->aceleracaoAngular = aceleracaoAngular;
}

void Robots::mudarAcao(int acao)
{
	this->acao = acao;
}

void Robots::construirChassi(dWorldID world)
{
    for (int i=0; i < 2; i++)
    {
        // Cria objeto e geometria
        this->body[i] = dBodyCreate(world);
        this->box[i] = dCreateBox(0,LENGTH/(1+i),WIDTH,HEIGHT);

        // Define a posição do objeto
        dBodySetPosition(this->body[i],this->pegarX(),this->pegarY(),STARTZ+HEIGHT/2-HEIGHT*i);

		// Se o robô for do segundo time, deve ser rotacionado em 180 graus
        if ((this->id == 3) || (this->id == 4) || (this->id == 5))
        {
			dQuaternion q;
			dQFromAxisAndAngle(q,0,0,1,M_PI);
			dBodySetQuaternion(this->body[i],q);
		}

        // Define a massa do objeto
        dMass m;
        dMassSetBox(&m,1,LENGTH/(1+i),WIDTH,HEIGHT);	// O segundo bloco é mais curto
        dMassAdjust(&m,CMASS*(1+i*2));					// O segundo bloco é mais pesado
        dBodySetMass(this->body[i],&m);
                
        // Associa o objeto à sua geometria
        dGeomSetBody(this->box[i],this->body[i]);
    }
		
    // O chassis é composto por dois blocos que são fixos entre si
    dJointID fixed = dJointCreateFixed(world,0);
    dJointAttach(fixed,this->body[1],this->body[0]);
    dJointSetFixed(fixed); 
}

void Robots::construirRodas(dWorldID world)
{
    for (int i=0; i < 2; i++)
    {
        // Cria objeto e geometria
        this->wheel[i] = dBodyCreate(world);
        this->cylinder[i] = dCreateCylinder(0,RADIUS,wTHICK);
			
        // Define a posição e orientação do objeto
        dQuaternion q;
        dQFromAxisAndAngle(q,1,0,0,M_PI*0.5);
        dBodySetQuaternion(this->wheel[i],q);
        dBodySetPosition(this->wheel[i],this->pegarX(),this->pegarY()+(1-2*i)*((WIDTH/2)+(wTHICK/2)),STARTZ);

        // Define a massa do objeto
        dMass m;
        dMassSetCylinder(&m,1,3,RADIUS,wTHICK);
        dMassAdjust(&m,WMASS);
        dBodySetMass(this->wheel[i],&m);
			
        // Associa o objeto à sua geometria
        dGeomSetBody(this->cylinder[i],this->wheel[i]);
    }
}

void Robots::conectarChassiRodas(dWorldID world)
{
    const dReal *a;
    
    for (int i = 0; i < 2; i++)
    {
        this->joint[i] = dJointCreateHinge2(world,0);
        dJointAttach(this->joint[i],this->body[0],this->wheel[i]);
			
        a = dBodyGetPosition (this->wheel[i]);
        dJointSetHinge2Anchor(this->joint[i],a[0],a[1],a[2]);
        dJointSetHinge2Axis1(this->joint[i],0,0,1);
        dJointSetHinge2Axis2(this->joint[i],0,1,0);

        // set joint suspension 
        dJointSetHinge2Param(this->joint[i],dParamSuspensionERP,0.4);

        //set stops to make sure wheels always stay in alignment
        dJointSetHinge2Param(this->joint[i],dParamLoStop,0);
        dJointSetHinge2Param(this->joint[i],dParamHiStop,0);
    }
}

void Robots::criarEspacoRobo(dSpaceID space)
{
    this->robot_space = dSimpleSpaceCreate (space);
    dSpaceSetCleanup(this->robot_space,0);
		
    dSpaceAdd(this->robot_space,this->box[0]);
    dSpaceAdd(this->robot_space,this->box[1]);
    dSpaceAdd(this->robot_space,this->cylinder[0]);
    dSpaceAdd(this->robot_space,this->cylinder[1]);
}

void Robots::construirRobo(dWorldID world, dSpaceID space)
{
	this->construirChassi(world);
	this->construirRodas(world);
	this->conectarChassiRodas(world);
	this->criarEspacoRobo(space);
}
