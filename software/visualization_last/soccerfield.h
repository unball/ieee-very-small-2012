/*
    @file soccerfield.h

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

#ifndef SOCCERFIELD_H
#define SOCCERFIELD_H
#define USE_MATH_DEFINES
#include <math.h>
// System Settings

#define M          4
#define MILISEC    50
#define DIVSEC     20 //(1000/MILISEC)

// System Macros

#define XPOS(X)         (M*(X)+WIDTH/2)
#define YPOS(Y)         (HEIGHT/2-M*(Y))
#define aXPOS(X)         (X-WIDTH/2)/M
#define aYPOS(Y)         (HEIGHT/2-Y)/M
#define ANGLE(A)        (360 / (2 * M_PI) * A)

#define ANGLE16TH(A)    (16*(A))

// Geometric Settings

#define LINE_THICKNESS  M*0.3
#define BORDER          10

// Field

#define GOAL_WIDTH      M*10
#define GOAL_HEIGHT     M*40

#define AREA_ARC_WIDTH  M*20
#define AREA_ARC_HEIGHT M*25
#define AREA_WIDTH      M*15
#define AREA_HEIGHT     M*70

#define CIRCLE_DIAM     M*40

#define CORNER_RAD      M*7

#define MARK_WIDTH      M*7.5
#define MARK_HEIGHT     M*7.5
#define MARK_DIAM       M*4
#define MARK_FB_LEFT    XPOS(-37.5)
#define MARK_FB_RIGHT   XPOS(37.5)
#define MARK_FB_TOP     YPOS(40)
#define MARK_FB_BOTTOM  YPOS(-40)
#define MARK_FB_ROBOT   M*20
#define MARK_PK_LEFT    MARK_FB_LEFT
#define MARK_PK_RIGHT   MARK_FB_RIGHT
#define MARK_PK_CENTER  YPOS(0)

#define FIELD_WIDTH     M*150
#define FIELD_HEIGHT    M*130
#define FIELD_BORDER    (GOAL_WIDTH+BORDER)
#define FIELD_LEFT      FIELD_BORDER
#define FIELD_RIGHT     (FIELD_BORDER+FIELD_WIDTH)
#define FIELD_TOP       FIELD_BORDER
#define FIELD_BOTTOM    (FIELD_BORDER+FIELD_HEIGHT)

// Robot/Enemy
#define ROBOT_CHASSIS   Qt::black

#define ROBOT_COLOR     Qt::yellow
#define ROBOT_WIDTH     M*7.5
#define ROBOT_HEIGHT    ROBOT_WIDTH
#define ROBOT_P1        Qt::red
#define ROBOT_P2        Qt::magenta
#define ROBOT_P3        Qt::black

#define ENEMY_COLOR     Qt::blue
#define ENEMY_WIDTH     ROBOT_WIDTH
#define ENEMY_HEIGHT    ROBOT_HEIGHT
#define ENEMY_P1        ROBOT_P1
#define ENEMY_P2        ROBOT_P2
#define ENEMY_P3        ROBOT_P3

// Ball
#define BALL_COLOR      QColor(255,165,0)
#define BALL_DIAM       M*4.27

// Drawing Window
#define WIDTH           (FIELD_WIDTH + 2*FIELD_BORDER)
#define HEIGHT          (FIELD_HEIGHT + 2*FIELD_BORDER)

// Window
#define WINDOW_WIDTH    (WIDTH+2*BORDER)
#define WINDOW_HEIGHT   (HEIGHT+2*BORDER)

 #include <QWidget>

 class QTimer;

 class SoccerField : public QWidget
 {
     Q_OBJECT

 public:
     SoccerField(QWidget *parent = 0);
     int tempo;
     int goal;
     bool simulador;
     bool manual;
     float robot_x[3];
          float robot_y[3];
               float robot_theta[3];
     float enemy_x[3];
          float enemy_y[3];
               float enemy_theta[3];
     float ball_x;
          float ball_y;

 public slots:
     void restartGame();
     void endGame();
     void copyThis(char read[30], char write[30]);
     void savePos(char write[30], bool n);
     unsigned long int loadPos(char read[30], unsigned long int p, bool fwd);
     void getPose();
     int goalDisplay();


 private slots:
     void getPositions();
     void readPositions();

 signals:
     void timer();

 private:
        QTimer *updateTimer;

 protected:
     void goalEvent(QEvent *event);
     void paintEvent(QPaintEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void drawField(QPainter &painter);
     void drawRobots(QPainter &painter);
     void drawRobot(QPainter &painter, int i, float x, float y, float theta);
     void drawEnemy(QPainter &painter, int i, float x, float y, float theta);
     void drawBall(QPainter &painter);


 private:
     bool ballHit(const QPoint &pos) const;
     char enemyHit(const QPoint &pos) const;
     char robotHit(const QPoint &pos) const;

     int timerCount;
     QTimer *autoShootTimer;

     char robotPressed;
     char enemyPressed;
     bool ballPressed;
     char robotRightPressed;
     char enemyRightPressed;
     bool jogoIniciado;
 };

#endif

