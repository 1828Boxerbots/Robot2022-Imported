// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/StopLoadIntakeCommand.h"

StopLoadIntakeCommand::StopLoadIntakeCommand(LoaderSubsystem* pLoader) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pLoader = pLoader;

  AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void StopLoadIntakeCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void StopLoadIntakeCommand::Execute() 
{
  m_pLoader->InnerLoader(0.0);
}

// Called once the command ends or is interrupted.
void StopLoadIntakeCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool StopLoadIntakeCommand::IsFinished() {
  return false;
}
