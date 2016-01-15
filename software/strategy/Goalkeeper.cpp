#include <Goalkeeper.h>

bool defend(Robot &robot)
{
    double angle = M_PI_2;
    
    if (robot.turn(angle))
        alignRobotWithBall(robot);
    
    return false; // never ends
}

void alignRobotWithBall(Robot &robot)
{
    double distance;
    
    //stop(robot); // just in case robot is still turning
    distance = calculateDistanceToWalk(robot);
    
    if (isBallDistanceInsideGoalBorder() && isDistanceSignificant(distance))
    {
        robot.move(distance);
    }
    else
        robot.stop();
}

double calculateDistanceToWalk(Robot &robot)
{
    double distance = ball.getY() - robot.getY();
		
	if (isRobotOutsideGoalBorder(robot))
		distance = 0;
    
    return distance;
}

bool isRobotOutsideGoalBorder(Robot &robot)
{
    double goalBorder = 0.1787;
    
    if (abs(robot.getY()) >= goalBorder)
        return true;
    else
        return false;
}

bool isDistanceSignificant(double distance)
{
    float threshold = 0.02;
    
    if (abs(distance) > threshold)
        return true;
    else
        return false;
}

bool isBallDistanceInsideGoalBorder()
{
    double goalBorder = 0.1787;
    
    if (abs(ball.getY()) < goalBorder)
        return true;
    else
        return false;
}
