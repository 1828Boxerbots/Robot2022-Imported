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
    units::second_t targetTime = timer.Get() + 5_s;
    
    double currentDistance = GetDistance();
    //double targetDistance = currentDistance + fabsf(inch);

    if(currentDistance < inch)
    {
        ClimbMotor(fabsf(speed));
    }
    while(currentDistance < inch)
    {
        SetRatchet(false);
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
    units::second_t targetTime = timer.Get() + 5_s;

    double currentDistance = GetDistance();
    //double targetDistance = currentDistance - fabsf(inch);

    if(currentDistance > fabsf(inch))
    {
        ClimbMotor(-fabsf(speed));
    }
    while(currentDistance > fabsf(inch))
    {
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

void ClimbSubsystem::SetRatchet(bool isEngaged)
{
    #ifndef NOHW_SERVO
    if(isEngaged == true)
    {
        m_servo.SetAngle(0.0);
    }
    else
    {
        m_servo.SetAngle(180.0);
    }
    m_isEngaged = isEngaged;
    #endif
    frc::SmartDashboard::PutBoolean("ClimbSub::PeriodicRatchet isEngaged", m_isEngaged);
}

void ClimbSubsystem::PeriodicRatchet(){}

void ClimbSubsystem::ClimbDistance(double dist, double controllerValueY, double controllerValueX, double speed)
{
    if(controllerValueY > 0.5 || controllerValueY < -0.5)
    {
        if (controllerValueY>=0.5 && m_isTop == false)
        {
            m_isTop = true;
            SetRatchet(false);
            Util::DelayInSeconds(0.5_s);
            //ClimbUpInInch(fabsf(dist), fabsf(speed));
            ClimbUpInInch(25, fabsf(speed));
            SetRatchet(true);
        }
        else if(controllerValueY<=-0.5 && m_isTop == true)
        {
            //ClimbDownInInch(fabsf(dist), fabsf(speed));
            ClimbDownInInch(0, fabsf(speed));
            m_isTop = false;
        }
    }
    else
    {
        GetDistance();
        if(controllerValueX > 0.5)
        {
            SetRatchet(false);
        }
        else if(controllerValueX < -0.5)
        {
            SetRatchet(true);
        }
        ClimbMotor(controllerValueX * 0.5);
    }
}