// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CompetitionCMD.h"

CompetitionCMD::CompetitionCMD(DriveTrainSubsystem *pDrive, ShooterSubsystem *pShoot, LoaderSubsystem *pLoader, double shootSpeed, 
                                double driveSpeed, double driveTime)
{
  m_pDrive = pDrive;
  m_pShoot = pShoot;
  m_pLoader = pLoader;
  m_shootSpeed = shootSpeed;
  m_driveSpeed = driveSpeed;
  m_driveTime = driveTime;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
  AddRequirements(m_pLoader);
  AddRequirements(m_pShoot);
}

// Called when the command is initially scheduled.
void CompetitionCMD::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CompetitionCMD::Execute() 
{
  //Move Arm
  m_pLoader->MoveArm(0.2);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->MoveArm(0.00125);
  Util::DelayInSeconds(0.1_s);
  m_pLoader->MoveArm(0.0);

  //Shoot
  //m_pShoot->SetShooterSpeed(m_shootSpeed);
  m_pShoot->ShootMotor(m_shootSpeed);
  Util::DelayInSeconds(0.5_s);
  m_pLoader->InnerLoader(-0.5);
  Util::DelayInSeconds(1_s);
  m_pLoader->InnerLoader(0.0);
  m_pShoot->ShootMotor(0.0);

  //Back up
  m_pDrive->ForwardInTime(m_driveTime, -m_driveSpeed);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void CompetitionCMD::End(bool interrupted) {}

// Returns true when the command should end.
bool CompetitionCMD::IsFinished() {
  return m_isFinished;
}
