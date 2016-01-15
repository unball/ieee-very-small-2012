/**
 * @file      Robot.cpp
 * @author    Tiago Pimentel Martins da Silva
 * @author    Matheus V. Portela
 * @author    Caio R. Có Soares
 * @date      22/08/2011
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */

#include <Robot.h>
#include <Strategy.h>

int Robot::numberOfRobots = 0;

Robot::Robot()
{
    this->id = this->numberOfRobots++;
    
    if (this->id < 3)
        this->team = 0;
    else
        this->team = 1;
    
    this->x = 100;
    this->y = 100;
    this->th = 100;
    
    this->tacticPosition = 0;
    
    this->l = 0;
    this->r = 0;
    
    this->action = 0;
}

int Robot::getId()
{
    return this->id;
}

int Robot::getTeam()
{
    return this->team;
}

int Robot::getTacticPosition()
{
    return this->tacticPosition;
}

double Robot::getX()
{
    return this->x;
}

double Robot::getY()
{
    return this->y;
}

vector<double> Robot::getPose()
{
    vector<double> pose(3);
    
    pose[0] = this->getX();
    pose[1] = this->getY();
    pose[2] = this->getTh();
    
    return pose;
}

vector<double> Robot::getPosition()
{
    vector<double> position(2);
    
    position[0] = this->getX();
    position[1] = this->getY();
    
    return position;
}

double Robot::getTh()
{
    return this->th;
}

int Robot::getLeft()
{
    return this->l;
}

int Robot::getRight()
{
    return this->r;
}

double Robot::getVel()
{
    return this->v;
}

double Robot::getRotVel()
{
    return this->w;
}

int Robot::getAction()
{
    return this->action;
}

void Robot::setTeam(int team)
{
    this->team = team;
}

void Robot::setTacticPosition(int tacticPosition)
{
    this->tacticPosition = tacticPosition;
}

void Robot::setX(double x)
{
    this->x = x;
}

void Robot::setY(double y)
{
    this->y = y;
}

void Robot::setTh(double th)
{
    this->th = th;
}

void Robot::setLeft(int l)
{
    this->l = l;
}

void Robot::setRight(int r)
{
    this->r = r;
}

void Robot::setVel(double v)
{
    this->v = v;
}

void Robot::setRotVel(double w)
{
    this->w = w;
}

void Robot::setAction(int action)
{
    this->action = action;
}

void Robot::removeAction()
{
    LOG(LEVEL_DEBUG) << "Robot " << this->getId() << ": No action";
    this->setAction(0);
}

void Robot::printInfo()
{
    LOG(LEVEL_INFO) << "Robot " << this->getId() << ":"
                    << " X: " << this->getX()
                    << " Y: " << this->getY()
                    << " Th: " << this->getTh()*TO_DEG;
}

////////////////////////////////////////////////////////////////////////

bool Robot::move(vector<double> target)
{
	/* LOGIC */

    if(this->isMoveTargetReached(target))
    {
        this->stop();
        return true;
    }
    
    this->setLeft(l);
    this->setRight(r);
    
    return false;
}

bool Robot::move(double x, double y, double th)
{
	vector<double> target(3);
	
	target[0] = x;
	target[1] = y;
	target[2] = th;
	
	return this->move(target);
}

bool Robot::move(double distance)
{
    static bool isInitPositionSet = false;
    static vector<double> initPosition(2);
    
    // only goes here once
    if(!isInitPositionSet)
    {
        initPosition[0] = this->getX();
        initPosition[1] = this->getY();
        isInitPositionSet = true;
    }
    
    vector<double> currentPosition(2);
    currentPosition[0] = this->getX();
    currentPosition[1] = this->getY();
    
    // go forward until travelled distance is the desired one
    double travelledDistance = calculateDistance(initPosition, currentPosition);
    if((distance > 0) && (travelledDistance < distance))
    {
        this->setLeft(2);
        this->setRight(2);
        return false;
    }
    else if ((distance < 0) && (travelledDistance < abs(distance)))
    {
        this->setLeft(-2);
        this->setRight(-2);
        return false;
    }
    else
    {
        isInitPositionSet = false;
        this->stop();
        return true;
    }
}

bool Robot::isMoveTargetReached(vector<double> target)
{
    double tolerance = 0.03;
    
    vector<double> robotPosition = this->getPosition();
    double distance = calculateDistance(robotPosition, target);
    
    if(distance < tolerance)
        return true;
    else
        return false;
}

bool Robot::turn(double angle)
{
    if(this->isTurnTargetReached(angle))
    {
        this->stop();
        return true;
    }
    else
    {
		this->setLeft(-1);
		this->setRight(1);

        return false;
    }
}

