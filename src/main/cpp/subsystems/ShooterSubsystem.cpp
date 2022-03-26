// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project. 

#include "subsystems/ShooterSubsystem.h"
#include "Util.h"
ShooterSubsystem::ShooterSubsystem(){}

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {}

void ShooterSubsystem::Init()
{
#ifndef NOHW
    m_shooterEncoder.SetDistancePerPulse(m_DISPULSE_SHOOT);
#endif
    ResetEncoder();
}

// ENCODER FUNCTIONS
void ShooterSubsystem::ResetEncoder()
{
#ifndef NOHW
    m_shooterEncoder.Reset();
#endif
}

double ShooterSubsystem::GetShooterSpeed()
{
double speed = 0.0;
#ifndef NOHW
    //Units are distance PER SECOND as scaled by SetDistancePerPulse()
    speed = -m_shooterEncoder.GetRate();
#endif
    frc::SmartDashboard::PutNumber("ShooterSub::Speed", speed);
    return speed;
}

double ShooterSubsystem::GetShootDistance()
{
    double dist = 0.0;
#ifndef NOHW
    dist = m_shooterEncoder.GetDistance();
#endif
    frc::SmartDashboard::PutNumber("ShooterSub::GetShootDistance", dist);
    return dist;
}

void ShooterSubsystem::ShootToTimer(double time, double speed)
{
#ifndef NOHW
    m_shooterMotor.Set(speed);
    Util::DelayInSeconds((units::time::second_t) time);
    m_shooterMotor.Set(0.00000);
#endif
}
void ShooterSubsystem::SetShooterSpeed(double targetSpeed)
{
    #ifndef NOHW
    frc::Timer timer;
    timer.Start();
    units::second_t targetTime = timer.Get() + 3_s;
    //Using a linear function speed= (78)power + 0 (found testing different powers and graphing their speeds)
    // y=mx+b -> x= (y+b)/m
    double power = targetSpeed / 78;

    ShootMotor(power);//set power to negative for C418.
    while(GetShooterSpeed() < targetSpeed) //Set bothe GetShooterSpeed() and targetSpeed to absolute value for C418.
    {
        GetShooterSpeed();
        if(timer.Get()>=targetTime)
        {
            break;
        }
    }
    #endif
}

int ShooterSubsystem::GetEncoderRaw()
{
    int raw = 0;
#ifndef NOHW
    raw = m_shooterEncoder.GetRaw();
#endif
    frc::SmartDashboard::PutNumber("ShooterRaw", raw);
    return raw;
}

// SHOOTER FUNCTIONS
void ShooterSubsystem::ShootMotor(double speed)
{
#ifndef NOHW
    m_shooterMotor.Set(speed);
    frc::SmartDashboard::PutNumber("ShootMotor-Speed",speed);
#endif
}