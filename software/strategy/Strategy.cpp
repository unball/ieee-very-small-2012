/**
 * @file      Strategy.cpp
 * @author    André Luiz Siega Nepomuceno
 * @author    Gabriel Calache Cozendey
 * @author    George Andrew Brindeiro
 * @author    Marcos da Silva Pereira
 * @author    Vitor Barbosa Almeida
 * @date      18/10/2012
 *
 * @attention Copyright (C) 2012
 * @attention UnBall Robot Soccer Team
 */

#include <Strategy.h>
#include <Config.h>
#include <Keys.h>

// Robot variables
Robot robot[6];
Ball ball;

// Communication variables
Communicator* com_read;
Communicator* com_write;
bool can_write = false;

// UI variables
int n_robot = 0;
Stacks keys;
int v = 0;
int dv = 0;

bool paused = true;



int main (int argc, char **argv)
{
	
        LOG(LEVEL_INFO) << "\n\nUnBall Robot Soccer Team"
					<< "\nStrategy Module\n";
	
	InputKey input;
	
	boost::thread inputThread(input);

    menu();

	startCommunication();
	
	while(true)
		loop();

	return 0;
}

void menu()
{
	// Print controls for UI
	LOG(LEVEL_INFO) << "\nControls:\n"
                    << "\t'w' Forward\n"
			        << "\t's' Backward\n"
                    << "\t'd' Clockwise turn\n"
			        << "\t'a' Counterclockwise turn\n"
                    << "\t'p' Pause robots\n";
					/*<< "Plays:\n"
					<< "\t'z' Penalty kick\n"
                    << "\t'x' Goal kick";*/
}

void startCommunication()
{
        Config strategy_cfg("strategy.config");

	// Setup read/write channels
	LOG(LEVEL_DEBUG) << "Setup read/write channels" << endl;
        
        if(strategy_cfg.get("system_mode") == "online") 
        {
                //com_read = new Communicator(string("Vision"),string("Strategy"),READ);
                LOG(LEVEL_ERROR) << "Vision->Strategy not active (turned off in code)";
                com_write = new Communicator(string("Strategy"),string("Communication"),WRITE);
                
                LOG(LEVEL_DEBUG) << "Create com_write variables" << endl;
	
                char linear_name[6];
                char angular_name[6];
                
                for(int num_player = 0; num_player < 3; num_player++)
                {
                        // Build variable names
                        sprintf(linear_name, "p%dl", num_player);
                        sprintf(angular_name, "p%dr", num_player);
                        
                        // Create variables
                        com_write->create(string(linear_name));
                        com_write->create(string(angular_name));
                }
        }
        
        else
        {
                LOG(LEVEL_DEBUG) << "Setup read/write channels" << endl;
                com_read = new Communicator(string("Simulation"),string("Strategy"),READ);
                com_write  = new Communicator(string("Strategy"),string("Simulation"),WRITE);
                
                LOG(LEVEL_DEBUG) << "Create com_write variables" << endl;
	
                char linear_name[6];
                char angular_name[6];
                
                for(int num_team = 0; num_team < 2; num_team++)
                {
                        for(int num_player = 0; num_player < 3; num_player++)
                        {
                                // Build variable names
                                sprintf(linear_name, "t%dp%dv", num_team, num_player);
                                sprintf(angular_name, "t%dp%dw", num_team, num_player);
                                
                                // Create variables
                                com_write->create(string(linear_name));
                                com_write->create(string(angular_name));
                        }
                }
                
                com_write->create(string("simulation_command"));
        }

}

void loop()
{
	keyboardCommand();
	
	//if(com_read->ready())
	//{
		//receivePoses();
		////can_write = true;
	//}
	
	if (!paused)
		controller();
	
	if(com_write->ready()/* && can_write*/)
	{
		sendVelocities();
		can_write = false;
	}
}

