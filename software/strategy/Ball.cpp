#include <Ball.h>

Ball::Ball()
{
	this->x = 0;
	this->y = 0;
	this->vx = 0;
	this->vy = 0;
	this->vMod = 0;
	this->vAngle = 0;
}

double Ball::getX()
{
	return this->x;
}

double Ball::getY()
{
	return this->y;
}

vector<double> Ball::getPosition()
{
    vector<double> position(2);
    
    position[0] = this->getX();
    position[1] = this->getY();
    
    return position;
}

double Ball::getVelX()
{
	return this->vx;
}

double Ball::getVelY()
{
	return this->vy;
}

double Ball::getVel()
{
	return this->vMod;
}

double Ball::getVelAngle()
{
	return this->vAngle;
}

void Ball::setX(double x)
{
	this->x = x;
}

void Ball::setY(double y)
{
	this->y = y;
}

void Ball::setVelX(double vx)
{
	this->vx = vx;
}

void Ball::setVelY(double vy)
{
	this->vy = vy;
}

void Ball::setVel(double vMod)
{
	this->vMod = vMod;
}

void Ball::setVelAngle(double vAngle)
{
	this->vAngle = vAngle;
}

void Ball::refreshState(double x, double y)
{
	LOG(LEVEL_DEBUG) << "Refreshing ball state";
	
	// calculate velocities
	this->setVelX(x - this->x);
	this->setVelY(y - this->y);
	this->setVel(sqrt(pow(this->getVelX(), 2) + pow(this->getVelY(), 2)));
	this->setVelAngle(atan2(y - this->y, x - this->x));
	
	// refresh position
	this->setX(x);
	this->setY(y);
	
	LOG(LEVEL_DEBUG) << "Ball X = " << this->getX();
	LOG(LEVEL_DEBUG) << "Ball Y = " << this->getY();
	LOG(LEVEL_DEBUG) << "Ball VelX = " << this->getVelX();
	LOG(LEVEL_DEBUG) << "Ball VelY = " << this->getVelY();
	LOG(LEVEL_DEBUG) << "Ball Vel = " << this->getVel();
	LOG(LEVEL_DEBUG) << "Ball VelAngle = " << this->getVelAngle()*TO_DEG;
}

////////////////////////////////////////////////////////

int Ball::defineSquare()
{
	double x = this->getX();								//Definir o quadrante da bola   __defesa__ataque_
	double y = this->getY();								//                              |       |       |
															//                              |___2___|___1___|  robot[1]
	if((x >= 0) && (y >= 0))								//                              |       |       |
	{														//                              |___3___|___4___|  robot[0]
		LOG(LEVEL_DEBUG) << "Bola no quadrante 1";
		return 1;
	}
	
	if((x < 0) && (y >= 0))
	{
		LOG(LEVEL_DEBUG) << "Bola no quadrante 2";
		return 2;
	}
	
	if((x <= 0) && (y < 0))
	{
		LOG(LEVEL_DEBUG) << "Bola no quadrante 3";
		return 3;
	}
	
	if((x > 0) && (y < 0))
	{
		LOG(LEVEL_DEBUG) << "Bola no quadrante 4";
		return 4;
	}
	
	return 0;
}

int Ball::defineField()
{
	double x = this->getX();
	
	if(x >= 0)
	{
		LOG(LEVEL_DEBUG) << "Bola no campo de ataque";
		return 1;
	}
	else if(x < 0)
	{
		LOG(LEVEL_DEBUG) << "Bola no campo de defesa";
		return 2;
	}
	
	return 0;
}

bool Ball::nearWall()
{
	double x = this->getX();
	double y = this->getY();
	
	if(y >= 0.55)
	{
		return true;
	}
	else if(x <= -0.65)
	{
		return true;
	} 
	else if(y <= -0.55)
	{
		return true;
	}
	else if(x >= 0.65)
	{	
		return true;
	}
	else
	{
		return false;
	}
}

bool Ball::goal()
{
	double x = this->getX();
	
	if((x > 0.75) || (x < -0.75))
		return true;
	
	return false;
}
