// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LoadToShooterCommand.h"

LoadToShooterCommand::LoadToShooterCommand(LoaderSubsystem *ploader, double speed) 
{
  m_pLoader = ploader;
  m_speed = speed;

  // Use addRequirements() here to declare subsystem dependencies.
   AddRequirements(ploader);
}

// Called when the command is initially scheduled.
void LoadToShooterCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LoadToShooterCommand::Execute() 
{
   m_pLoader->LoadToPhoto(m_speed, false, 4.0);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void LoadToShooterCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool LoadToShooterCommand::IsFinished() 
{
  return m_isFinished;
}
