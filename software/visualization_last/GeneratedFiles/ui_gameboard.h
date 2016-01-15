/********************************************************************************
** Form generated from reading UI file 'gameboard.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOARD_H
#define UI_GAMEBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

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
            GameBoard->setObjectName(QStringLiteral("GameBoard"));
        GameBoard->resize(400, 300);
        centralWidget = new QWidget(GameBoard);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GameBoard->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GameBoard);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        GameBoard->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GameBoard);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GameBoard->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GameBoard);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GameBoard->setStatusBar(statusBar);

        retranslateUi(GameBoard);

        QMetaObject::connectSlotsByName(GameBoard);
    } // setupUi

    void retranslateUi(QMainWindow *GameBoard)
    {
        GameBoard->setWindowTitle(QApplication::translate("GameBoard", "GameBoard", 0));
    } // retranslateUi

};

namespace Ui {
    class GameBoard: public Ui_GameBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOARD_H
