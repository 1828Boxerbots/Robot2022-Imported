// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PosWallAutoCommand.h"
#include <Util.h>

PosWallAutoCommand::PosWallAutoCommand
(LoaderSubsystem *pLoader, ShooterSubsystem *pShoot, DriveTrainSubsystem *pDrive, 
double turnAngleToShoot, double turnAngleToLeave) 
{
  m_pLoaderSub = pLoader;
  m_pShooterSub = pShoot;
  m_pDriveSub = pDrive;
  m_turnAngleToShoot = turnAngleToShoot;
  m_turnAngleToLeave = turnAngleToLeave;

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pLoaderSub);
  AddRequirements(m_pShooterSub);
  AddRequirements(m_pDriveSub);
}

// Called when the command is initially scheduled.
void PosWallAutoCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PosWallAutoCommand::Execute() 
{
  // Variables.
  double intakeSpeed = 0.8;
  double distanceToBall = 33.0;
  double distanceToLeave = 40.0;
  double backwardDistance = 27.0;
  double innerSpeed = 0.8;
  units::degree_t turnAngleToShoot = (units::degree_t) m_turnAngleToShoot;
  units::degree_t turnAngleToLeave = (units::degree_t) m_turnAngleToLeave;
  double turnSpeed = 0.2;
  units::degree_t turnDeadZone = (units::degree_t) 5.0;
  double shooterTargetSpeed = 70.0;
  double stopSpeed = 0.0;


  //1. Drop Arm.
  //m_pLoaderSub->AutoArm(armSpeed);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 1");

  //2. Turn on Intake.
  m_pLoaderSub->IntakeLoader(intakeSpeed);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 2");

  //3. Move Forward 42 inches.
  m_pDriveSub->ForwardInInch(distanceToBall, 0.4);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 3");

  //4. Move Backwards a little to counter drift.
  m_pDriveSub->ForwardInTime(0.5, -0.2);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 4");

  Util::DelayInSeconds((units::time::second_t) 3.0);

  //5. Move Backward 30 inches.
  m_pDriveSub->BackwardInInch(backwardDistance, 0.6);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 5");

  //6. Turn 180 degrees.
  m_pDriveSub->TurnAngleRelative(turnAngleToShoot, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 6");

  //7. Vision Align.
  //m_pDriveSub->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 7");

  //8. Turn on Shooter.
  m_pShooterSub->SetShooterSpeed(shooterTargetSpeed);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 8");

  //9. Load in Seconds to Shoot.
  m_pLoaderSub->LoadToTimer(3.0, innerSpeed);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 9");

  //10. Turn off Shooter.
  m_pShooterSub->SetShooterSpeed(stopSpeed);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 10");

  //11. Turn off Intake.
  m_pLoaderSub->IntakeLoader(stopSpeed);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 11");

  //12. Turn 90 degrees to the Right.
  m_pDriveSub->TurnAngleRelative(turnAngleToLeave, turnSpeed);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 12");

  //13. Move Forward 60 inches to leave Tarmac.
  m_pDriveSub->ForwardInInch(distanceToLeave, 0.5);
  frc::SmartDashboard::PutString("PosWallAutoCommand", "Step 13");


 m_isFinished = true;
}

// Called once the command ends or is interrupted.
void PosWallAutoCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool PosWallAutoCommand::IsFinished() {
  return m_isFinished;
}
