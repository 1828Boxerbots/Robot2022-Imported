// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/SmartLoadCommand.h"

SmartLoadCommand::SmartLoadCommand() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void SmartLoadCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SmartLoadCommand::Execute() {}

// Called once the command ends or is interrupted.
void SmartLoadCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool SmartLoadCommand::IsFinished() {
  return false;
}
