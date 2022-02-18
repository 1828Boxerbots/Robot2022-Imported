// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/ShooterSubsystem.h"

ShooterSubsystem::ShooterSubsystem()
{
#ifndef NOHW
    m_shooterEncoder.SetDistancePerPulse(m_pulseDisShoot);
#endif
}

// This method will be called once per scheduler run
void ShooterSubsystem::Periodic() {}

// ENCODER FUNCTIONS
void ShooterSubsystem::ResetEncoder()
{
#ifndef NOHW
    m_shooterEncoder.Reset();
#endif
}

double ShooterSubsystem::GetEncoderSpeed()
{
#ifndef NOHW
    //Units are distance PER SECOND as scaled by SetDistancePerPulse()
    return m_shooterEncoder.GetRate();
#endif
}

int ShooterSubsystem::GetEncoderRaw()
{
#ifndef NOHW
    return m_shooterEncoder.GetRaw();
#endif
}

// SHOOTER FUNCTIONS
void ShooterSubsystem::ShootMotor(double speed)
{
#ifndef NOHW
    m_shooterMotor.Set(speed);
#endif
}