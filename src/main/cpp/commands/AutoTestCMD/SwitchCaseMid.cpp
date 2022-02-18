// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/AutoTestCMD/SwitchCaseMid.h"

SwitchCaseMid::SwitchCaseMid(DriveTrainSubsystem* pDrive) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void SwitchCaseMid::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SwitchCaseMid::Execute() 
{
  //FOrward 3 feet
  m_pDrive->ForwardInInch(36);
  //Stop
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void SwitchCaseMid::End(bool interrupted) {}

// Returns true when the command should end.
bool SwitchCaseMid::IsFinished() {
  return m_isFinished;
}
