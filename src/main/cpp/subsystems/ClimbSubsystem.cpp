// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#include <frc/Timer.h>
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
    double dist = 0.0;
#ifndef NOHW_CLIMB
    dist = -m_climbEncoder.GetDistance();
#endif
    frc::SmartDashboard::PutNumber("ClimbSub::GetDistance", dist);
    return dist;
}

int ClimbSubsystem::GetRaw()
{
    int raw = 0;
#ifndef NOHW_CLIMB
    raw = m_climbEncoder.GetRaw();
#endif
    frc::SmartDashboard::PutNumber("ClimbSub::GetRaw", raw);
    return raw;
}

// MOTOR FUNCTIONS

void ClimbSubsystem::ClimbMotor(double speed)
{
#ifndef NOHW_CLIMB
    m_climb.Set(speed);
#endif
}

void ClimbSubsystem::ClimbUpInInch(double inch, double speed)
{
#ifndef NOHW_ClIMB
    frc::Timer timer;
    timer.Start();
    units::second_t targetTime = timer.Get() + 3_s;
    
    double currentDistance = GetDistance();
    double targetDistance = currentDistance + fabsf(inch);

    while(currentDistance < targetDistance)
    {
        ClimbMotor(fabsf(speed));
        currentDistance = GetDistance();
        if(timer.Get()>=targetTime)
        {
            break;
        }
    }

    //Stop
    ClimbMotor(0.0);
#endif
}

void ClimbSubsystem::ClimbDownInInch(double inch, double speed)
{
#ifndef NOHW_CLIMB
    frc::Timer timer;
    timer.Start();
    units::second_t targetTime = timer.Get() + 3_s;

    double currentDistance = GetDistance();
    double targetDistance = currentDistance - fabsf(inch);

    while(currentDistance > targetDistance)
    {
        ClimbMotor(-fabsf(speed));
        currentDistance = GetDistance();
        if(timer.Get()>=targetTime)
        {
            break;
        }
    }

    //Stop
    ClimbMotor(0.0);
#endif
}

void ClimbSubsystem::EncoderTest()
{
#ifndef NOHW_CLIMB
    int GetRaw = m_climbEncoder.GetRaw();
    double GetDistancePerPulse = m_climbEncoder.GetDistancePerPulse();
    double GetDistance = m_climbEncoder.GetDistance();
    bool GetDirection = m_climbEncoder.GetDirection();

    frc::SmartDashboard::PutNumber("ClimbSub::GetRaw", GetRaw);
    frc::SmartDashboard::PutNumber("ClimbSub::GetDistancePerPulse", GetDistancePerPulse);
    frc::SmartDashboard::PutNumber("ClimbSub::GetDistance", GetDistance);
    frc::SmartDashboard::PutBoolean("ClimbSub::GetDirection", GetDirection);
#endif
}