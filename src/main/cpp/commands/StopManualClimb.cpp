// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/StopManualClimb.h"

StopManualClimb::StopManualClimb(ClimbSubsystem* pClimb)
{
  m_pClimb = pClimb;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pClimb);
}

// Called when the command is initially scheduled.
void StopManualClimb::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void StopManualClimb::Execute()
{
  m_pClimb->ClimbMotor(0.0);
  m_pClimb->SetRatchet(true);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void StopManualClimb::End(bool interrupted) {}

// Returns true when the command should end.
bool StopManualClimb::IsFinished() {
  return m_isFinished;
}
