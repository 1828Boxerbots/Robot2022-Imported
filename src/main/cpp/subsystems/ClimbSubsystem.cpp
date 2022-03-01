// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ClimbSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

ClimbSubsystem::ClimbSubsystem() 
{
    return;
}

// This method will be called once per scheduler run
void ClimbSubsystem::Periodic() 
{
    return;
}

void ClimbSubsystem::Init()
{
#ifndef NOHW_CLIMB
    m_climbEncoder.SetDistancePerPulse(m_DISPULSE_CLIMB);
#endif
    ResetEncoder();
}

// ENCODER FUNCTIONS

void ClimbSubsystem::ResetEncoder()
{
#ifndef NOHW_CLIMB
    m_climbEncoder.Reset();
#endif
}

double ClimbSubsystem::GetDistance()
{
#ifndef NOHW_CLIMB
    return m_climbEncoder.GetDistance();
#else
    return 0.0;
#endif
}

int ClimbSubsystem::GetRaw()
{
#ifndef NOHW_CLIMB
    return m_climbEncoder.GetRaw();
#else
    return 0;
#endif
}

// MOTOR FUNCTIONS

void ClimbSubsystem::ClimbMotor(double speed)
{
#ifndef NOHW_CLIMB
    m_climb.Set(speed);
#endif
}

void ClimbSubsystem::EncoderTest()
{
    #ifndef NOHW_CLIMB
  int GetRaw = m_climbEncoder.GetRaw();
  double GetDistancePerPulse = m_climbEncoder.GetDistancePerPulse();
  double GetDistance = m_climbEncoder.GetDistance();
  bool GetDirection = m_climbEncoder.GetDirection();

    frc::SmartDashboard::PutNumber("ClimbSubsystem-GetRaw", GetRaw);
    frc::SmartDashboard::PutNumber("ClimbSubsystem-GetDistancePerPulse", GetDistancePerPulse);
    frc::SmartDashboard::PutNumber("ClimbSubsystem-GetDistance", GetDistance);
    frc::SmartDashboard::PutBoolean("ClimbSubsystem-GetDirection", GetDirection);
    #endif
}