#pragma once

#include "Constants.h"

#include <frc/DriverStation.h>
#include <frc/TimedRobot.h>
#include <ctre/Phoenix.h>



struct RobotData;

struct DrivebaseData
{
    double currentLDBPos;
    double currentRDBPos;

    double lDriveVel;
    double rDriveVel;
};

class Drivebase
{

public:
    void RobotInit();
    void RobotPeriodic(const RobotData &robotData, DrivebaseData &drivebaseData);
    void DisabledInit();

private:

    void updateData(const RobotData &robotData, DrivebaseData &drivebaseData);
    void teleopControl(const RobotData &robotData);


    ctre::phoenix::motorcontrol::can::TalonFX dbLM{leftLeadDeviceID};
    ctre::phoenix::motorcontrol::can::TalonFX dbLS{leftFollowDeviceID};
    ctre::phoenix::motorcontrol::can::TalonFX dbRM{rightLeadDeviceID};
    ctre::phoenix::motorcontrol::can::TalonFX dbRS{rightFollowDeviceID};
};