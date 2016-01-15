#ifndef ALGEBRA_H
#define ALGEBRA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <Constants.h>
#include <Ball.h>
#include <ProcessLogger.h>
#include <Strategy.h>

using namespace std;

class Robot; // Needs to be forward declared!

extern Ball ball;
extern double dt;
extern Robot robot[6];

double calculateDistance(vector<double> point1, vector<double> point2);
double reduceAngle(double angle);
double calculateAngleFromBallToGoal(int teamNumber);
bool checkObstacleInLine(vector<double> robot, vector<double> target, vector<double> possibleObstaclePosition);

#endif
