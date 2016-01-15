#ifndef BALL_H
#define BALL_H

#include <cmath>

#include <ProcessLogger.h>

using namespace std;

#ifndef TO_RAD
#define TO_RAD M_PI/180;
#endif
#ifndef TO_DEG
#define TO_DEG 180/M_PI;
#endif

class Ball
{
  public:
	Ball();
  
	double getX();
	double getY();
	vector<double> getPosition();
	double getVelX();
	double getVelY();
	double getVel();
	double getVelAngle();
	
	void setX(double x);
	void setY(double y);
	void setVelX(double vx);
	void setVelY(double vy);
	void setVel(double vMod);
	void setVelAngle(double vAngle);
	
	void refreshState(double x, double y);
	
	int defineSquare();
	int defineField();
	
	bool nearWall();
	bool goal();
	
  private:
	double x, y;
	double vx, vy;
	double vMod, vAngle;
};

#endif
