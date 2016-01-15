#include <Algebra.h>

double calculateDistance(vector<double> point1, vector<double> point2)
{
    double dx = point2[0] - point1[0];
    double dy = point2[1] - point1[1];
    
    double distance = sqrt(dx*dx + dy*dy);
    
    return distance;
}

// Reduce angles to the range [M_PI, -M_PI[
double reduceAngle(double angle)
{
    while(angle < -M_PI)
        angle += 2*M_PI;
    while(angle >= M_PI)
        angle -= 2*M_PI;
    
    return angle;
}

double calculateAngleFromBallToGoal(int teamNumber)
{
    double goalX = CONST(GOAL_LENGTH_X);
    double goalY = 0;
    
    if (teamNumber == 1)
        goalX = -goalX;
        
    return atan2(goalY - ball.getY(), goalX - ball.getX());
}

bool checkObstacleInLine(vector<double> robot, vector<double> target, vector<double> possibleObstaclePosition)
{
	double a, b, distance;
	
	//get line
	//y = ax + b
	a = (target[1]-robot[1])/(target[0]-robot[0]);
	b = robot[1] - a*robot[0];
	 
	//get the line distance to the obstacle mass center 
	//d = |ax+by+c|/sqrt(a²+b²);
	distance = (abs(-a*possibleObstaclePosition[0] + possibleObstaclePosition[1] -b))/(sqrt(pow(a,2) + pow(b,2)));
	
	//see if distance is bigger than the robot width plus 10% (to be studied)
	if (distance > 0.083)
	{
		return false;
	}
	
	return true;
}