void keyboardCommand()
{	
	char cmd;
	if(keys.pop(&cmd))
	{		
	    switch(cmd)
	    {
			// Joystick
		    case 'w': case 'W':
				{
					v++;
					
					int l = (v-dv);
					int r = (v+dv);
					
					if(l > 15 || l < -15 || r > 15 || r < -15)
					{
						v--;
						
						LOG(LEVEL_INFO) << "cannot saturate max v";
					}
					else
					{
						robot[n_robot].setLeft(l);
						robot[n_robot].setRight(r);
						LOG(LEVEL_INFO) << "v = " << v;
						LOG(LEVEL_INFO) << "l = " << l;
						LOG(LEVEL_INFO) << "r = " << r;
					}
				}
				break;
		
		    case 's': case 'S':
				{
					v--;
					
					int l = (v-dv);
					int r = (v+dv);
					
					if(l > 15 || l < -15 || r > 15 || r < -15)
					{
						v++;
						
						LOG(LEVEL_INFO) << "cannot saturate min v";
					}
					else
					{
						robot[n_robot].setLeft(l);
						robot[n_robot].setRight(r);
						LOG(LEVEL_INFO) << "v = " << v;
						LOG(LEVEL_INFO) << "l = " << l;
						LOG(LEVEL_INFO) << "r = " << r;
					}
				}
				break;
		
		    case 'd': case 'D':
				{
					dv--;
					
					int l = (v-dv);
					int r = (v+dv);
					
					if(l > 15 || l < -15 || r > 15 || r < -15)
					{
						dv++;
						
						LOG(LEVEL_INFO) << "cannot saturate min dv";
					}
					else
					{
						robot[n_robot].setLeft(l);
						robot[n_robot].setRight(r);
						LOG(LEVEL_INFO) << "dv = " << dv;
						LOG(LEVEL_INFO) << "l = " << l;
						LOG(LEVEL_INFO) << "r = " << r;
					}
				}
			    break;
		
		    case 'a': case 'A':
				{
					dv++;
					
					int l = (v-dv);
					int r = (v+dv);
					
					if(l > 15 || l < -15 || r > 15 || r < -15)
					{
						dv--;
						
						LOG(LEVEL_INFO) << "cannot saturate max dv";
					}
					else
					{
						robot[n_robot].setLeft(l);
						robot[n_robot].setRight(r);
						LOG(LEVEL_INFO) << "v = " << v;
						LOG(LEVEL_INFO) << "l = " << l;
						LOG(LEVEL_INFO) << "r = " << r;
					}
				}
			    break;
			
		    // Choose which robot to control
		    case '0': case '1': case '2':
		    case '3': case '4': case '5':
			    n_robot = cmd - '0';
			    LOG(LEVEL_INFO) << "Controling robot " << n_robot;
			    break;
		
		    // Restart system
		    case 'r': case 'R':
                LOG(LEVEL_INFO) << "Not done yet";
			    break;
            
            // Pause
            case 'p': case 'P':
                paused = !paused;
                LOG(LEVEL_INFO) << "PAUSED = " << paused;
                
                if (paused)
					for (int i = 0; i<3; i++)
						robot[i].stop();
			    break;
			    
            default:
                LOG(LEVEL_INFO) << "key " << cmd;
	    }
    }
}

void receivePoses()
{
	// LogLevel log_level = LEVEL_DEBUG;
	
	LOG(log_level) << "Receive poses";
	
	string str_buffer;
	double new_x;
	double new_y;
	double new_th;

	char x_name[6];
	char y_name[6];
	char t_name[6];
	
	for(int num_team = 0; num_team < 2; num_team++)
	{
		for(int num_player = 0; num_player < 3; num_player++)
		{
			// Build variable names
			sprintf(x_name, "t%dp%dx", num_team, num_player);
			sprintf(y_name, "t%dp%dy", num_team, num_player);
			sprintf(t_name, "t%dp%dt", num_team, num_player);
			
			// Read x position
			(*com_read) >> IN(string(x_name), &str_buffer);
			new_x = atof(str_buffer.c_str());
			
			// Read y position
			(*com_read) >> IN(string(y_name), &str_buffer);
			new_y = atof(str_buffer.c_str());
			
			// Read theta angle
			(*com_read) >> IN(string(t_name), &str_buffer);
			new_th = atof(str_buffer.c_str());
			
			// Change robot's current pose
			// (num_team*3) + num_player goes from 0 to 5
			robot[(num_team*3) + num_player].setX(new_x);
			robot[(num_team*3) + num_player].setY(new_y);
			robot[(num_team*3) + num_player].setTh(new_th);
			
            LOG(log_level) << "Team " << num_team << " Player " << num_player;
			LOG(log_level) << "X = " << new_x;
			LOG(log_level) << "Y = " << new_y;
			LOG(log_level) << "Th = " << new_th;
		}
	}
	
	// Read ball x position
	(*com_read) >> IN(string("ball_x"), &str_buffer);
	new_x = atof(str_buffer.c_str());
	
	// Read ball y position
	(*com_read) >> IN(string("ball_y"), &str_buffer);
	new_y = atof(str_buffer.c_str());
	
    LOG(log_level) << "Ball ";
	LOG(log_level) << "X = " << new_x;
	LOG(log_level) << "Y = " << new_y;

    ball.refreshState(new_x, new_y);
	
	com_read->done();
}

