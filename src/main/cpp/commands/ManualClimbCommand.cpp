// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/ManualClimbCommand.h"

ManualClimbCommand::ManualClimbCommand(ClimbSubsystem *pClimbSub, frc::XboxController *pXbox, double speed) 
{
  m_pClimbSub = pClimbSub;

  m_pXbox = pXbox;

  m_speed = speed;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(pClimbSub);
}

// Called when the command is initially scheduled.
void ManualClimbCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ManualClimbCommand::Execute() 
{

  m_pClimbSub->GetDistance();
  
  if(m_pXbox->GetLeftBumper())
  {
    //Climb arms are moving down.
    m_pClimbSub->SetRatchet(true);
    //Util::DelayInSeconds(0.3_s);
    m_pClimbSub->ClimbMotor(fabsf(m_speed));
  }
  else
  {
    // Climb arms are moving up.
    m_pClimbSub->SetRatchet(false);
    Util::DelayInSeconds(0.3_s);
    m_pClimbSub->ClimbMotor(-fabsf(m_speed));
  }

  //int pov = m_pXbox->GetPOV();

  // switch(pov)
  // {
      
  //   case 0:
  //     // Pressing the D-Pad Right.
  //     // Climb arms are moving up.
  //     m_pClimbSub->SetRatchet(false);
  //     Util::DelayInSeconds(0.3_s);
  //     m_pClimbSub->ClimbMotor(-fabsf(m_speed));
  //     break;

  //   case 180:
  //     // Pressing the D-Pad Left.
  //     // Climb arms are moving down.
  //     m_pClimbSub->SetRatchet(true);
  //     //Util::DelayInSeconds(0.3_s);
  //     m_pClimbSub->ClimbMotor(fabsf(m_speed));
  //     break;
    
  //   default:
  //     //Stop Climb Motor.
  //     m_pClimbSub->ClimbMotor(0.0);
  //     m_pClimbSub->SetRatchet(true);
  // }
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void ManualClimbCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool ManualClimbCommand::IsFinished() 
{
  return m_isFinished;
}
