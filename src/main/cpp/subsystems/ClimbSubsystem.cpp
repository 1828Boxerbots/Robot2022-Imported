// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ClimbSubsystem.h"

ClimbSubsystem::ClimbSubsystem()
{
#ifndef NOHW
    m_encoderFront.SetDistancePerPulse(m_pulseDisFront);
#endif
}

// This method will be called once per scheduler run
void ClimbSubsystem::Periodic() {}

// ENCODER FUNCTIONS

void ClimbSubsystem::ResetEncoder()
{
#ifndef NOHW
    m_encoderFront.Reset();
#endif
}

double ClimbSubsystem::GetDistance()
{
#ifndef NOHW
    return m_encoderFront.GetDistance();
#else
    return 0.0;
#endif
}

int ClimbSubsystem::GetRaw()
{
#ifndef NOHW
    return m_encoderFront.GetRaw();
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