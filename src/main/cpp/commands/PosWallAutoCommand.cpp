// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PosWallAutoCommand.h"

PosWallAutoCommand::PosWallAutoCommand
(LoaderSubsystem *pLoader, ShooterSubsystem *pShoot, DriveTrainSubsystem *pDrive, 
double turnAngleToShoot, double distanceBack, double turnAngleToLeave) 
{
  m_pLoaderSub = pLoader;
  m_pShooterSub = pShoot;
  m_pDriveSub = pDrive;
  m_turnAngleToShoot = turnAngleToShoot;
  m_turnAngleToLeave = turnAngleToLeave;
  m_distanceBack = distanceBack;

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
  double armSpeed = 0.4;
  double intakeSpeed = 0.8;
  double distanceToBall = 42.0;
  double distanceToLeave = 60.0;
  double backwardDistance = 30.0;
  double driveTrainSpeed = 0.4; 
  double innerSpeed = 0.25;
  double innerTime = 0.0;
  units::degree_t turnAngleToShoot = (units::degree_t) m_turnAngleToShoot;
  units::degree_t turnAngleToLeave = (units::degree_t) m_turnAngleToLeave;
  double turnSpeed = 0.2;
  units::degree_t turnDeadZone = (units::degree_t) 5.0;
  double shooterTargetSpeed = 70;
  double shooterStopSpeed = 0.0;
  double timeLimit = 8.0;


  //1. Drop arm.
  //m_pLoaderSub->IntakeLoader(armSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-WallSteps", "step 1");

  //2. Turn on intake loader.
  m_pLoaderSub->IntakeLoader(intakeSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 2");

  //3. Move forward to ball.
  m_pDriveSub->ForwardInInch(distanceToBall, driveTrainSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 3");

  //4. Stop intake.
  m_pLoaderSub->IntakeLoader(0.0);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 4");

  //5. Move backwards.
  m_pDriveSub->BackwardInInch(backwardDistance, driveTrainSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 5");

  //6. Turn 180 degrees to shoot.
  m_pDriveSub->TurnAngleRelative(turnAngleToShoot, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 6");

  //7. VisionAllign.
  //m_pDriveSub->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 7");

  //8. Load to Photo Ball 1.
  m_pLoaderSub->LoadToPhoto(innerSpeed, true, timeLimit);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 8");

  //9. Turn on Shooter.
  m_pShooterSub->SetShooterSpeed(shooterTargetSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 9");

  //10. Load to Shoot Ball 1.
  m_pLoaderSub->LoadToPhoto(innerSpeed, false, timeLimit);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 10");

  //11. VisionAllign.
  //m_pDriveSub->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 11");

  //12. Load to Photo Ball 2.
  m_pLoaderSub->LoadToPhoto(innerSpeed, true, timeLimit);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 12");

  //13. Turn on Shooter.
  m_pShooterSub->SetShooterSpeed(shooterTargetSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 13");

  //14. Load to Shoot Ball 2.
  m_pLoaderSub->LoadToPhoto(innerSpeed, false, timeLimit);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 14");

  //15. Turn off Shooter.
  m_pShooterSub->SetShooterSpeed(shooterStopSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 15");

  //16. Turn 90 degrees to leave tarmac.
  m_pDriveSub->TurnAngleRelative(turnAngleToLeave, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 16");

  //17. Move forward to leave tarmac.
  m_pDriveSub->ForwardInInch(distanceToLeave, driveTrainSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 17");
  
 
 m_isFinished = true;
}

// Called once the command ends or is interrupted.
void PosWallAutoCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool PosWallAutoCommand::IsFinished() {
  return m_isFinished;
}
