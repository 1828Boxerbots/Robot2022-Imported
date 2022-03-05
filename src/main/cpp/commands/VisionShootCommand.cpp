// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionShootCommand.h"

VisionShootCommand::VisionShootCommand(DriveTrainSubsystem* pDrive, ShooterSubsystem* pShooter, LoaderSubsystem* pLoader, double targetSpeed, double driveSpeed, 
                      double loadSpeed, double loadTime, units::degree_t deadZone)
{
  m_pDrive = pDrive;
  m_pShooter = pShooter;
  m_pLoader = pLoader;
  m_targetSpeed = targetSpeed;
  m_driveSpeed = driveSpeed;
  m_loadSpeed = loadSpeed;
  m_loadTime = loadTime;
  m_deadZone = deadZone;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
  AddRequirements(m_pShooter);
  AddRequirements(m_pLoader);
}

// Called when the command is initially scheduled.
void VisionShootCommand::Initialize()
{}

// Called repeatedly when this Command is scheduled to run
void VisionShootCommand::Execute()
{
  // Vision Allign
  if(m_pDrive->VisionAllign(m_driveSpeed, m_deadZone))
  {

    //Calculate the speed of the shooter needed

    // ShootSpeed
    m_pShooter->SetShooterSpeed(m_targetSpeed);

    m_pLoader->LoadToTimer(m_loadTime, m_loadSpeed);

    m_pShooter->ShootMotor(0.0);
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void VisionShootCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionShootCommand::IsFinished() {
  return m_isFinished;
}
