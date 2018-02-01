#include "mainscreen.h"
#include "ui_mainscreen.h"
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>
#include "attitudeindicator.h"
#include <qtimer.h>
#include <QJoysticks.h>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>

const qreal THRESH=0.5;
const int STEP=1;
QTimer* axisTimer = new QTimer();
MainScreen::MainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);

    QwtDialSimpleNeedle *needleOne = new QwtDialSimpleNeedle(
                QwtDialSimpleNeedle::Arrow, true, Qt::red,
                QColor( Qt::gray ).light( 130 ) );
    ui->leftMotorDial->setNeedle(needleOne);
    QwtDialSimpleNeedle *needleTwo = new QwtDialSimpleNeedle(
                QwtDialSimpleNeedle::Arrow, true, Qt::red,
                QColor( Qt::gray ).light( 130 ) );
    ui->rightMotorDial->setNeedle(needleTwo);


    //----------------------------------------------

    d_ai = new AttitudeIndicator( ui->balanceMeterPlace );
    d_ai->setReadOnly(true);
    QGridLayout *layout = new QGridLayout( ui->balanceMeterPlace );
    layout->setSpacing( 5 );
    layout->setMargin( 0 );


    //ui->balanceMeterPlace->setLayout(layout);
    d_ai->scaleDraw()->setPenWidth( 2 );

    //    QTimer *gradientTimer = new QTimer( d_ai );
    //    gradientTimer->connect( gradientTimer, SIGNAL( timeout() ),
    //        this, SLOT( changeGradient() ) );
    //    gradientTimer->start( 100 );

    //    QTimer *angleTimer = new QTimer( d_ai );
    //    angleTimer->connect( angleTimer, SIGNAL( timeout() ),
    //        this, SLOT( changeAngle() ) );

    //    angleTimer->start( 100 );

    layout->addWidget(d_ai);
    layout->setColumnStretch(0,1);

    //--------------------------------------------------

    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";

    /*
     *   Identify the port the arduino uno is on.
     */
    bool arduino_is_available = false;
    QString arduino_uno_port_name;

    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the arduino uno
            qDebug()<<"serialPortInfo.productIdentifier:  "<<serialPortInfo.productIdentifier();
            qDebug()<<"serialPortInfo.vendorIdentifier():  "<<serialPortInfo.vendorIdentifier();

            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available){
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }

    //-------------------------------------------------

    /*
         * QJoysticks is single instance, you can use the "getInstance()" function
         * directly if you want, or you can create a pointer to it to make code
         * easier to read;
         */


    instance = QJoysticks::getInstance();
//    if(instance->count()==0)
//    {

//        QMessageBox::warning(NULL, tr("Duadrotor warning"),
//                              tr("No Joysticks found. Connect a joystick and restart the program. "),
//                              QMessageBox::Ok);

//    }
    connect(instance,SIGNAL(buttonEvent(QJoystickButtonEvent)),this,SLOT(ProcessJoystickButton(QJoystickButtonEvent)));
    connect(instance,SIGNAL(axisEvent(QJoystickAxisEvent)),this,SLOT(ProcessJoystickAxis(QJoystickAxisEvent)));
    //--------------------------------------------------

    axisTimer->setInterval(100);
    connect(axisTimer,SIGNAL(timeout()),this,SLOT(AxisTriggered()));


}

MainScreen::~MainScreen()
{
    delete ui;

//    delete arduino;
//    instance->deleteLater();
//    axisTimer->deleteLater();

}

void MainScreen::changeSpeed()
{

}

void MainScreen::changeGradient()
{
    static double offset = 0.005;

    double gradient = d_ai->gradient();

    if ( ( gradient < -0.05 && offset < 0.0 ) ||
         ( gradient > 0.05 && offset > 0.0 ) )
    {
        offset = -offset;
    }

    d_ai->setGradient( gradient + offset );

}

void MainScreen::changeAngle()
{
    static double offset = 0.05;

    double angle = d_ai->angle();
    if ( angle > 180.0 )
        angle -= 360.0;

    if ( ( angle < -5.0 && offset < 0.0 ) ||
         ( angle > 5.0 && offset > 0.0 ) )
    {
        offset = -offset;
    }

    d_ai->setAngle( angle + offset );

}

void MainScreen::ProcessJoystickButton(QJoystickButtonEvent e)
{

    if(e.pressed)
    {
        switch (e.button) {
        case 1:
            gSelectedmotor=2;
            break;
        case 3:
            gSelectedmotor=4;
        default:
            break;
        }

    }
    else
    {
        gSelectedmotor=0;
        axisTimer->stop();
    }

    qDebug()<< "Selected motor "<<gSelectedmotor;

}

void MainScreen::ProcessJoystickAxis(QJoystickAxisEvent e)
{

    if(gSelectedmotor!=0)
    {

        qDebug()<<"selected axis : " << e.axis;
        if(e.axis==0 || e.axis==1)
        {
            if(e.value<-1*THRESH)
                gSpeedChange=STEP;
            if(e.value>THRESH)
                gSpeedChange=-STEP;
            if(e.value <= THRESH && e.value >= -1* THRESH)
            {
                gSpeedChange=0;
                axisTimer->stop();
                return;
            }
            axisTimer->start();

        }


    }
    else
    {
        gSpeedChange=0;
        axisTimer->stop();

    }

}

void MainScreen::AxisTriggered()
{

    qDebug()<<"Speed change: " << gSpeedChange;
    if(gSelectedmotor==4)
    {
        ui->leftMotorDial->setValue(ui->leftMotorDial->value()+gSpeedChange);


//        std::string s = std::to_string(int(ui->leftMotorDial->value()));
//        s= 'L' + s;
//        char const *pchar = s.c_str();  //use char const* as target type

        QByteArray buffer = 'L' +QByteArray::number(int(ui->leftMotorDial->value())) + "\n";
        qDebug()<<"message to write: "<<buffer;
        arduino->write(buffer); //send the buffer
    }


    if(gSelectedmotor==2)
    {
        ui->rightMotorDial->setValue(ui->rightMotorDial->value()+gSpeedChange);
//        std::string s = std::to_string(int(ui->rightMotorDial->value()));
//        s= 'R' + s;
//        char const *pchar = s.c_str();  //use char const* as target type

        QByteArray buffer = 'R' +QByteArray::number(int(ui->rightMotorDial->value())) + "\n";
        qDebug()<<"message to write: "<<buffer;
        arduino->write(buffer); //send the buffer

//        qDebug()<<"message to write: "<<pchar;
//        arduino->write(pchar); //send the buffer

    }

    QThread::msleep(50);
    //ui->leftMotorDial->update();
}

void MainScreen::readSerial()
{
    auto serialData = arduino->readAll();
    qDebug()<<serialData;
}

