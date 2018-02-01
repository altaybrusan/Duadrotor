/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCREEN_H
#define UI_MAINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_dial.h"
#include "qwt_text_label.h"

QT_BEGIN_NAMESPACE

class Ui_MainScreen
{
public:
    QAction *action_Exit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *leftFrame;
    QVBoxLayout *verticalLayout;
    QwtDial *leftMotorDial;
    QwtTextLabel *TextLabel;
    QFrame *balanceFrame;
    QVBoxLayout *verticalLayout_2;
    QFrame *balanceMeterPlace;
    QwtTextLabel *balanceLbl;
    QFrame *rightFrame;
    QVBoxLayout *verticalLayout_3;
    QwtDial *rightMotorDial;
    QwtTextLabel *rightLbl;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainScreen)
    {
        if (MainScreen->objectName().isEmpty())
            MainScreen->setObjectName(QStringLiteral("MainScreen"));
        MainScreen->resize(986, 587);
        MainScreen->setStyleSheet(QStringLiteral("background-color: rgb(51, 51, 51);"));
        action_Exit = new QAction(MainScreen);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        centralWidget = new QWidget(MainScreen);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        leftFrame = new QFrame(centralWidget);
        leftFrame->setObjectName(QStringLiteral("leftFrame"));
        leftFrame->setFrameShape(QFrame::StyledPanel);
        leftFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(leftFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        leftMotorDial = new QwtDial(leftFrame);
        leftMotorDial->setObjectName(QStringLiteral("leftMotorDial"));
        leftMotorDial->setStyleSheet(QStringLiteral("color: rgb(0, 255, 0);"));
        leftMotorDial->setUpperBound(35);
        leftMotorDial->setScaleMaxMajor(10);
        leftMotorDial->setValue(0);
        leftMotorDial->setReadOnly(true);
        leftMotorDial->setLineWidth(4);
        leftMotorDial->setFrameShadow(QwtDial::Sunken);
        leftMotorDial->setMode(QwtDial::RotateNeedle);
        leftMotorDial->setOrigin(135);
        leftMotorDial->setMaxScaleArc(270);

        verticalLayout->addWidget(leftMotorDial);

        TextLabel = new QwtTextLabel(leftFrame);
        TextLabel->setObjectName(QStringLiteral("TextLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        TextLabel->setFont(font);
        TextLabel->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(TextLabel);


        horizontalLayout->addWidget(leftFrame);

        balanceFrame = new QFrame(centralWidget);
        balanceFrame->setObjectName(QStringLiteral("balanceFrame"));
        balanceFrame->setFrameShape(QFrame::StyledPanel);
        balanceFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(balanceFrame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        balanceMeterPlace = new QFrame(balanceFrame);
        balanceMeterPlace->setObjectName(QStringLiteral("balanceMeterPlace"));
        balanceMeterPlace->setFrameShape(QFrame::StyledPanel);
        balanceMeterPlace->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(balanceMeterPlace);

        balanceLbl = new QwtTextLabel(balanceFrame);
        balanceLbl->setObjectName(QStringLiteral("balanceLbl"));
        balanceLbl->setFont(font);
        balanceLbl->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(balanceLbl);


        horizontalLayout->addWidget(balanceFrame);

        rightFrame = new QFrame(centralWidget);
        rightFrame->setObjectName(QStringLiteral("rightFrame"));
        rightFrame->setFrameShape(QFrame::StyledPanel);
        rightFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(rightFrame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        rightMotorDial = new QwtDial(rightFrame);
        rightMotorDial->setObjectName(QStringLiteral("rightMotorDial"));
        rightMotorDial->setStyleSheet(QStringLiteral("color: rgb(0, 255, 0);"));
        rightMotorDial->setUpperBound(35);
        rightMotorDial->setReadOnly(true);
        rightMotorDial->setLineWidth(4);
        rightMotorDial->setOrigin(135);
        rightMotorDial->setMaxScaleArc(270);

        verticalLayout_3->addWidget(rightMotorDial);

        rightLbl = new QwtTextLabel(rightFrame);
        rightLbl->setObjectName(QStringLiteral("rightLbl"));
        rightLbl->setFont(font);
        rightLbl->setStyleSheet(QStringLiteral("color: rgb(255, 255, 255);"));

        verticalLayout_3->addWidget(rightLbl);


        horizontalLayout->addWidget(rightFrame);

        MainScreen->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainScreen);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 986, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainScreen->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainScreen);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainScreen->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainScreen);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainScreen->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(action_Exit);

        retranslateUi(MainScreen);

        QMetaObject::connectSlotsByName(MainScreen);
    } // setupUi

    void retranslateUi(QMainWindow *MainScreen)
    {
        MainScreen->setWindowTitle(QApplication::translate("MainScreen", "Duadrotor", Q_NULLPTR));
        action_Exit->setText(QApplication::translate("MainScreen", "&Exit", Q_NULLPTR));
        TextLabel->setPlainText(QApplication::translate("MainScreen", "Left Motor [4]", Q_NULLPTR));
        balanceLbl->setPlainText(QApplication::translate("MainScreen", "Balance", Q_NULLPTR));
        rightLbl->setPlainText(QApplication::translate("MainScreen", "Right Motor [2]", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainScreen", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainScreen: public Ui_MainScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
