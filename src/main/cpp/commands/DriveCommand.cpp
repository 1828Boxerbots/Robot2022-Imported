// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/DriveCommand.h"

DriveCommand::DriveCommand(DriveTrainSubsystem* pDriveTrain, frc::XboxController* pController, DriveTrainSubsystem::DriveStyles style)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDriveTrain = pDriveTrain;
  m_pController = pController;

  m_style = style;

  AddRequirements(pDriveTrain);
}

// Called when the command is initially scheduled.
void DriveCommand::Initialize() 
{
  m_pDriveTrain->SetDrive(m_style);
}

// Called repeatedly when this Command is scheduled to run
void DriveCommand::Execute()
{
  switch (m_pDriveTrain->GetDrive())
  {
    //Tank Drive
    case DriveTrainSubsystem::TANK_STYLE:
      m_left = -m_pController->GetLeftY();
      m_right = -m_pController->GetRightY();
      CheckDeadZone(m_left);
      CheckDeadZone(m_right);
      m_pDriveTrain->MoveTank(m_left * m_scale, m_right * m_scale);
      break;

    //Arcade Drive
    case DriveTrainSubsystem::ARCADE_STYLE:
      m_left = m_pController->GetLeftY();
      m_right = -m_pController->GetLeftX();
      CheckDeadZone(m_left);
      CheckDeadZone(m_right);
      m_pDriveTrain->MoveArcade(m_right * m_scale, m_left * m_scale);
      break;

    //RC Drive
    case DriveTrainSubsystem::RC_STYLE:
      m_left = -m_pController->GetLeftY();
      m_right = m_pController->GetRightX();
      CheckDeadZone(m_left);
      CheckDeadZone(m_right);
      m_pDriveTrain->MoveArcade(m_right * m_scale, m_left * m_scale);
      break;

    //Uh oh forgot to SetDrive()
    default:
      m_pDriveTrain->SetDrive(DriveTrainSubsystem::RC_STYLE);
      break;
  }
}

double DriveCommand::CheckDeadZone(double stickInput)
{
  if(stickInput > -m_deadZoneRange && stickInput < m_deadZoneRange)
  {
    return 0.0;
  }

  return stickInput;
}

// Called once the command ends or is interrupted.
void DriveCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool DriveCommand::IsFinished() {
  return false;
}
