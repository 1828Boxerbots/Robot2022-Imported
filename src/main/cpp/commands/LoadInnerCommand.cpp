// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LoadInnerCommand.h"
#include "constants.h"
LoadInnerCommand::LoadInnerCommand(LoaderSubsystem* pLoader,frc::XboxController *box, double speed) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pLoader = pLoader;
  m_speed = speed;
  m_pxBox = box;
  AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void LoadInnerCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LoadInnerCommand::Execute()
{
  if(m_pxBox!=nullptr&&m_pxBox->GetLeftBumper())
  {
    m_pLoader->InnerLoader(-m_speed);
  }
  else
  {
    m_pLoader->InnerLoader(m_speed);
  }
}

// Called once the command ends or is interrupted.
void LoadInnerCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool LoadInnerCommand::IsFinished() {
  return m_isFinished;
}