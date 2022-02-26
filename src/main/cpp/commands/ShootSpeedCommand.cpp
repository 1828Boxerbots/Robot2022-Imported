// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ShootSpeedCommand.h"

ShootSpeedCommand::ShootSpeedCommand(ShooterSubsystem* pShooter, LoaderSubsystem* pLoader, double targetSpeed)
{
  m_pShooter = pShooter;
  m_pLoader = pLoader;
  m_targetSpeed = targetSpeed;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pShooter);
  AddRequirements(m_pLoader);
}

// Called when the command is initially scheduled.
void ShootSpeedCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ShootSpeedCommand::Execute()
{
  //Using a linear function speed= (1565)power + 0 (found testing different powers and graphing their speeds)
  // y=mx+b -> x= (y+b)/m
  double power = m_targetSpeed / 1565;

  m_pShooter->ShootMotor(-power);
  while(m_pShooter->GetShooterSpeed() < m_targetSpeed)
  {
    m_pShooter->GetShooterSpeed();
  }
  
  while(!m_pLoader->IsPhotoActive())
  {
    m_pLoader->InnerLoader(-1.0);
  }

  m_pShooter->ShootMotor(0.0);
  m_pLoader->InnerLoader(0.0);
}

// Called once the command ends or is interrupted.
void ShootSpeedCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ShootSpeedCommand::IsFinished() {
  return false;
}
