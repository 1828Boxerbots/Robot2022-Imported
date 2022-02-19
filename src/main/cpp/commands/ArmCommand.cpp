// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ArmCommand.h"

ArmCommand::ArmCommand(LoaderSubsystem *pLoader, double speed)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pLoader = pLoader;
  m_speed = speed;
  AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void ArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ArmCommand::Execute() 
{
  m_pLoader->MoveArm(m_speed);
}

// Called once the command ends or is interrupted.
void ArmCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ArmCommand::IsFinished() {
  return false;
}
