// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/StopLoadInnerCommand.h"

StopLoadInnerCommand::StopLoadInnerCommand(LoaderSubsystem* pLoader) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pLoader = pLoader;

  AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void StopLoadInnerCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void StopLoadInnerCommand::Execute() 
{
  m_pLoader->InnerLoader(0.0);
}

// Called once the command ends or is interrupted.
void StopLoadInnerCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool StopLoadInnerCommand::IsFinished() {
  return false;
}
