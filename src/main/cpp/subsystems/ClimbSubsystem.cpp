// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ClimbSubsystem.h"

ClimbSubsystem::ClimbSubsystem()
{
#ifndef NOHW
    m_encoderBack.SetDistancePerPulse(m_pulseDisBack);
    m_encoderFront.SetDistancePerPulse(m_pulseDisFront);
#endif
}

// This method will be called once per scheduler run
void ClimbSubsystem::Periodic() {}

// ENCODER FUNCTIONS

void ClimbSubsystem::ResetEncoder()
{
#ifndef NOHW
    m_encoderBack.Reset();
    m_encoderFront.Reset();
#endif
}

double ClimbSubsystem::GetFrontDistance()
{
#ifndef NOHW
    return m_encoderFront.GetDistance();
#else
    return 0.0;
#endif
}

double ClimbSubsystem::GetBackDistance()
{
#ifndef NOHW
    return m_encoderBack.GetDistance();
#else
    return 0.0;
#endif
}

int ClimbSubsystem::GetFrontRaw()
{
#ifndef NOHW
    return m_encoderFront.GetRaw();
#else
    return 0;
#endif
}

int ClimbSubsystem::GetBackRaw()
{
#ifndef NOHW
    return m_encoderBack.GetRaw();
#else
    return 0;
#endif
}

// MOTOR FUNCTIONS

void ClimbSubsystem::FrontClimb(double speed)
{
#ifndef NOHW
    m_front.Set(speed);
#endif
}

void ClimbSubsystem::BackClimb(double speed)
{
#ifndef NOHW
    m_back.Set(speed);
#endif
}