// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/Pos1AutoCommand.h"

Pos1AutoCommand::Pos1AutoCommand(DriveTrainSubsystem *pdrive, LoaderSubsystem *pload, ShooterSubsystem *pshoot) 
{
  m_pdrive = pdrive;
  m_ploader = pload;
  m_pshooter = pshoot;

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
  double armSpeed = 0.4;
  double intakeSpeed = 0.8;
  double distanceToBall = 40.375;
  double forwardSpeed = 0.6;
  double innerSpeed = 0.5;
  units::degree_t turnAngle = (units::degree_t) 180.0;
  double turnSpeed = 0.3;
  units::degree_t turnDeadZone = (units::degree_t) 0.5;
  double shooterSpeed = 0.7;

  //1. DropArm
  m_ploader->AutoArm(armSpeed);

  //2. Turn on Intake 
  m_ploader->IntakeLoader(intakeSpeed);

  //3. Forward to Ball
  m_pdrive->ForwardInInch(distanceToBall, forwardSpeed);

  //4. Load Ball 1 to Photo
  m_ploader->LoadToPhoto(innerSpeed);

  //5. Turn Around 180 Towards Target
  m_pdrive->TurnAngleRelative(turnAngle, turnSpeed, turnDeadZone);

  //6. Allign Robot to Target to Prepare for Shooting
  m_pdrive->VisionAllign(turnSpeed, turnDeadZone);

  //7. Shoot Ball 1 Towards Target
  m_pshooter->SetShooterSpeed(shooterSpeed);

  //8. Load Ball 2 to Photo
  m_ploader->LoadToPhoto(innerSpeed);

  //9. Allign Robot to Target to Prepare for Shooting
  m_pdrive->VisionAllign(turnSpeed, turnDeadZone);

  //10. Shoot Ball 2 Towards Target
  m_pshooter->SetShooterSpeed(shooterSpeed);

  m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void Pos1AutoCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool Pos1AutoCommand::IsFinished() {
  return m_IsFinished;
}
