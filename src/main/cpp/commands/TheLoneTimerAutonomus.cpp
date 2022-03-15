// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/TheLoneTimerAutonomus.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include "Util.h"

TheLoneTimerAutonomus::TheLoneTimerAutonomus(DriveTrainSubsystem *pdrive, LoaderSubsystem *pload, ShooterSubsystem *pshoot, double speed, double turnAngle) 
{
  m_pdrive = pdrive;
  m_ploader = pload;
  m_pshooter = pshoot;
  m_turnAngle = turnAngle;

  forwardSpeed = speed;

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
  double intakeSpeed = 10.8;
  double innerSpeed = 0.5;
  units::degree_t turnAngle = (units::degree_t) m_turnAngle;
  double turnSpeed = 0.15;
  units::degree_t turnDeadZone = (units::degree_t) 2.0;
  double shooterTargetSpeed = 45.0; //74


  //1. DropArm
    //m_ploader->AutoArm(armSpeed);
    m_ploader->MoveArm(0.2);
    Util::DelayInSeconds(0.5_s);
    m_ploader->MoveArm(0.0);
    frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 1");

  //2. Turn on Intake 
  //m_ploader->IntakeLoader(intakeSpeed);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 2");
  
  //3. Forward to Ball
  // 0.76 to avoid wall
  m_pdrive->ForwardInTime(1, forwardSpeed);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 3");
  Util::DelayInSeconds(1.0_s);

  //5. Turn Around 180 Towards Target
  m_ploader->IntakeLoader(0);
  // m_pdrive->TurnAngleRelative(turnAngle, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 5");

  // 6. Allign Robot to Target to Prepare for Shooting
  // m_pdrive->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 6");

  // 7-8. Shoot Ball 1 Towards Target
  //m_pshooter->SetShooterSpeed(shooterTargetSpeed);
  Util::Log("TheLoneTimerAutonomus-Steps","step 7");
  //m_ploader->LoadToTimer(1.5,0.6);
  frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 8");

  //10. Allign Robot to Target to Prepare for Shooting
  // m_pdrive->VisionAllign(turnSpeed, turnDeadZone);
    frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 10");

  //11. Shoot Ball 2 Towards Target 
  //m_pshooter->SetShooterSpeed(shooterTargetSpeed);
    frc::SmartDashboard::PutString("TheLoneTimerAutonomus-Steps", "step 11");

  //12. Load Ball 2 to Shooter  
  //m_ploader->LoadToTimer(3,innerSpeed);
  //m_pshooter->ShootMotor(0.0);

  m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void TheLoneTimerAutonomus::End(bool interrupted) {}

// Returns true when the command should end.
bool TheLoneTimerAutonomus::IsFinished() {
  return m_IsFinished;
}