int stop_count[3] = {0,0,0};

float x_old[3] = {0.0,0.0,0.0};
float y_old[3] = {0.0,0.0,0.0};
float t_old[3] = {0.0,0.0,0.0};

void controller()
{
	/* EVERYONE'S CODE HERE */
	
	/* POSITIONS */
	
	LOG(LEVEL_INFO) << "Ball: " << ball.getX() << " " << ball.getY();
	LOG(LEVEL_INFO) << "Purple Robot: " << robot[0].getX() << " " << robot[0].getY() << " " << robot[0].getTh();
	LOG(LEVEL_INFO) << "Green Robot: " << robot[1].getX() << " " << robot[1].getY() << " " << robot[1].getTh();
	LOG(LEVEL_INFO) << "Red Robot: " << robot[2].getX() << " " << robot[2].getY() << " " << robot[2].getTh();
	LOG(LEVEL_INFO) << "Robot 0: " << robot[0].getLeft() << " " << robot[0].getRight();
        LOG(LEVEL_INFO) << "Robot 1: " << robot[1].getLeft() << " " << robot[1].getRight();
        LOG(LEVEL_INFO) << "Robot 2 " << robot[2].getLeft() << " " << robot[2].getRight();
	/* MAIN */
	
	// Spin goalie
	//robot[0].setLeft(-15);
	//robot[0].setRight(15);
	
    // (Marcos) Testes Semana de Extensao
	//robot[1].goTo(25, 0);    
	//robot[1].goTo(120, 0);    
	//robot[1].goTo(25, 75);    
	//robot[1].goTo(25, 65);    
	//robot[1].setRight(0);
	//robot[2].setLeft(-1);
	//robot[2].setRight(0);
        //robot[3].setLeft(-1);
	//robot[3].setRight(0);
        //robot[4].turn(30);
        
        
        
        robot[1].setRotVel(2);
        robot[2].setVel(1);
        //robot[1].setRight(1);
	
        //robot[1].lookAt(25,0);
        
        //robot[1].lookAndGo(ball.getX(), ball.getY());


//	robot[1].lookAndGo(ball.getX(), ball.getY());
//	robot[2].lookAndGo(ball.getX(), ball.getY());
	// Update stop count
	//for(int i = 0; i < 3; i++)
	//{
		//float dx = robot[i].getX()-x_old[i];
		//float dy = robot[i].getY()-y_old[i];
		//float d = sqrt(dx*dx+dy*dy);
		//float t = abs(robot[i].getTh()-t_old[i]);
		
		//if(d < 0.03 && t < M_PI/8.0)
			//stop_count[i] += 1;
		//else
			//stop_count[i] = 0;
		
		//x_old[i] = robot[i].getX();
		//y_old[i] = robot[i].getY();
		//t_old[i] = robot[i].getTh();
	//}

	//float dx1 = robot[1].getX()-ball.getX();
	//float dy1 = robot[1].getY()-ball.getY();
	//float d1 = sqrt(dx1*dx1+dy1*dy1);
	
	//float dx2 = robot[2].getX()-ball.getX();
	//float dy2 = robot[2].getY()-ball.getY();
	//float d2 = sqrt(dx2*dx2+dy2*dy2);

	//if(d1 < d2)
	//{
		//if(stop_count[1] < 3000)
			//robot[1].lookAndGo(ball.getX(),ball.getY());
		//else
		//{
			//robot[1].setLeft(-15);
			//robot[1].setRight(-15);
		//}
	//}
	//else
	//{
		//if(robot[1].getX() > -20)
			//robot[1].lookAndGo(-30,50);
		//else
			//robot[1].stop();//goAndStop(-40,0.0);
	//}
		
	//if(d2 < d1)
	//{
		//if(stop_count[2] < 3000)
			//robot[2].lookAndGo(ball.getX(),ball.getY());
		//else
		//{
			//robot[2].setLeft(-15);
			//robot[2].setRight(-15);
		//}
	//}
	//else
	//{
		//if(robot[2].getX() > -20)
			//robot[2].lookAndGo(-30,-50);
		//else
			//robot[2].stop();//goAndStop(-40,0.0);
	//}
	//Goalkeeper
//	if(stop_count[0] < 3000)
//	{
    
//		if (ball.getX() < -40 && (robot[0].getX() < -50 || robot[0].getY() < 20|| robot[0].getY() > -20))
//			robot[0].lookAndGo(ball.getX(),ball.getY());
//		else robot[0].lookAndGo(-55,0.0);
//	}
//	else
//	{
//		robot[0].setLeft(-15);
//		robot[0].setRight(-15);
//	}
	
	/*if (ball.getY() < 0)
	{
		robot[0].setLeft(-15);
		robot[0].setRight(15);
	}
	else
	{
		robot[0].setLeft(15);
		robot[0].setRight(-15);
	}*/
	
	/* GO AND STOP */
	
	//robot[1].goAndStop(75.0,0);
	
	/* LOOK AND GOS */
	
	//robot[0].lookAndGo(ball.getX(),ball.getY());
	//robot[1].lookAndGo(ball.getX(),ball.getY());
	//robot[2].lookAndGo(ball.getX(),ball.getY());
	
	/* PENALTY KICKS? */
	
	/*robot[0].setLeft(15);
	robot[0].setRight(-15);*/
	
	//robot[1].setLeft(15);
	//robot[1].setRight(15);
	//robot[2].setLeft(15);
	//robot[2].setRight(15);
	
	/* MISC OLD SHIT */
	
	/*float dx = robot[1].getX()-ball.getX();
	float dy = robot[1].getY()-ball.getY();
	float d1 = dx*dx+dy*dy;
	
	dx = robot[2].getX()-ball.getX();
	dy = robot[2].getY()-ball.getY();
	float d2 = dx*dx+dy*dy;
	
	if (d1 < d2)
	{
		robot[1].goTo(ball.getX(),ball.getY());
		robot[2].stop();
	}
	else
	{
		robot[2].goTo(ball.getX(),ball.getY());
		robot[1].stop();
	}*/
	
	/*for(int i = 1; i < 3;0 i++)
	{
		int dx = abs(robot[i].getX()-x_old[i]);
		int dy = abs(robot[i].getY()-y_old[i]);
		int d = dx*dx+dy*dy;
		int t = abs(robot[i].getTh()-t_old[i]);
		
		if(d < 0.01 && t < M_PI/12.0)
			stop_count[i] += 1;
		else
			stop_count[i] = 0;
		
		x_old[i] = robot[i].getX();
		y_old[i] = robot[i].getY();
		t_old[i] = robot[i].getTh();
		
		//if(stop_count[i] < 100)
		if (true)
			robot[i].goTo(ball.getX(),ball.getY());
		else
		{
			robot[i].setLeft(-5);
			robot[i].setRight(-5);
		}
	}*/
	
	//robot[0].lookAt(ball.getX(),ball.getY());
	//robot[2].goalie(1,ball.getY());
	
	
}

