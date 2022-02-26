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
  m_pLoader->AutoArm(m_speed);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void AutoArmCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmCommand::IsFinished() {
  return m_isFinished;
}
