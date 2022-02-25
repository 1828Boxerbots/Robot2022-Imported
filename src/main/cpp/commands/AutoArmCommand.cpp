// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoArmCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>

AutoArmCommand::AutoArmCommand(LoaderSubsystem *pLoader, double speed)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pLoader = pLoader;
  m_speed = speed;
  AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void AutoArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoArmCommand::Execute() 
{
  frc::SmartDashboard::PutString("AutoArmCommand", "Execute Start");
  m_pLoader->MoveArm(0.0);

  int count = 0;
  //Assuming the m_speed >0 is up while m_speed < 0 is down
  if (m_speed > 0)
  {
    frc::SmartDashboard::PutString("AutoArmCommand 1", "speed>0");

     while (m_pLoader->IsHighLimitSwitchActive() == true)
    {
      m_pLoader->MoveArm(fabsf(m_speed));
      bool HigherLimitSwitch = m_pLoader->IsHighLimitSwitchActive();
      frc::SmartDashboard::PutNumber("AutoArmCommand-Count", count++);
    } 
  }

  else if (m_speed < 0) 
  {
    frc::SmartDashboard::PutString("AutoArmCommand 1", "speed<0");

    while (m_pLoader->IsLowLimitSwitchActive() == true)
    {
      m_pLoader->MoveArm(-fabsf(m_speed));
      bool LowerLimitSwitch = m_pLoader->IsLowLimitSwitchActive();
      frc::SmartDashboard::PutNumber("AutoArmCommand-Count", count++);
    } 
  } 
  else
  {
    frc::SmartDashboard::PutString("AutoArmCommand 1", "speed=0");
  }

    frc::SmartDashboard::PutString("AutoArmCommand", "Execute End");


  m_pLoader->MoveArm(0.0);
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void AutoArmCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmCommand::IsFinished() {
  return m_isFinished;
}
