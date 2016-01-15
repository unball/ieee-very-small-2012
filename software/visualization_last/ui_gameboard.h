/********************************************************************************
** Form generated from reading UI file 'gameboard.ui'
**
** Created: Tue Jul 31 11:01:42 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOARD_H
#define UI_GAMEBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameBoard
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GameBoard)
    {
        if (GameBoard->objectName().isEmpty())
            GameBoard->setObjectName(QString::fromUtf8("GameBoard"));
        GameBoard->resize(400, 300);
        centralWidget = new QWidget(GameBoard);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GameBoard->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameBoard);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        GameBoard->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GameBoard);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GameBoard->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GameBoard);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GameBoard->setStatusBar(statusBar);

        retranslateUi(GameBoard);

        QMetaObject::connectSlotsByName(GameBoard);
    } // setupUi

    void retranslateUi(QMainWindow *GameBoard)
    {
        GameBoard->setWindowTitle(QApplication::translate("GameBoard", "GameBoard", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GameBoard: public Ui_GameBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOARD_H
