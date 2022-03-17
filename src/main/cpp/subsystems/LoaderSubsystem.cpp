// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/LoaderSubsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Util.h"
LoaderSubsystem::LoaderSubsystem() = default;

// This method will be called once per scheduler run
void LoaderSubsystem::Periodic() {}

void LoaderSubsystem::Init() {}

// MOTOR INTAKE FUNCTIONS

void LoaderSubsystem::IntakeLoader(double speed)
{
#ifndef NOHW
    m_intake.Set(speed);
#endif
}
void LoaderSubsystem::LoadToTimer(double time, double speed)
{
    InnerLoader(-speed);
    // IntakeLoader(speed);
    Util::DelayInSeconds((units::time::second_t) time);
    InnerLoader(0.0);
    // IntakeLoader(0.0);
}
void LoaderSubsystem::InnerLoader(double speed)
{
#ifndef NOHW
    m_inner.Set(speed);
    m_innerUp.Set(speed);
#endif
}

// PHOTOGATE FUNCTIONS

bool LoaderSubsystem::IsPhotoActive()
{
        frc::SmartDashboard::PutNumber("LoaderSubsystem-HeartBeat", m_heartBeat++);

#ifndef NOHW
    frc::SmartDashboard::PutBoolean("LoaderSubsystem-IsPhotoActive", m_photogate.Get());

    return m_photogate.Get();
#else
    return false;
#endif
}

// ARM FUNCTIONS

void LoaderSubsystem::MoveArm(double speed)
{
#ifndef NOHW
    m_arm.Set(speed);
#endif
}

bool LoaderSubsystem::IsLowLimitSwitchActive()
{
  frc::SmartDashboard::PutNumber("LoaderSubsystem-HeartBeat", m_heartBeat++);

    bool Low= false;
  
   #ifndef NOHW
    bool High = m_limitSwitchHigh.Get();
    Low= m_limitSwitchLow.Get();


    frc::SmartDashboard::PutBoolean("LoaderSubsystem-IsHighLimitSwitchActive", High);
    frc::SmartDashboard::PutBoolean("LoaderSubsystem-IsLowLimitSwitchActive", Low);

    return Low;
#else
    return false;
#endif
}

bool LoaderSubsystem::IsHighLimitSwitchActive()
{
    frc::SmartDashboard::PutNumber("LoaderSubsystem-HeartBeat", m_heartBeat++);

    bool High= false;
  
   #ifndef NOHW
    bool Low = m_limitSwitchLow.Get();
    High= m_limitSwitchHigh.Get();


    frc::SmartDashboard::PutBoolean("LoaderSubsystem-IsHighLimitSwitchActive", High);
    frc::SmartDashboard::PutBoolean("LoaderSubsystem-IsLowLimitSwitchActive", Low);

    return High;
#else
    return false;
#endif
}

void LoaderSubsystem::LoadToPhoto(double speed, bool loadToShoot, double timeOut)
{
  m_timer.Reset();
  m_timer.Start();

  double startTime = (double) m_timer.Get();

  IntakeLoader(speed);
  InnerLoader(-speed);

  int count = 0;

  do 
  {
    bool photo = IsPhotoActive();
    double currentTime = (double) m_timer.Get() - startTime;

    frc::SmartDashboard::PutNumber("LoadToPhotoCommand-Count", count++);
    frc::SmartDashboard::PutBoolean("LoadToPhotoCommand-Photo", photo);
    frc::SmartDashboard::PutNumber("LoadToPhotoCommand-Timer", currentTime);
    frc::SmartDashboard::PutNumber("LoadToPhotoCommand-StartTime", startTime);

    if(currentTime > timeOut)
    {
      break;
    }

  } while (IsPhotoActive() == loadToShoot);

  IntakeLoader(0.0);
  InnerLoader(0.0);

  m_timer.Stop();
}

void LoaderSubsystem::AutoArm(double speed)
{
#ifndef NOHW_SENSORS
 frc::SmartDashboard::PutString("AutoArmCommand", "Execute Start");
  MoveArm(0.0);

  int count = 0;
  //Assuming the speed >0 is up while speed < 0 is down
  if (speed > 0)
  {
    frc::SmartDashboard::PutString("AutoArmCommand 1", "speed>0");

     while (IsHighLimitSwitchActive() == true)
    {
      MoveArm(fabsf(speed));
      bool HigherLimitSwitch = IsHighLimitSwitchActive();
      frc::SmartDashboard::PutNumber("AutoArmCommand-Count", count++);
      frc::SmartDashboard::PutNumber("LoaderSubsystem-HigherLimitSwitch", HigherLimitSwitch);
    } 
  }

  else if (speed < 0) 
  {
    frc::SmartDashboard::PutString("AutoArmCommand 1", "speed<0");

    while (IsLowLimitSwitchActive() == true)
    {
      MoveArm(-fabsf(speed));
      bool LowerLimitSwitch = IsLowLimitSwitchActive();
      frc::SmartDashboard::PutNumber("AutoArmCommand-Count", count++);
      frc::SmartDashboard::PutNumber("LoaderSubsystem-LowerLimitSwitch", LowerLimitSwitch);
    } 
  } 
  else
  {
    frc::SmartDashboard::PutString("AutoArmCommand 1", "speed=0");
  }

    frc::SmartDashboard::PutString("AutoArmCommand", "Execute End");


  MoveArm(0.0);
#endif
}