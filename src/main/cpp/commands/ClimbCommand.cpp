// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ClimbCommand.h"
#include "cmath"
#include "Util.h"

// The distance is inches.
ClimbCommand::ClimbCommand(ClimbSubsystem *pClimb,double distance, double speed) 
{
  m_pClimb = pClimb;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(m_pClimb);
  m_dist = distance;
  m_speed = speed;
}

// Called when the command is initially scheduled.
void ClimbCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ClimbCommand::Execute() 
{
 double current = m_pClimb->GetDistance();

 if(m_dist < current)
 {
   m_pClimb->ClimbDownInInch(m_dist, m_speed);
 }
 else
 {
   m_pClimb->SetRatchet(false);
   m_pClimb->ClimbUpInInch(m_dist, m_speed);
   m_pClimb->SetRatchet(true);
 }

 m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void ClimbCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimbCommand::IsFinished() 
{
  return m_IsFinished;
}
