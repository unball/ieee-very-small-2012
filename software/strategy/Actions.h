#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <ProcessLogger.h>

#include <Robot.h>
#include <Ball.h>
#include <Algebra.h>
#include <Constants.h>

#define NO_ANGLE 12345

class Robot; // Needs to be forward declared!

// Strategy variables
extern Ball ball;
extern Robot robot[6];

// Actions functions
bool pause(int pausedTimes);
bool penalty(int penaltyCharge);
bool goalKick(int goalKickCharge);

#endif
