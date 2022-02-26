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
  double CurrentClimbDistance = 0;
  m_pClimb->ClimbMotor(0.0);
  double StartingClimbPosition = m_pClimb->GetDistance();

  frc::SmartDashboard::PutNumber("ClimbCommand-ClimbStart", StartingClimbPosition);
  frc::SmartDashboard::PutNumber("ClimbCommand-ClimbSpeed", m_speed);

 if (m_speed > 0)
 {
  while(CurrentClimbDistance < fabsf(m_distance))
    {
      m_pClimb->ClimbMotor(-fabsf(m_speed));
      double CurrentClimbPosition = m_pClimb->GetDistance();


      frc::SmartDashboard::PutNumber("ClimbCommand-CurrentClimbDistance", CurrentClimbDistance);
      frc::SmartDashboard::PutNumber("ClimbCommand-CurrentClimbPosition+", CurrentClimbPosition);
      
       CurrentClimbDistance = CurrentClimbPosition - StartingClimbPosition;
      } 
 }
 else if (m_speed < 0)
 {
  while(CurrentClimbDistance < -fabsf(m_distance))
    {
      m_pClimb->ClimbMotor(fabsf(m_speed));
      double CurrentClimbPosition = m_pClimb->GetDistance();

      frc::SmartDashboard::PutNumber("ClimbCommand-CurrentClimbDistance", CurrentClimbDistance);
      frc::SmartDashboard::PutNumber("ClimbCommand-CurrentClimbPosition-", CurrentClimbPosition);     

      CurrentClimbDistance = CurrentClimbPosition - StartingClimbPosition;
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
