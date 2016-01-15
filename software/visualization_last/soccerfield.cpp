/*
    @file soccerfield.cpp

    @contributor	William Batista Aguiar Motta	@email yosoyninja@gmail.com

    @attention Copyright (C) 2013
    @attention UnBall Robot Soccer Team

       Este programa é um software livre; você pode redistribui-lo e/ou
    modifica-lo dentro dos termos da Licença Pública Geral GNU como
    publicada pela Fundação do Software Livre (FSF); na versão 2 da
    Licença, ou (na sua opnião) qualquer versão.

    Este programa é distribuido na esperança que possa ser  util,
    mas SEM NENHUMA GARANTIA; sem uma garantia implicita de ADEQUAÇÂO a qualquer
    MERCADO ou APLICAÇÃO EM PARTICULAR. Veja a
    Licença Pública Geral GNU para maiores detalhes.

    Você deve ter recebido uma cópia da Licença Pública Geral GNU
    junto com este programa, se não, escreva para a Fundação do Software
    Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QShortcut>
#include <QVBoxLayout>
#include <QWidget>

#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>

#include <QDateTime>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "soccerfield.h"
#include <ios>
#include <iostream>
using namespace std;

#include <fstream>

ifstream myReadFile;
ofstream outdata;
ofstream outPos;
bool append=false;
char arqName[]="jogoArq.dat", fileName[]="jogo.dat";
unsigned long int ponto=0, ponto2=0, ponto3=3;
int w_bx, w_by;
int w_ry[3], w_rx[3], w_rt[3];
int w_iy[3], w_ix[3], w_it[3];

SoccerField::SoccerField(QWidget *parent)
    : QWidget(parent)
{
    printf("olá mundo!");
    //tempo e posições iniciais
    tempo=0;
    loadPos("poses.dat", 0, true);

    //modos iniciais
    jogoIniciado=false;
    manual = true;
    simulador = true;

    //nada pressionado
    ballPressed=false;
    robotPressed=0;
    enemyPressed=0;

    // Inicializa área de desenho
    setPalette(QPalette(QColor(Qt::gray)));
    setAutoFillBackground(true);

    // Inicializa timer para redesenho, que chama a função getPositions() de tempos em tempos
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer->start(MILISEC);
}

 unsigned long int SoccerField::loadPos(char read[30], unsigned long int p, bool fwd) {

     char id[10], s[10];
     int n;

     //abre arquivo e procura posicao inicial
     ifstream in;
     in.open(read);
     in.seekg(p);

     //loop de leitura
     if (in.is_open()) {
         while (!in.eof()) {
             if(!fwd) {
                 for(int i=0; i<10; i++){
                     in.unget();
                     p=in.tellg();
                     if (p==0)
                         break;
                     char c = in.peek();
                     printf("|%c|",c);
                     if (c=='#')
                         break;
                 }
                 p=in.tellg();
             }

             in >> id;
             in >> s;
             n = atoi(s);
             int i = id[2]-'0';
             switch (id[0]) {
             case 't':
                 if(p!=0) tempo=n+1;
                 break;
             case 'r':
                 if(id[1]=='x') { robot_x[i] = n; }
                 else if(id[1]=='y') { robot_y[i] = n; }
                 else if(id[1]=='t') { robot_theta[i] = n; }
                 break;
             case 'i':
                 if(id[1]=='x') { enemy_x[i] = n; }
                 else if(id[1]=='y') { enemy_y[i] = n; }
                 else if(id[1]=='t') { enemy_theta[i] = n; }
                 break;
             case 'b':
                 if(id[1]=='x') { ball_x = n; }
                 else if(id[1]=='y') { ball_y = n; }
                 break;
             case 'f':
                 if(fwd) p = in.tellg();
                 in.close();
                 update();
                 return p;
             }
         }
     }
     if(in.is_open())
         in.close(); //final alternativo
     return p;
 }

 void SoccerField::savePos(char write[30], bool n) {

     //abre arquivo
     ofstream out;
     if(n) out.open(write, ios::app);
     else out.open(write);

     //msg de erro se out nao for encontrado
     if( !out ) { cerr << "Error: file could not be opened" << endl; return; }

     //escreve
     out << " t " << tempo << endl;
     for(int i=0; i<3; i++){
         out << "rx" << i << " " << robot_x[i] << " ry" << i << " " << robot_y[i] << " rt" << i << "  " << robot_theta[i]  << " ";
         out << "ix" << i << "  " << enemy_x[i] << " iy" << i << "  " << enemy_y[i] << " it" << i << "  " << enemy_theta[i]  << " ";
         w_rx[i]=robot_x[i]; w_ry[i]=robot_y[i]; w_rt[i]=robot_theta[i];
         w_ix[i]=enemy_x[i]; w_iy[i]=enemy_y[i]; w_it[i]=enemy_theta[i];
     }
     out << "bx " << ball_x << " by " << ball_y << " ";
     w_bx = ball_x; w_by = ball_y;
     out << "f # " << endl;

     //fecha arquivo
     out.close();
 }


 void SoccerField::readPositions() {
     if(jogoIniciado) {
         ponto3=ponto2;
         ponto2=loadPos(arqName, ponto2, true);
         if(ponto2==ponto3) endGame();
     }
 }

 void SoccerField::getPose() {
     if(!simulador)
         readPositions();
     else
         tempo++;
     if(tempo%DIVSEC == 0)
         emit timer();
     //get positions...
     update();
 }

 void SoccerField::getPositions()
 {
     if (simulador && jogoIniciado) {
         savePos(fileName, append);
         append=true;
     }
     if(!manual) {
         getPose();
     }
 }

 void SoccerField::copyThis(char read[30], char write[30]) {
     ofstream out;
     ifstream in;
     out.open(write);
     in.open(read);
     char output[100];
     if (in.is_open()) {
         while (!in.eof()) {
             in >> output;
             if(out) { out << output << " ";
                 if(output[0]=='#') { out << endl; }
             }
         }
     }
     if( !out ) cerr << "Error: file could not be opened" << endl;
     in.close();
     out.close();
 }

 void SoccerField::goalEvent(QEvent *event)
 {

     QRect leftGoal(FIELD_LEFT-GOAL_WIDTH, (HEIGHT-GOAL_HEIGHT)/2, GOAL_WIDTH, GOAL_HEIGHT);
     QRect rightGoal(FIELD_RIGHT, (HEIGHT-GOAL_HEIGHT)/2, GOAL_WIDTH, GOAL_HEIGHT);

     if(event->Timer)
     {
         if(leftGoal.contains(ball_x, ball_y))
         {
             goal = 0;
             ball_x = 0;
             ball_y = 0;

         }
         else if(rightGoal.contains(ball_x, ball_y))
         {
             goal = 1;
             ball_x = 0;
             ball_y = 0;

         }

         else goal = 2;

     }
 }

 int SoccerField::goalDisplay()
 {

     if(goal == 1 || goal == 0)
     {
         return goal;
     }
     else return 2;

 }

 void SoccerField::restartGame()
 {
     endGame();
     jogoIniciado=true;
     manual = false;
     tempo=0;
 }

 void SoccerField::endGame()
 {
     //mandar msg pro simulador parar o jogo
     //pular para o final se estiver no modo arquivo
     ponto2=0;
     append = false;
     jogoIniciado = false;
     manual = true;
 }

 //eventos do mouse
 void SoccerField::mousePressEvent(QMouseEvent *event)
 {
     if (!manual) return;

     if (event->button() == Qt::RightButton) {
         robotRightPressed = robotHit(event->pos());
         if (robotRightPressed==0) enemyRightPressed = enemyHit(event->pos());
     }

     if (event->button() == Qt::LeftButton) {

         if (ballHit(event->pos())) ballPressed = true;
         else {
             robotPressed = robotHit(event->pos());
             if (robotPressed==0) enemyPressed = enemyHit(event->pos());
         }

     }
 }

 void SoccerField::mouseMoveEvent(QMouseEvent *event)
 {
     if (ballPressed) {
         QPoint pos = event->pos();
         ball_x=aXPOS(pos.x());
         ball_y=aYPOS(pos.y());
         update();
     }
     else if (robotPressed>0) {
         QPoint pos = event->pos();
         robot_x[robotPressed-1]=aXPOS(pos.x());
         robot_y[robotPressed-1]=aYPOS(pos.y());
         update();
     }
     else if (enemyPressed>0) {
         QPoint pos = event->pos();
         enemy_x[enemyPressed-1]=aXPOS(pos.x());
         enemy_y[enemyPressed-1]=aYPOS(pos.y());
         update();
     }
     else if (enemyRightPressed>0) {
         QPoint pos = event->pos();
         int i = enemyRightPressed-1;
         double rad = atan2((YPOS(enemy_y[i])-pos.y()),(XPOS(enemy_x[i])-pos.x()));
         enemy_theta[i]=ANGLE(qRound(rad * 180 / 3.14159265));
         update();
     }
     else if (robotRightPressed>0) {
         QPoint pos = event->pos();
         int i = robotRightPressed-1;
         double rad = atan2((YPOS(robot_y[i])-pos.y()),(XPOS(robot_x[i])-pos.x()));
         robot_theta[i]=ANGLE(qRound(rad * 180 / 3.14159265));
         update();
     }
 }

 void SoccerField::mouseReleaseEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::RightButton) {
         robotRightPressed = 0;
         enemyRightPressed = 0;
     } else
         if (event->button() == Qt::LeftButton) {
             ballPressed = false;
             robotPressed = 0;
             enemyPressed = 0;
         }
 }

 //detecta se o mouse esta sobre o objeto (bola, robo ou inimigo)
 bool SoccerField::ballHit(const QPoint &pos) const
 {
     QRect bola = QRect(XPOS(ball_x)-BALL_DIAM/2, YPOS(ball_y)-BALL_DIAM/2, BALL_DIAM, BALL_DIAM);
     return bola.contains(pos);
 }

 char SoccerField::robotHit(const QPoint &pos) const
 {
     QRect robo;
     for(int i=2;i>=0;i--){
         robo = QRect(XPOS(robot_x[i])-ROBOT_WIDTH/2, YPOS(robot_y[i])-ROBOT_HEIGHT/2, ROBOT_WIDTH, ROBOT_HEIGHT);
         QMatrix matrix;
         matrix.translate(XPOS(robot_x[i]), YPOS(robot_y[i]));
         matrix.rotate(-robot_theta[i]);
         QPoint pos2 = QPoint( ( pos.x() - XPOS(robot_x[i]) ), ( pos.y() - YPOS(robot_y[i]) ));
         if (robo.contains(matrix.map(pos2))) return i+1;
     }
     return 0;
 }

 char SoccerField::enemyHit(const QPoint &pos) const
 {
     QRect inimigo;
     for(int i=2;i>=0;i--){
         QRect inimigo = QRect(XPOS(enemy_x[i])-ENEMY_WIDTH/2, YPOS(enemy_y[i])-ENEMY_HEIGHT/2, ENEMY_WIDTH, ENEMY_HEIGHT);
         QMatrix matrix;
         matrix.translate(XPOS(enemy_x[i]), YPOS(enemy_y[i]));
         matrix.rotate(-enemy_theta[i]);
         QPoint pos2 = QPoint( ( pos.x() - XPOS(enemy_x[i]) ), ( pos.y() - YPOS(enemy_y[i]) ));
         if (inimigo.contains(matrix.map(pos2))) return i+1;
     }
     return 0;
 }

 /** A partir daqui... desenho do campo **////
 void SoccerField::paintEvent(QPaintEvent * /* event */)
 {
     QPainter painter(this);

     drawField(painter);
     drawRobots(painter);
     drawBall(painter);
 }


 inline void SoccerField::drawField(QPainter &painter)
 {

     painter.setRenderHint(QPainter::Antialiasing);

     // Linhas brancas com espessura LINE_THICKNESS, preenchimento verde
     painter.setPen(QPen(Qt::white, LINE_THICKNESS));
     painter.setBrush(Qt::green);

     // Desenho do campo (posicionado para respeitar as bordas)
     painter.drawRect(FIELD_BORDER, FIELD_BORDER, FIELD_WIDTH, FIELD_HEIGHT);

     // Desenho dos gols
     painter.drawRect(FIELD_LEFT-GOAL_WIDTH, (HEIGHT-GOAL_HEIGHT)/2, GOAL_WIDTH, GOAL_HEIGHT);
     painter.drawRect(FIELD_RIGHT, (HEIGHT-GOAL_HEIGHT)/2, GOAL_WIDTH, GOAL_HEIGHT);

     // Desenho das áreas
     painter.drawArc(FIELD_LEFT, (HEIGHT-AREA_ARC_HEIGHT)/2, AREA_ARC_WIDTH, AREA_ARC_HEIGHT, ANGLE16TH(-90), ANGLE16TH(180));
     painter.drawRect(FIELD_LEFT, (HEIGHT-AREA_HEIGHT)/2, AREA_WIDTH, AREA_HEIGHT);

     painter.drawArc(FIELD_RIGHT-AREA_ARC_WIDTH, (HEIGHT-AREA_ARC_HEIGHT)/2, AREA_ARC_WIDTH, AREA_ARC_HEIGHT, ANGLE16TH(90), ANGLE16TH(180));
     painter.drawRect(FIELD_RIGHT-AREA_WIDTH, (HEIGHT-AREA_HEIGHT)/2, AREA_WIDTH, AREA_HEIGHT);

     // Desenho da linha de meio de campo e círculo central
     painter.drawLine(WIDTH/2, FIELD_TOP, WIDTH/2, FIELD_BOTTOM);
     painter.drawArc((WIDTH-CIRCLE_DIAM)/2, (HEIGHT-CIRCLE_DIAM)/2, CIRCLE_DIAM, CIRCLE_DIAM, ANGLE16TH(0), ANGLE16TH(360));

     // Desenho dos cantos, preenchimento branco
     painter.setBrush(Qt::white);

     static const QPointF corner[3] = {
         QPointF(0, 0),
         QPointF(CORNER_RAD, 0),
         QPointF(0,CORNER_RAD),
     };

     // Canto Superior Esquerdo
     painter.translate(FIELD_BORDER,FIELD_BORDER);
     painter.drawPolygon(corner,3);

     // Canto Superior Direito
     painter.translate(FIELD_WIDTH,0);
     painter.rotate(90);
     painter.drawPolygon(corner,3);

     // Canto Inferior Direito
     painter.translate(FIELD_HEIGHT,0);
     painter.rotate(90);
     painter.drawPolygon(corner,3);

     // Canto Inferior Esquerdo
     painter.translate(FIELD_WIDTH,0);
     painter.rotate(90);
     painter.drawPolygon(corner,3);

     painter.resetTransform();

     // Desenho das marcas do campo

     // Free-Kick/Penalty-Kick Lines
     static const QLineF FK_PK[4] = {

         QLineF(MARK_PK_LEFT-MARK_WIDTH/2, MARK_PK_CENTER, MARK_PK_LEFT+MARK_WIDTH/2, MARK_PK_CENTER),
         QLineF(MARK_PK_LEFT, MARK_PK_CENTER-MARK_HEIGHT/2, MARK_PK_LEFT, MARK_PK_CENTER+MARK_HEIGHT/2),
         QLineF(MARK_PK_RIGHT-MARK_WIDTH/2, MARK_PK_CENTER, MARK_PK_RIGHT+MARK_WIDTH/2, MARK_PK_CENTER),
         QLineF(MARK_PK_RIGHT, MARK_PK_CENTER-MARK_HEIGHT/2, MARK_PK_RIGHT, MARK_PK_CENTER+MARK_HEIGHT/2),

     };

     painter.drawLines(FK_PK,4);

     // Free-Ball Lines
     static const QLineF FB[8] = {

         QLineF(MARK_FB_LEFT-MARK_WIDTH/2, MARK_FB_TOP, MARK_FB_LEFT+MARK_WIDTH/2, MARK_FB_TOP),
         QLineF(MARK_FB_LEFT, MARK_FB_TOP-MARK_HEIGHT/2, MARK_FB_LEFT, MARK_FB_TOP+MARK_HEIGHT/2),
         QLineF(MARK_FB_LEFT-MARK_WIDTH/2, MARK_FB_BOTTOM, MARK_FB_LEFT+MARK_WIDTH/2, MARK_FB_BOTTOM),
         QLineF(MARK_FB_LEFT, MARK_FB_BOTTOM-MARK_HEIGHT/2, MARK_FB_LEFT, MARK_FB_BOTTOM+MARK_HEIGHT/2),
         QLineF(MARK_FB_RIGHT-MARK_WIDTH/2, MARK_FB_TOP, MARK_FB_RIGHT+MARK_WIDTH/2, MARK_FB_TOP),
         QLineF(MARK_FB_RIGHT, MARK_FB_TOP-MARK_HEIGHT/2, MARK_FB_RIGHT, MARK_FB_TOP+MARK_HEIGHT/2),
         QLineF(MARK_FB_RIGHT-MARK_WIDTH/2, MARK_FB_BOTTOM, MARK_FB_RIGHT+MARK_WIDTH/2, MARK_FB_BOTTOM),
         QLineF(MARK_FB_RIGHT, MARK_FB_BOTTOM-MARK_HEIGHT/2, MARK_FB_RIGHT, MARK_FB_BOTTOM+MARK_HEIGHT/2),

     };

     painter.drawLines(FB,8);

     // Free-Ball Robot Positions
     painter.setBrush(Qt::gray);

     painter.drawEllipse(MARK_FB_LEFT-MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_TOP-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);
     painter.drawEllipse(MARK_FB_LEFT+MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_TOP-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);
     painter.drawEllipse(MARK_FB_LEFT-MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_BOTTOM-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);
     painter.drawEllipse(MARK_FB_LEFT+MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_BOTTOM-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);
     painter.drawEllipse(MARK_FB_RIGHT-MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_TOP-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);
     painter.drawEllipse(MARK_FB_RIGHT+MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_TOP-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);
     painter.drawEllipse(MARK_FB_RIGHT-MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_BOTTOM-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);
     painter.drawEllipse(MARK_FB_RIGHT+MARK_FB_ROBOT-MARK_DIAM/2, MARK_FB_BOTTOM-MARK_DIAM/2, MARK_DIAM, MARK_DIAM);

 }

 inline void SoccerField::drawRobots(QPainter &painter)
 {
     for(int i=0; i < 3; i++){

         drawRobot(painter, i, XPOS(robot_x[i]), YPOS(robot_y[i]), robot_theta[i]);
         drawEnemy(painter, i, XPOS(enemy_x[i]), YPOS(enemy_y[i]), enemy_theta[i]);

     }

 }

 inline void SoccerField::drawRobot(QPainter &painter, int i, float x, float y, float theta)
 {

     painter.setRenderHint(QPainter::Antialiasing);

     QColor playerColor;
     //QPixmap im("icone.png");
     //painter.drawPixmap(x-25, y-25, 50, 50, im);

     switch(i){

     case 0:
         playerColor = ROBOT_P1;
         break;
     case 1:
         playerColor = ROBOT_P2;
         break;
     case 2:
         playerColor = ROBOT_P3;
         break;

     }

     painter.translate(x,y);
     painter.rotate(theta);

     painter.setPen(Qt::NoPen);
     painter.setBrush(ROBOT_CHASSIS);
     painter.drawRect(-ROBOT_WIDTH/2, -ROBOT_HEIGHT/2, ROBOT_WIDTH, ROBOT_HEIGHT);

     painter.setBrush(ROBOT_COLOR);
     painter.drawRect(-ROBOT_WIDTH/2, -ROBOT_HEIGHT/2, ROBOT_WIDTH/2, ROBOT_HEIGHT/2);

     painter.setBrush(playerColor);
     painter.drawRect(0, -ROBOT_HEIGHT/2, ROBOT_WIDTH/2, ROBOT_HEIGHT/2);

     painter.resetTransform();

 }

 inline void SoccerField::drawEnemy(QPainter &painter, int i, float x, float y, float theta)
 {

     painter.setRenderHint(QPainter::Antialiasing);
     painter.setPen(Qt::NoPen);

     QColor playerColor;

     switch(i){

     case 0:
         playerColor = ENEMY_P1;
         break;
     case 1:
         playerColor = ENEMY_P2;
         break;
     case 2:
         playerColor = ENEMY_P3;
         break;

     }

     painter.translate(x,y);
     painter.rotate(theta);

     painter.setPen(Qt::NoPen);
     painter.setBrush(ROBOT_CHASSIS);
     painter.drawRect(-ENEMY_WIDTH/2, -ENEMY_HEIGHT/2, ENEMY_WIDTH, ENEMY_HEIGHT);

     painter.setBrush(ENEMY_COLOR);
     painter.drawRect(-ENEMY_WIDTH/2, -ENEMY_HEIGHT/2, ENEMY_WIDTH/2, ENEMY_HEIGHT/2);

     painter.setBrush(playerColor);
     painter.drawRect(0, -ENEMY_HEIGHT/2, ENEMY_WIDTH/2, ENEMY_HEIGHT/2);

     painter.resetTransform();

 }

 inline void SoccerField::drawBall(QPainter &painter)
 {
     painter.setRenderHint(QPainter::Antialiasing);

     painter.setPen(Qt::NoPen);

     painter.translate(XPOS(ball_x),YPOS(ball_y));
     painter.setBrush(BALL_COLOR);
     painter.drawEllipse(-BALL_DIAM/2,-BALL_DIAM/2,BALL_DIAM,BALL_DIAM);
     painter.resetTransform();
 }
