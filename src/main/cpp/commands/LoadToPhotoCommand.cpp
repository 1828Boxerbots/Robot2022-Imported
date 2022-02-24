// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LoadToPhotoCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

LoadToPhotoCommand::LoadToPhotoCommand(LoaderSubsystem *ploader, double speed) 
{
  m_pLoader = ploader;
  m_speed = speed;
  // Use addRequirements() here to declare subsystem dependencies.

  AddRequirements(ploader);
}

// Called when the command is initially scheduled.
void LoadToPhotoCommand::Initialize() 
{
}

// Called repeatedly when this Command is scheduled to run
void LoadToPhotoCommand::Execute() 
{
  m_pLoader->IntakeLoader(m_speed);
  m_pLoader->InnerLoader(-m_speed);

  int count = 0;

  do 
  {
    bool photo = m_pLoader->IsPhotoActive();

    frc::SmartDashboard::PutNumber("LoadToPhotoCommand-Count", count++);
    frc::SmartDashboard::PutBoolean("LoadToPhotoCommand-Photo", photo);
  } while (m_pLoader->IsPhotoActive() == true);

  m_pLoader->IntakeLoader(0.0);
  m_pLoader->InnerLoader(0.0);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void LoadToPhotoCommand::End(bool interrupted) 
{
}

// Returns true when the command should end.
bool LoadToPhotoCommand::IsFinished() 
{
  return m_isFinished;
}
