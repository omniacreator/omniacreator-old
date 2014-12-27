/**
* @file atlanta-hobbyist-robot-club-demo-12-2014.cpp
* Atlanta Hobbyist Robot Club Demo
*
* @version @n 1.0
* @date @n Dec 2014
*
* @author @n Kwabena W. Agyeman
*/

#include "InterfaceLibrary.h"

#define FR_GP2D02_VIN 0
#define FR_GP2D02_VOUT 1
#define FL_GP2D02_VIN 2
#define FL_GP2D02_VOUT 3
#define BR_GP2D02_VIN 4
#define BR_GP2D02_VOUT 5
#define BL_GP2D02_VIN 6
#define BL_GP2D02_VOUT 7

#define QTI_0 8
#define QTI_1 9
#define QTI_2 10
#define QTI_3 11
#define QTI_4 12
#define QTI_5 13
#define QTI_6 14
#define QTI_7 15

#define LEFT_ENCODER_BW 21
#define LEFT_ENCODER_FW 20
#define RIGHT_ENCODER_BW 23
#define RIGHT_ENCODER_FW 22

#define LEFT_MOTOR_BW 24
#define LEFT_MOTOR_FW 25
#define RIGHT_MOTOR_BW 27
#define RIGHT_MOTOR_FW 26

void initGP2D02(int vin, int vout)
{
    high(vin);
    input(vout);
}

int readGP2D02(int vin, int vout)
{
    int result = 0;

    low(vin);
    pause(70);
    high(vin);

    for(int i = 0; i < 8; i++)
    {
        waitcnt((CLKFREQ / 10000) + CNT); // pause(0.1)
        low(vin);
        waitcnt((CLKFREQ / 10000) + CNT); // pause(0.1)
        high(vin);

        result += result + input(vout);
    }

    pause(2);

    return result;
}

volatile int FRGP2D02 = 0;
volatile int FLGP2D02 = 0;
volatile int BRGP2D02 = 0;
volatile int BLGP2D02 = 0;

void GP2D02Reader()
{
    initGP2D02(FR_GP2D02_VIN, FR_GP2D02_VOUT);
    initGP2D02(FL_GP2D02_VIN, FL_GP2D02_VOUT);
    initGP2D02(BR_GP2D02_VIN, BR_GP2D02_VOUT);
    initGP2D02(BL_GP2D02_VIN, BL_GP2D02_VOUT);

    for(;;)
    {
        FRGP2D02 = readGP2D02(FR_GP2D02_VIN, FR_GP2D02_VOUT);
        FLGP2D02 = readGP2D02(FL_GP2D02_VIN, FL_GP2D02_VOUT);
        BRGP2D02 = readGP2D02(BR_GP2D02_VIN, BR_GP2D02_VOUT);
        BLGP2D02 = readGP2D02(BL_GP2D02_VIN, BL_GP2D02_VOUT);
    }
}

void initQTI(int pin)
{
    high(pin);
}

int readQTI(int pin)
{
    high(pin);
    pause(1);
    return rc_time(pin, 1);
}

const int encoderTable[16] = {+0,-1,+1,+0,+1,+0,+0,-1,-1,+0,+0,+1,+0,+1,-1,+0};

volatile int leftPosition = 0;

void readLeftEncoder()
{
    int oldTemp = INA;
    int oldTemp0 = (oldTemp & (1 << LEFT_ENCODER_BW)) != 0;
    int oldTemp1 = (oldTemp & (1 << LEFT_ENCODER_FW)) != 0;
    int oldState = (oldTemp1 << 1) | (oldTemp0 << 0);

    for(;;)
    {
        int newTemp = INA;
        int newTemp0 = (newTemp & (1 << LEFT_ENCODER_BW)) != 0;
        int newTemp1 = (newTemp & (1 << LEFT_ENCODER_FW)) != 0;
        int newState = (newTemp1 << 1) | (newTemp0 << 0);

        leftPosition += encoderTable[(oldState << 2) | (newState << 0)];
        oldState = newState;
    }
}

volatile int rightPosition = 0;

void readRightEncoder()
{
    int oldTemp = INA;
    int oldTemp0 = (oldTemp & (1 << RIGHT_ENCODER_BW)) != 0;
    int oldTemp1 = (oldTemp & (1 << RIGHT_ENCODER_FW)) != 0;
    int oldState = (oldTemp1 << 1) | (oldTemp0 << 0);

    for(;;)
    {
        int newTemp = INA;
        int newTemp0 = (newTemp & (1 << RIGHT_ENCODER_BW)) != 0;
        int newTemp1 = (newTemp & (1 << RIGHT_ENCODER_FW)) != 0;
        int newState = (newTemp1 << 1) | (newTemp0 << 0);

        rightPosition += encoderTable[(oldState << 2) | (newState << 0)];
        oldState = newState;
    }
}

ILCore core;

ILOscilloscope GP2D02View;
ILOscilloscopeCurve GP2D02Curve;

ILOscilloscope QTIView;
ILOscilloscopeBar QTIBar;

ILInterface MotorView;
ILInterfaceGroupBox MotorLeftGroup;
ILInterfaceSlider MotorLeftSpeed;
ILInterfaceLabel MotorLeftPosition;
ILInterfaceGroupBox MotorRightGroup;
ILInterfaceSlider MotorRightSpeed;
ILInterfaceLabel MotorRightPosition;

