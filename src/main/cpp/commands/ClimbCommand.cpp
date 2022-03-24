// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ClimbCommand.h"
#include "cmath"
#include "Util.h"

// The distance is inches.
ClimbCommand::ClimbCommand(ClimbSubsystem *pClimb) 
{
  m_pClimb = pClimb;
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
  double secondsDelay = 2.0;

  //Steps:
  m_pClimb->ClimbUpInInch(upDistance, climbSpeed);
  Util::DelayInSeconds((units::time::second_t)secondsDelay);
  m_pClimb->ClimbDownInInch(downDistance, climbSpeed);


 m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void ClimbCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimbCommand::IsFinished() 
{
  return m_IsFinished;
}
