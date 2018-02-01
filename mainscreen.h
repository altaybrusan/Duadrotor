#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <QJoysticks.h>
#include <QSerialPort>
#include <QByteArray>

namespace Ui {
class MainScreen;
}
class AttitudeIndicator;
class QwtDialSimpleNeedle;
class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();


private Q_SLOTS:
    void changeSpeed();
    void changeGradient();
    void changeAngle();
    void ProcessJoystickButton(QJoystickButtonEvent e);
    void ProcessJoystickAxis(QJoystickAxisEvent e);
    void AxisTriggered();
    void readSerial();

private:
    Ui::MainScreen *ui;

    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 6790;
    static const quint16 arduino_uno_product_id = 29987;
    QByteArray serialData;
    QString serialBuffer;
    QString parsed_data;

    int gSelectedmotor=0;
    QJoysticks* instance;
    int gSpeedChange=0;
    AttitudeIndicator *d_ai;

};

#endif // MAINSCREEN_H
