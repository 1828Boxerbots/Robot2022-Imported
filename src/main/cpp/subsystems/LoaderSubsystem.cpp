// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/LoaderSubsystem.h"

LoaderSubsystem::LoaderSubsystem() = default;

// This method will be called once per scheduler run
void LoaderSubsystem::Periodic() {}

// ARM FUNCTIONS

double LoaderSubsystem::GetServo()
{
#ifndef NOHW
    return m_armServo.Get();
#else
    return 0.0;
#endif
}

void LoaderSubsystem::SetServoAngle(double angle)
{
#ifndef NOHW
    m_armServo.Set(angle);
#endif
}

// MOTOR INTAKE FUNCTIONS

void LoaderSubsystem::IntakeLoader(double speed)
{
#ifndef NOHW
    m_intake.Set(speed);
#endif
}

void LoaderSubsystem::InnerLoader(double speed)
{
#ifndef NOHW
    m_inner.Set(speed);
#endif
}

// PHOTOGATE FUNCTIONS

bool LoaderSubsystem::IsPhotoActive()
{
#ifndef NOHW
    return true;
#else
    return false;
#endif
}