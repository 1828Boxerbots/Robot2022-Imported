// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ClimbCommand.h"
#include "cmath"

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
  double StartingClimbPosition = m_pClimb->GetDistance();
  double CurrentClimbDistance;
  m_pClimb->ResetEncoder();
  m_pClimb->ClimbMotor(0.0);
 
 if (m_speed > 0)
 {
  while(CurrentClimbDistance < m_distance)
    {
      m_pClimb->ClimbMotor(fabsf(m_speed));

      frc::SmartDashboard::PutNumber("ClimbCommand-CurrentClimbDistance", CurrentClimbDistance);
      
      double CurrentClimbPosition = m_pClimb->GetDistance();

       CurrentClimbDistance = CurrentClimbPosition - StartingClimbPosition;
      } 
 }
 else if (m_speed < 0)
 {
  while(CurrentClimbDistance > m_distance)
    {
      m_pClimb->ClimbMotor(-fabsf(m_speed));

      frc::SmartDashboard::PutNumber("ClimbCommand-CurrentClimbDistance", CurrentClimbDistance);
      
      double CurrentClimbPosition = m_pClimb->GetDistance();
     

      CurrentClimbDistance = fabsf(CurrentClimbPosition) - StartingClimbPosition;
      } 
 }
 
 m_pClimb->ClimbMotor(0.0);

 m_IsFinished = true;
}

// Called once the command ends or is interrupted.
void ClimbCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ClimbCommand::IsFinished() 
{
  return m_IsFinished;
}
