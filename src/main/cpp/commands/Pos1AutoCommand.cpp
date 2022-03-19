// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Pos1AutoCommand.h"
#include <frc/smartdashboard/SmartDashboard.h>

Pos1AutoCommand::Pos1AutoCommand(DriveTrainSubsystem *pdrive, LoaderSubsystem *pload, ShooterSubsystem *pshoot, double turnAngle) 
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
void Pos1AutoCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Pos1AutoCommand::Execute() 
{
  // Variables.
  double armSpeed = 0.4;
  double intakeSpeed = 0.8;
  double distanceToBall = 45.0;
  double forwardSpeed = 0.6;
  double innerSpeed = 0.8;
  units::degree_t turnAngle = (units::degree_t) m_turnAngle;
  double turnSpeed = 0.2;
  units::degree_t turnDeadZone = (units::degree_t) 5.0;
  double shooterTargetSpeed = 70;
  double StopSpeed = 0.0;


  //1. Drop Arm.
  //m_ploader->AutoArm(armSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 1");

  //2. Turn on Intake.
  m_ploader->IntakeLoader(intakeSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 2");

  //3. Move Forward 45 inches.
  m_pdrive->ForwardInInch(distanceToBall, forwardSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 3");

  //4. Turn 180 degrees.
  m_pdrive->TurnAngleRelative(turnAngle, turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 4");

  //5. Vision Align.
  //m_pdrive->VisionAllign(turnSpeed, turnDeadZone);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 5");

  //6. Turn on shooter.
  m_pshooter->SetShooterSpeed(shooterTargetSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 6");


  //7. Load in Seconds to Shoot.
  m_ploader->LoadToTimer(3.0, innerSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 7");

  //8. Turn off Intake.
  m_ploader->IntakeLoader(StopSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 8");

  //9. Turn off Shooter
  m_pshooter->SetShooterSpeed(StopSpeed);
  frc::SmartDashboard::PutString("Pos1AutoCommand", "Step 9");

  m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void Pos1AutoCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool Pos1AutoCommand::IsFinished() {
  return m_IsFinished;
}
