// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LoadInOne.h"

LoadInOne::LoadInOne( LoaderSubsystem *pLoader, double speed,frc::XboxController *pController)
{
  m_speed = speed;
  // Use AddRequirements() here to declare subsystem dependencies.
  m_pLoader = pLoader;
  m_pController = pController;
  AddRequirements(m_pLoader);
}

// Called when the command is initially scheduled.
void LoadInOne::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LoadInOne::Execute() 
{
  if(m_pController->GetLeftBumper()&&m_pController != nullptr)
  {
    m_pLoader->IntakeLoader(-m_speed);
    m_pLoader->InnerLoader(-m_speed);  
  }
  else
  {
    m_pLoader->IntakeLoader(m_speed);
    m_pLoader->InnerLoader(m_speed);
  }
}

// Called once the command ends or is interrupted.
void LoadInOne::End(bool interrupted) {}

// Returns true when the command should end.
bool LoadInOne::IsFinished() {
  return m_isFinished;
}