bool Robot::turnFast(double angle)
{
    if(this->isTurnTargetReached(angle))
    {
        this->stop();
        return true;
    }
    else
    {
		if(angle > this->getTh())
		{
			this->setLeft(-3);
			this->setRight(3);
		}
		else
		{
			this->setLeft(3);
			this->setRight(-3);
		}

        return false;
    }
}

bool Robot::isTurnTargetReached(double angle)
{
    double tolerance = 45*TO_RAD;
    
    if(abs(this->getTh() - angle) < tolerance)
        return true;
    else
        return false;
}

bool Robot::stop()
{
    this->setLeft(0);
    this->setRight(0);
    return true;
}

bool Robot::waitInDefense()
{
	vector<double> targetPosition(3);
    
    targetPosition[0] = -CONST(FIELD_WIDTH) / 4;
    targetPosition[1] = ball.getY();
    targetPosition[2] = 0;

    if(this->move(targetPosition))
    {
        this->stop();
        return true;
    }
    
    return false;
}
		
bool Robot::waitInAttack()								//O robô fica parado no centro do campo de defesa esperando uma oportunidade de chutar para o gol.
{
	vector<double> targetPosition(3);
    
    targetPosition[0] = CONST(FIELD_WIDTH) / 4;
    targetPosition[1] = 0;
    targetPosition[2] = 0;

	if(this->move(targetPosition))
    {
        this->stop();
        return true;
    }
    
    return false;
}

bool Robot::goToBall()									//O robô segue em direção à bola.
{
    vector<double> targetPosition(3);
    
    targetPosition[0] = ball.getX();
    targetPosition[1] = ball.getY();
    targetPosition[2] = 0;

    if(this->move(targetPosition))
    {
        this->stop();
        return true;
    }
    
    return false;
}

bool Robot::kick()										//O robô chuta.
{
    static bool reachedBall = false;
    static double staticX, staticY, staticTh;
    
    // once that robot reaches ball, it will never more enter this if-case
    if(!reachedBall)
    {
        reachedBall = this->alignWithBallAndGoal();
        
        // when reached ball, calculate how to go a little bit further
        if (reachedBall)
        {
			staticTh = calculateAngleFromBallToGoal(this->getTeam());
			staticX = ball.getX() + 0.10*cos(staticTh);
			staticY = ball.getY() + 0.10*sin(staticTh);
		}
	}
    else
    {
		// move a little bit further (to kick!)
        if(this->move(staticX, staticY, staticTh))
        {
            this->stop();
            reachedBall = false; // it must be manually changed
            return true;
        }
    }
    
    return false;
}

bool Robot::alignWithBallAndGoal()
{
	double th = calculateAngleFromBallToGoal(this->getTeam());
	double x = ball.getX() - 0.20*cos(th);
	double y = ball.getY() - 0.20*sin(th);
	
	return this->move(x, y, th);
}

bool Robot::nearWall()								//Verifica se o robô está perto da parede.
{
	double th = this->getTh();
	double x = this->getX();
	double y = this->getY();
	
	if((y >= 0.55) && (th > 0) && (th < M_PI))
		return true;
	else if(((x <= -0.65) && (th > M_PI/2)) || ((x <= -0.65) && (th < -M_PI/2)))
		return true;
	else if((y <= -0.55) && (th > -M_PI) && (th < 0))
		return true;
	else if(((x >= 0.65) && (th > -M_PI/2)) || ((x >= 0.65) && (th < M_PI/2)))	
		return true;
	else
		return false;
}

bool Robot::lookAt(float x, float y)
{
	float dx = x-getX();
	float dy = y-getY();		
	float target_angle = atan2(dy,dx);
	
	float error = reduceAngle(this->getTh()-target_angle)*180/M_PI;
	//int saida = 4.0*error/180.0;
	
	if (abs(error) > 45)
	{
		if (error > 0)
		{
			setLeft(1);
			setRight(-1);
		}
		if (error < 0)
		{
			setLeft(-1);
			setRight(1);
		}
		
		return false;
	}
	
	return true;

	/*if (saida != 0)
	{
		this->setLeft(saida);
		this->setRight(-saida);
		
		return false;
	}
	else return true;*/
}
		
void Robot::goTo(float x, float y)
{	
	if (lookAt(x,y))
	{
		setLeft(5);
		setRight(5);
	}
}

