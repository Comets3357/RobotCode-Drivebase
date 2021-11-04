#pragma once

#include <frc/DriverStation.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>

struct RobotData;

struct ControlData
{
    // states:
    bool manualMode = false;
    bool climbMode = false;
    bool shift = false;

    // drivebase:
    double lDrive;
    double rDrive;
    bool turnResponsive;
    bool dbInverted;
    double maxStraight = 1;
    double maxTurn = 0.4;
};

struct ControllerData
{
    // btn data:
    // L = left, R = right, p = primary, s = secondary, Btn = button

    // primary:

    double pLXStick = 0;
    double pLYStick = 0;
    double pRXStick = 0;
    double pRYStick = 0;

    bool pLShoulderSwitch = false;
    bool pRShoulderSwitch = false;

    // secondary:

    double sLXStick = 0;
    double sLYStick = 0;
    double sRXStick = 0;
    double sRYStick = 0;

    bool sLStickBtn = false;
    bool sRStickBtn = false;

    double sLTrigger = 0;
    double sRTrigger = 0;
    bool sLBumper = false;
    bool sRBumper = false;

    bool sXBtn = false;
    bool sYBtn = false;
    bool sABtn = false;
    bool sBBtn = false;

    bool sABtnToggled = false;
    bool sBBtnToggled = false;
    bool sXBtnToggled = false;
    bool sYBtnToggled = false;

    bool sLCenterBtn = false;
    bool sRCenterBtn = false;

    bool sLCenterBtnToggled = false;
    bool sRCenterBtnToggled = false;

    int sDPad = -1;
};

class Controller
{

public:
    void TeleopPeriodic(const RobotData &robotData, ControllerData &controllerData, ControlData &controlData);

private:
    void updateBtnData(ControllerData &controllerData);
    void updateControlData(const ControllerData &controllerData, ControlData &controlData);

    // basic btn getters:
    bool getBtn(int js, int index);
    bool getBtnToggled(int js, int index);
    int getPOV(int js, int index);
    double getAxis(int js, int index);

    frc::Joystick primary{0};
    frc::Joystick secondary{1};
};

