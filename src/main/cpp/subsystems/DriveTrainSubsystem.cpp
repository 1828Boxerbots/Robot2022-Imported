// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveTrainSubsystem.h"
#include "Util.h"
#include <cmath>
DriveTrainSubsystem::DriveTrainSubsystem(){}

// This method will be called once per scheduler run
void DriveTrainSubsystem::Periodic() {}

void DriveTrainSubsystem::Init()
{
#ifndef NOHW
    m_rightMotor.SetInverted(true);
    m_leftEncoder.Reset();
    m_rightEncoder.Reset();
    m_leftEncoder.SetReverseDirection(true);
    m_rightEncoder.SetReverseDirection(true);
    m_adi.Reset();
    
    m_leftEncoder.SetDistancePerPulse(m_DISPULSE_LEFT);
    m_rightEncoder.SetDistancePerPulse(m_DISPULSE_RIGHT);

    //Get the default instance of NetworkTables that was created automatically
    auto inst = nt::NetworkTableInstance::GetDefault();

    //Get the table within that instance that contains the data. There can
    //be as many tables as you like and exist to make it easier to organize
    //your data. In this case, it's a table called datatable.
    m_table = inst.GetTable("datatable");

    //Get the entries within that table that correspond Angle from the PI
    m_piAngle = m_table->GetEntry("Angle");
#endif
}

// MOTOR FUNCTIONS
void DriveTrainSubsystem::SetMotorL(double speed)
{
#ifndef NOHW
    m_leftMotor.Set(speed);
#endif
}

void DriveTrainSubsystem::SetMotorR(double speed)
{
#ifndef NOHW
    m_rightMotor.Set(speed);
#endif
}

// ENCODER FUNCTIONS
void DriveTrainSubsystem::ResetEncoders()
{
#ifndef NOHW
    m_leftEncoder.Reset();
    m_rightEncoder.Reset();
#endif
}

void DriveTrainSubsystem::GetEncoderDistance(double* pLeft, double* pRight)
{
#ifndef NOHW
    double left = m_leftEncoder.GetDistance(); 
    double right = m_rightEncoder.GetDistance();

    if(pLeft != nullptr)
    {
        *pLeft = left;
    }
    if(pRight != nullptr)
    {   
        *pRight = -right;
    }
    frc::SmartDashboard::PutNumber("Left Encoder Distance", left);
    frc::SmartDashboard::PutNumber("Right Encoder Distance", right);

#endif
}

void DriveTrainSubsystem::GetEncoderRaw(int* pLeft, int* pRight)
{
#ifndef NOHW
    int left = m_leftEncoder.GetRaw();
    int right = m_rightEncoder.GetRaw();

    frc::SmartDashboard::PutNumber("Left Ecnoder Raw", left);
    frc::SmartDashboard::PutNumber("Right Encoder Raw", right);

    if(pLeft != nullptr)
    {
        *pLeft = left;
    }
    if(pRight != nullptr)
    {
        *pRight = right;
    }
#endif
}

// ADI FUNCTIONS
units::degree_t DriveTrainSubsystem::GetADIAngle()
{
#ifndef NOHW
    frc::SmartDashboard::PutNumber("ADI Angle", (double)m_adi.GetAngle());
    return m_adi.GetAngle();
    return 0_deg;
#else
    return (units::degree_t) 0;
#endif
}

units::degree_t DriveTrainSubsystem::GetAngleX()
{
#ifndef NOHW
    return m_adi.GetGyroAngleX();
    return 0_deg;
#else
    return (units::degree_t) 0;
#endif
}

units::degree_t DriveTrainSubsystem::GetAngleY()
{
#ifndef NOHW
    return m_adi.GetGyroAngleY();
    return 0_deg;
#else
    return (units::degree_t) 0;
#endif
}

units::degree_t DriveTrainSubsystem::GetAngleZ()
{
#ifndef NOHW
    return m_adi.GetGyroAngleZ();
    return 0_deg;
#else
    return (units::degree_t) 0;
#endif
}

// DRIVE FUNCTIONS
void DriveTrainSubsystem::MoveTank(double left, double right)
{
    SetMotorL(left);
    SetMotorR(right);
}
void DriveTrainSubsystem::ForwardInTime(double time, double speed)
{
    MoveTank(speed, speed);
    Util::Log("My Code hTingy",time);
    Util::DelayInSeconds((units::time::second_t) time);

    //Stop
    MoveTank(0.0, 0.0);
}

void DriveTrainSubsystem::MoveArcade(double X, double Y)
{
    double left = X + Y;
    double right = X - Y;

    MoveTank(left, right);
}

