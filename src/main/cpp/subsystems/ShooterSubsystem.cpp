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
#ifndef NOHW_SENSORS
    m_shooterEncoder.SetDistancePerPulse(m_DISPULSE_SHOOT);
#endif
    ResetEncoder();
}

// ENCODER FUNCTIONS
void ShooterSubsystem::ResetEncoder()
{
#ifndef NOHW_SENSORS
    m_shooterEncoder.Reset();
#endif
}

double ShooterSubsystem::GetShooterSpeed()
{
#ifndef NOHW_SENSORS
    //Units are distance PER SECOND as scaled by SetDistancePerPulse()
    frc::SmartDashboard::PutNumber("ShooterSpeed", -m_shooterEncoder.GetRate());
    return -m_shooterEncoder.GetRate();
#endif
}

double ShooterSubsystem::GetShootDistance()
{
#ifndef NOHW_SENSORS
    frc::SmartDashboard::PutNumber("ShooterDistance", m_shooterEncoder.GetDistance());
    return m_shooterEncoder.GetDistance();
#endif
}
void ShooterSubsystem::ShootToTimer(double time, double speed){
m_shooterMotor.Set(speed);
    Util::DelayInSeconds((units::time::second_t) time);
m_shooterMotor.Set(0.00000);
}
void ShooterSubsystem::SetShooterSpeed(double targetSpeed)
{
    #ifndef NOHW_SENSORS
    //Using a linear function speed= (78)power + 0 (found testing different powers and graphing their speeds)
    // y=mx+b -> x= (y+b)/m
    double power = targetSpeed / 78;

    ShootMotor(power);//set power to negative for C418.
    while(GetShooterSpeed() < targetSpeed) //Set bothe GetShooterSpeed() and targetSpeed to absolute value for C418.
    {
        GetShooterSpeed();
    }
    #endif
}

int ShooterSubsystem::GetEncoderRaw()
{
#ifndef NOHW_SENSORS
    frc::SmartDashboard::PutNumber("ShooterRaw", m_shooterEncoder.GetRaw());
    return m_shooterEncoder.GetRaw();
#endif
}

// SHOOTER FUNCTIONS
void ShooterSubsystem::ShootMotor(double speed)
{
#ifndef NOHW_SENSORS
    m_shooterMotor.Set(speed);
#endif
}