// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/VisionShootCommand.h"

VisionShootCommand::VisionShootCommand(DriveTrainSubsystem* pDrive, ShooterSubsystem* pShooter, LoaderSubsystem* pLoader, double driveSpeed, double loadSpeed, units::degree_t deadZone)
{
  m_pDrive = pDrive;
  m_pShooter = pShooter;
  m_pLoader = pLoader;
  m_driveSpeed = driveSpeed;
  m_loadSpeed = loadSpeed;
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
  // LoadToPhoto
  m_pLoader->LoadToPhoto(m_loadSpeed);
  // Vision Allign
  m_pDrive->VisionAllign(m_driveSpeed, m_deadZone);

  //Calculate the speed of the shooter needed

  // ShootSpeed
  m_pShooter->SetShooterSpeed(50);

  m_isFinished = true;
}

void VisionShootCommand::LoadToPhoto()
{
  m_pLoader->IntakeLoader(m_loadSpeed);
  m_pLoader->InnerLoader(-m_loadSpeed);

  do 
  {
    bool photo = m_pLoader->IsPhotoActive();

    frc::SmartDashboard::PutBoolean("VisionShootCMD-Photo", photo);
  } while (m_pLoader->IsPhotoActive() == true);

  m_pLoader->IntakeLoader(0.0);
  m_pLoader->InnerLoader(0.0);
}

// Called once the command ends or is interrupted.
void VisionShootCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool VisionShootCommand::IsFinished() {
  return m_isFinished;
}