// IMU AND DRIVE FUNCTIONS
void DriveTrainSubsystem::TurnAngleRelative(units::degree_t angle, double speed, units::degree_t deadZone)
{
    units::degree_t currentAngle = GetAngleX();
    units::degree_t targetAngle = currentAngle + angle;
    units::degree_t lowAngle = targetAngle - deadZone;
    units::degree_t highAngle = targetAngle + deadZone;

    frc::SmartDashboard::PutNumber("TargetAngle-Relative", (double)targetAngle);
    frc::SmartDashboard::PutNumber("TargetAngle-Anglex", (double)GetAngleX());
    frc::SmartDashboard::PutNumber("TargetAngle-Angley", (double)GetAngleY());
    frc::SmartDashboard::PutNumber("TargetAngle-Anglez", (double)GetAngleZ());
    frc::SmartDashboard::PutNumber("TargetAngle-Angle", (double)angle);
    frc::SmartDashboard::PutNumber("TargetAngle-DeadZone", (double)deadZone);
    frc::SmartDashboard::PutNumber("TargetAngle-speed", (double)speed);

    while(currentAngle > highAngle or currentAngle < lowAngle)
    {
        if(currentAngle > highAngle)
        {
            MoveTank(speed, -speed);
        }
        else if(currentAngle < lowAngle)
        {
            MoveTank(-speed, speed);
        }
        currentAngle = GetAngleX();
        frc::SmartDashboard::PutNumber("CurrentAngle-Relative", (double)currentAngle);
    }

    //Stop
    MoveTank(0.0, 0.0);
}

void DriveTrainSubsystem::TurnAngleAbsolute(units::degree_t angle, double speed, units::degree_t deadZone)
{
    units::degree_t currentAngle = GetAngleX();
    units::degree_t lowAngle = angle - deadZone;
    units::degree_t highAngle = angle + deadZone;

    frc::SmartDashboard::PutNumber("TargetAngle-Absolute", (double)angle);
    while(currentAngle > highAngle or currentAngle < lowAngle)
    {
        if(currentAngle > highAngle)
        {
            MoveTank(-speed, speed);
        }
        else if(currentAngle < lowAngle)
        {
            MoveTank(speed, -speed);
        }
        currentAngle = GetAngleX();
        frc::SmartDashboard::PutNumber("CurrentAngle-Absolute", (double)currentAngle);
    }

    //Stop
    MoveTank(0.0, 0.0);
}

// ENCODER AND DRIVE FUNCTIONS
void DriveTrainSubsystem::ForwardInInch(double inch, double speed)
{
#ifndef NOHW_SENSORS
    double currentDistance;
    GetEncoderDistance(nullptr,&currentDistance);
    double targetDistance = currentDistance + inch;

    while(currentDistance < targetDistance)
    {
        MoveTank(speed, speed);
        GetEncoderDistance(nullptr,&currentDistance);
    }

    //Stop
    MoveTank(0.0, 0.0);
#endif
}

void DriveTrainSubsystem::BackwardInInch(double inch, double speed)
{
#ifndef NOHW_SENSORS
    double currentDistance;
    GetEncoderDistance(nullptr, &currentDistance);
    double targetDistance = currentDistance - fabsf(inch);

    while(currentDistance > targetDistance)
    {
        MoveTank(-fabsf(speed), -fabsf(speed));
        GetEncoderDistance(nullptr,&currentDistance);
    }

    //Stop
    MoveTank(0.0, 0.0);
#endif
}

void DriveTrainSubsystem::ForwardInInchIMU(double inch, double correctionSpeed, units::degree_t deadZoneAngle, double baseSpeed)
{
    #ifndef NOHW_SENSORS
    double currentDistance;
    GetEncoderDistance(&currentDistance);
    double targetDistance = currentDistance + inch;

    units::degree_t startAngle = GetADIAngle();
    units::degree_t currentAngle = GetADIAngle();
    units::degree_t lowAngle = startAngle - deadZoneAngle;
    units::degree_t highAngle = startAngle + deadZoneAngle;
    while(currentDistance < targetDistance)
    {        
        currentAngle = GetADIAngle();
        if(currentAngle < lowAngle)
        {
            MoveTank(baseSpeed, baseSpeed - correctionSpeed);
        }
        else if(currentAngle > highAngle)
        {
            MoveTank(baseSpeed, baseSpeed + correctionSpeed);
        }
        else
        {
            MoveTank(baseSpeed, baseSpeed);
        }
        GetEncoderDistance(&currentDistance);
    }

    MoveTank(0.0, 0.0);
    #endif
}

// DRIVE STYLE FUNCTIONS
void DriveTrainSubsystem::SetDrive(DriveStyles styles)
{
    m_currentStyle = styles;
}

DriveTrainSubsystem::DriveStyles DriveTrainSubsystem::GetDrive()
{
    return m_currentStyle;
}


// PI / VISION FUNCTIONS
double DriveTrainSubsystem::GetPIAngle()
{
#ifndef NOHW
    return m_piAngle.GetDouble(-666);
#endif
}

bool DriveTrainSubsystem::VisionAllign(double speed, units::degree_t deadZone)
{
    double turnAngle = -GetPIAngle();
    frc::SmartDashboard::PutNumber("PiAngle", turnAngle);
    if(turnAngle != 666)
    {
        TurnAngleRelative((units::degree_t)turnAngle, speed, deadZone);
        return true;
    }
    else
    {
        return false;
    }
}