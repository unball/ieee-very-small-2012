#include <Actions.h>

/*
 * Play1 consists in one set of actions for one robot.
 */
bool pause(int pausedTimes)
{
	robot[0].stop();
	robot[1].stop();
	robot[2].stop();
	
	if((pausedTimes % 2) == 0)
		return true;
	else
		return false;
}
	
	/*static int moveIndex = 0;
	
   if ((moveIndex == 0) && (robot[1].move(-0.2, -0.2, M_PI)))
		moveIndex = 1;
	
	
	if ((moveIndex == 1) && (robot[1].move(-0.2, 0.2, NO_ANGLE)))
		moveIndex = 2;
		
	if ((moveIndex == 2) && (robot[1].move(0.2, 0.2, -M_PI)))
		moveIndex = 3;
		
	if ((moveIndex == 3) && (robot[1].kick()))
		moveIndex = 4;
	
	
	// finish play
	if (moveIndex == 4)
	{
		robot[1].stop();
		moveIndex = 0;
		return true;
	}
	
	return false;
}*/

/*
 * Play2 consists in one action for different robots
 */
bool penalty(int penaltyCharge)
{
	robot[0].stop();
	robot[1].stop();
	robot[2].stop();
	
	if((penaltyCharge % 2) == 0)
	{
		if(robot[1].kick())	
			return true;
	}
	else
		return false;
}
	
	
	
	/*static int moveIndex = 0;
	bool moveReturn1, moveReturn2;
	
	if (moveIndex == 0)
	{
		moveReturn1 = robot[0].move(-0.4, 0.2, -M_PI);
		moveReturn2 = robot[1].move(-0.2, 0.2, NO_ANGLE);
		
		if (moveReturn1 && moveReturn2)
			moveIndex = 1;
	}

	if ((moveIndex == 1) && (robot[4].move(-0.2, -0.2, NO_ANGLE)))
		moveIndex = 2;
	
	if ((moveIndex == 2) && (robot[5].move(0, 0, M_PI)))
		moveIndex = 3;
	
	// finish play
	if (moveIndex == 3)
	{
		moveIndex = 0;
		return true;
	}
	
	return false;
}*/

bool goalKick(int goalKickCharge)
{
	
	vector<double> targetPositionRobot0(3);
    vector<double> targetPositionRobot1(3);
    
    targetPositionRobot0[0] = -CONST(FIELD_WIDTH) / 4;
    targetPositionRobot0[1] = 0.325;
    targetPositionRobot0[2] = 0;
    
	targetPositionRobot1[0] = -CONST(FIELD_WIDTH) / 4;
    targetPositionRobot1[1] = -0.325;
    targetPositionRobot1[2] = 0;
    
	robot[0].move(targetPositionRobot0);
	robot[1].move(targetPositionRobot1);

    if((goalKickCharge % 2) == 0)
	{
		if(robot[2].kick())
			return true;
	}
	else
		return false;
}
	/*static int moveIndex = 0;
	
	if ((moveIndex == 0) && (robot[0].kick()))
	{
		moveIndex = 1;
	}
	
	if ((moveIndex == 1) && (robot[3].kick()))
	{
		moveIndex = 2;
	}
	
	if (moveIndex == 2)
	{
		moveIndex = 0;
		return true;
	}
	
	return false;
}*/
