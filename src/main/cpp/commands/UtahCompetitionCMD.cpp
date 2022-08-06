// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/UtahCompetitionCMD.h"

UtahCompetitionCMD::UtahCompetitionCMD(DriveTrainSubsystem* pDrive, LoaderSubsystem* pLoader, ShooterSubsystem* pShoot,
                                        double driveSpeed, double shootSpeed)
{
  m_pDrive = pDrive;
  m_pLoader = pLoader;
  m_pShoot = pShoot;
  m_driveSpeed = driveSpeed;
  m_shootSpeed = shootSpeed;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pDrive);
  AddRequirements(m_pLoader);
  AddRequirements(m_pShoot);
}

// Called when the command is initially scheduled.
void UtahCompetitionCMD::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void UtahCompetitionCMD::Execute()
{
  // Drop Arm
  m_pLoader->MoveArm(0.3);
  Util::DelayInSeconds(0.75_s);
  m_pLoader->MoveArm(0.0);

  // Start Shoot
  //m_pShoot->MotorVoltage((units::volt_t)m_shootSpeed);
  m_pShoot->ShootMotor(m_shootSpeed);
  Util::DelayInSeconds(1_s);
  // Back up
  m_pDrive->ForwardInTime(1.0, -m_driveSpeed);
  // Shoot / Load
  m_pLoader->InnerLoader(-0.5);
  Util::DelayInSeconds(1_s);
  m_pLoader->InnerLoader(0.0);
  m_pShoot->ShootMotor(0.0);
  // Back up more
  m_pDrive->ForwardInTime(0.5, -m_driveSpeed);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void UtahCompetitionCMD::End(bool interrupted) {}

// Returns true when the command should end.
bool UtahCompetitionCMD::IsFinished() {
  return m_isFinished;
}
