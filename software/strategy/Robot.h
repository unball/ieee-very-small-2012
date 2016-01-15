/**
 * @file      Robot.h
 * @author    Tiago Pimentel Martins da Silva
 * @author    Matheus V. Portela
 * @author    Caio R. Có Soares
 * @date      22/08/2011
 *
 * @attention Copyright (C) 2011
 * @attention UnBall Robot Soccer Team
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Algebra.h>
#include <ProcessLogger.h>

using namespace std;

class Robot
{
    public:
        Robot();

        // Get attributes
        int getId();
        int getTeam();
        int getTacticPosition();
        
        double getX();
        double getY();
        double getTh();
        
        vector<double> getPose();
        vector<double> getPosition();
        
        int getLeft();
        int getRight();
        
        double getVel();
        double getRotVel();
        
        int getAction();
        
        // Set attributes
        void setTeam(int team);
        void setTacticPosition(int tacticPosition);
        
        void setX(double x);
        void setY(double y);
        void setTh(double th);
        
        void setLeft(int l);
        void setRight(int r);
        
        void setVel(double v);
        void setRotVel(double w);
        
        void setAction(int action);
        
        void removeAction();
        
        void printInfo();
        
        
        bool move(vector<double> target);
        bool move(double x, double y, double th);
        bool move(double distance);
        bool isMoveTargetReached(vector<double> target);
        bool turn(double angle);
        bool turnFast(double angle);
        bool isTurnTargetReached(double angle);
        bool stop();
        bool waitInDefense();
        bool goDefense(int square);
        bool waitInAttack();
        bool goToBall();
        bool kick();
        bool alignWithBallAndGoal();
        bool nearWall();
        bool avoidWall();
        
        bool lookAt(float x, float y);
		void goTo(float x, float y);
		void lookAndGo(float x, float y);
		bool goAndStop(float x, float y);
		void lookAndGoFlex(float x, float y);
    
    private:
        static int numberOfRobots;
        
        // Atributos de identificação
        int id;
        int team;
        int tacticPosition;
        
        // Atributos de localização
        double x, y, th;
        
        // Atributos de velocidade
        int l;
        int r;
        double v, w;
        
        // Atributos de controle
        int action;
};

#endif // ROBOT_H

