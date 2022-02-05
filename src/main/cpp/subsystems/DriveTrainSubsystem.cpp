// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/DriveTrainSubsystem.h"

DriveTrainSubsystem::DriveTrainSubsystem()
{
#ifndef NOHW
    // m_leftEncoder.SetDistancePerPulse(m_pulseDisLeft);
    // m_rightEncoder.SetDistancePerPulse(m_pulseDisRight);
#endif
}

// This method will be called once per scheduler run
void DriveTrainSubsystem::Periodic() {}

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
// void DriveTrainSubsystem::ResetEncoders()
// {
// #ifndef NOHW
//     m_leftEncoder.Reset();
//     m_rightEncoder.Reset();
// #endif
// }

// void DriveTrainSubsystem::GetEncoderDistance(double* pLeft, double* pRight)
// {
// #ifndef NOHW
//     double left = m_leftEncoder.GetDistance(); 
//     double right = m_rightEncoder.GetDistance();
//     pLeft = &left;
//     pRight = &right;
// #endif
// }

// void DriveTrainSubsystem::GetEncoderRaw(int* pLeft, int* pRight)
// {
// #ifndef NOHW
//     int left = m_leftEncoder.GetRaw();
//     int right = m_rightEncoder.GetRaw();
//     pLeft = &left;
//     pRight = &right;
// #endif
//}

// DRIVE FUNCTIONS
void DriveTrainSubsystem::MoveTank(double left, double right)
{
    SetMotorL(left);
    SetMotorR(right);
}

void DriveTrainSubsystem::MoveArcade(double X, double Y)
{
    double left = X + Y;
    double right = X - Y;

    MoveTank(left, right);
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