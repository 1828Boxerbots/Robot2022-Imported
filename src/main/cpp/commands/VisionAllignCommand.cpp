// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionAllignCommand.h"

VisionAllignCommand::VisionAllignCommand(DriveTrainSubsystem *pDrive, LoaderSubsystem *pLoader, ShooterSubsystem *pShooter, double speed, units::degree_t deadZone)
{
  m_pDrive = pDrive;
  m_pLoader = pLoader;
  m_pShooter = pShooter;
  m_speed = speed;
  m_deadZone = deadZone;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void VisionAllignCommand::Initialize()
{ }

// Called repeatedly when this Command is scheduled to run
void VisionAllignCommand::Execute()
{
  m_pDrive->MoveTank(0.0, 0.0);
  m_pLoader->InnerLoader(0.0);
  m_pLoader->IntakeLoader(0.0);
  m_pShooter->ShootMotor(0.0);
  m_pDrive->VisionAllign(m_speed, m_deadZone);
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void VisionAllignCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionAllignCommand::IsFinished()
{
  return m_isFinished;
}
