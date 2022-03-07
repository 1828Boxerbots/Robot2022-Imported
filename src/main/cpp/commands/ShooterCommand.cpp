// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShooterCommand.h"

ShooterCommand::ShooterCommand(ShooterSubsystem * pShoot, double speed)
{
  m_pShooter = pShoot;
  AddRequirements(pShoot);
  m_speed=speed;
}

// Called when the command is initially scheduled.
void ShooterCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ShooterCommand::Execute() 
{
  frc::SmartDashboard::PutNumber("Shooter Speed: RPS ", m_pShooter->GetShooterSpeed());
  m_pShooter->ShootMotor(m_speed);
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void ShooterCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ShooterCommand::IsFinished() {
  return m_isFinished;
}