int main()
{
    cog_run((void (*)(void *)) &GP2D02Reader, 100);

    initQTI(QTI_0);
    initQTI(QTI_1);
    initQTI(QTI_2);
    initQTI(QTI_3);
    initQTI(QTI_4);
    initQTI(QTI_5);
    initQTI(QTI_6);
    initQTI(QTI_7);

    cog_run((void (*)(void *)) &readLeftEncoder, 100);
    cog_run((void (*)(void *)) &readRightEncoder, 100);

    pwm_start(100);

    core.init();
    // core.clearAll();

    GP2D02View.init(&core, "GP2D02 View");
    GP2D02View.setXAxisRangeAutoScale(false);
    GP2D02View.setXAxisRangeLower(-181); // 255 * sin(0 + 45)
    GP2D02View.setXAxisRangeUpper(+181); // 255 * sin(180 + 45)
    GP2D02View.setYAxisRangeAutoScale(false);
    GP2D02View.setYAxisRangeLower(-181); // 255 * sin(0 + 45)
    GP2D02View.setYAxisRangeUpper(+181); // 255 * sin(180 + 45)
    GP2D02Curve.init(&GP2D02View, "");
    GP2D02Curve.setCoordinateSystem(CS_POLAR);
    GP2D02Curve.setAngleUnits(AU_DEGREES);
    GP2D02Curve.setFillStyle(FS_SOLID_PATTERN);

    QTIView.init(&core, "QTI View");
    QTIView.setBackgroundColor(0xFF444444);
    QTIView.setYAxisLabel("time in us");
    QTIView.setYAxisRangeAutoScale(false);
    QTIView.setYAxisRangeLower(1);
    QTIView.setYAxisRangeUpper(10000);
    QTIBar.init(&QTIView, "");
    QTIBar.setLineColor(0xFF7F0000);
    QTIBar.setFillColor(0x7F7F0000);

    MotorView.init(&core, "Motor View");
    MotorLeftGroup.init(&MotorView, "Left Motor Control");
    MotorLeftSpeed.init(&MotorLeftGroup, "Speed Control");
    MotorLeftSpeed.setMinimum(-100);
    MotorLeftSpeed.setMaximum(100);
    MotorLeftSpeed.reset();
    MotorLeftPosition.init(&MotorLeftGroup, "Position = 0");
    MotorRightGroup.init(&MotorView, "Right Motor Control");
    MotorRightSpeed.init(&MotorRightGroup, "Speed Control");
    MotorRightSpeed.setMinimum(-100);
    MotorRightSpeed.setMaximum(100);
    MotorRightSpeed.reset();
    MotorRightPosition.init(&MotorRightGroup, "Position = 0");

    for(;;)
    {
        GP2D02Curve.addIndexKeyValue(0, 0 + 45, FRGP2D02);
        GP2D02Curve.addIndexKeyValue(1, 90 + 45, FLGP2D02);
        GP2D02Curve.addIndexKeyValue(2, 180 + 45, BLGP2D02);
        GP2D02Curve.addIndexKeyValue(3, 270 + 45, BRGP2D02);
        GP2D02Curve.addIndexKeyValue(4, 360 + 45, FRGP2D02);

        QTIBar.addKeyValue(0, readQTI(QTI_0));
        QTIBar.addKeyValue(1, readQTI(QTI_1));
        QTIBar.addKeyValue(2, readQTI(QTI_2));
        QTIBar.addKeyValue(3, readQTI(QTI_3));
        QTIBar.addKeyValue(4, readQTI(QTI_4));
        QTIBar.addKeyValue(5, readQTI(QTI_5));
        QTIBar.addKeyValue(6, readQTI(QTI_6));
        QTIBar.addKeyValue(7, readQTI(QTI_7));

        ///////////////////////////////////////////////////////////////////////

        int leftSpeed = MotorLeftSpeed.getValue();

        if(leftSpeed > 0)
        {
            pwm_set(LEFT_MOTOR_FW, 0, leftSpeed);
            low(LEFT_MOTOR_BW);
        }
        else if(leftSpeed < 0)
        {
            pwm_set(LEFT_MOTOR_BW, 0, -leftSpeed);
            low(LEFT_MOTOR_FW);
        }
        else
        {
            low(LEFT_MOTOR_BW);
            low(LEFT_MOTOR_FW);
        }

        char leftBuffer[100] = {};
        sprinti(leftBuffer, "Position = %d", leftPosition);
        MotorLeftPosition.setText(leftBuffer);

        ///////////////////////////////////////////////////////////////////////

        int rightSpeed = MotorRightSpeed.getValue();

        if(rightSpeed > 0)
        {
            pwm_set(RIGHT_MOTOR_FW, 1, rightSpeed);
            low(RIGHT_MOTOR_BW);
        }
        else if(rightSpeed < 0)
        {
            pwm_set(RIGHT_MOTOR_BW, 1, -rightSpeed);
            low(RIGHT_MOTOR_FW);
        }
        else
        {
            low(RIGHT_MOTOR_BW);
            low(RIGHT_MOTOR_FW);
        }

        char rightBuffer[100] = {};
        sprinti(rightBuffer, "Position = %d", rightPosition);
        MotorRightPosition.setText(rightBuffer);
    }

    return 0;
}
