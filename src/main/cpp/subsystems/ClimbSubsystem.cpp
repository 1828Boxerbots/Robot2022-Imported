// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ClimbSubsystem.h"

ClimbSubsystem::ClimbSubsystem()
{ }

// This method will be called once per scheduler run
void ClimbSubsystem::Periodic() {}

void ClimbSubsystem::Init()
{
#ifndef NOHW
    m_climbEncoder.SetDistancePerPulse(m_DISPULSE_CLIMB);
#endif
    ResetEncoder();
}

// ENCODER FUNCTIONS

void ClimbSubsystem::ResetEncoder()
{
#ifndef NOHW
    m_climbEncoder.Reset();
#endif
}

double ClimbSubsystem::GetDistance()
{
#ifndef NOHW
    return m_climbEncoder.GetDistance();
#else
    return 0.0;
#endif
}

int ClimbSubsystem::GetRaw()
{
#ifndef NOHW
    return m_climbEncoder.GetRaw();
#else
    return 0;
#endif
}

// MOTOR FUNCTIONS

void ClimbSubsystem::ClimbMotor(double speed)
{
#ifndef NOHW
    m_climb.Set(speed);
#endif
}