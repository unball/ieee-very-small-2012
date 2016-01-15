#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include <Robot.h>
#include <Constants.h>
#include <Algebra.h>
#include <ProcessLogger.h>

#include <stdlib.h>
#include <math.h>
#include <vector>

class Robot; // Needs to be forward declared!

extern Ball ball;

bool defend(Robot &robot);
void alignRobotWithBall(Robot &robot);
double calculateDistanceToWalk(Robot &robot);
bool isRobotOutsideGoalBorder(Robot &robot);
bool isDistanceSignificant(double dY);
bool isBallDistanceInsideGoalBorder();

#endif // GOALKEEPER_H
