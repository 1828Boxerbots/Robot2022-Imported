// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShootTriggerController.h"

ShootTriggerController::ShootTriggerController(ShooterSubsystem* pShooter, frc::XboxController* pController)
{
  m_pController = pController;
  m_pShooter = pShooter;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pShooter);
}

// Called when the command is initially scheduled.
void ShootTriggerController::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ShootTriggerController::Execute()
{
  m_pShooter->ShootMotor(m_pController->GetRightTriggerAxis());
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void ShootTriggerController::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootTriggerController::IsFinished() {
  return m_isFinished;
}