void Robot::lookAndGo(float x, float y)
{
	float dx = x-getX();
	float dy = y-getY();		
	float target_angle = atan2(dy,dx);
	static float errorAck = 0.0;
	static float errorAnt = 0.0;
	
	float error = reduceAngle(this->getTh()-target_angle)*180/M_PI;
	
	errorAck = errorAck + error;
	
	int turn = 5*(error + /*0.00025*errorAck+*/(error-errorAnt)*0.01)/180.0; //kp=8;
	errorAnt=error;
	int fwd = 4;//7*(180-abs(error));//16-(dx*dx+dy*dy);
	
	int left = turn+fwd;//(error > 0) ? (turn+fwd) : (-turn+fwd);
	int right = -turn+fwd;//(error > 0) ? (-turn+fwd) : (turn+fwd);
	
	LOG(LEVEL_INFO) << "error: " << error;
	
	if (abs(error) > 8)
	{
		setLeft(left);
		setRight(right);
	}
	else
	{
		if (getTh() < (2*M_PI/3.0) || getTh() > (-2*M_PI/3.0) || getTh() > (2*M_PI-4*M_PI/3.0))
		{
			setLeft(15);
			setRight(15);
		}
		else
		{
			setLeft(5);
				setRight(5);
			/*if(getY() < 0)
			{
				setLeft(4+2);
				setRight(4-2);
			}
			else
			{
				setLeft(4-2);
				setRight(4+2);
			}*/
		}
			
	}
}

void Robot::lookAndGoFlex(float x, float y)
{
	float dx = x-getX();
	float dy = y-getY();		
	float target_angle = atan2(dy,dx);
	static float alphaAck = 0.0;
	static float alphaAnt = 0.0;
	static float betaAck = 0.0;
	static float betaAnt = 0.0;
	
	float alpha = reduceAngle(this->getTh()-target_angle)*180/M_PI;
	float beta = 180-alpha;
	
	if(alpha >= beta)
	{
		alphaAck = alphaAck + alpha;
		
		int turn = 10*(alpha /*+ 0.00025*errorAck+(alpha-alphaAnt)*0.01*/)/180.0; //kp=8;
		alphaAnt=alpha;
		int fwd = 4;//7*(180-abs(error));//16-(dx*dx+dy*dy);
		
		int left = turn+fwd;//(error > 0) ? (turn+fwd) : (-turn+fwd);
		int right = -turn+fwd;//(error > 0) ? (-turn+fwd) : (turn+fwd);
		
		LOG(LEVEL_INFO) << "alpha: " << alpha;
		
		if (abs(alpha) > 8)
		{
			setLeft(left);
			setRight(right);
		}
		else
		{
			if (getTh() < (M_PI/2.0) || getTh() > (-M_PI/2.0) || getTh() > (3.0*M_PI/2.0))
			{
				setLeft(15);
				setRight(15);
			}
			else
			{
				setLeft(1);
				setRight(1);
			}
				
		}
	}
	else if(beta < alpha)
	{
		betaAck = betaAck + beta;
		
		int turn = -10*(beta + /*0.00025*errorAck+*/(beta-betaAnt)*0.01)/180.0; //kp=8;
		betaAnt=beta;
		int fwd = -4;//7*(180-abs(error));//16-(dx*dx+dy*dy);
		
		int left = turn+fwd;//(error > 0) ? (turn+fwd) : (-turn+fwd);
		int right = -turn+fwd;//(error > 0) ? (-turn+fwd) : (turn+fwd);
		
		LOG(LEVEL_INFO) << "beta: " << beta;
		
		if (abs(beta) > 8)
		{
			setLeft(left);
			setRight(right);
		}
		else
		{
			if (getTh() < (M_PI/2.0) || getTh() > (-M_PI/2.0) || getTh() > (3.0*M_PI/2.0))
			{
				setLeft(15);
				setRight(15);
			}
			else
			{
				setLeft(1);
				setRight(1);
			}
				
		}
	}
}

bool Robot::goAndStop(float x, float y)
{
	float dx = x-getX();
	float dy = y-getY();		
	float target_angle = atan2(dy,dx);
	static float errorAck = 0.0;
	static float errorAnt = 0.0;
	
	float d = sqrt(dx*dx+dy*dy);
	float t = reduceAngle(this->getTh()-target_angle)*180/M_PI;
	
	errorAck = errorAck + t;
	
	int turn = 10*(t + (t-errorAnt)*0.01)/180.0; //kp=8;
	errorAnt=t;
	int fwd = (15.0/75)*d;
	
	int left = turn+fwd;
	int right = -turn+fwd;
	
	if (d > 1.5)
	{
		LOG(LEVEL_INFO) << "d: " << d;
		LOG(LEVEL_INFO) << "t: " << t;
		
		setLeft(left);
		setRight(right);
	}
	else
	{
		LOG(LEVEL_INFO) << "x: " << getX();
		LOG(LEVEL_INFO) << "y: " << getY();
		
		stop();
		return true;
	}
	
	return false;
}
