// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoArmCommand.h"

AutoArmCommand::AutoArmCommand(LoaderSubsystem *pLoader, double speed, units::second_t moveTime)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pLoader = pLoader;
  m_speed = speed;
  m_moveTime = moveTime;
  AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void AutoArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoArmCommand::Execute() 
{
  m_pLoader->MoveArm(m_speed);
  Util::DelayInSeconds(m_moveTime);
  m_pLoader->MoveArm(0.0);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void AutoArmCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmCommand::IsFinished() {
  return m_isFinished;
}
