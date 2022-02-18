// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/LoadInOne.h"

LoadInOne::LoadInOne( LoaderSubsystem *pLOAD, double sped)
 {
m_sped = sped;
  // Use AddRequirements() here to declare subsystem dependencies.
  m_pLoader = pLOAD;
  AddRequirements(m_pLoader);
}

// Called when the command is initially scheduled.
void LoadInOne::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LoadInOne::Execute() 
{
  m_pLoader->InnerLoader(m_sped);
  m_pLoader->IntakeLoader(m_sped);
}

// Called once the command ends or is interrupted.
void LoadInOne::End(bool interrupted) {}

// Returns true when the command should end.
bool LoadInOne::IsFinished() {
  return false;
}