void sendVelocities()
{
	Config strategy_cfg("strategy.config");

	// LogLevel log_level = LEVEL_DEBUG;

	LOG(log_level) << "Send velocities";

	char str_buffer[22];
	char linear_name[6];
	char angular_name[6];

	if(strategy_cfg.get("system_mode") == "online")
	{
		for(int num_player = 0; num_player < 3; num_player++)
		{
			// Build variable names
			sprintf(linear_name, "p%dl", num_player);
			sprintf(angular_name, "p%dr", num_player);

			// Stuff left velocity into buffer and write to communicator
			sprintf(str_buffer,"%d",robot[num_player].getLeft());
			(*com_write) << OUT(string(linear_name), string(str_buffer));

			// Stuff right velocity into buffer and write to communicator
			sprintf(str_buffer,"%d",robot[num_player].getRight());
			(*com_write) << OUT(string(angular_name), string(str_buffer));

			LOG(log_level) << "Player " << num_player;
			LOG(log_level) << "L = " << robot[num_player].getLeft();
			LOG(log_level) << "R = " << robot[num_player].getRight();
		}
	}
	else
	{
		for(int num_team = 0; num_team < 2; num_team++)
		{
			for(int num_player = 0; num_player < 3; num_player++)
			{
				// Build variable names
				sprintf(linear_name, "t%dp%dv", num_team, num_player);
				sprintf(angular_name, "t%dp%dw", num_team, num_player);

				// Stuff linear velocity into buffer and write to communicator
				sprintf(str_buffer,"%20.4f",robot[num_player].getVel());
				(*com_write) << OUT(string(linear_name), string(str_buffer));

				// Stuff angular velocity into buffer and write to communicator
				sprintf(str_buffer,"%20.4f",robot[num_player].getRotVel());
				(*com_write) << OUT(string(angular_name), string(str_buffer));

				LOG(log_level) << "Player " << num_player;
				LOG(log_level) << "L = " << robot[num_player].getLeft();
				LOG(log_level) << "R = " << robot[num_player].getRight();
			}
		}
	}

	com_write->done();
}
