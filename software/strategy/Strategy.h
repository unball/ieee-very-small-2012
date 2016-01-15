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

#ifndef STRATEGY_H
#define STRATEGY_H

/**
 * @brief Bibliotecas utilizadas
 * 
 * Inclui todas as bibliotecas que serao utilizadas pelo
 * simulador
 */

#include <string>

#include <boost/thread.hpp>

// Keyboard listener

#ifdef __unix__
#include <termios.h>
#include <unistd.h>  
#endif // __unix__

#include <cassert>
#include <cstdio>

#include <Robot.h>
#include <Communicator.h>
#include <ProcessLogger.h>

// Strategy headers
#include <Goalkeeper.h>
#include <Algebra.h>
#include <Constants.h>
#include <Stack.h>

using namespace std;

class Robot; // Needs to be forward declared!

// Robot variables
extern Robot robot[6];
extern int n_robot; // Number of controlled robot

// Ball pose
extern double ball_x;
extern double ball_y;

// Communication variables to simulation module
extern Communicator* com_read;
extern Communicator* com_write;
extern bool can_write;

// UI variables
extern Stacks keys;

extern int actionIndex;
extern string command_buffer;

// Function declarations
void menu();

void startCommunication();
void loop();
void keyboardCommand();
void receivePoses();
void controller();
void sendVelocities();

#endif // STRATEGY_H

