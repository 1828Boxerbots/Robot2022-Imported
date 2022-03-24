// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ClimbCommand.h"
#include "cmath"

// The distance is inches.
ClimbCommand::ClimbCommand(ClimbSubsystem *pClimb, double speed, double distance) 
{
  m_pClimb = pClimb;
  m_speed = speed;
  m_distance = distance;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pClimb);
}

// Called when the command is initially scheduled.
void ClimbCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbCommand::Execute() 
{
  //Variables:
  double downDistance = 1.0;
  double upDistance = 1.0;
  double climbSpeed = 0.2;

  //Steps:
  m_pClimb->ClimbUpInInch(upDistance, climbSpeed);

 m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void ClimbCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimbCommand::IsFinished() 
{
  return m_IsFinished;
}
