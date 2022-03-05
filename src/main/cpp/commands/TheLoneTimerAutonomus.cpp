// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TheLoneTimerAutonomus.h"
#include <frc/smartdashboard/SmartDashboard.h>

TheLoneTimerAutonomus::TheLoneTimerAutonomus(DriveTrainSubsystem *pdrive, LoaderSubsystem *pload, ShooterSubsystem *pshoot, double turnAngle) 
{
  m_pdrive = pdrive;
  m_ploader = pload;
  m_pshooter = pshoot;
  m_turnAngle = turnAngle;

  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pdrive);
  AddRequirements(m_ploader);
  AddRequirements(m_pshooter);
}

// Called when the command is initially scheduled.
void TheLoneTimerAutonomus::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TheLoneTimerAutonomus::Execute() 
{
  double armSpeed = 0.4;
  double intakeSpeed = 10.8;
  double distanceToBall = 45.0;
  double forwardSpeed = 0.6;
  double innerSpeed = 0.5;
  units::degree_t turnAngle = (units::degree_t) m_turnAngle;
  double turnSpeed = 0.1;
  units::degree_t turnDeadZone = (units::degree_t) 5.0;
  double shooterTargetSpeed = 70;
  double shooterStopSpeed = 0.0;

  //1. DropArm
  //m_ploader->AutoArm(armSpeed);
    frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 1");

  //2. Turn on Intake 
  m_ploader->IntakeLoader(intakeSpeed);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 2");
  //3. Forward to Ball
  m_pdrive->ForwardInTime(0.76, forwardSpeed);
    frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 3");

  //4. Load Ball 1 to Photo
  m_ploader->LoadToTimer(3.5,innerSpeed);
  m_ploader->IntakeLoader(0);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 4");

  //5. Turn Around 180 Towards Target
  m_pdrive->TurnAngleRelative(turnAngle, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 5");

  //6. Allign Robot to Target to Prepare for Shooting
  //m_pdrive->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 6");

  //7. Shoot Ball 1 Towards Target
  m_pshooter->SetShooterSpeed(shooterTargetSpeed);
  m_ploader->LoadToTimer(1,0);
  m_ploader->LoadToTimer(1);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 7");

  // //8. Load Ball 1 to Shooter
  // m_ploader->LoadToPhoto(innerSpeed, false);
  //   frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 8");

  // //9. Load Ball 2 to Photo
  // m_ploader->LoadToPhoto(innerSpeed, true);
  //   frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 9");

  // //10. Allign Robot to Target to Prepare for Shooting
  // //m_pdrive->VisionAllign(turnSpeed, turnDeadZone);
  //   frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 10");

  // //11. Shoot Ball 2 Towards Target 
  // m_pshooter->SetShooterSpeed(shooterTargetSpeed);
  //   frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 11");

  // //12. Load Ball 2 to Shooter
  // m_ploader->LoadToPhoto(innerSpeed, false);
  //   frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 12");

  // //13. Stop Shooter Motor
  // m_pshooter->SetShooterSpeed(shooterStopSpeed);
  //   frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 13");

  m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void TheLoneTimerAutonomus::End(bool interrupted) {}

// Returns true when the command should end.
bool TheLoneTimerAutonomus::IsFinished() {
  return m_IsFinished;
}
