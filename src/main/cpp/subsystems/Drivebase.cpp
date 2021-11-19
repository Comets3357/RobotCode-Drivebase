#include "subsystems/Drivebase.h"
#include "RobotData.h"

void Drivebase::RobotInit()
{
    dbLM.ConfigFactoryDefault();
    dbLS.ConfigFactoryDefault();
    dbRM.ConfigFactoryDefault();
    dbRS.ConfigFactoryDefault();

    dbLS.Follow(dbLM);
    dbRS.Follow(dbRM);

    dbLM.SetInverted(true);
    dbLS.SetInverted(true);
    dbRM.SetInverted(false);    
    dbRS.SetInverted(false);

    dbLM.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
    dbLS.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
    dbRM.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
    dbRS.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);

    // NEED TO SET CURRENT LIMIT
    dbLM.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    dbRM.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
   
}

void Drivebase::RobotPeriodic(const RobotData &robotData, DrivebaseData &drivebaseData)
{
    updateData(robotData, drivebaseData);

    if (frc::DriverStation::GetInstance().IsEnabled())
    {
        dbRM.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
        dbRS.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
        dbLM.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
        dbLS.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
    }

    teleopControl(robotData);
}

void Drivebase::DisabledInit()
{
    
    dbLM.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    dbRM.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
    dbRM.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
    dbRS.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
    dbLM.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
    dbLS.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
}

// updates encoder and gyro values
void Drivebase::updateData(const RobotData &robotData, DrivebaseData &drivebaseData)
{
    // //add back wheel encoders at some point
    // drivebaseData.currentLDBPos = dbLMEncoder.GetPosition();
    // drivebaseData.currentRDBPos = dbRMEncoder.GetPosition();

    // drivebaseData.lDriveVel = dbRMEncoder.GetVelocity();
    // drivebaseData.rDriveVel = dbLMEncoder.GetVelocity();
}
// driving functions:

// adjusts for the deadzone and converts joystick input to velocity values for PID
void Drivebase::teleopControl(const RobotData &robotData)
{

    double tempLDrive = robotData.controlData.lDrive;
    double tempRDrive = robotData.controlData.rDrive;

    // converts from tank to arcade drive, limits the difference between left and right drive
    double frontBack = robotData.controlData.maxStraight * (tempLDrive + tempRDrive) / 2;
    double leftRight = robotData.controlData.maxTurn * (tempRDrive - tempLDrive) / 2;

    //deadzone NOT needed for drone controller
    if (tempLDrive <= -0.08 || tempLDrive >= 0.08)
    {
        tempLDrive = (frontBack - leftRight);
    }
    else
    {
        tempLDrive = 0;
    }

    if (tempRDrive <= -0.08 || tempRDrive >= 0.08)
    {
        tempRDrive = (frontBack + leftRight);
    }
    else
    {
        tempRDrive = 0;
    }

    //set as percent vbus
    dbLM.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, tempLDrive);
    dbRM.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, tempRDrive);
}