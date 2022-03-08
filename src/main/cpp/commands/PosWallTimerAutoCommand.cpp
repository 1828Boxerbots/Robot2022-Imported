// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/PosWallTimerAutoCommand.h"
#include "Util.h"

PosWallTimerAutoCommand::PosWallTimerAutoCommand(LoaderSubsystem *pLoader, ShooterSubsystem *pShoot, DriveTrainSubsystem *pDrive,
double turnAngleToShoot, double TurnAngleToLeave) 
{
  m_pLoaderSub = pLoader;
  m_pShootSub = pShoot;
  m_pDriveSub = pDrive;
  m_turnAngleToShoot = turnAngleToShoot;
  m_turnAngleToLeave = TurnAngleToLeave;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pLoaderSub);
  AddRequirements(m_pShootSub);
  AddRequirements(m_pDriveSub);
}

// Called when the command is initially scheduled.
void PosWallTimerAutoCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PosWallTimerAutoCommand::Execute() 
{
   // Variables.
  double armSpeed = 0.4;
  double intakeSpeed = 0.8;
  units::degree_t turnAngleToShoot = (units::degree_t) m_turnAngleToShoot;
  units::degree_t turnAngleToLeave = (units::degree_t) m_turnAngleToLeave;
  double turnSpeed = 0.2;
  units::degree_t turnDeadZone = (units::degree_t) 5.0;
  double shooterTargetSpeed = 70.0;
  double shooterStopSpeed = 0.0;
  double loadTimeToLoadPartI = 1.25;
  double loadTimeToLoadPartII = 3.0;
  double counterMovement = 0.5;


  //1. Drop arm.
  //m_pLoaderSub->AutoArmInTime(armSpeed, 0.4);
  frc::SmartDashboard::PutString("Pos1AutoCommand-WallSteps", "step 1");

  //2. Turn on intake loader.
  m_pLoaderSub->IntakeLoader(intakeSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 2");

  //3. Move forward to ball 42 inches (changing the speed or time can affect the distance).
  m_pDriveSub->ForwardInTime(1.2, 0.4); 
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 3");

  //4. Move backwards 30 inches (changing the speed or time can affect the distance).
  m_pDriveSub->ForwardInTime(0.95, -0.4);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 4");

  //5. Move forward to counter drift (changing the speed or time can affect the distance).
  m_pDriveSub->ForwardInTime(0.03, -0.4);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 5");

  //6. Turn 180 degrees to shoot.
  m_pDriveSub->TurnAngleRelative(turnAngleToShoot, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 6");

  //7. VisionAllign.
  //m_pDriveSub->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 7");

    //8. Turn on Shooter.
  m_pShootSub->SetShooterSpeed(shooterTargetSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 8");

  Util::DelayInSeconds((units::time::second_t)0.5);

  //9. Load to Timer Ball 1.
  m_pLoaderSub->LoadToTimer(loadTimeToLoadPartI, 0.6);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 9");

  //10. VisionAllign.
  //m_pDriveSub->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 10");

    //11. Turn on Shooter.
  m_pShootSub->SetShooterSpeed(shooterTargetSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 11");

  //12. Load to Timer Ball 2.
  m_pLoaderSub->LoadToTimer(loadTimeToLoadPartII, 0.5);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 12");


  //13. Turn off Shooter.
  m_pShootSub->SetShooterSpeed(shooterStopSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 13");

  //14. Stop intake.
  m_pLoaderSub->IntakeLoader(0.0);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 14");

  //15. Turn 90 degrees to leave tarmac.
  m_pDriveSub->TurnAngleRelative(turnAngleToLeave, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 15");

  //16. Move forward to leave tarmac (changing the speed or time can affect the distance, and it needs to have enough to leave tarmac).
  m_pDriveSub->ForwardInTime(3.0, 0.4);
  frc::SmartDashboard::PutString("Pos1AutoCommand-Steps", "step 16");
  
 
 m_isFinished = true;
}

// Called once the command ends or is interrupted.
void PosWallTimerAutoCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool PosWallTimerAutoCommand::IsFinished() {
  return m_isFinished;
}
